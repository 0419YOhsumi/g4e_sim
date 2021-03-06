//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//

#include "ConeParticleGunMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "ConeParticleGun.hh"
#include "G4Geantino.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

ConeParticleGunMessenger::ConeParticleGunMessenger(ConeParticleGun *fPtclGun) : fParticleGun(fPtclGun), fShootIon(false), fAtomicNumber(0), fAtomicMass(0), fIonCharge(0),
                                                                                fIonExciteEnergy(0.0), fIonFloatingLevelBase('\0'), fIonEnergyLevel(0)
{
    particleTable = G4ParticleTable::GetParticleTable();

    gunDirectory = new G4UIdirectory("/generator/coneParticleGun/");
    gunDirectory->SetGuidance("Particle Gun control commands.");

    listCmd = new G4UIcmdWithoutParameter("/generator/coneParticleGun/List", this);
    listCmd->SetGuidance("List available particles.");
    listCmd->SetGuidance(" Invoke G4ParticleTable.");

    particleCmd = new G4UIcmdWithAString("/generator/coneParticleGun/particle", this);
    particleCmd->SetGuidance("Set particle to be generated.");
    particleCmd->SetGuidance(" (geantino is default)");
    particleCmd->SetGuidance(" (ion can be specified for shooting ions)");
    particleCmd->SetParameterName("particleName", true);
    particleCmd->SetDefaultValue("geantino");
    G4String candidateList;
    G4ParticleTable::G4PTblDicIterator *itr = particleTable->GetIterator();
    itr->reset();
    while ((*itr)()) {
        G4ParticleDefinition *pd = itr->value();
        if (!(pd->IsShortLived()) || pd->GetDecayTable()) {
            candidateList += pd->GetParticleName();
            candidateList += " ";
        }
    }
    candidateList += "ion ";
    particleCmd->SetCandidates(candidateList);

    directionCmd = new G4UIcmdWith3Vector("/generator/coneParticleGun/direction", this);
    directionCmd->SetGuidance("Set momentum direction.");
    directionCmd->SetGuidance("Direction needs not to be a unit vector.");
    directionCmd->SetParameterName("ex", "ey", "ez", true, true);
    directionCmd->SetRange("ex != 0 || ey != 0 || ez != 0");

    energyCmd = new G4UIcmdWithADoubleAndUnit("/generator/coneParticleGun/energy", this);
    energyCmd->SetGuidance("Set kinetic energy.");
    energyCmd->SetParameterName("Energy", true, true);
    energyCmd->SetDefaultUnit("GeV");

    energyStdDevCmd = new G4UIcmdWithADoubleAndUnit("/generator/coneParticleGun/energyStdDev", this);
    energyStdDevCmd->SetGuidance("Energy spread");
    energyStdDevCmd->SetParameterName("Energy", true, true);
    energyStdDevCmd->SetDefaultUnit("GeV");
    //energyCmd->SetUnitCategory("Energy");
    //energyCmd->SetUnitCandidates("eV keV MeV GeV TeV");

    coneAngleStdDevCmd = new G4UIcmdWithADoubleAndUnit("/generator/coneParticleGun/coneAngleStdDev", this);
    coneAngleStdDevCmd->SetGuidance("Cone angle standard deviation");
    coneAngleStdDevCmd->SetParameterName("Cone angle deviation", true, true);
    coneAngleStdDevCmd->SetDefaultUnit("deg");
    coneAngleStdDevCmd->SetUnitCategory("Angle");

    momCmd = new G4UIcmdWith3VectorAndUnit("/generator/coneParticleGun/momentum", this);
    momCmd->SetGuidance("Set momentum. This command is equivalent to two commands /gun/direction and /gun/momentumAmp");
    momCmd->SetParameterName("px", "py", "pz", true, true);
    momCmd->SetRange("px != 0 || py != 0 || pz != 0");
    momCmd->SetDefaultUnit("GeV");

    momAmpCmd = new G4UIcmdWithADoubleAndUnit("/generator/coneParticleGun/momentumAmp", this);
    momAmpCmd->SetGuidance("Set absolute value of momentum.");
    momAmpCmd->SetGuidance("Direction should be set by /gun/direction command.");
    momAmpCmd->SetGuidance("This command should be used alternatively with /gun/energy.");
    momAmpCmd->SetParameterName("Momentum", true, true);
    momAmpCmd->SetDefaultUnit("GeV");

    positionCmd = new G4UIcmdWith3VectorAndUnit("/generator/coneParticleGun/position", this);
    positionCmd->SetGuidance("Set starting position of the particle.");
    positionCmd->SetParameterName("X", "Y", "Z", true, true);
    positionCmd->SetDefaultUnit("cm");

    positionStdDevCmd = new G4UIcmdWith3VectorAndUnit("/generator/coneParticleGun/positionStdDev", this);
    positionStdDevCmd->SetGuidance("Set starting position smearing of the particle.");
    positionStdDevCmd->SetParameterName("dX", "dY", "dZ", true, true);
    positionStdDevCmd->SetDefaultUnit("cm");
    //positionCmd->SetUnitCategory("Length");
    //positionCmd->SetUnitCandidates("microm mm cm m km");

    timeCmd = new G4UIcmdWithADoubleAndUnit("/generator/coneParticleGun/time", this);
    timeCmd->SetGuidance("Set initial time of the particle.");
    timeCmd->SetParameterName("t0", true, true);
    timeCmd->SetDefaultUnit("ns");
    //timeCmd->SetUnitCategory("Time");
    //timeCmd->SetUnitCandidates("ns ms s");

    polCmd = new G4UIcmdWith3Vector("/generator/coneParticleGun/polarization", this);
    polCmd->SetGuidance("Set polarization.");
    polCmd->SetParameterName("Px", "Py", "Pz", true, true);
    polCmd->SetRange("Px>=-1.&&Px<=1.&&Py>=-1.&&Py<=1.&&Pz>=-1.&&Pz<=1.");

    numberCmd = new G4UIcmdWithAnInteger("/generator/coneParticleGun/number", this);
    numberCmd->SetGuidance("Set number of particles to be generated.");
    numberCmd->SetParameterName("N", true, true);
    numberCmd->SetRange("N>0");

    ionCmd = new G4UIcommand("/generator/coneParticleGun/ion", this);
    ionCmd->SetGuidance("Set properties of ion to be generated.");
    ionCmd->SetGuidance("[usage] /gun/ion Z A [Q E flb]");
    ionCmd->SetGuidance("        Z:(int) AtomicNumber");
    ionCmd->SetGuidance("        A:(int) AtomicMass");
    ionCmd->SetGuidance("        Q:(int) Charge of Ion (in unit of e)");
    ionCmd->SetGuidance("        E:(double) Excitation energy (in keV)");
    ionCmd->SetGuidance("        flb:(char) Floating level base");

    G4UIparameter *param;
    param = new G4UIparameter("Z", 'i', false);
    ionCmd->SetParameter(param);
    param = new G4UIparameter("A", 'i', false);
    ionCmd->SetParameter(param);
    param = new G4UIparameter("Q", 'i', true);
    param->SetDefaultValue(-1);
    ionCmd->SetParameter(param);
    param = new G4UIparameter("E", 'd', true);
    param->SetDefaultValue(0.0);
    ionCmd->SetParameter(param);
    param = new G4UIparameter("flb", 'c', true);
    param->SetDefaultValue("noFloat");
    param->SetParameterCandidates("noFloat X Y Z U V W R S T A B C D E");
    ionCmd->SetParameter(param);

    // set initial value to ConeParticleGun
    fParticleGun->SetParticleDefinition(G4Geantino::Geantino());
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.0, 0.0, 0.0));
    fParticleGun->SetParticleEnergy(1.0 * GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0.0 * cm, 0.0 * cm, 0.0 * cm));
    fParticleGun->SetParticleTime(0.0 * ns);
}

ConeParticleGunMessenger::~ConeParticleGunMessenger()
{
    delete listCmd;
    delete particleCmd;
    delete directionCmd;
    delete energyCmd;
    delete momCmd;
    delete momAmpCmd;
    delete positionCmd;
    delete timeCmd;
    delete polCmd;
    delete numberCmd;
    delete ionCmd;
    delete gunDirectory;
}

void ConeParticleGunMessenger::SetNewValue(G4UIcommand *command, G4String newValues)
{
    G4ExceptionDescription ed;
    if (command == listCmd) {
        particleTable->DumpTable();
    } else if (command == particleCmd) {
        if (newValues == "ion") {
            fShootIon = true;
        } else {
            fShootIon = false;
            G4ParticleDefinition *pd = particleTable->FindParticle(newValues);
            if (pd != 0) {
                fParticleGun->SetParticleDefinition(pd);
            } else {
                ed << "Particle [" << newValues << "] is not found.";
                command->CommandFailed(ed);
            }
        }

    } else if (command == directionCmd) { fParticleGun->SetParticleMomentumDirection(directionCmd->GetNew3VectorValue(newValues)); }
    else if (command == energyCmd) { fParticleGun->SetParticleEnergy(energyCmd->GetNewDoubleValue(newValues)); }
    else if (command == momCmd) { fParticleGun->SetParticleMomentum(momCmd->GetNew3VectorValue(newValues)); }
    else if (command == momAmpCmd) { fParticleGun->SetParticleMomentum(momAmpCmd->GetNewDoubleValue(newValues)); }
    else if (command == positionCmd) { fParticleGun->SetParticlePosition(positionCmd->GetNew3VectorValue(newValues)); }
    else if (command == timeCmd) { fParticleGun->SetParticleTime(timeCmd->GetNewDoubleValue(newValues)); }
    else if (command == polCmd) { fParticleGun->SetParticlePolarization(polCmd->GetNew3VectorValue(newValues)); }
    else if (command == numberCmd) { fParticleGun->SetNumberOfParticles(numberCmd->GetNewIntValue(newValues)); }
    else if (command == coneAngleStdDevCmd) { fParticleGun->SetConeAngleStdDev(timeCmd->GetNewDoubleValue(newValues)); }
    else if (command == energyStdDevCmd) { fParticleGun->SetParticleEnergyStdDev(timeCmd->GetNewDoubleValue(newValues)); }
    else if (command == positionStdDevCmd) { fParticleGun->SetParticlePositionStdDev(momCmd->GetNew3VectorValue(newValues)); }
    else if (command == ionCmd) {
        if (fShootIon) {
            IonCommand(newValues);
        } else {
            ed << "Set /gun/particle to ion before using /gun/ion command";
            command->CommandFailed(ed);
        }
    }
}

G4String ConeParticleGunMessenger::GetCurrentValue(G4UIcommand *command)
{
    G4String cv;

    if (command == directionCmd) { cv = directionCmd->ConvertToString(fParticleGun->GetParticleMomentumDirection()); }
    else if (command == particleCmd) { cv = fParticleGun->GetParticleDefinition()->GetParticleName(); }
    else if (command == energyCmd) {
        G4double ene = fParticleGun->GetParticleEnergy();
        if (ene == 0.) { G4cerr << " ConeParticleGun:  was defined in terms of momentum." << G4endl; }
        else { cv = energyCmd->ConvertToString(ene, "GeV"); }
    } else if (command == momCmd || command == momAmpCmd) {
        G4double mom = fParticleGun->GetParticleMomentum();
        if (mom == 0.) { G4cerr << " ConeParticleGun:  was defined in terms of kinetic energy." << G4endl; }
        else {
            if (command == momCmd) { cv = momCmd->ConvertToString(mom * (fParticleGun->GetParticleMomentumDirection()), "GeV"); }
            else { cv = momAmpCmd->ConvertToString(mom, "GeV"); }
        }
    } else if (command == positionCmd) { cv = positionCmd->ConvertToString(fParticleGun->GetParticlePosition(), "cm"); }
    else if (command == timeCmd) { cv = timeCmd->ConvertToString(fParticleGun->GetParticleTime(), "ns"); }
    else if (command == polCmd) { cv = polCmd->ConvertToString(fParticleGun->GetParticlePolarization()); }
    else if (command == numberCmd) { cv = numberCmd->ConvertToString(fParticleGun->GetNumberOfParticles()); }
    else if (command == ionCmd) {
        if (fShootIon) {
            cv = ItoS(fAtomicNumber) + " " + ItoS(fAtomicMass) + " ";
            cv += ItoS(fIonCharge);
        } else {
            cv = "";
        }
    }
    return cv;
}

#include "G4IonTable.hh"

void ConeParticleGunMessenger::IonCommand(G4String newValues)
{
    G4Tokenizer next(newValues);
    // check argument
    fAtomicNumber = StoI(next());
    fAtomicMass = StoI(next());
    fIonCharge = fAtomicNumber;
    fIonExciteEnergy = 0.0;
    fIonFloatingLevelBase = '\0';
    G4String sQ = next();
    if (!(sQ.isNull())) {
        if (StoI(sQ) >= 0)
            fIonCharge = StoI(sQ);

        sQ = next();
        if (!(sQ.isNull())) {
            fIonExciteEnergy = StoD(sQ) * keV;

            sQ = next();
            if (sQ.isNull() || sQ == "noFloat") { fIonFloatingLevelBase = '\0'; }
            else { fIonFloatingLevelBase = sQ[(size_t) 0]; }
        }
    }
    G4ParticleDefinition *ion = 0;
    ion = G4IonTable::GetIonTable()->GetIon(fAtomicNumber, fAtomicMass, fIonExciteEnergy, fIonFloatingLevelBase);
    if (ion == 0) {
        G4ExceptionDescription ed;
        ed << "Ion with Z=" << fAtomicNumber;
        ed << " A=" << fAtomicMass << "is not defined";
        ionCmd->CommandFailed(ed);
    } else {
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(fIonCharge * eplus);
    }
}

