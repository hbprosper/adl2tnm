//------------------------------------------------------------------
// File:        analyzer.cc
// Description: Analyzer for ADL analysis:
//
// ADL file: razorboost_adl2tnm.adl
// info block
//	info        	analysis
//	experiment  	CMS
//	id          	SUS-16-050
//	publication 	Phys.Rev. D97 (2018) no.1, 012007
//	sqrtS       	13.0
//	lumi        	35.9
//	arXiv       	1710.11188
//	hepdata     	https://www.hepdata.net/record/ins1633588
//	doi         	10.1103/PhysRevD.97.012007
//
// Created:     Sun May  5 21:48:25 2019 by adl2tnm.py v2.0.0
//------------------------------------------------------------------
#include "tnm.h"
#include "TNMAdapter.h"
#include "analyzer_s.h"

using namespace std;
//------------------------------------------------------------------
int main(int argc, char** argv)
{
  // If you want canvases to be visible during program execution, just
  // uncomment the line below
  //TApplication app("analyzer", &argc, argv);

  // Get command line arguments
  commandLine cl(argc, argv);
    
  // Get names of ntuple files to be processed
  vector<string> filenames = fileNames(cl.filelist);

  // Create tree reader
  itreestream stream(filenames, "");
  if ( !stream.good() ) error("can't read root input files");

  // Create a buffer to receive events from the stream
  // The default is to select all branches
  // Use second argument to select specific branches
  // Example:
  //   varlist = 'Jet_PT Jet_Eta Jet_Phi'
  //   ev = eventBuffer(stream, varlist)

  eventBuffer ev(stream);
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
  TNMAdapter adapter;

  analyzer_s analyzer;
  //------------------------------------------------------------------
  // Loop over events
  //------------------------------------------------------------------
  for(int entry=0; entry < nevents; entry++)
    {
      // read an event into event buffer
      ev.read(entry);
      if ( entry % 1000 == 0 ) cout << entry << endl;

      // map external objects to internal ones
      std::vector<TNMObject> Muon;
      adapter(ev, "Muon", 	Muon);

      std::vector<TNMObject> Jet;
      adapter(ev, "Jet", 	Jet);

      std::vector<TNMObject> Tau;
      adapter(ev, "Tau", 	Tau);

      std::vector<TNMObject> Photon;
      adapter(ev, "Photon", 	Photon);

      TNMObject MET;
      adapter(ev, "MET", 	MET);

      std::vector<TNMObject> Electron;
      adapter(ev, "Electron", 	Electron);

      std::vector<TNMObject> FatJet;
      adapter(ev, "FatJet", 	FatJet);


      analyzer.run(Muon,
                   Jet,
                   Tau,
                   Photon,
                   MET,
                   Electron,
                   FatJet);

    }

  // summarize analysis
  analyzer.summary(of.file_, cout);

  ev.close();
  of.close();
  return 0;
}
