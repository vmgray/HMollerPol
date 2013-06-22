/***********************************************************
Programmer: Valerie Gray
Purpose:

This is the main function for the H moller Geant4 simulation
it should put everything together...

Entry Conditions:
Date: 05-15-2013
Modified:
Assisted By: Wouter Deconinck
 *********************************************************/

#include <iostream>

#include <G4RunManager.hh>
#include <G4PhysListFactory.hh>
#include <G4VModularPhysicsList.hh>

#include <G4VisManager.hh>
#include <G4VisExecutive.hh>

#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
//do I need all of these?? what are they for?  I got then for the Qweak and what they do is beyond me
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "HMollerPolDetectorConstruction.hh"

//what are these for? agian they are from Qweak
#ifdef G4UI_USE_QT
    #include "G4UIQt.hh"
#endif

#ifdef G4UI_USE_XM
    #include "G4UIXm.hh"
#endif

#ifdef G4VIS_USE
    #include "G4VisExecutive.hh"
#endif

//why is this not a void function? Why is it getting passed anything?
//what is the point of whatever it is getting passed
//if this is the number of things passed and the commands, then how does it work
//
int main (int argc, char** argv)
{
  //-------------------------------
  // Initialization of Run manager
  // This is need so that all the "events" are looped through in a run
  //-------------------------------
  G4cout << "RunManager construction starting...." << G4endl;
  G4RunManager* runManager = new G4RunManager;

  // Detector geometry
  //how?? this works I have no idea
  //pass the geometry of the HMolPol to the Geant4 class G4VUserDetectorConstruction
  G4VUserDetectorConstruction* detector = new HMollerPolDetectorConstruction();
  // give the run manager the geometry
  runManager->SetUserInitialization(detector);

  // Physics we want to use
  G4int verbose = 0;
  //physics list factory allows one to use the standard geant4 physics list
  G4PhysListFactory* factory = new G4PhysListFactory;
  // use the FTFP-BERT
  //(FTRP_BERT - http://geant4.cern.ch/support/proc_mod_catalog/physics_lists/hadronic/FTFP_BERT.html)
  //(FTRP - http://geant4.cern.ch/support/proc_mod_catalog/physics_lists/hadronic/FTFP.html)
  //physics list - this is replacing the LHEP physics list
  // standard EM processes are include in all list
  // this may be no the right physics list for Mainz energy, but should be for JLab
  G4VModularPhysicsList* physlist = factory->GetReferencePhysList("FTFP_BERT");
  physlist->SetVerboseLevel(verbose);
  // give the run manager the physics list
  runManager->SetUserInitialization(physlist);

  // Initialize Run manager
  // we can either us this or have /run/initialize staring all out macros...
  // this is nicer
  runManager->Initialize();
  G4UIsession* session = 0;

  //----------------
  // Visualization:
  //----------------

  //I have no idea what any of this does... so please don't ask :-)

  // WFTM is argc and what does it value have to do with getting a GUI??
  if (argc==1)   // Define UI session for interactive mode.
  {

      // G4UIterminal is a (dumb) terminal.
     #if defined(G4UI_USE_XM)
      session = new G4UIXm(argc,argv);
     #elif defined(G4UI_USE_WIN32)
     session = new G4UIWin32();
     #elif defined(G4UI_USE_QT)
      session = new G4UIQt(argc,argv);
     #elif defined(G4UI_USE_TCSH)
      session = new G4UIterminal(new G4UItcsh);
     #else
       session = new G4UIterminal();
     #endif

  }


 #ifdef G4VIS_USE
   // Visualization, if you choose to have it!
   //
   // Simple graded message scheme - give first letter or a digit:
   //  0) quiet,         // Nothing is printed.
   //  1) startup,       // Startup and endup messages are printed...
   //  2) errors,        // ...and errors...
   //  3) warnings,      // ...and warnings...
   //  4) confirmations, // ...and confirming messages...
   //  5) parameters,    // ...and parameters of scenes and views...
   //  6) all            // ...and everything available.

   G4VisManager* visManager = new G4VisExecutive;
   //visManager -> SetVerboseLevel (1);
   visManager ->Initialize();
 #endif
   //(above) this ifdef if G4VIS_USE (what is that) is being used then
   //it will start up the visualization manager and initialize it
   //if not it will skip that.  (so it only happens iff we run interactively?? - but maybe not :(

   //not sure what this does??? explain please*********************************
   //get the pointer to the User Interface manager
   G4UImanager * UI = G4UImanager::GetUIpointer();

  if (session)   // Define UI session for interactive mode.
     {
       // G4UIterminal is a (dumb) terminal.
       //UI->ApplyCommand("/control/execute myVis.mac");

 #if defined(G4UI_USE_XM) || defined(G4UI_USE_WIN32) || defined(G4UI_USE_QT)
       // Customize the G4UIXm,Win32 menubar with a macro file :
       UI->ApplyCommand("/control/execute gui.mac");
 #endif

       //If this is one is using the GUI?? I am not following, but if so then
       // it starts it and deletes it??
       //WTFM is up with the create and then right away delete something

       session->SessionStart();
       delete session;
     }
   else           // Batch mode
     {
 #ifdef G4VIS_USE
       visManager->SetVerboseLevel("quiet");
 #endif
       G4String command = "/control/execute ";
       G4String fileName = argv[1];
       UI->ApplyCommand(command+fileName);
     }



 #ifdef G4VIS_USE
   delete visManager;
 #endif

   delete runManager;

  return 0;
}
