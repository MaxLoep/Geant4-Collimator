#include "SensitiveDetector.hh"
#include "Analysis.hh"

#include "G4VTouchable.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4VProcess.hh"

#include "G4ParticleTypes.hh"


SD2::SD2(const G4String& name)
 : G4VSensitiveDetector(name)
{}


SD2::~SD2()
{}


void SD2::Initialize(G4HCofThisEvent* /*hce*/)
{}


G4bool SD2::ProcessHits(G4Step* step, G4TouchableHistory* /*history*/)
{
  // Current track:
  const G4Track* track = step->GetTrack();

 // keep only outgoing particle
 const G4ParticleDefinition* particle = track->GetParticleDefinition();
 

    // Remember preStepPoint:
    G4StepPoint* preStepPoint = step->GetPreStepPoint();

    // Ekin:
    G4double Ekin =  preStepPoint->GetKineticEnergy();

    // Obtain local coordinates:
    const G4VTouchable* touchable = preStepPoint->GetTouchable();
    G4ThreeVector globalPosition = preStepPoint->GetPosition();
    G4ThreeVector localPosition
      = touchable->GetHistory()->GetTopTransform().TransformPoint(globalPosition);
    // // Example for obtaining the local direction:
    // G4ThreeVector globalDirection = preStepPoint->GetMomentumDirection();
    // G4ThreeVector localDirection
    //   = touchable->GetHistory()->GetTopTransform().TransformAxis(localDirection);

    // Time
    G4double time = preStepPoint->GetGlobalTime();

    // Get Analysis Manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Store neutron hit in the ntuple
    if(particle == G4Neutron::Neutron())  analysisManager->FillNtupleDColumn(3, 0, Ekin/MeV);
    if(particle == G4Neutron::Neutron())  analysisManager->FillNtupleDColumn(3, 1, localPosition.x()/cm);
    if(particle == G4Neutron::Neutron())  analysisManager->FillNtupleDColumn(3, 2, localPosition.y()/cm);
    if(particle == G4Neutron::Neutron())  analysisManager->AddNtupleRow(3);

    // Store gamma hit in the ntuple
    if(particle == G4Gamma::Gamma())  analysisManager->FillNtupleDColumn(4, 0, Ekin/MeV);
    if(particle == G4Gamma::Gamma())  analysisManager->FillNtupleDColumn(4, 1, localPosition.x()/cm);
    if(particle == G4Gamma::Gamma())  analysisManager->FillNtupleDColumn(4, 2, localPosition.y()/cm);
    if(particle == G4Gamma::Gamma())  analysisManager->AddNtupleRow(4);

    // // Store hit in histogram 
    // analysisManager->FillH1(0, ID);
    // analysisManager->FillH1(1, pdgCode);
    // analysisManager->FillH1(2, Ekin/MeV);
    // analysisManager->FillH1(3, localPosition.x()/cm);
    // analysisManager->FillH1(4, localPosition.y()/cm);
    // analysisManager->FillH1(5, time/ns);
  // }
  return true;
}


void SD2::EndOfEvent(G4HCofThisEvent* /*hce*/)
{}

