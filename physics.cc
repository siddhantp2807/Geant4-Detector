#include "physics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4DecayPhysics.hh"

MyPhysicsList::MyPhysicsList() : G4VModularPhysicsList()
{
    // Electromagnetic physics
    RegisterPhysics(new G4EmStandardPhysics());

    // Optical physics
    RegisterPhysics(new G4OpticalPhysics());

    // Hadronic physics
    RegisterPhysics(new G4HadronElasticPhysics());
    RegisterPhysics(new G4HadronInelasticQBBC());

    // Decay physics
    RegisterPhysics(new G4DecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
