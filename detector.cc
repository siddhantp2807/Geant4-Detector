#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
    // Constructor implementation
}

MySensitiveDetector::~MySensitiveDetector() {
    // Destructor implementation
}


G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhis)
{
    // Extracting track, volume, and energy deposition information
    G4Track *track = aStep->GetTrack();
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    // Getting event information
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    // Using Analysis Manager to fill ntuple with position data
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector[0]);
    man->FillNtupleDColumn(2, posDetector[1]);
    man->FillNtupleDColumn(3, posDetector[2]);
    man->AddNtupleRow(0);

    // Indicate that a hit was processed (returning true)
    return true;
}
