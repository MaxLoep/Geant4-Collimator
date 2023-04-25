#include "SensitiveDetector.hh"
#include "Analysis.hh"

#include "G4VTouchable.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4VProcess.hh"

#include "G4ParticleTypes.hh"


SD1::SD1(const G4String& name)
 : G4VSensitiveDetector(name)
{}


SD1::~SD1()
{}


void SD1::Initialize(G4HCofThisEvent* /*hce*/)
{}


G4bool SD1::ProcessHits(G4Step* step, G4TouchableHistory* /*history*/)
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
    if(particle == G4Neutron::Neutron())  analysisManager->FillNtupleDColumn(1, 0, Ekin/MeV);
    if(particle == G4Neutron::Neutron())  analysisManager->FillNtupleDColumn(1, 1, localPosition.x()/cm);
    if(particle == G4Neutron::Neutron())  analysisManager->FillNtupleDColumn(1, 2, localPosition.y()/cm);
    if(particle == G4Neutron::Neutron())  analysisManager->FillNtupleDColumn(1, 3, time/ns);
    if(particle == G4Neutron::Neutron())  analysisManager->AddNtupleRow(1);

    // Store gamma hit in the ntuple
    if(particle == G4Gamma::Gamma())  analysisManager->FillNtupleDColumn(2, 0, Ekin/MeV);
    if(particle == G4Gamma::Gamma())  analysisManager->FillNtupleDColumn(2, 1, localPosition.x()/cm);
    if(particle == G4Gamma::Gamma())  analysisManager->FillNtupleDColumn(2, 2, localPosition.y()/cm);
    if(particle == G4Gamma::Gamma())  analysisManager->FillNtupleDColumn(2, 3, time/ns);
    if(particle == G4Gamma::Gamma())  analysisManager->AddNtupleRow(2);

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


void SD1::EndOfEvent(G4HCofThisEvent* /*hce*/)
{}

