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

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "BeagleGeneratorMessenger.hh"
#include "BeagleGenerator.hh"


g4e::BeagleGeneratorMessenger::BeagleGeneratorMessenger(BeagleGenerator *interface)
        : fBeagleInterface(interface)
{
    fDirectoryCmd = new G4UIdirectory("/generator/beagle/");
    fDirectoryCmd->SetGuidance("Reading Beagle event from an Ascii file");

    fVerboseCmd = new G4UIcmdWithAnInteger("/generator/beagle/verbose", this);
    fVerboseCmd->SetGuidance("Set verbose level");
    fVerboseCmd->SetParameterName("verboseLevel", false, false);
    fVerboseCmd->SetRange("verboseLevel>=0 && verboseLevel<=2");

    fOpenCmd = new G4UIcmdWithAString("/generator/beagle/open", this);
    fOpenCmd->SetGuidance("(re)open data file (Beagle Ascii format)");
    fOpenCmd->SetParameterName("input ascii file", true, true);
}


g4e::BeagleGeneratorMessenger::~BeagleGeneratorMessenger() {
    delete fVerboseCmd;
    delete fOpenCmd;
    delete fDirectoryCmd;
}


void g4e::BeagleGeneratorMessenger::SetNewValue(G4UIcommand *command, G4String newValues) {
    // verbosity level
    if (command == fVerboseCmd) {
        int level = G4UIcmdWithAnInteger::GetNewIntValue(newValues);
        fBeagleInterface->SetVerboseLevel(level);
    }

    // open command
    else if (command == fOpenCmd) {
        fBeagleInterface->Open(newValues);
    }
}


G4String g4e::BeagleGeneratorMessenger::GetCurrentValue(G4UIcommand *command) {
    G4String value;
    if (command == fVerboseCmd) {
        value = G4UIcmdWithAnInteger::ConvertToString(fBeagleInterface->GetVerboseLevel());
    } else if (command == fOpenCmd) {
        value = fBeagleInterface->GetFileName();
    }
    return value;
}
