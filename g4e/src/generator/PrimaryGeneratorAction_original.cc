#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "PythiaAsciiReader.hh"
#include "HepMcAsciiGenerator.hh"
#include "BeagleGenerator.hh"

#include "ConeParticleGun.hh"

#include <spdlog/fmt/ostr.h>

PrimaryGeneratorAction::PrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction()
{
    // default generator is particle gun.
    fConeParticleGunGenerator = new ConeParticleGun();
    fParticleGunGenerator = new G4ParticleGun();
    fHepMcAsciiGenerator = new HepMcAsciiGenerator();
    fPythiaAsciiGenerator = new PythiaAsciiReader();
    fBeagleGenerator = new g4e::BeagleGenerator();
    
    
    gentypeMap["coneParticleGun"] = fConeParticleGunGenerator;
    gentypeMap["particleGun"] = fParticleGunGenerator;
    gentypeMap["hepmcAscii"] = fHepMcAsciiGenerator;
    gentypeMap["pythiaAscii"] = fPythiaAsciiGenerator;
    gentypeMap["beagle"] = fBeagleGenerator;

    messenger = new PrimaryGeneratorMessenger(this);
}

void PrimaryGeneratorAction::SelectGenerator(const G4String& name) {
    auto pos = gentypeMap.find(name);

    // Check we have such generator
    if (pos == gentypeMap.end()) {
        fmt::print(G4cerr, "PrimaryGeneratorAction::SelectGenerator no generator with name '{}'\n", name);
        return;
    }

    //currentGenerator = pos->second; <= this is default 
    currentGenerator = new G4GenaralParticleSource(); // change for /gps commands 12/21
    currentGeneratorName = name;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete messenger;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    if (currentGenerator)
        currentGenerator->GeneratePrimaryVertex(anEvent);
    else
        G4Exception("PrimaryGeneratorAction::GeneratePrimaries",
                    "PrimaryGeneratorAction001", FatalException,
                    "generator is not instantiated.");
}