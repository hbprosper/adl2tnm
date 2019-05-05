# lhada2tnm

## Introduction

This program converts analysis descriptions given in the Analysis
Description Language (ADL) defined at the 2015 Les Houches Workshop
(with subsequent refinements) to a C++ program that runs within
__TheNtupleMaker__ (TNM) ROOT n-tuple analysis framework developed by Sezen Sekmen and Harrison Prosper. This program is a proof of principle of the ADL concept The __adl2tnm__
package is structured as follows,

| __Directory__  | __Description__                   |
| --------|-------------------|
| bin           |  location of __adl2tnm.py__                                  |
| examples/razorboost |  CMS razor boost analysis |
| examples/data           |  contains __ttjets\_nano.root__ |
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
  source setup.sh
```

## Example
In this example, we shall try to run the __CMS razor boost  analysis__,
described in the ADL file 

__examples/razorboost/razorboost.adl__ 

on a 1000-event __CMS nano-AOD__ file called 

__examples/data/ttjets\_nano.root__

Go to the directory __examples/razorboost__  and execute the following
command
```bash
	mkvariables.py ../data/ttjets_nano.root
```
This should produce a file called __variables.txt__ listing all of the
variables in the first tree (Events) found in the ROOT file.  Now execute the command
```bash
	adl2tnm.py -a myanalyzer 
```
This should create a directory called __myanalyzer__. Go to that
directory and build the analyzer program __myanalyzer__ using
```bash
   cd myanalyzer
	make
```
List, in the file __filelist.txt__, the names of the files to be read by cmsnano,
e.g., as follows,
```bash
	ls -1 ../../data/ttjets_nano.root > filelist.txt
```
then do
```bash
	./myanalyzer | tee summary.dat
```
to run the  program.
You will see several "no dictionary" warnings about complicated types that
__treestream__ dutifully ignores! More importantly, you should see a file called
__summary.dat__ when the program completes containing cut-flow
summaries of the analysis.

