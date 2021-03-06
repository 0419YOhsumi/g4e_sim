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
// $Id: JLeicEventAction.hh,v 1.3 2006-06-29 16:37:51 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef JLeicEventAction_h
#define JLeicEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "RootFlatIO.hh"
#include <G4GenericMessenger.hh>


class JLeicEventActionMessenger;
class JLeicHistogramManager;


class JLeicEventAction : public G4UserEventAction
{
public:
    JLeicEventAction(g4e::RootFlatIO *, JLeicHistogramManager*);

    ~JLeicEventAction() = default;

public:
    void BeginOfEventAction(const G4Event *) override;

    void EndOfEventAction(const G4Event *) override;

    void SetVerbose(G4int level) { fVerbose = level; }    /// 0 = nothing, 1 = some, 2 = debug
    G4int GetVerbose() { return fVerbose; }                /// 0 = nothing, 1 = some, 2 = debug


    void SetPrintModulo(G4int val) { fPrintModulo = val; }
    G4int GetPrintModulo() { return fPrintModulo; }

    //----- EVENT STRUCTURE -----
    g4e::RootFlatIO *mRootEventsOut = nullptr;

private:
    G4int calorimeterCollID;
    G4int vertexCollID;
    JLeicEventActionMessenger *eventMessenger;
    JLeicHistogramManager* fHistos;


    G4int fVerbose;
    G4double nstep, nstepCharged, nstepNeutral;
    G4double Nch, Nne, GamDE;
    G4double NE, NP;
    G4double Transmitted, Reflected;

    G4String drawFlag;
    G4int fPrintModulo;
    G4GenericMessenger fMessenger;
};

#endif

    
