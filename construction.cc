#include "construction.hh"
#include "G4Polyhedra.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();    
    
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // Define PbWO4 material
    G4Material* PbWO4 = new G4Material("PbWO4", 8.28 * g/cm3, 3);
    PbWO4->AddElement(nist->FindOrBuildElement("Pb"), 1);
    PbWO4->AddElement(nist->FindOrBuildElement("W"), 1);
    PbWO4->AddElement(nist->FindOrBuildElement("O"), 4);


    G4Material *DetMat = nist->FindOrBuildMaterial("G4_Si");
    G4Box *solidWorld = new G4Box("solidWorld", 1*m, 1*m, 1*m);
    
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // Create a hexagonal solid shape using G4Polyhedra
    G4int numZPlanes = 2;
    G4double zPlanes[] = { -0.01*m, 0.01*m };
    G4double rInner[] = { 0., 0. };
    G4double rOuter[] = { 0.05*m, 0.05*m }; // Smaller radius for the hexagon
    G4Polyhedra *solidHexagon = new G4Polyhedra("solidHexagon", 0., 360.*deg, 6, numZPlanes, zPlanes, rInner, rOuter);
    
    logicHexagon = new G4LogicalVolume(solidHexagon, PbWO4, "logicHexagon"); // Assign the value here

    
    G4RotationMatrix* rotationMatrix = new G4RotationMatrix();

    rotationMatrix->rotateZ(90.*deg);

//  Geometry Construction.

for (G4int i = 0; i < 19; ++i) {
    for (G4int j = 0; j < 11; ++j) {
        for (G4int k = 0; k <20; ++k){
            new G4PVPlacement( rotationMatrix, G4ThreeVector(90*cm-i*10*cm, -90*cm + j*(30/sqrt(3))*cm  , 90*cm - k*(5)*cm), logicHexagon, "physHexagon", logicWorld, false, 0, true);

        }       
    }
}

for (G4int i = 0; i < 19; ++i) {
    for (G4int j = 0; j < 11; ++j) {
        for (G4int k = 0; k<20; ++k){
            new G4PVPlacement( rotationMatrix, G4ThreeVector(95*cm-i*10*cm, (-90 + 15/sqrt(3))*cm + j*(30/sqrt(3))*cm  , 90*cm - k*(5)*cm), logicHexagon, "physHexagon", logicWorld, false, 0, true);

        }
       
    }
}


    return physWorld;
}


void MyDetectorConstruction::ConstructSDandField()

{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicHexagon->SetSensitiveDetector(sensDet);
}