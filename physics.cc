#include "physics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4DecayPhysics.hh"

MyPhysicsList::MyPhysicsList() : G4VModularPhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics());


    RegisterPhysics(new G4OpticalPhysics());


    RegisterPhysics(new G4HadronElasticPhysics());
    RegisterPhysics(new G4HadronInelasticQBBC());


    RegisterPhysics(new G4DecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
