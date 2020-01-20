#!/usr/bin/env python
#-----------------------------------------------------------
import os, re
import sys, os, re, optparse, urllib, subprocess
from time import ctime
#-----------------------------------------------------------
print(sys.version)
VERSION = "v1.0.0"
USAGE ='''
    Usage:
       adlcompare.py -s "select-string" ADL-file-names
    '''
def decodeCommandLine():

    parser = optparse.OptionParser(usage=USAGE,
                                       version=VERSION)
            
    parser.add_option("-s", "--select",
                      action="store",
                      dest="select",
                      type="string",
                      default="",
                      help="selection string")

    options, args = parser.parse_args()
    if len(args) == 0:
        sys.exit(USAGE)

    if options.select == '':
        sys.exit(USAGE)

    return (args, options)

def nameonly(s):
    import posixpath
    return posixpath.splitext(posixpath.split(s)[1])[0]

def boohoo(message):
    sys.exit('\n** adlcompare.py ERROR *** %s\n' % message)
#-----------------------------------------------------------
# some regular expressions
#-----------------------------------------------------------
symbol  = re.compile(r'==|>=|<=|>|<')
swords  = re.compile('[|]?[a-zA-Z][\w]*[|]?')
lparens = re.compile('[(]')
rparens = re.compile('[)]')

def build_regex(options):
    cmd = r'select.*'
    for t in options.select.split():
        cmd += r'.*?%s' % t
    cmd += '.*'

    # take care of parentheses
    cmd = lparens.sub('[(]', cmd)
    cmd = rparens.sub('[)]', cmd)
    
    #print('\n%s' % cmd)
    search  = re.compile(cmd)
    return search
#-----------------------------------------------------------
def readADL(filename):
    blocktype = ''
    blockname = ''    
    selectmap = {}
    rec = ''
    records= open(filename).readlines()
    for record in records:
        t = record.split('#')
        if len(t) > 0:
            t = t[0].strip()
            if t == '': continue
            record = t

        t = record.split()
        token = t[0]
        if token == 'object':
            blocktype = token
            blockname = t[1]
        elif token == 'region':
            blocktype = token
            blockname = t[1]
        elif token in ['select', 'reject']:
            record = ' '.join(t) + '\t@ %s %s\n' % \
              (blocktype, blockname)
        rec += record  
    return rec
#-----------------------------------------------------------
def main():
    filenames, options = decodeCommandLine()

    # read each file as one continuous string
    records = [readADL(x) for x in filenames]

    search  = build_regex(options)
    
    for r, f in zip(records, filenames):
        recs = search.findall(r)
        if len(recs) == 0: continue

        # found a match
        name = nameonly(f)
        print('\n%s' % name)
        for rec in recs:
            print('  %s' % rec)
#-----------------------------------------------------------
try:
    main()
except KeyboardInterrupt:
    print
    print("ciao!")
    
