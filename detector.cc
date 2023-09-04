#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) 
{}

MySensitiveDetector::~MySensitiveDetector() 
{}


G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhis)
{

    G4Track *track = aStep->GetTrack();
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    // G4cout << "Hit in sensitive detector!" << G4endl;
    // G4cout << "Particle: " << track->GetDefinition()->GetParticleName() << G4endl;
    // G4cout << "Energy Deposit: " << energyDeposit << " MeV" << G4endl;


 
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();


    if (energyDeposit != 0.) { 
       
        G4AnalysisManager *man = G4AnalysisManager::Instance();
        man->FillNtupleIColumn(0, evt);
        man->FillNtupleDColumn(1, posDetector[0]);
        man->FillNtupleDColumn(2, posDetector[1]);
        man->FillNtupleDColumn(3, posDetector[2]);
        man->FillNtupleDColumn(4, energyDeposit);
        man->AddNtupleRow(0);
    }


    return true;
}
