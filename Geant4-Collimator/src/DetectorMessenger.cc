/*
This file contains examples on how to create custom GUI-commands and macro-file-commands.
The actual functions can be found in files where they change variables, e.g. DetectorConstruction.cc
*/

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"               //to create directories to sort your custom commands
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"

#include "G4UIcmdWithAString.hh"          //for commands with a string
#include "G4UIcmdWithABool.hh"            //for commands with a bool
#include "G4UIcmdWithAnInteger.hh"        //for commands with an integer
#include "G4UIcmdWithADouble.hh"          //for commands with a double
#include "G4UIcmdWithADoubleAndUnit.hh"   //for commands with a double and a unit
#include "G4UIcmdWithoutParameter.hh"     //for commands without a parameter

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:G4UImessenger(), 
 fDetector(Det), fTestemDir(nullptr), fDetDir(nullptr), 
 fOutFoldCmd(nullptr),
 fMaterCmd(nullptr),
 fchange_aCmd(nullptr), fchange_bCmd(nullptr), fchange_cCmd(nullptr), fchange_dCmd(nullptr), fchange_eCmd(nullptr), fchange_fCmd(nullptr)
{
  //Create a directory for your custom commands
  fTestemDir = new G4UIdirectory("/custom/");
  fTestemDir->SetGuidance("custom commands defined in DetectorMessenger.cc");

  //Create a sub-directory for better sorting - geometry changing variables
  G4bool broadcast = false;
  fDetDir = new G4UIdirectory("/custom/geo/",broadcast);
  fDetDir->SetGuidance("Custom commands that change the geometry.");

  //Create a sub-directory for better sorting - analysis changing variables
  fDetDir = new G4UIdirectory("/custom/ana/",broadcast);
  fDetDir->SetGuidance("Custom commands that change the analysis.");

  // Change output folder name
  fOutFoldCmd = new G4UIcmdWithAString("/custom/ana/setOutFolder",this);
  fOutFoldCmd->SetGuidance("Set the name of the output folder");
  fOutFoldCmd->SetParameterName("choice",false);
  fOutFoldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Change Material dummyMat
  fMaterCmd = new G4UIcmdWithAString("/custom/geo/setMat",this);
  fMaterCmd->SetGuidance("Select material of the box.");
  fMaterCmd->SetParameterName("choice",false);
  fMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  // Change parameters a,b,c,d,e with Macro commands
  // Change a
  fchange_aCmd = new G4UIcmdWithADoubleAndUnit("/custom/geo/change_a",this);
  fchange_aCmd->SetGuidance("Change the thickness of shielding (default 20cm)");
  fchange_aCmd->SetParameterName("a",false);
  fchange_aCmd->SetRange("a>=0.");
  fchange_aCmd->SetUnitCategory("Length");
  fchange_aCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Change b
  fchange_bCmd = new G4UIcmdWithADoubleAndUnit("/custom/geo/change_b",this);
  fchange_bCmd->SetGuidance("Change the Entrance_Diameter of the colli (default 4cm)");
  fchange_bCmd->SetParameterName("b",false);
  fchange_bCmd->SetRange("0. < b < 6.");
  fchange_bCmd->SetUnitCategory("Length");
  fchange_bCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Change c
  fchange_cCmd = new G4UIcmdWithADoubleAndUnit("/custom/geo/change_c",this);
  fchange_cCmd->SetGuidance("Change the inner diameter (choke) of the colli (default 2cm)");
  fchange_cCmd->SetParameterName("c",false);
  fchange_cCmd->SetRange("0.< c < 6.");
  fchange_cCmd->SetUnitCategory("Length");
  fchange_cCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Change d
  fchange_dCmd = new G4UIcmdWithADoubleAndUnit("/custom/geo/change_d",this);
  fchange_dCmd->SetGuidance("Change the Exit_Diameter of the colli (default 4cm)");
  fchange_dCmd->SetParameterName("d",false);
  fchange_dCmd->SetRange("0. < d < 6.");
  fchange_dCmd->SetUnitCategory("Length");
  fchange_dCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Change e
  fchange_eCmd = new G4UIcmdWithADoubleAndUnit("/custom/geo/change_e",this);
  fchange_eCmd->SetGuidance("Change the rotation of the collimator (default 0°)");
  fchange_eCmd->SetParameterName("e",false);
  fchange_eCmd->SetRange("e>=0.");
  fchange_eCmd->SetUnitCategory("Angle");
  fchange_eCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Change f
  fchange_fCmd = new G4UIcmdWithADoubleAndUnit("/custom/geo/change_f",this);
  fchange_fCmd->SetGuidance("Change the position of the target (default 0cm)");
  fchange_fCmd->SetParameterName("f",false);
  fchange_fCmd->SetRange("0. <= f <= 3.76");  //Distance to Inlet is 4cm, target is 0.24cm thick = 3.76cm of space
  fchange_fCmd->SetUnitCategory("Length");
  fchange_fCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}


DetectorMessenger::~DetectorMessenger()
{
  delete fDetDir;
  delete fTestemDir;

  // Change output folder name
  delete fOutFoldCmd;

  // Change Material dummyMat
  delete fMaterCmd;

  // Change to parameters a,b,c,d,e 
  delete fchange_aCmd;
  delete fchange_bCmd;
  delete fchange_cCmd;
  delete fchange_dCmd;
  delete fchange_eCmd;
  delete fchange_fCmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  // Change output folder name
  if( command == fOutFoldCmd )
   { fDetector->SetOutputFolder(newValue);}

  // Change Material dummyMat
  if( command == fMaterCmd )
   { fDetector->SetAbsorMaterial(newValue);}

  // Change to parameters a,b,c,d,e 
  if( command == fchange_aCmd )
   { fDetector->change_a(fchange_aCmd->GetNewDoubleValue(newValue));} 
  
  if( command == fchange_bCmd )
   { fDetector->change_b(fchange_bCmd->GetNewDoubleValue(newValue));} 

  if( command == fchange_cCmd )
   { fDetector->change_c(fchange_cCmd->GetNewDoubleValue(newValue));} 
  
  if( command == fchange_dCmd )
   { fDetector->change_d(fchange_dCmd->GetNewDoubleValue(newValue));} 

  if( command == fchange_eCmd )
   { fDetector->change_e(fchange_eCmd->GetNewDoubleValue(newValue));}

  if( command == fchange_fCmd )
   { fDetector->change_f(fchange_fCmd->GetNewDoubleValue(newValue));}
}
