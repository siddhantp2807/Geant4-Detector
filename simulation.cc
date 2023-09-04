#include <iostream>
#include "detector.hh"
#include "detector.cc"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "construction.cc"
#include "construction.hh"
#include "physics.cc"
#include "physics.hh"
#include "action.cc"
#include "action.hh"
#include "generator.cc"
#include "generator.hh"
#include "run.hh"
#include "run.cc"

int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    runManager->Initialize();


  G4UIExecutive* ui = 0;
  if ( argc == 1 ) 
  { 
      ui = new G4UIExecutive(argc, argv); 
  }
  

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if(ui)
  {
  
  UImanager->ApplyCommand( "/control/execute vis.mac");
  ui->SessionStart();
  }
  else
  {
    G4String command = "/control/execute ";
    G4String filename = argv[1];
    UImanager->ApplyCommand(command+filename);
  }

  return 0;
}