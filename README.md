# adl2tnm

## Introduction

This program converts analysis descriptions given in the Analysis
Description Language (ADL) defined at the 2015 Les Houches Workshop
(with subsequent refinements) to a C++ program that runs within
__TheNtupleMaker__ (TNM) ROOT n-tuple analysis framework developed by Sezen Sekmen and Harrison Prosper. This program is a proof of principle of the ADL concept. The __adl2tnm__
package is structured as follows,

| __Directory__  | __Description__                   |
| --------|-------------------|
| bin           |  location of __adl2tnm.py__                                  |
| examples/monophoton |  ATLAS EXOT-2016-32 analysis |
|                     |  __ATLASEXOT1704.0384_Delphes_adl2tnm.adl__ |
|                     |  __DM_10_800_Delphes.root__ |
| examples/razorboost |  CMS razor boost analysis |
|                     |  __razorboost_adl2tnm.adl__ |
|                     |  __SUSY_T5tttt_CMSNANOAOD.root__ |
| examples/softdilepton |  CMS SUS-16-048 analysis |
|                     |  __CMSSUS16048_adl2tnm.adl__ |
|                     |  __pp13TeVhzz4l.root__ |
| downloads   | required code would be downloaded here |

## Installation

Install this package using the commands
```bash
  git clone https://github.com/hbprosper/adl2tnm
  cd adl2tnm
  source install.sh
  ```
and once per terminal session do
```bash
  source setup.(c)sh
```

## Example
In this example, we shall try to run the __CMS razor boost  analysis__,
described in the ADL file 

__examples/razorboost/razorboost_adl2tnm.adl__ 

on a 10,000-event __CMS nano-AOD__ file called 

__examples/razorboost/SUSY_T5tttt_CMSNANOAOD.root__

Go to the directory __examples/razorboost__  and execute the following
command
```bash
	mkvariables.py SUSY_T5tttt_CMSNANOAOD.root
```
This should produce a file called __variables.txt__ listing all of the
variables in the first tree (Events) found in the ROOT file.  Now execute the command
```bash
	adl2tnm.py -a razor razorboost_adl2tnm.adl
```
This should create a directory called __razor__. Go to that
directory and build the analyzer program __razor__ using
```bash
   cd razor
   make
   source setup.(c)sh
```
List, in the file __filelist.txt__, the names of the files to be read by __razor__,
e.g., as follows,
```bash
	ls -1 ../SUSY_T5tttt_CMSNANOAOD.root > filelist.txt
./razor | tee summary.dat
```
to run the  program.
You will see several "no dictionary" warnings about complicated types that
__treestream__ dutifully ignores! More importantly, you should see a file called
__summary.dat__ when the program completes containing cut-flow
summaries of the analysis.

