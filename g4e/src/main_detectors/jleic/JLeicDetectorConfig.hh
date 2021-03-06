//
// Created by yulia on 6/6/19.
//

#ifndef G4E_JLeicDetectorParameters_HH
#define G4E_JLeicDetectorParameters_HH

// -------beampipe---------------
#include "ir_Beampipe/ir_Beampipe.hh"


//------- Barrel ----
#include "cb_Solenoid/cb_Solenoid.hh"

#include "cb_VTX/cb_VTX.hh"
#include "cb_SiDISCS/cb_SiDISCS.hh"     // Central Barrel -Si Discs along the beamline
#include "cb_CTD/cb_CTD.hh"
#include "cb_DIRC/cb_DIRC.hh"
#include "cb_EMCAL/cb_EMCAL.hh"
#include "cb_HCAL/cb_HCAL.hh"


//---- Rear electron ----

#include "ce_GEM/ce_GEM.hh"
#include "ce_MRICH/ce_MRICH.hh"
#include "ce_EMCAL/ce_EMCAL.hh"

#include "ffe_CPOL/ffe_CPOL.hh"
#include "ffe_LUMI/ffe_LUMI.hh"
#include "ffe_LOWQ2/ffe_LOWQ2.hh"

//------ Forward Hadron -----
#include "ci_GEM/ci_GEM.hh"
#include "ci_DRICH/ci_DRICH.hh"
#include "ci_TRD/ci_TRD.hh"
#include "ci_EMCAL/ci_EMCAL.hh"
#include "ci_HCAL/ci_HCAL.hh"

#include "fi_D1TRK/fi_D1TRK.hh"
#include "fi_D1EMCAL/fi_D1EMCAL.hh"

#include "ffi_D2TRK/ffi_D2TRK.hh"  // Far-forward Ion - Silicon discs in D2 magnet
#include "ffi_ZDC/ffi_ZDC.hh"         // Far-forward Ion   - HCAL ZDC
#include "ffi_RPOT_D2/ffi_RPOT_D2.hh"         // Far-forward Ion   -Roman Pots before D3
#include "ffi_RPOT_D3/ffi_RPOT_D3.hh"         // Far-forward Ion   -Roman Pots after D3

struct JLeicDetectorConfig {
    int ElectronBeamEnergy =10;
    int IonBeamEnergy=200;
    std::string BeamlineName="erhic";

    struct World_Config {

        double ShiftVTX = 40. * cm;
        double SizeR = 300. * cm;
        double SizeZ = 50000. * cm;
    } World;

    struct ci_Endcap_Config {
        double RIn = 20. * cm;
        double ROut = NAN;
        double SizeZ = 250 * cm;
        double ShiftZ = 0. * cm;
        double PosX = 0. * cm;
        double PosZ = 0. * cm;
    } ci_Endcap;

    struct ce_Endcap_Config {
        double RIn = 20 * cm;
        double SizeZ = 62 * cm;
        double PosZ = NAN;
        double ROut = NAN;
    } ce_Endcap;


    //------------ BAREL-----
    cb_Solenoid_Config cb_Solenoid;


    cb_VTX_Config   cb_VTX;
    cb_SiDISCS_Config   cb_SiDISCS;

    cb_CTD_Config   cb_CTD;
    cb_DIRC_Config  cb_DIRC;
    cb_EMCAL_Config cb_EMCAL;
    cb_HCAL_Config  cb_HCAL;
    //------------E-ENDCAP-----

    ce_GEM_Config  ce_GEM;
    ce_MRICH_Config  ce_MRICH;
    ce_EMCAL_Config  ce_EMCAL;

    //------------Far-Forward-Electron-----
    ffe_CPOL_Config ffe_CPOL;
    ffe_LUMI_Config ffe_LUMI;
    ffe_LOWQ2_Config ffe_LOWQ2;

    //------------H-ENDCAP-----
    ci_GEM_Config  ci_GEM;
    ci_DRICH_Config  ci_DRICH;
    ci_TRD_Config  ci_TRD;
    ci_EMCAL_Config  ci_EMCAL;
    ci_HCAL_Config  ci_HCAL;

    //------------Far-Forward-Ion-----
    fi_D1TRK_Config  fi_D1TRK;
    fi_D1EMCAL_Config  fi_D1EMCAL;

      // --- Tracking in D2 -----
     ffi_D2TRK_Config ffi_D2TRK;
    //---------------HCAL -ZDC  and Roman Pots-------------------------
    ffi_ZDC_Config  ffi_ZDC;
    ffi_RPOT_D2_Config  ffi_RPOT_D2;
    ffi_RPOT_D3_Config  ffi_RPOT_D3;

    //---------------Beampipe------------------------
    ir_Beampipe_Config ir_Beampipe;
} ;


#endif //G4E_JLeicDetectorParameters_HH
