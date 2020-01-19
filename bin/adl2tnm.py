#!/usr/bin/env python
#--------------------------------------------------------------------------------
# Description: Prototype transpiler of a ADL description to a TNM analyzer
# Created: 12-Dec-2017 Harrison B. Prosper & Sezen Sekmen
#          12-May-2018 HBP assume case insensitivity, remove dependence on loop
#                      keyword, better handling of mapping from vector<TEParticle
#                      to vector<TLorentzVector>
#          14-May-2018 HBP add count histogram for each cut block
#          16-May-2018 HBP completely decouple lhada analyzer from tnm
#          18-May-2018 HBP fix bug process_functions
#          14-Oct-2018 HBP use LHADA2TNM_PATH/external/include to find includes
#          20-Mar-2019 HBP fix implicit loop bug and make implicit loops more
#                      robust
#          28-Apr-2019 HBP adapt to recent changes to adl. Also, build
#                      adapter automatically from variables.txt
#          04-May-2019 HBP bug fixes and testing on razorboost.adl, change
#                      TEParticle to TNMObject
#          21-Jun-2019 HBP write region summaries in the same order as regions
#                      are list in ADL file.
#          17-Jan-2020 HBP 1. make compatible with Python 3
#                          2. handle weight statement
#                          3. write out selected regions to a TTree
#          19-Jan-2020 HBP more fixes for Python 3
#--------------------------------------------------------------------------------
import sys, os, re, optparse, urllib, subprocess
from time import ctime
#--------------------------------------------------------------------------------
print(sys.version)
VERSION = 'v2.1.0'
DEBUG  = 0

# ADL block types
BLOCKTYPES = ['info', 'function', 'object', 'define', 'region']

# ADL keywords
KEYWORDS   = ['experiment',
              'id',
              'publication',
              'sqrtS',
              'lumi',
              'arXiv',
              'hepdata',
              'doi',
              'arg',
              'code',
              'take',
              'set',
              'weight',
              'select',
              'reject']

MATHFUN = ['sqrt', 'or',  'and', 'size',
           'abs',  'exp', 'log', 'sum', 
           'sin',  'cos', 'tan', 'mass',
           'pow',  'min', 'max'
           'sinh', 'cosh','tanh']
TOKENS  = set(BLOCKTYPES+KEYWORDS)

SPACE6  = ' '*6

# some simple regular expression to dissect ADL file
KWORDS   = r'\b(%s)\b' % '|'.join(KEYWORDS)
exclude  = re.compile(KWORDS)
getwords = re.compile('lha[.][a-zA-Z0-9]+|[a-zA-Z][a-zA-Z0-9_]*')
getvars  = re.compile('@?[a-zA-Z][a-zA-Z0-9_.;:@#\$]*@?')
getdvars = re.compile('[a-zA-Z]+[a-zA-Z0-9;:@#\$]*[.]')
swords   = re.compile('[a-zA-Z][\w]*')
swords_extended  = re.compile('[|]?[a-zA-Z][\w]*[|]?')

cppAND   = re.compile(r'\band|AND\b')
cppOR    = re.compile(r'\bor|OR\b')
cppEQEQ  = re.compile('(?<!=|[>]|[<])=')
scrubdot = re.compile('[a-zA-Z]+[.]')
a = '^\s*(double\s+\w+?[(].*?[^)]?[)]|'\
  'float\s+\w+?[(].*?[^)]?[)]|'\
  'std::vector[<]TLorentzVector[>]\s+\w+?[(].*?[^)]?[)])'
getfunctions = re.compile(a, re.M)
takefunction = re.compile('[\w+_]+?\s*[(]')
tlorentz_vector = re.compile('vector\s*[<]\s*TLorentzVector\s*[>]')
nip      = re.compile('[_](?=[a-zA-Z])|(?<=[a-zA-Z0-9])[_](?= )')

boolean  = re.compile(r'\band|AND|or|OR\b')
#--------------------------------------------------------------------------------
NAMES = {'name': 'analyzer',
         'treename': 'Delphes',
         'info': '//',
         'time': ctime(),
         'aoddef': '',
         'aodimpl': '',
         'percent': '%',
         'Adapter': 'Adapter',
         'adapter': 'adapter',
         'analyzer':'analyzer',
         'version': VERSION
        }
#--------------------------------------------------------------------------------
# some objects are singletons, that is, there is only one instance of the
# object per event. find out which objects are singletons from the
# variables.txt file
OBJECTS = {}
SINGLETONS = set()
NONSINGLETONS = set()
SYMBOLS = set()

IOBJECTS = {}
ISYMBOLS = set()
#--------------------------------------------------------------------------------

TEMPLATE_ADAPTER_CC = \
'''//------------------------------------------------------------------
// File: %(adaptername)s.cc
// Description: map input objects to TNMObjects
// Created:     %(time)s by adl2tnm.py %(version)s
//------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <stdlib.h>
#include "TString.h"
#include "%(adaptername)s.h"

using namespace std;

%(adaptername)s::%(adaptername)s()
{
}

%(adaptername)s::~%(adaptername)s()
{
}

void %(adaptername)s::operator()(eventBuffer& ev, 
%(tab)sstd::string name, std::vector<TNMObject>& p)
{
  p.clear();
%(vbody)s
}

void %(adaptername)s::operator()(eventBuffer& ev, 
%(tab)sstd::string name, TNMObject& p)
{
%(sbody)s
}
'''

TEMPLATE_ADAPTER_H = \
'''#ifndef %(adaptername)s_H
#define %(adaptername)s_H
//------------------------------------------------------------------
// File: %(adaptername)s.h
// Description: map input objects to TNMObjects
// Created:     %(time)s by adl2tnm.py %(version)s
//------------------------------------------------------------------
#include <vector>
#include <string>
#include "tnm.h"
#include "TNMObject.h"

struct %(adaptername)s
{
  %(adaptername)s();
  ~%(adaptername)s();
  void operator()(eventBuffer& ev, std::string a, std::vector<TNMObject>& p);
  void operator()(eventBuffer& ev, std::string a, TNMObject& p);
};
#endif
'''


# C++ ADL analyzer template
TEMPLATE_CC =\
'''//------------------------------------------------------------------
// File:        %(name)s_s.cc
// Description: Analyzer for ADL-based analysis:
%(info)s
// Created:     %(time)s by adl2tnm.py %(version)s
//------------------------------------------------------------------
#include <algorithm>
#include "%(name)s_s.h"
%(includes)s
%(namespaces)s
using namespace std;
//------------------------------------------------------------------
// The following functions, objects, and variables are globally visible
// within this programming unit.
//------------------------------------------------------------------
double sum(vector<TNMObject>& o, string attribute)
{ 
  double x=0;
  for(size_t c=0; c < o.size(); c++) x += o[c](attribute);
  return x;
}

inline
double mass(TNMObject o) { return o("mass"); }

inline
size_t size(vector<TNMObject>& o) { return o.size(); }

%(fundef)s
//------------------------------------------------------------------
%(objdef)s
//------------------------------------------------------------------
%(vardef)s
//------------------------------------------------------------------
%(regdef)s
//------------------------------------------------------------------
%(name)s_s::%(name)s_s(TFile* _file)
  : file(_file),
    tree(0)
{
%(vdefines)s
%(vobjects)s
%(vcuts)s
  // 1 if a region is selected, 0 otherwise
  passed.clear();
  passed.resize(regions.size(), 0);

  // accumulate number of times each region is selected
  total.clear();
  total.resize(regions.size(), 0);

  // order of regions in ADL file
  order.clear();
%(order)s
  if ( file )
    {
      file->cd();
      tree = new TTree("regions", "selected regions");
      for(size_t c=0; c < regions.size(); c++)
	    {
	      int j = order[c];
	      std::string name(regions[j]->name());
	      tree->Branch(name.c_str(), &passed[j], string(name+string("/F")).c_str());
	    }
    } 
}

%(name)s_s::~%(name)s_s() {}

%(runargsimpl)s
{
  // copy to internal buffers
%(copyargsimpl)s
  // reset all objects
  for(size_t c=0; c < defines.size(); c++) defines[c]->reset();
  for(size_t c=0; c < objects.size(); c++) objects[c]->reset();
  for(size_t c=0; c < regions.size(); c++) regions[c]->reset();

  // apply selection criteria
  for(size_t c=0; c < objects.size(); c++) objects[c]->select();

  // apply selection criteria
  for(size_t c=0; c < regions.size(); c++)
    {
      passed[c] = regions[c]->select() ? regions[c]->weight : 0;
      total[c] += passed[c];
    }

    if ( file )
    {
      file->cd();
      tree->Fill();
    }
}

void %(name)s_s::summary(ostream& os)
{
  os << std::endl << "Summary" << std::endl << std::endl;
  for(size_t c=0; c < order.size(); c++)
    {
      size_t j = order[c];
      regions[j]->summary(os);
      regions[j]->write(file);
      //os << regions[j]->name() << "\ttotal: " << total[j] << endl << endl;
    }

  if ( file )
    {
      file->cd();
      tree->Write();
    }
}
'''

# C++ ADL analyzer header template
TEMPLATE_HH =\
'''#ifndef %(name)s_s_HH
#define %(name)s_s_HH
//------------------------------------------------------------------
// File:        %(name)s_s.h
// Description: Analyzer for ADL-based analysis:
%(info)s
// Created:     %(time)s by adl2tnm.py %(version)s
//------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TNMObject.h"
//------------------------------------------------------------------
struct TNMThing
{
  TNMThing() {}
  virtual ~TNMThing() {}
  virtual std::string name() { return std::string(""); }
  virtual void reset() {}
  virtual bool select() { return true; }
  virtual void write(TFile* fout) {}
  virtual void summary(std::ostream& os) {}

  float weight;
};
    
struct %(name)s_s
{
  std::vector<TNMThing*> defines;
  std::vector<TNMThing*> objects;
  std::vector<TNMThing*> regions;

  TFile* file;
  TTree* tree;
  std::vector<float> passed;
  std::vector<float> total;
  std::vector<int>   order;
  
  %(name)s_s(TFile* _file);
  ~%(name)s_s();
  void run(%(runargs)s);
  void summary(std::ostream& os);
};

#endif
'''

# C++ TNM analyzer template
TNM_TEMPLATE_CC =\
'''//------------------------------------------------------------------
// File:        %(name)s.cc
// Description: Analyzer for ADL analysis:
%(info)s
// Created:     %(time)s by adl2tnm.py %(version)s
//------------------------------------------------------------------
#include "tnm.h"
#include "%(adaptername)s.h"
#include "%(name)s_s.h"

using namespace std;
//------------------------------------------------------------------
int main(int argc, char** argv)
{
  // If you want canvases to be visible during program execution, just
  // uncomment the line below
  //TApplication app("%(name)s", &argc, argv);

  // Get command line arguments
  commandLine cl(argc, argv);
    
  // Get names of ntuple files to be processed
  vector<string> filenames = fileNames(cl.filelist);

  // Create tree reader
  itreestream stream(filenames, "%(treename)s");
  if ( !stream.good() ) error("can't read root input files");

  // Create a buffer to receive events from the stream
  // The default is to select all branches
  // Use second argument to select specific branches
  // Example:
  //   varlist = "Jet_PT Jet_Eta Jet_Phi"
  //   ev = eventBuffer(stream, varlist)
  // If you write varlist = "Jet" then all branches starting with 
  //   Jet will be selected.

  eventBuffer ev(stream, "%(varlist)s");
  int nevents = ev.size();
  cout << "number of events: " << nevents << endl;

  // Create output file for histograms; see notes in header 
  outputFile of(cl.outputfilename);
  //------------------------------------------------------------------
  // Define histograms
  //------------------------------------------------------------------
  //setStyle();

  //------------------------------------------------------------------
  // Create an event adapter to map input types to a standard internal 
  // type and create the analyzer
  //------------------------------------------------------------------
  %(adaptername)s %(adapter)s;

  %(name)s_s %(analyzer)s(of.file);
  //------------------------------------------------------------------
  // Loop over events
  //------------------------------------------------------------------
  for(int entry=0; entry < nevents; entry++)
    {
      // read an event into event buffer
      ev.read(entry);
      //if ( entry %(percent)s 1000 == 0 ) cout << entry << endl;
%(extobjimpl)s
%(runimpl)s
    }

  // summarize analysis
  %(analyzer)s.summary(cout);

  ev.close();
  of.close();
  return 0;
}
'''

DEF_TEMPLATE_CC = '''
struct %(defname)s_s : public TNMThing
{
  %(defname)s_s() : TNMThing(), done(false) {}
  ~%(defname)s_s() {}
  void reset() { done = false; }
  operator %(deftype)s()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
%(deftrig)s
        value = %(defstatement)s;
        return value;
      }
  }
  bool done;
  %(deftype)s value;
} %(defname)s;
'''
#--------------------------------------------------------------------------------
USAGE ='''
    Usage:
       adl2tnm.py [options] ADL-file-name

    Options:
    -a name of analyzer to be created [analyzer]
    -e name of event adapter          [create one from variables.txt]
    -t name of ROOT tree              [use first tree in ROOT file]
    '''
def decodeCommandLine():

    parser = optparse.OptionParser(usage=USAGE, version=VERSION)
            
    parser.add_option("-a", "--analyzer",
                      action="store",
                      dest="name",
                      type="string",
                      default=NAMES['analyzer'],
                      help="name of analyzer to be created")

    parser.add_option("-e", "--eventadapter",
                      action="store",
                      dest="adaptername",
                      type="string",
                      default='',
                      help="name of event adapter")

    parser.add_option("-t", "--tree",
                      action="store",
                      dest="treename",
                      type="string",
                      default='',
                      help="name of ROOT tree to read")

    options, args = parser.parse_args()
    if len(args) == 0:
        sys.exit(USAGE)
            
    filename = args[0]
    print('''
    analyzer:        %(name)s
    event adapter:   %(adaptername)s
    ROOT tree:       %(treename)s
    ADL filename:    %(filename)s
''' % {'name': options.name,
           'adaptername': options.adaptername,
           'treename': options.treename,
           'filename': filename})

    return (filename, options)

def nameonly(s):
    return posixpath.splitext(posixpath.split(s)[1])[0]

def join(left, a, right):
    s = ""
    for x in a:
        s = s + "%s%s%s" % (left, x, right)
    return s

# split a record into words, but exclude ADL keywords
def getWords(records):
    words = []
    for record in records:
        words += str.split(record)
    # exclude ADL keywords
    record = ' '.join(words)
    words  = str.split(exclude.sub('', record))
    return words

def boohoo(message):
    sys.exit('\n** adl2tnm.py ERROR *** %s\n' % message)

#------------------------------------------------------------------------------
# fill various caches
#------------------------------------------------------------------------------
def fill_EXTERNALS(filename='../variables.txt'):
    if not os.path.exists(filename):
        boohoo('''
    file %s not found
        ''' % filename)
        
    records = [str.strip(x) for x in
                   open(filename).readlines()]

    # skip header
    jj = 0
    for ii, record in enumerate(records):
        if record == '':
            jj = ii + 1
            break
    
    # loop over records
    records = records[jj:]
    for ii, record in enumerate(records):    
        t = str.split(record)
        vtype = t[0]
        vname = t[2]
        count = int(t[3])
        # determine whether or not current object is a singleton.
        # a singleton does not have a counter variable 
        a_singleton = len(t) < 5

        # A Delphes Hack!
        a_singleton = a_singleton or vname[:8] in ['MissingE', 'ScalarHT']
                  
        k = str.find(vname, '_')
        if a_singleton:
            if k < 0:
                oname = 'Event'
                fname = vname
            else:
                oname = vname[:k]
                fname = vname[k+1:]
                
            if not oname in NONSINGLETONS:
                SINGLETONS.add(oname)
        else:
            if k < 0:
                oname = vname
                fname = ''
            else:
                oname = vname[:k]
                fname = vname[k+1:]
            NONSINGLETONS.add(oname)
            
        #print(vtype, oname, fname)
        
        if not (oname in OBJECTS):
            OBJECTS[oname] = {}
        OBJECTS[oname][fname] = vtype
        SYMBOLS.add(oname)
        SYMBOLS.add(fname)

    if DEBUG > 0:
        onames = OBJECTS.keys()
        onames.sort()
        for oname in onames:
            if oname in SINGLETONS:
                which = ' <= singleton'
            else:
                which = ''
            print('\nobject( %s )%s' % (oname, which))
            fields = OBJECTS[oname].keys()
            fields.sort()
            for field in fields:
                print('  field( %s \t%s )' % \
                          (OBJECTS[oname][field], field))
#------------------------------------------------------------------------------
# build body of Adapter from variables.txt
#------------------------------------------------------------------------------
def buildAdapterBody(names, partial=False, filename='../variables.txt'):
    if not os.path.exists(filename):
        boohoo('''
    file %s not found
        ''' % filename)
        
    records = [str.strip(x) for x in
                   open(filename).readlines()]

    # skip header
    jj = 0
    for ii, record in enumerate(records):
        if record == '':
            jj = ii + 1
            break
    
    # loop over records
    records = records[jj:]
    OBJ   = {}
    for ii, record in enumerate(records):
        t = str.split(record)
        vtype = t[0]
        vname = t[2]

        ##DB
        #print("vtype( %s )\tvname( %s )" % (vtype, vname))
        
        # determine whether or not current object is a singleton.
        # a singleton does not have a counter variable
        a_singleton = len(t) < 5
        
        k = str.find(vname, '_')
        if a_singleton:
            if k < 0:
                oname = 'Event'
                fname = vname
            else:
                oname = vname[:k]
                fname = vname[k+1:]
        else:
            if k < 0:
                oname = vname
                fname = ''
            else:
                oname = vname[:k]
                fname = vname[k+1:]
        ##DB       
        #print("\toname( %s )\tfname( %s ) %s" % (oname, fname, a_singleton))
        
        if not (oname in OBJ): OBJ[oname] = {'singleton': a_singleton,
                                                 'pt':  None,
                                                 'eta': None,
                                                 'phi': None,
                                                 'mass': None,
                                                 'fields': []}
        # special handling for pt, eta, phi, mass
        lfname = fname.lower()
        if lfname in ['pt', 'eta', 'phi', 'mass']: OBJ[oname][lfname] = vname
        OBJ[oname]['fields'].append((fname, vname))


    sbody = ''
    vbody = ''
    onames= OBJ.keys()

    for oname in onames:
        
        # only build objects that appear in the internal symbol table

        if not (oname in ISYMBOLS):
            continue
        
        if DEBUG > 0:
            print('buildAdapter object ( %s )' % oname)

        ##DB
        ##print('buildAdapter object ( %s )' % oname)
        
        obj =  OBJ[oname]
        names['oname'] = oname

        ##D
        if oname in SINGLETONS:
        #if obj['singleton']:
            # ----------------------
            # SINGLETON OBJECT
            # ----------------------            
            names['tab'] = ' '*6
            for fname in ['pt', 'eta', 'phi', 'mass']:
                if obj[fname] == None:
                    names[fname] = "0"
                else:
                    names[fname] = 'ev.%s' % obj[fname]

            # Delphes hack
            if oname == 'MissingET':
                names['pt'] = 'ev.MissingET_MET'
            elif oname == 'ScalarHT':
                names['pt'] = 'ev.ScalarHT_HT'
                
            sbody += '''
  if ( name == string("%(oname)s") )
    {
      TNMObject q("%(oname)s", 
                  %(pt)s, 
                  %(eta)s,
                  %(phi)s,
                  %(mass)s);
''' % names
            for fname, vname in obj['fields']:
                names['vname'] = vname                
                if fname == '':
                    names['fname'] = vname
                else:
                    names['fname'] = fname
                # only fields that appear in internal symbol table
                if not (fname in ISYMBOLS): continue
                sbody += '%(tab)sq.Value["%(fname)s"] \t= ev.%(vname)s;\n' % names
            sbody += '''
      p = q;
      return;
    }'''
        else:
            # ----------------------
            # MULTIPLE OBJECT
            # ----------------------             
            names['tab'] = ' '*10
            for fname in ['pt', 'eta', 'phi', 'mass']:
                if obj[fname] == None:
                    names[fname] = "0"
                else:
                    names[fname] = 'ev.%s[c]' % obj[fname]
                    
            fname, vname = obj['fields'][0]
            names['vname'] = vname
            
            vbody += '''
  if ( name == string("%(oname)s") )
    {
      for (size_t c=0; c < ev.%(vname)s.size(); c++)
        {
          p.push_back(TNMObject("%(oname)s", 
                                %(pt)s, 
                                %(eta)s,
                                %(phi)s,
                                %(mass)s));
''' % names
            for fname, vname in obj['fields']:
                if str.lower(fname) in ['pt', 'eta', 'phi', 'mass']: continue
                    
                names['vname'] = vname               
                if fname == '':
                    names['fname'] = '"%s"' % vname
                    fname = vname
                else:
                    names['fname'] = '"%s"' % fname

                # Delphes hack
                if vname.find('_size') > 2: continue

                if partial:
                    # only fields that appear in internal symbol table
                    if not (fname in ISYMBOLS):
                        if aname in ISYMBOLS:
                            names['fname'] = '"|%s|"' % fname
                            vbody += '%(tab)sp.back().Value[%(fname)s] '\
                            '\t= fabs(ev.%(vname)s[c]);\n' % names
                        else:
                            continue
                    
                vbody += '%(tab)sp.back().Value[%(fname)s] '\
                    '\t= ev.%(vname)s[c];\n' % names

                # hack for charge
                if fname == 'Charge':
                    names['fname'] = '"charge"'
                    vbody += '%(tab)sp.back().Value[%(fname)s] '\
                    '\t= ev.%(vname)s[c];\n' % names
                elif fname == 'charge':
                    names['fname'] = '"Charge"'
                    vbody += '%(tab)sp.back().Value[%(fname)s] '\
                    '\t= ev.%(vname)s[c];\n' % names
                       
            vbody += '''        }
      return;
    }
'''            
    names['sbody'] = sbody
    names['vbody'] = vbody
#------------------------------------------------------------------------------
# Look for header file on given list of search paths
#------------------------------------------------------------------------------
def findHeaderFile(infile, incs):
	ifile = strip(os.popen("find %s 2>/dev/null" % infile).readline())    
	if ifile != "":
		filepath = ifile
		for includepath in incs:
			tmp = splitfields(filepath, includepath + '/',1)
			if len(tmp) == 2:
				base, ifile = tmp
			else:
				base = ''
				ifile = tmp[0]

			if base == '': return (filepath, ifile)
		return (filepath, filepath)

	ifile = infile
	for includepath in incs:
		filepath = includepath + "/" + ifile
		filepath = strip(os.popen("find %s 2>/dev/null" % filepath).readline())
		if filepath != "": return (filepath, ifile)

		filepath = includepath + "/include/" + ifile
		filepath = strip(os.popen("find %s 2>/dev/null" % filepath).readline())
		if filepath != "": return (filepath, ifile)

	return ("","")
#------------------------------------------------------------------------------
# Make a valiant attempt to analyze, and extract, calling sequence of a function
#------------------------------------------------------------------------------
funcname = re.compile('[a-zA-Z]+[\w\<:,\>]*(?=[(])')
findtemparg = re.compile('(?<=[<]).+(?=[>])')
def decodeFunction(record):
    record = str.replace(record, "\n", " ")
    fname  = funcname.findall(record)
    if len(fname) == 0:
        boohoo("can't decode %s" % record)
    fname = fname[0]
    rtype, args = str.split(record, fname)
    rtype = str.strip(rtype)
    args  = str.strip(args)[1:-1]
    
    # since template arguments can include commas, hide them before
    # splitting using commas
    targs  = findtemparg.findall(args)
    hidden = []
    for ii, t in enumerate(targs):
        orig = '<%s>' % t
        temp = '@%d' % ii
        hidden.append((orig, temp))
        args = str.replace(args, orig, temp)

    # replace commas by "#" and go back to original types
    # and split at "#"
    args = [str.strip(x) for x in str.split(args, ",")]
    args = '#'.join(args)
    for orig, temp in hidden:
        args = str.replace(args, temp, orig)

    # ok, now get types etc.
    args = [str.strip(x) for x in str.split(args, "#")]
    argtypes = []
    argnames = []
    for arg in args:
        t = str.split(arg, ' ')
        if len(t) == 1:
            argtypes.append(t[0])
            argnames.append('')
        elif len(t) > 1:
            argtypes.append(' '.join(t[:-1]))
            argnames.append(t[-1])
    return (rtype, fname, argtypes, argnames)
#-----------------------------------------------------------------------------
# Use a simple bubble-like sort to sort items according to dependency
#------------------------------------------------------------------------------
def sortObjects(objects):
    from copy import deepcopy
    # 1) get blocks with no dependencies on internal blocks
    obs = []
    names = []
    for t in objects:
        name  = t[0]
        words = t[1]
        if len(words) > 0: continue
        # this block has no internal dependencies
        obs.append(deepcopy(t))
        names.append(name)

        t[0] = None
    names = set(names)
    
    # 2) sort remaining blocks so that dependent blocks occur after the
    #    the blocks on which they depend
    for ii in range(len(objects)):
        for t in objects:
            name  = t[0]
            if name == None: continue
            words = t[1]                
            
            incomplete = len(words.intersection(names)) < len(words) 
            if incomplete: continue

            # the dependency of this block has been fully satisfied
            obs.append(deepcopy(t))
            names.add(name)
            t[0] = None
    return obs    
#--------------------------------------------------------------------------------
# Read ADL file and extract blocks into a simple internal data structure
#--------------------------------------------------------------------------------
def checkForErrors(records):
    if len(SYMBOLS) == 0: return
    blocktypes = set(BLOCKTYPES)
    keywords   = set(KEYWORDS)
    mathfun    = set(MATHFUN)
    tokens     = set(BLOCKTYPES+KEYWORDS)
    findwords  = re.compile(r'[a-zA-Z][\w_]*')

    # check symbols
    lsymbols = set(); lmap = {} # local symbols
    gsymbols = set(); gmap = {} # gloabl symbols
    for ii, (lineno, record) in enumerate(records):
        words  = findwords.findall(record)
        if len(words) < 2: continue
            
        token  = words[0]
        name   = words[1]

        if name in SYMBOLS:
            pass
        elif token in ['object', 'define', 'region']:
            if not (name in gsymbols): gmap[name] = []
            gsymbols.add(name)
            gmap[name].append((ii, lineno))

        values = set(words[1:]) - mathfun
        
        for name in values:
            if name in SYMBOLS:
                pass
            elif token in ['select', 'region', 'take', 'define']:
                if not (name in lsymbols): lmap[name] = []
                if str.lower(name) in ['pt', 'eta', 'phi', 'mass', 'charge']: continue
                lsymbols.add(name)
                lmap[name].append((ii, lineno))               

    if DEBUG > 0:
        keys = [x for x in gmap.keys()]
        keys.sort()
        print('\nobject, define, region\n')
        for name in keys:
            ii = gmap[name] 
            print(name, ii)

        keys = [x for x in lmap.keys()]
        keys.sort()
        print('\nselect, reject\n')
        for name in keys:
            ii = lmap[name] 
            print(name, ii)

    unknowns = lsymbols - gsymbols

    warnings = []
    for unknown in unknowns:
        indices = lmap[unknown]
        for ii, lineno in lmap[unknown]:
            ll, record = records[ii]
            t = str.split(record)
            if t[0] == 'take':
                # most likely an instance
                continue
            warnings.append((lineno, record, unknown))
    if len(warnings) > 0:
        print('\n** adl2tnm WARNING *** verify the following line(s)\n')
        warnings.sort()
        for ii, record, name in warnings:
            print('%5d: %s --> %s ?' % (ii, record, name))
        print
    
def extractBlocks(filename):
    if DEBUG > 0:
        print('\nBEGIN( extractBlocks )')
        
    from copy import deepcopy
    import re

    #--------------------------------------------
    # read ADL file
    #--------------------------------------------
    try:
        records = open('../%s' % filename).readlines()
    except:
        try:
            records = open(filename).readlines()
        except:
            boohoo('unable to open ADL file %s' % filename)

    #--------------------------------------------    
    # set up some simple regular expressions
    #--------------------------------------------    
    stripcomments = re.compile('[#].*')
    blocktypes = r'\b(%s)\b' % '|'.join(BLOCKTYPES)
    isblock    = re.compile(blocktypes)
    fcallname  = re.compile('[a-zA-Z_][\w_]+?\s*(?=[(])')    
   
    #-------------------------------------------- 
    # strip out comments and blank lines,
    # but note original line numbers of records
    #--------------------------------------------        
    orig_records = [x for x in records]
    records = []
    for ii, record in enumerate(orig_records):
        lineno = ii+1
        record = stripcomments.sub('', record)
        record = str.strip(record)
        if record == '': continue
        records.append((lineno, record))
    
    #--------------------------------------------    
    # loop over ADL records
    #--------------------------------------------    
    blocks      = {}
    funnames    = [] # keep track pf function names
    defnames    = [] # keep track of defines
    objectnames = [] # keep track of block names
    regnames    = [] # keep track of region names
    statement   = [] # keep track of records that comprise a statement
    
    # begin loop over records
    bname  = None
    orig_records = deepcopy(records)
    
    for ii, (lineno, record) in enumerate(records):

        # look for a block
        if isblock.findall(record) != []:
            
            # found a block; get its type and name
            t = record.split()
            if len(t) < 2:
                boohoo('problem at line\n%4d %s\n' % (lineno, record))
            # block type, block name
            btype, bname = t[:2] # could be a define
            if DEBUG > 0:
                print("\n=>Found( %s, %s )" % (btype, bname))
   
            # fall on sword if we have duplicate block names
            if bname in blocks:
                boohoo('duplicate block name %s at line'\
                           '\n%4d %s\n' % (bname, lineno, record))
                            
            blocks[bname] = {'type': btype, 'body': []}
            if   btype == 'object':
                objectnames.append(bname)
                continue
            
            elif btype == 'region':
                regnames.append(bname)
                continue
            
            elif btype == 'define':
                record = record.split('=')[-1].strip()
                defnames.append(bname)
                # NB: don't continue because this is a one liner
                
        if bname == None:
            boohoo('problem at line\n%4d %s\n' % (lineno, record))

        # statements can extend over multiple records (lines), so
        # lookahead to determine if current record is the end
        # of the current statement
        statement.append(record)

        try:
            l, next_record = records[ii+1]
            next_token = str.split(next_record)[0]
        except:
            next_token = None

        if  (next_token == None) or (next_token in TOKENS):
            # next token is a reserved token (either a blocktype
            # or a keyword), so current record is the end of the
            # current statement
            blocks[bname]['body'].append(' '.join(statement))

            if DEBUG > 0:
                print(" %s statement( %s )" % (bname, blocks[bname]['body']))

            # update internal symbol table
            ISYMBOLS.add(bname)
            wds = swords_extended.findall(blocks[bname]['body'][-1])
            tok = wds[0]
            wds = wds[1:]
            ISYMBOLS.update(set(wds))
            
            # remember to reset statement
            statement = []

    # cache original order of regions
    region_names = regnames

    # convert to sets for easier comparisons
    objectnames = set(objectnames)
    regnames    = set(regnames)
    defnames    = set(defnames)
                
    # reorganize the blocks
    blockmap = {}
    for key in blocks.keys():
        block = blocks[key]
        blocktype = block['type']
        if not (blocktype in blockmap):
            blockmap[blocktype] = []
        body  = block['body']
        words = ' '.join(getWords(body))
        words = set(getwords.findall(words))

        # if block type is object, strip away words within this
        # block that are not object names using set intersection:
        # C = A and B. the remaining words will be user-defined
        # words and will be used to sort the blocks according to
        # block-to-block dependency
        if blocktype == 'object':
            words = objectnames.intersection(words)
        elif blocktype == 'region':
            words = regnames.intersection(words)

        blockmap[blocktype].append([key, deepcopy(words), deepcopy(body)])

    # sort object blocks so that a block that depends on other blocks
    # is placed after those blocks.
    if 'object' in blockmap:
        blockmap['object'] = sortObjects(blockmap['object'])

    
    # sort region blocks so that a block that depends on other blocks
    # is placed after those blocks.
 
    if 'region' in blockmap:
        blockmap['region'] = sortObjects(blockmap['region'])

    #--------------------------------------------            
    # get list of potential functions other than
    # standard math functions
    #--------------------------------------------
    recs = []
    for btype in ['object', 'define', 'region']:
        if not (btype in blockmap): continue
        for name, words, records in blockmap[btype]:
            recs += records
    onerecord = ' '.join(recs)
    
    found_functions = fcallname.findall(onerecord)
    funnames = set(map(str.strip, found_functions)) - TOKENS
    blockmap['function'] = []
    for name in funnames:
        cmd = 'grep "\s%s\s*[(]" $ADL2TNM_PATH/downloads/*.h' % name
        res = os.popen(cmd).read()
        res = str.strip(res)
        if res == '':
            continue
            
        ISYMBOLS.add(name)
        ISYMBOLS.add('_%s' % name)
        
        t = str.split(res, ':')
        header = str.strip(t[0])

        # check for namespaces
        cmd = 'grep -E "\s*namespace\s+\w+" %s' % header
        res = os.popen(cmd).read()
        res = str.strip(res)
        body= [header]
        if res != '':
            t = res.split()
            res = ' '.join(t[:2])
            body.append(res)

        fcallseq = re.compile(r'%s\s*[(][^)]+?[)]' % name)
        fseq = fcallseq.findall(onerecord)
        if len(fseq) == 0:
            boohoo('problem decoding function %s' % name)
        i = fseq[0].find('(')
        words = fseq[0][i+1:-1].split(',')
        # NB: prefix with "_"
        blockmap['function'].append(("_%s" % name, words, body))
        # update symbol table
        SYMBOLS.add(name)
        
        if DEBUG > 0:
            print('FUNCTION( %s ) %s' % (name, header))
            print('   FCALL( %s )' % fseq)

    if DEBUG > 0:
        if len(funnames) == 0:
            print('\n\t*** NO FUNCTIONS IN ADL FILE ***\n')
            
    #--------------------------------------------
    # do some checks
    #--------------------------------------------
    checkForErrors(orig_records)
    
    # add original order of regions to blockmap
    if 'region' in blockmap:
        regmap = {}
        for ii, (regname, _, _) in enumerate(blockmap['region']):
            regmap[regname] = ii
            
        print_order = [0]*len(region_names)
        for ii, regname in enumerate(region_names):
           print_order[ii] = regmap[regname]
           
    blockmap['print_order'] = print_order
    return blockmap
#--------------------------------------------------------------------------------
def printBlocks(blocks):
    out = open('blocks.log', 'w')
    for blocktype in BLOCKTYPES:
        if not (blocktype in blocks): continue
        record = "[%s]" % blocktype
        out.write('%s\n' % record)
        record = '-'*80
        out.write('%s\n' % record)
        for name, words, body in blocks[blocktype]:
            record = "%-12s\t%s" % (name, words)
            out.write('%s\n' % record)
            for record in body:
                record = "\t%s" % record
                out.write('%s\n' % record)
            record = '-'*80
            out.write('%s\n' % record)
    out.close()
#--------------------------------------------------------------------------------
# The following functions convert ADL blocks to C++
#--------------------------------------------------------------------------------
def process_info(names, blocks):
    info = '//\n// ADL file: %(filename)s\n' % names
    info+= '// info block\n'

    if not ('info' in blocks):
        boohoo("Thou lump of foul deformity. I can't find info block!")

    name, words, body = blocks['info'][0]
    
    for record in body:
        t = str.split(record)
        record = '//\t%-12s\t%s\n' % (t[0], ' '.join(t[1:]))
        info += record
    info += '//'
    names['info'] = info
#--------------------------------------------------------------------------------
def process_functions(names, blocks, blocktypes):

    if DEBUG > 0:
        print('\nBEGIN( process_function )')
    
    if not ('function' in blocks):
        names['includes']  = ''
        names['namespaces'] = ''
        return

    # extract headers to be included
    namespaceset = set()
    includeset = set()
    headers = set()
    for name, words, records in blocks['function']:
        for record in records:
            #t = record.split()
            #token = t[0]
            #if token != 'code': continue
            #includeset.add(t[1])
            t = record.split()
            if t[0] == 'namespace':
                namespaceset.add(t[-1])
            else:
                headers.add(record)
                include = str.split(record, '/')[-1]
                includeset.add(include)
                if DEBUG > 0:
                    print("  name( %s) \tinclude( %s )" % (name, include))

    includes = ''
    for record in includeset:
        includes += '#include "%s"\n' % record
    names['includes'] = includes

    namespaces = ''
    for record in namespaceset:
        namespaces += 'using namespace %s;\n' % record
    names['namespaces'] = namespaces

    # create functions
    fundef = '//\n// functions\n'
    functions = {}
    for name, words, records in blocks['function']:
        
        # NB: remove "_" from name, which was added in extractBlocks
        name = name[1:]

        # cache original name
        origname = name
        
        # this function could be within a namespace:
        # <namespace>.[<namespace>.]<function>
        t = str.split(name, '.')
        name = t[-1] # assume function name is last field
        if len(t) > 1:
            namespace = ':: '.join(t[:-1]) + '::'
        else:
            namespace = ''
        extname = namespace + name
        # prefix internal name with an "_"
        intname = '_%s' % str.replace(extname, '::', '_')

        if DEBUG > 1:
            print("  internal, external names( %s, %s )" % (intname, extname))
            
        # get details of external function
        args = []
        for header in headers:
            if DEBUG > 1:
                print('\nHEADER( %s )' % header)
            # copy header to local include directory
            os.system('cp %s include/' % header)
            
            # find all function declarations in header
            record = open(header).read()            
            t = getfunctions.findall(record)
            for x in t:
                if DEBUG > 0:
                    print('  FOUND( %s )' % x)

                # make a valiant attempt to decode function
                rtype, namen, argtypes, argnames = decodeFunction(x)
                
                if name == namen:
                    
                    # we have a match, so create internal function
                    #if len(args) != len(argtypes):
                    #    boohoo('''argument count mismatch in function %s.
                    #expected arguments %s, but %s found in ADL file
                    #''' % (origname, v, args))

                    # note: internal functions could have arguments
                    # such as vector<TNMObject> that map to
                    # vector<TLorentzVector>. unfortunately, even though
                    # TNMObject inherits from TLorentzVector, vector<TNMObject>
                    # is not type compatible with vector<TLorentzVector>. So,
                    # we need to copy each TNMObject to a TLorentzVector.
                    # however, a singleton TNMObject is type compatible with
                    # TLorentzVector and no copying is needed.
                    copyvars=''
                    argsrec = ''
                    argscall= ''
                    for ii, arg in enumerate(argnames):
                        argc = arg
                        # check for vector<TLorenzVector>
                        if tlorentz_vector.findall(argtypes[ii]) != []:
                            argc = arg + '_'
                            copyvars+='  vector<TLorentzVector> %s;\n' % argc
                            copyvars+='  for(size_t ii=0; ii < %s.size(); ii++)'\
                              ' %s.push_back(%s[ii]);\n' % (arg, argc, arg)
                            argtypes[ii] = 'vector<TNMObject>&'
                            
                        argsrec += '%s %s, ' % (argtypes[ii], arg)
                        argscall+= '%s, ' % argc
                    if argsrec != '':
                        argsrec = argsrec[:-2]
                        argscall= argscall[:-2]
                    if tlorentz_vector.findall(rtype) != []:
                        copyvars+='\n'
                        copyvars+='  vector<TLorentzVector> t '\
                          '= %s(%s);\n' % (extname, argscall)
                        copyvars+='  vector<TNMObject> o;\n'
                        copyvars+='  for(size_t ii=0; ii < t.size(); ii++)'\
                              ' o.push_back(t[ii]);\n'
                        copyvars+='  return o;'
                        rtype = 'std::vector<TNMObject>'
                    else:
                        copyvars+='  return %s(%s);' % (extname, argscall)

                    fundef += '''inline\n%(rtype)s\t%(intname)s(%(args)s)
{
%(copyvars)s
};

''' % {'rtype': rtype,
           'intname': intname,
           'extname': extname,
           'copyvars': copyvars,
           'args': argsrec,
           'argscall': argscall}
                    # cache function info
                    functions[origname] = (rtype, intname, extname, argtypes)
                    if DEBUG > 0:
                        print('=>MATCH( %s )' % list(functions[origname]))
    names['fundef'] = fundef
    blocks['function_info'] = functions
#--------------------------------------------------------------------------------
# check whether we have at least one implicit loop in the current record.
# we have an implicit loop if the record contains a non-singleton object name
#--------------------------------------------------------------------------------
def checkForLoopables(record, blocktypes, loopables):
        
    # get words from record, including those of the form <name>.<variable>
    words   = set(getvars.findall(record))
    if DEBUG > 0:
        print(" checkForLoopables( %s )" % words)

    objectnames = set(blocktypes['object'])
    loopy = set()
    for x in words:
        t = str.split(x, '.')
        name = t[0]
        if name in SINGLETONS: continue
            
        if name in loopables:
            loopy.add(name)
        elif name in objectnames:
            loopy.add(name)
            loopables.add(name)
            
    if DEBUG > 0:
        if len(loopy) > 0:
            print("  FOUND LOOPABLES ( %s )" % loopy)
            
    return loopy
#--------------------------------------------------------------------------------
# handle cutvectors depending on whether we have a select or a reject
#--------------------------------------------------------------------------------
inside  = re.compile('[\w_\/\-\+\*\(\)\.\[\]|]+\s*'\
                         '\[\]\s*-?[0-9]*[.]?[0-9]*\s-?[0-9]*[.]?[0-9]*')
                         
outside = re.compile('[\w_\/\-\+\*\(\)\.\[\]|]+\s*'\
                         '\]\[\s*-?[0-9]*[.]?[0-9]*\s-?[0-9]*[.]?[0-9]*')

def fixrecord(record, loopables):
    # look for statements of the form
    #    s [] lo up => ((s >= lo) and (s <= up)) 
    # or
    #    s ][ lo up => ((s <= lo) or (s >= up))
    #

    insides  = inside.findall(record)
    outsides = outside.findall(record)
    
    for rec in insides:
        q = rec.split('[]')
        with_left_paren  = False
        with_right_paren = False
        if len(q) > 1:
            s, b = map(str.strip, q)
            # check for possible enclosing parentheses
            if s[0]  == '(':
                s = s[1:]
                with_left_paren  = True

            if b[-1] == ')':
                b = b[:-1]
                with_right_paren = True

            c = b.split()
            if len(c) != 2:
                boohoo("** can't decode line\n%s" % record)
            lo, up = c
            newrec = '(%s >= %s) and (%s <= %s)' % (s, lo, s, up)

            if with_left_paren:
                newrec = '( %s' % newrec
            if with_right_paren:
                newrec = '%s )' % newrec

            t = record.split(rec)
            record = t[0] + newrec + t[1]
                
    for rec in outsides:
        q = rec.split('][')
        with_left_paren  = False
        with_right_paren = False

        if len(q) > 1:
            s, b = map(str.strip, q)                
            # check for possible enclosing parentheses
            if s[0]  == '(':
                s = s[1:]
                with_left_paren  = True

            if b[-1] == ')':
                b = b[:-1]
                with_right_paren = True

            c = b.split()
            if len(c) != 2:
                boohoo("** can't decode line\n%s" % record)
            lo, up = c
            newrec = '(%s <= %s) or (%s >= %s)' % (s, lo, s, up)

            if with_left_paren:
                newrec = '( %s' % newrec
            if with_right_paren:
                newrec = '%s )' % newrec

            t = record.split(rec)
            record = t[0] + newrec + t[1]
        
    # start with some simple replacements
    record = str.replace(record, "|", "@")
    record = str.replace(record, "[", "#")
    record = str.replace(record, "]", "$")
    
    # replace AND and OR with c++ syntax for the same
    record = cppAND.sub('&&\n\t\t', record)
    record = cppOR.sub('||\n\t\t', record)
    # use a set to avoid recursive edits
    words  = set(getvars.findall(record))

    # fix loopables in current record
    onames = set()
    for ii, name in enumerate(words):
        t = str.split(name, '.')
        a_loopable = t[0] in loopables
        if a_loopable:
            onames.add(t[0])
            
    for oname in onames:
        # change only if attribute is not .size
        edit = re.compile(r'\b%s\b(?![.]size)' % oname)
        newfield = r'%s[n]' % oname
        record = edit.sub(newfield, record)

    return (record, words)
#--------------------------------------------------------------------------------
# convert given ADL record into the corresponding C++ code snippet
# record:     current ADL record
# btype:      current ADL block type or apply
# blocktypes: block types and associated names
#--------------------------------------------------------------------------------
def convert2cpp(record, blocktypes,
                    cutvector=set(),
                    loopables=set(),
                    localvars=set(),
                    blocktype=None):
    # we want
    #    b     -> p("b")     if b is not preceded by "a."
    #    a.b   -> a("pt")    if b is preceded by "a."
    #    a     -> a[n]       if a is a loopable
    #    a     -> a          if a local variable or a singleton
    #    a.b   -> a[n]("b")  if a is a dotted loopable
    #    a[m].b-> a[m]("b")  
    #    size(a) -> a.size()
    #    
    # however, if a variable is a local variable, e.g., assigned
    # within an implied loop, it should be used as is.

    #DEBUG = 1 if record.find("muons[") > -1 else 0 
    if DEBUG > 0:
        print('    ORIGINAL_RECORD( %s )' % record)
        
    record, words = fixrecord(record, loopables)

    # handle sum(a.b)
    cmd  = re.compile('sum\s*[(].*?[)]')
    recs = cmd.findall(record)
    for rec in recs:
        wds = swords.findall(rec)
        if len(wds) == 3:
            newrec =  '%s(%s, "%s")' % tuple(wds)
            t = record.split(rec)
            record = t[0] + newrec + t[1]

    # handle size(A)
    cmd  = re.compile('size\s*[(].*?[)]')
    recs = cmd.findall(record)
    for rec in recs:
        wds = swords.findall(rec)
        if len(wds) == 2:
            newrec =  '%s.size()' % wds[1]
            t = record.split(rec)
            record = t[0] + newrec + t[1]
            
    if DEBUG > 0:
        print('     FIXED_RECORD( %s )' % record)
        print('     WORDS( %s )' % words)

    # identify attributes
    fields = set()
    for name in words:
        # split into name plus field
        t = str.split(name, '.')
        dotted = len(t) > 1
        oname  = swords.findall(t[0])[0] # strip away decorations
        fname  = '_%s' % oname  # internal function name
        field  = t[-1]          # note: could be same as oname

        # fix certain fields
        if field == 'size':
            edit     = re.compile(r'[.]size(?![(])')
            newfield = r'.size()'
            record   = edit.sub(newfield, record)
            
        # if name is that of a region, fix record accordingly
        if 'region' in blocktypes:
            if name in blocktypes['region']:
                edit = re.compile(r'(?<!region[_])\b%s\b' % name)
                newname = 'region_%s()' % name
                if DEBUG > 0:
                    print("\tregion: name( %s ) newname( %s )" % (name, newname))
                record = edit.sub(newname, record)
                
        if 'define_types' in blocktypes:
            # if name is that of a define, type cast for TNMObject
            # unless the object is being passed to functions such as
            # mass(*)
            if oname in blocktypes['define']:
                
                deftype = blocktypes['define_type'][oname]
                if deftype == 'TNMObject':
                    cmd  = re.compile('mass\s*\(\s*%s\s*\)' % oname)
                    if len(cmd.findall(record)) == 0:
                        newname = '((%s)%s)' % (deftype, oname)
                        edit = re.compile(r'\b%s\b' % oname)
                        record = edit.sub(newname, record)
                    
        # skip if singleton, loopable, local variable, etc.
        a_object    = oname in blocktypes['object']
        a_region    = oname in blocktypes['region']
        a_define    = oname in blocktypes['define']               
        a_singleton = oname in SINGLETONS
        a_loopable  = oname in loopables
        a_localvar  = oname in localvars
        a_function  = fname in blocktypes['function']
        isfunc = re.compile('%s\s*[(].*?[)]' % oname).findall(record)
        a_function  = a_function or len(isfunc) > 0
        
        skip = \
          a_object or\
          a_region or\
          a_define or\
          a_singleton or\
          a_loopable or\
          a_localvar or\
          a_function

        if dotted:
            # we have identified a dotted variable, so cache
            # field unless it is a special field such as size
            if field in ['size']:
                pass
            else:
                fields.add('.%s' % field)
        else:
            # now try to identify non-dotted attributes by a
            # process of elimination
            if skip: continue
            # none of the above, so assume this is an undotted
            # attribute of current block
            fields.add(field)

    if DEBUG > 0:
        print('      FIELDS:')
        for field in fields:
            print('       %s' % field)
            
    # now change fields
    # observe rule(s):
    # 1. define and region names should not be changed
    oldrecord = record

    for field in fields:
        if field in blocktypes['define']:
            continue
        if field in blocktypes['region']:
            continue

        newfield = field
        dotted   = field[0] == '.'
        if dotted:
            # DOTTED FIELD
            field = field[1:]
            edit  = re.compile(r'[.]%s' % field)
            newfield = '("%s")' % field
            record = edit.sub(newfield, record)
        else:
            # NOT A DOTTED FIELD
            edit = re.compile('(?<!([.]|["]))%s' % field)
            newfield = 'p("%s")' % field
            record = edit.sub(newfield, record)

    if DEBUG > 0:
        print("OLD_RECORD( %s )" % str.strip(oldrecord))                    
        print("NEW_RECORD( %s )" % str.strip(record))                    

    # now go back to original symbols |, [, and ]    
    record = str.replace(record, '@', '|')
    record = str.replace(record, '#', '[')
    record = str.replace(record, '$', ']')

    if DEBUG > 0:
        print('-'*80)
        print("CLEAN_RECORD( %s )" % record)
        print('-'*80)
    return record

def change_to_internal_name(statement, blocks):
    if not ('function_info' in blocks): return statement

    functions = blocks['function_info']
    words = swords.findall(statement)
    for word in words:
        if not (word in functions): continue
        rtype, intname, extname, argtypes = functions[word]
        cmd = re.compile(r'\b%s\b' % extname)
        statement = cmd.sub(intname, statement)
    return statement

def process_object_body(name, records, TAB, blocks, blocktypes):
    
    def decode_and_look_ahead(index, records):
        record= records[index]
        t     = str.split(record)
        token = t[0]
        value = ' '.join(t[1:])
        if index < len(records) - 1:
            t = str.split(records[index+1])
            next_token = t[0]
        else:
            next_token = None
        return (token, value, next_token)

    if DEBUG > 0:
        print('\nBEGIN( process_object_body ) OBJECT( %s )' % name)

    tab     = TAB
    tab4    = ' '*4

    # cache for names of returned vector-valued variables
    # associated with loopable objects
    cut_vector  = set() 
    take_values = [] # cache for take statements
    sort_objects= False
    loop_count  = 0  # counter for implicit loops
    local_vars  = set()
    loopables   = set()
    objdef      = ''
    singleton_object = False
    
    for index in range(len(records)):
        
        token, value, next_token = decode_and_look_ahead(index, records)
        record = records[index]
        if DEBUG > 0:
            print(" TOKEN( %s )\tvalue( %s ) NEXT_TOKEN( %s )" % \
              (token, value, next_token))
            
        if   token == 'take':
            # --------------------------------------------            
            # TAKE format: take object-name [instance-nane]
            # --------------------------------------------
            take_values.append(value)
            
            # check next token. if it is a take, continue
            # to next record
            if next_token == 'take':
                continue

            # 1. if we have multiple takes, it is assumed that
            #    we wish to concatenate the list of objects.
            # 2. if we have an instance name after the object name in
            #    the take command
            t = str.split(take_values[0])
            value = t[0]
            
            if len(take_values) == 1:
                
                # handle SINGLE TAKE COMMAND
                
                # note: if the value of take is a singleton object
                # so too is the current object. If so, update the
                # singleton cache

                singleton_object = value in SINGLETONS
                if singleton_object: SINGLETONS.add(name)
                    
                if singleton_object:
                    if DEBUG > 0:
                        print('\tSINGLETON')
                    objdef += '%s// singleton object\n' % tab                      
                    objdef += '%s%s = %s;\n' % (tab, name, value)
                else:
                    objdef += '%s%s.clear();\n' % (tab, name)

                    if value.find('(') < 0:
                        objdef += '\n%s// note: o and %s are the same object\n' % \
                          (tab, value)                        
                        objdef += '%svector<TNMObject>& o = %s;\n\n' % (tab, value)
                    else:
                        # take value is a function, so must use a copy
                        value = change_to_internal_name(value, blocks)
                        objdef += '%svector<TNMObject> o = %s;\n\n' % (tab, value)

                    # handle take instance
                
                    if len(t) > 1:
                        obj_instance  = t[1]
                        objdef_inloop = '%s%sTNMObject& %s = p;\n' % \
                        (tab, tab4, obj_instance)
                        local_vars.add(obj_instance)
                    else:
                        objdef_inloop = ''
            else:
                
                # handle MULTIPLE TAKE COMMANDS
                sort_objects = True
                objdef_inloop = ''
                objdef += '%s%s.clear();\n' % (tab, name)                        
                objdef += '%s// concatenate vectors\n' % tab
                objdef += '%svector<TNMObject> o;\n' % tab           
                for v in take_values:
                    t = str.split(v)
                    value   = t[0]
                    objdef += '%sfor(size_t n=0; n < %s.size(); n++)\n' % \
                    (tab, v)
                    objdef += '%s  {\n' % tab
                    objdef += '%s    o.push_back(%s[n]);\n' % (tab, value)
                    objdef += '%s  }\n' % tab
                        
                    # handle take instance
                    
                    if len(t) > 1:
                        obj_instance  = t[1]
                        objdef_inloop = '%s%sTNMObject& %s = p;\n' % \
                        (tab, tab4, obj_instance)
                        local_vars.add(obj_instance)                        
                objdef += '%s\n' % tab
                
            if singleton_object:
                pass
            else:
                objdef += '%sfor(size_t c=0; c < o.size(); c++)\n' % tab
                objdef += '%s  {\n' % tab
                objdef += '%s%sTNMObject& p = o[c];\n' % (tab, tab4)
                if objdef != '': objdef += objdef_inloop

            # move to next (non-take) record
            continue
                
        # check for implicit loops in current statement
        loopy =  checkForLoopables(record, blocktypes, loopables)

        if token in ['select', 'reject', 'set']:
            # --------------------------------------------            
            # if the current record contains a loopable,
            # then assume entire select, reject, or define
            # statement lies within a loop
            # --------------------------------------------                        
            if   token == 'select':
                # SELECT
                prefix = '!'
                logic  = '.AND()'
            elif token == 'reject':
                # REJECT
                prefix = ''
                logic  = '.OR()'
            elif token == 'weight':
                prefix = ''
                logic  = ''
            else:
                # SET
                prefix = ''
                logic  = ''

                t = map(str.strip, str.split(value, '='))
                if len(t) != 2:
                    boohoo('problem in line: %d\n%s' % (lineno, record))
                        
                varname = t[0]
                value   = t[1]
                local_vars.add(varname)
                
            if len(loopy) > 0:
                # ----------------------------------------
                # statement contains loopables
                # ----------------------------------------                
                if DEBUG > 0:
                    print('   BEGIN( IMPLICIT LOOP )')
                    
                # this select contains an implicit loop and
                # therefore returns multiple values that we refer to as a
                # cutvector.
                loop_count += 1
                cutvarname = 'cut%d' % loop_count
                cut_vector.add(cutvarname)

                # for now, we handle function calls with a single
                # implicit loop.
                # get any name from loopables
                for object_name in loopables: break
                
                # adjust tab
                tab = TAB + tab4

                if token in ['select', 'reject']:
                    loop_varname = cutvarname
                    objdef += '%sTNMBool %s(%s.size());\n' % (tab, cutvarname,
                                                                 object_name)
                else:
                    # SET
                    loop_varname = varname
                    objdef += '%svector<float> %s(%s.size());\n' % (tab,
                                                                 varname,
                                                                 object_name)
                    loopables.add(varname)
                    
                objdef += '%sfor(size_t n=0; n < %s.size(); n++)\n' % \
                (tab, object_name)
                objdef += '%s  {\n' % tab
                statement = convert2cpp(value,
                                        blocktypes,
                                        cutvector=cut_vector,
                                        loopables=loopables,
                                        localvars=local_vars)
                statement = change_to_internal_name(statement, blocks)
                objdef += '%s%s%s[n] = %s;\n' % (tab, tab4,
                                                     loop_varname, statement)
                objdef += '%s  }\n' % tab
                if DEBUG > 0:
                    print('   END( IMPLICIT LOOP )')
                    
                if token in ['select', 'reject']:
                    objdef += '%sif ( %s(%s%s) ) continue;\n' % \
                  (tab, prefix, cutvarname, logic)
                  
                # reset tab
                tab = TAB
            else:
               statement = convert2cpp(value,
                                        blocktypes,
                                        cutvector=cut_vector,
                                        loopables=loopables,
                                        localvars=local_vars)
               statement = change_to_internal_name(statement, blocks)               
               if token in ['select', 'reject']:
                    objdef += '%s%sif ( %s(%s) ) continue;\n' % \
                    (tab, tab4, prefix, statement)
               else:
                   objdef += '%s%sfloat %s = %s;\n' % \
                     (tab, tab4, varname, statement)

    if singleton_object:
        pass
    else:
        objdef += '%s%s%s.push_back(p);\n' % (tab, tab4, name)
        objdef += '%s  }\n' % tab
        if sort_objects:
            objdef += '%ssort(%s.begin(), %s.end());\n' % (tab, name, name)
    return objdef

def process_objects(names, blocks, blocktypes):
    if DEBUG > 0:
        print('\nBEGIN( process_objects )')

    if not ('object' in blocks): return  ''
        
    tab2 = ' '*2
    tab4 = ' '*4
    tab6 = ' '*6
    tab8 = ' '*8
    
    intobjdef = ''
    extobjset = set()
    vobjects  = '%s// cache pointers to filtered objects\n' % tab2
    vobjects += '%sobjects.clear();\n' % tab2

    # determine which objects are internal and which are external,
    # taking note that the value of a "take" command could be a
    # function.
    for name, words, records in blocks['object']:
        if DEBUG > 0:
            print('INTERNAL OBJECT( %s )' % name)

        for record in records:
            t = str.split(record)
            token = t[0]

            if token == 'take':
                # check for external objects in take commands
                # an object is considered external if
                # 1. the objname is not the name of an object block
                # 2. if the take command has a value that is a function
                #    and if its argument(s) are not the names of object
                #    blocks
                objname = t[1]
                if takefunction.findall(objname) == []:
                    if not (objname in blocktypes['object']):
                        extobjset.add(objname)
                        #DB
                        #print("(1) objname( %s )" % objname)                        
                else:
                    # take value is a function, so extract the names
                    # of the input arguments
                    gargs = re.compile(r'[(][\w_,\s]+[)]')
                    args  = gargs.findall(objname)
                    if len(args) > 0:
                        args = str.split(args[0][1:-1], ',')
                    for objname in args:
                        if not (objname in blocktypes['object']):
                            extobjset.add(objname)
                        #DB
                        #print("(2) objname( %s )" % objname)                           
                        if DEBUG > 0:
                            print(' TAKE VALUE( %s ) ARGS( %s )' % \
                                      (record, objname))
                                      
                # now check if objname is a singleton
                # if it is then name inherits that property, so add
                # name to list of singletons
                if objname in SINGLETONS:
                    SINGLETONS.add(name)
                    if DEBUG > 0:
                        print('\tSINGLETON OBJECT( %s )' % name)
                   
        singleton = name in SINGLETONS
        if singleton:
            intobjdef += '\nTNMObject %s;\n\n' % name
        else:
            intobjdef += 'vector<TNMObject> %s;\n' % name

        vobjects += '%sobjects.push_back(&object_%s);\n' % (tab2, name)            

    # cache external object set
    blocktypes['extobjset'] = extobjset
    
    # create list of external objects
    extobjdef = ''
    for name in extobjset:
        if DEBUG > 0:
            print('EXTERNAL OBJECT( %s )' % name)        
        singleton = name in SINGLETONS
        if singleton:
            extobjdef += '\nTNMObject %s;\n\n' % name
            if DEBUG > 0:
                print("\tsingleton object( %s )" % name)
        else:
            extobjdef += 'vector<TNMObject> %s;\n' % name
            if DEBUG > 0:
                print("\tmulti object( %s )" % name)           
    
    # create records containing declarations of external and
    # internal objects.
    objdef = '''// proxies for external objects
%s
// internal objects
%s
''' % (extobjdef, intobjdef)

    # -------------------------------------------------------
    runimpl     = '      %(analyzer)s.run(' % names
    runtab      = ' '*len(runimpl)
    
    runargs     = ''
    runargsimpl = 'void %(name)s_s::run(' % names
    
    bigtab      = ' '*len(runargsimpl)
    smalltab    = ' '*len('  void run')+' '

    adapter     = names['adapter']
    copyargsimpl= ''
    extobjimpl  = '\n%s// map external objects to internal ones\n' % tab6
    for name in extobjset:
        singleton = name in SINGLETONS
        if singleton:
            rtype = 'TNMObject'
        else:
            rtype = 'std::vector<TNMObject>'        
        extobjimpl  += '%s%s %s;\n' % (tab6, rtype, name)

        rtype = rtype + '&'
        runargsimpl += '%s %s_,\n%s' % (rtype, name, bigtab)
        runargs     += '%s %s_,\n%s' % (rtype, name, smalltab)
        runimpl     += '%s,\n%s'  % (name, runtab)

        extobjimpl  += '%s%s(ev, "%s", \t%s);\n\n' % (tab6, adapter, name, name)
        copyargsimpl+= '  %s\t= %s_;\n' % (name, name)
        
    runimpl     = str.rstrip(runimpl)[:-1] + ');\n'
    runargs     = str.rstrip(runargs)[:-1]
    runargsimpl = str.rstrip(runargsimpl)[:-1] + ')\n'
 
    names['runimpl']     = runimpl
    names['runargs']     = runargs
    names['runargsimpl'] = runargsimpl
    names['copyargsimpl']= copyargsimpl
    
    # implement object selections
    objdef += '\n// object definitions\n'
    for name, words, records in blocks['object']:
        objdef += 'struct object_%s_s : public TNMThing\n' % name
        objdef += '{\n'
        objdef += '%sobject_%s_s() : TNMThing() {}\n' % (tab2, name)
        objdef += '%s~object_%s_s() {}\n' % (tab2, name) 
        objdef += '%sbool select()\n' % tab2
        objdef += '%s{\n' % tab2
        objdef += process_object_body(name, records, tab4, blocks, blocktypes)
        objdef += '%sreturn true;\n' % tab2
        objdef += '%s};\n' % tab2
        objdef += '} object_%s;\n\n' % name
        
    names['objdef']     = objdef   
    names['extobjimpl'] = extobjimpl
    names['vobjects']   = vobjects
#--------------------------------------------------------------------------------
def process_defines(names, blocks, blocktypes):
    if DEBUG > 0:
        print('\nBEGIN( process_defines )')

    names['vardef']  = ''
    names['vdefines']= ''
    if not ('define' in blocks): return  ''
        
    tab2 = ' '*2
    vardef   = '// defines (aliases)\n'
    vdefines = '  // cache pointers to defines\n'
    vdefines+= '  defines.clear();\n'
    for name, words, records in blocks['define']:    
        vdefines += '  defines.push_back(&%s);\n' % name

    if 'function_info' in blocks:
        functions = blocks['function_info']
        fnames    = set(functions.keys())
    else:
        functions = None
        fnames    = None
        
    # we need to arrange defines according to dependencies

    objects  = set([name for name, w, r in blocks['object']])
    defines  = set([name for name, w, r in blocks['define']])
    deflist  = []
    defmap   = {}
    for name, words, records in blocks['define']:
        
        statement = ' '.join(records)
        wordset   = set(swords.findall(statement))
        deflist.append([name, wordset.intersection(defines)])
        statement = convert2cpp(statement, blocktypes)
        defmap[name] = statement
    sorted_deflist = sortObjects(deflist)

    # need to determine type of each statement. for now assume
    # the type is a float if the first word of a statement is
    # not an object, otherwise it is a TNMObject.

    deftypemap = {}
    for name, words in sorted_deflist:
        statement = defmap[name]
        words = swords.findall(statement)
        if len(words) == 0:
            boohoo(" problem with define %s" % name)
            
        # check type of first word and assign
        # that type to the define object and add name to objects,
        # otherwise default to float.
        # however, if we have a.size set the type to size_t
        if words[0] in objects:
            if words[1] == 'size':
                deftype = 'size_t'
            else:
                deftype = 'TNMObject'
                objects.add(name)
        else:
            deftype  = 'float'
        deftypemap[name] = deftype
        
    # for each define, create a struct
    for name, w in sorted_deflist:
        statement = defmap[name]        
        
        words   = swords.findall(statement)
        wordset = set(words)
        if functions:
            wordset = wordset.intersection(fnames)
            for word in wordset:
                rtype, intname, extname, argtypes = functions[word]
                cmd = re.compile(r'\b%s\b' % word)
                statement = cmd.sub(intname, statement)

        # trigger call to defines
        ws = swords.findall(statement)
        deftrig = ''                
        for key in ws:
            if not (key in deftypemap): continue
            deftype = deftypemap[key]
            if deftype == 'float': continue
            cmd = re.compile(r'\b%s\b' % key)
            deftrig += '%sTNMObject %s_t = %s;\n' % (' '*8, key, key)
            
        # now change statements
        for key in deftypemap.keys():
            deftype = deftypemap[key]
            if deftype == 'float': continue
            cmd = re.compile(r'\b%s\b' % key)
            statement = cmd.sub('%s_t' % key, statement)
            
        names['defname'] = name
        names['deftrig'] = deftrig
        names['deftype'] = deftypemap[name]
        names['defstatement'] = statement
        deflist = [name, words]
        vardef += DEF_TEMPLATE_CC % names
        if DEBUG > 0:
            print('DEFINE( %s = %s)' % (name, statement) )

    names['vardef']  = vardef
    names['vdefines']= vdefines

    # cache define types
    blocktypes['define_type'] = deftypemap
#--------------------------------------------------------------------------------
def process_regions(names, blocks, blocktypes):
    if DEBUG > 0:
        print('\nBEGIN( process_regions )')
        
    names['varimpl'] = ''
    names['vcuts']   = ''
    names['regdef']  = ''
    
    if not ('region' in blocks):
        return
    
    cutdef  = '// regions\n'
    vcuts   = '  // cache pointers to regions\n'
    vcuts  += '  regions.clear();\n'
    for name, words, records in blocks['region']:    
        vcuts += '  regions.push_back(&region_%s);\n' % name
    
    # implement regions
    tab2 = ' '*2
    tab4 = tab2*2
      
    for name, words, records in blocks['region']:
        if DEBUG > 0:
            print('REGION( %s )' % name)

        weight_value = None # default weight value = 1.0
        
        # get cut strings
        values = []
        for record in records:
            t = str.split(record)
            token = t[0]
            
            # check for weight
            if token == 'weight':
                weight_value = ' '.join(t[1:])
                continue
            
            if not (token in ['select', 'reject']): continue
            value = ' '.join(t[1:])
            values.append(value)

        cutdef += 'struct region_%s_s : public TNMThing\n' % name 
        cutdef += '{\n'
        cutdef += '  std::string name_;\n'
        cutdef += '  double total;\n'
        cutdef += '  double dtotal;\n'
        cutdef += '  TH1F*  hcount;\n'
        cutdef += '  bool   done;\n'
        cutdef += '  bool   result;\n'
        cutdef += '  int    ncuts;\n\n'
        cutdef += '  std::string name() { return name_; }\n\n'
        cutdef += '  region_%s_s()\n' % name
        cutdef += '''    : TNMThing(),
      name_("%s"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      ncuts(%d)
''' % (name, len(values))
           
        cutdef += '''  {
    weight = 1.0; // default weight
    hcount = new TH1F("cutflow_%s", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
''' % name
        
        for value in values:
            cutdef += '    hcount->Fill("%s", 0);\n' % value
            #nip.sub('', value)        
        cutdef += '  }\n\n'
        cutdef += '  ~region_%s_s() {}\n\n' % name
        cutdef += '''  void summary(std::ostream& os)
  {
    os << name_ << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %(percent)s2d %(percent)s-45s:"
                " %(percent)s9.2f +/- %(percent)s5.1f %(percent)s6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
''' % {'percent': '%'}
        
        cutdef += '  void count(string c)\t\t{ hcount->Fill(c.c_str(), weight); }\n'
        cutdef += '  void write(TFile* fout)\t{ fout->cd(); hcount->Write(); }\n'
        cutdef += '  void reset()\t\t\t{ done = false; result = false; }\n'
        cutdef += '  bool operator()()\t\t{ return select(); }\n\n'     
        cutdef += '  bool select()\n'
        cutdef += '  {\n'
        cutdef +='''    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

'''
        for value in values:
            # convert to C++
            statement = convert2cpp(value, blocktypes, blocktype='region')
            statement = change_to_internal_name(statement, blocks)

            cutdef += '%sif ( !(%s) ) return false;\n' % (tab4, statement)
            cutdef += '%scount("%s");\n\n' % (tab4, value) #nip.sub('', value))

        # handle weight statement
        if weight_value != None:
            weight_statement = convert2cpp(weight_value,
                                               blocktypes,
                                               blocktype='region')
            weight_statement = change_to_internal_name(weight_statement, blocks)
            cutdef += '%sweight  = %s;\n' % (tab4, weight_statement)
            
        cutdef += '%stotal  += weight;\n'  % tab4
        cutdef += '%sdtotal += weight * weight;\n\n'  % tab4
        cutdef += '%s// NB: remember to update result\n' % tab4
        cutdef += '%sresult  = true;\n' % tab4
        cutdef += '%sreturn true;\n' % tab4
        cutdef += '  }\n'            
        cutdef += '} region_%s;\n\n' % name

    names['regdef'] = cutdef
    names['vcuts']  = vcuts
#--------------------------------------------------------------------------------
def main():

    # -----------------------------------------------------
    # check if setup.sh has been sourced
    # -----------------------------------------------------
    if not ("ADL2TNM_PATH" in os.environ):
        boohoo('''
    please source setup.sh in adl2tnm to define
    ADL2TNM_PATH
        then try again!
        ''')

    # -----------------------------------------------------     
    # get command line
    # -----------------------------------------------------  
    filename, option = decodeCommandLine()
    names  = NAMES
    names['filename']    = filename
    names['analyzer']    = option.name    
    names['name']        = option.name    
    names['treename']    = option.treename
    names['adaptername'] = option.adaptername

    # -----------------------------------------------------      
    # create analyzer directory and move to it
    # -----------------------------------------------------      
    result = os.popen('which mkanalyzer.py').read()
    if str.strip(result) == '':
        boohoo('''
        command mkanalyzer.py not found. please make sure that adl2tnm
        is installed using
            source install.sh
        ''')

    # check that variables.txt exists
    if not os.path.exists('variables.txt'):
        boohoo('''
    please run 
        mkvariables.py Root-file-name
    to create file variables.txt
        ''')

    # ok create analyzer directory
    os.system("mkanalyzer.py %(analyzer)s" % names)
    if not os.path.exists('%(analyzer)s' % names):
        boohoo('''
        hmmm! directory %(analyzer)s not found. looks like
        mkanalyzer.py failed. 
        ''' % names)

    fill_EXTERNALS(filename='variables.txt')

    # change to analyzer directory
    cwd = os.getcwd()
    os.chdir('%(analyzer)s' % names)

    # -----------------------------------------------------
    # IMPORTANT: from here onwards, we are in the
    # analyzer directory
    # -----------------------------------------------------    
    
    # check that src and include directories exist
    if not os.path.exists('src'):
        boohoo('src directory not found')

    if not os.path.exists('include'):
        boohoo('include directory not found')

    if not os.path.exists('include/linkdef.h'):
        boohoo('include/linkdef not found')        

    if not os.path.exists('Makefile'):
        boohoo('Makefile not found')
    
    # copy TNMObject.h, TNMObject.cc to local area
    cmd = '''
cp $ADL2TNM_PATH/downloads/TNMObject.h include/ 
cp $ADL2TNM_PATH/downloads/TNMObject.cc src/
''' % names
    os.system(cmd)
    
    # -----------------------------------------------------
    # get blocks from ADL file
    # -----------------------------------------------------    
    names['fundef']   = ''
    names['objdef']   = ''
    names['vardef']   = ''
    names['aodimpl']  = ''
    names['percent']  = '%'
    names['tab']      = '  '
    blocks = extractBlocks(filename)

    blocktypes = {}
    for btype in BLOCKTYPES:
        blocktypes[btype] = set()
        if not (btype in blocks): continue
        for name, words, records in blocks[btype]:
            blocktypes[btype].add(name)
            
    # -----------------------------------------------------
    # either create an event adapter,  or copy an existing
    # one to local area
    # -----------------------------------------------------
    if option.adaptername == '':
        names['adaptername'] = 'TNMAdapter'
        print("\tcreating event adapter %(adaptername)s" % names)
        
        record = TEMPLATE_ADAPTER_H % names
        open('include/%(adaptername)s.h' % names, 'w').write(record)

        buildAdapterBody(names)
        record = TEMPLATE_ADAPTER_CC % names
        open('src/%(adaptername)s.cc' % names, 'w').write(record)
    else:
        names['base'] = os.environ['ADL2TNM_PATH']
        fn = '%(base)s/downloads/%(adaptername)s.h' % names
        if not os.path.exists(fn):
            boohoo('adapter header\n\t%s\n not found' % fn)
    
        # copy specified adapter to local area
        cmd = '''
cp $ADL2TNM_PATH/downloads/%(adaptername)s.h include/ 
cp $ADL2TNM_PATH/downloads/%(adaptername)s.cc src/
''' % names
        os.system(cmd)        

            
    if DEBUG > 0: printBlocks(blocks)

    process_info(names, blocks)
    
    process_functions(names, blocks, blocktypes)

    process_objects(names,   blocks, blocktypes)

    process_defines(names,   blocks, blocktypes)

    process_regions(names,   blocks, blocktypes)

    # --------------------------------------------    
    # write out C++ code
    # --------------------------------------------

    # write summaries of regions in same order as in ADL file
    if 'print_order' in blocks:
        order = blocks['print_order']
        tab = '  '
        s = ''
        for ii in order:
            s += '%sorder.push_back(%d);\n' % (tab, ii)
        names['order'] = s
    else:
        names['order'] = ''
        
    record = TEMPLATE_CC % names
    open('src/%(name)s_s.cc' % names, 'w').write(record)

    record = TEMPLATE_HH % names
    open('include/%(name)s_s.h' % names, 'w').write(record)

    # create varlist for event_buffer
    names['varlist'] = ' '.join(blocktypes['extobjset'])
    record = TNM_TEMPLATE_CC % names
    open('%(name)s.cc' % names, 'w').write(record)


    # update linkdef
    linkdef = str.strip(os.popen('find * -name "linkdef*"').read())
    if linkdef != '':
        names['linkdef'] = linkdef
        record = str.strip(os.popen('grep %(name)s_s %(linkdef)s' % names).read())
        if record == '':
            print('update linkdef')
            record = str.strip(open(linkdef).read())
            records= str.split(record, '\n')[:-1]
            records.append('#pragma link C++ class TNMThing;' % names)
            records.append('#pragma link C++ class %(name)s_s;' % names)            
            records.append('#pragma link C++ class TNMObject;' % names)
            records.append('#pragma link C++ class vector<TNMObject>;' % names)
            records.append('')
            records.append('#endif')
            record = '\n'.join(records)
            open(linkdef, 'w').write(record)


    # update Makefile
    makefile = str.strip(os.popen('find * -name "Makefile*"').read())
    if makefile != '':
        names['makefile'] = makefile
        record = str.strip(os.popen('grep %(name)s_s %(makefile)s' % names).read())
        if record == '':
            print('update Makefile')
            names['makefile'] = makefile
            record = str.strip(open(makefile).read())
            tnm    = re.compile('tnm.h.*$', re.M)
            record = tnm.sub('tnm.h $(incdir)/%(name)s_s.h' % names, record)
            open(makefile, 'w').write(record)    
#--------------------------------------------------------------------------------     
try:
    main()
except KeyboardInterrupt:
    print
    print("ciao!")
    
