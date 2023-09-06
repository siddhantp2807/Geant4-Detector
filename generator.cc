#include "generator.hh"


MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName="pi0";
	G4ParticleDefinition *particle = particleTable->FindParticle("pi0");
	
	G4ThreeVector pos(0., 0., -20.*cm);
	G4ThreeVector mom(0.,0., 1.);
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(800.5*MeV);
	// fParticleGun->SetParticleMomentum(2*GeV);
	fParticleGun->SetParticleDefinition(particle);

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

