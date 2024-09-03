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
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "SizeConstant.hh"

#include "G4VisAttributes.hh"

#include <CLHEP/Units/PhysicalConstants.h>

namespace B1
{
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* g4matAir = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* g4matGe = nist->FindOrBuildMaterial("G4_Ge");
  G4Material* g4matAl = nist->FindOrBuildMaterial("G4_Al");
  G4Material* g4matCu = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* g4matFe = nist->FindOrBuildMaterial("G4_Fe");

  // Envelope parameters
  //
  G4double env_sizeXY = 4 * dGepRMax, env_sizeZ = 6 * dGepDz;
  G4Material* env_mat = g4matAir;

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = g4matAir;

  auto solidWorld = new G4Box("World",                           // its name
    0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
    world_mat,                                       // its material
    "World");                                        // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                           // at (0,0,0)
    logicWorld,                                // its logical volume
    "World",                                   // its name
    nullptr,                                   // its mother  volume
    false,                                     // no boolean operation
    0,                                         // copy number
    checkOverlaps);                            // overlaps checking

  //
  // Envelope
  //
  auto solidEnv = new G4Box("Envelope",                    // its name
    0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);  // its size

  auto logicEnv = new G4LogicalVolume(solidEnv,  // its solid
    env_mat,                                     // its material
    "Envelope");                                 // its name

  auto physEnv = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),          // at (0,0,0)
    logicEnv,                 // its logical volume
    "Envelope",               // its name
    logicWorld,               // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking


  //
  // HPGe detector tub without Well
  //
  G4Material* Ge_mat = g4matGe;
  G4ThreeVector posGe = G4ThreeVector(0, 0, dGepDz);

  // Trapezoid shape
  auto solidGe = new G4Tubs("Ge",
    0,
    dGepRMax,
    dGepDz,
    0,
    2*CLHEP::pi);

  auto logicGe = new G4LogicalVolume(solidGe,  // its solid
  Ge_mat,                                        // its material
  "Ge");                                         // its name

  auto physGe = new G4PVPlacement(nullptr,  // no rotation
    posGe,                     // at position
    logicGe,              // its logical volume
    "Ge",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  // G4cout << "flagggg:" << dWellpRMax << G4endl;
  
  // Air Well of HPGe detector
  
  G4Material* Well_mat = g4matAir;

  // Trapezoid shape
  auto solidWell = new G4Tubs("Well",
    0,
    dWellpRMax,
    dWellpDz,
    0,
    2*CLHEP::pi);

  G4double poszWell = dWellpDz - dGepDz;
  G4ThreeVector posWell = G4ThreeVector(0, 0, poszWell);

  auto logicWell = new G4LogicalVolume(solidWell,  // its solid
  Well_mat,                                        // its material
  "Well");                                         // its name

  auto physWell = new G4PVPlacement(nullptr,  // no rotation
    posWell,                     // at position
    logicWell,              // its logical volume
    "Well",                 // its name
    logicGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  // Al Window of HPGe detector
  
  G4Material* Window_mat = g4matAl;

  auto solidWindow = new G4Tubs("Window",
    dTAlpRMin,
    dTAlpRMax,
    dTAlpDz,
    0,
    2*CLHEP::pi);

  G4double poszWindow = dTAlpDz - dWellpDz;
  G4ThreeVector posWindow = G4ThreeVector(0, 0, poszWindow);

  auto logicWindow = new G4LogicalVolume(solidWindow,  // its solid
  Window_mat,                                        // its material
  "Window");                                         // its name

  auto physWindow = new G4PVPlacement(nullptr,  // no rotation
    posWindow,                     // at position
    logicWindow,              // its logical volume
    "Window",                 // its name
    logicWell,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  auto solidBWindow = new G4Tubs("BWindow",
    0,
    dBoAlpRMax,
    dBoAlpDz,
    0,
    2*CLHEP::pi);

  G4double poszBWindow = dTAlpDz - dWellpDz + dTAlpDz + dBoAlpDz;
  G4ThreeVector posBWindow = G4ThreeVector(0, 0, poszBWindow);

  auto logicBWindow = new G4LogicalVolume(solidBWindow,  // its solid
  Window_mat,                                        // its material
  "BWindow");                                         // its name

  auto physBWindow = new G4PVPlacement(nullptr,  // no rotation
    posBWindow,                     // at position
    logicBWindow,              // its logical volume
    "BWindow",                 // its name
    logicWell,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking



  // Al placeholder of Target
  G4double dHolderpRMin = 0;
  G4double dHolderpRMax = 15 / 2.0 * CLHEP::mm;
  auto solidHolder = new G4Tubs("Holder",
    dHolderpRMin,
    dHolderpRMax,
    dAlHolderpDz,
    0,
    2*CLHEP::pi);

  G4double poszHolder = dTAlpDz - dWellpDz + dTAlpDz - dAlHolderpDz;
  G4ThreeVector posHolder = G4ThreeVector(0, 0, poszHolder);

  auto logicHolder = new G4LogicalVolume(solidHolder,  // its solid
  Window_mat,                                        // its material
  "Holder");                                         // its name

  auto physHolder = new G4PVPlacement(nullptr,  // no rotation
    posHolder,                     // at position
    logicHolder,              // its logical volume
    "Holder",                 // its name
    logicWell,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking
  // const bool sourceflag = true;

  #if 0
  // Fe source holder of Target
  G4double dSourceHolderpRMin = 0;
  G4double dSourceHolderpRMax = 11 / 2.0 * CLHEP::mm;
  auto solidSourceHolder = new G4Tubs("SourceHolder",
    dSourceHolderpRMin,
    dSourceHolderpRMax,
    dSourceHolderpDz,
    0,
    2*CLHEP::pi);

  G4double poszSourceHolder = dTAlpDz - dWellpDz + dTAlpDz - 2 * dAlHolderpDz - dSourceHolderpDz;
  G4ThreeVector posSourceHolder = G4ThreeVector(0, 0, poszSourceHolder);
  G4Material* SourceHolder_mat = g4matFe;
  auto logicSourceHolder = new G4LogicalVolume(solidSourceHolder,  // its solid
  SourceHolder_mat,                                        // its material
  "SourceHolder");                                         // its name

  auto physSourceHolder = new G4PVPlacement(nullptr,  // no rotation
    posSourceHolder,                     // at position
    logicSourceHolder,              // its logical volume
    "SourceHolder",                 // its name
    logicWell,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  #endif

  // Ge Deadlayer
  G4double dDeadlayerpRMin = dWellpRMax;
  G4double dDeadlayerpRMax = dWellpRMax + dBDeadlayerpDz * 2;
  G4double dDeadlayerpDz = dWellpDz;
  auto solidDeadlayer = new G4Tubs("Deadlayer",
    dDeadlayerpRMin,
    dDeadlayerpRMax,
    dDeadlayerpDz,
    0,
    2*CLHEP::pi);

  auto logicDeadlayer = new G4LogicalVolume(solidDeadlayer,  // its solid
  Ge_mat,                                        // its material
  "Deadlayer");                                         // its name

  auto physDeadlayer = new G4PVPlacement(nullptr,  // no rotation
    posWell,                     // at position
    logicDeadlayer,              // its logical volume
    "Deadlayer",                 // its name
    logicGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  G4double dBDeadlayerpRMax = dWellpRMax + dBDeadlayerpDz * 2;
  // G4double dBDeadlayerpDz = 0.3 / 2 * CLHEP::um;
  auto solidBDeadlayer = new G4Tubs("BDeadlayer",
    0,
    dBDeadlayerpRMax,
    dBDeadlayerpDz,
    0,
    2*CLHEP::pi);

  auto logicBDeadlayer = new G4LogicalVolume(solidBDeadlayer,  // its solid
  Ge_mat,                                        // its material
  "BDeadlayer");                                         // its name

  G4double poszBDeadlayer = 2 * dWellpDz - dGepDz + dBDeadlayerpDz;
  G4ThreeVector posBDeadlayer = G4ThreeVector(0, 0, poszBDeadlayer);
  
  auto physBDeadlayer = new G4PVPlacement(nullptr,  // no rotation
    posBDeadlayer,                     // at position
    logicBDeadlayer,              // its logical volume
    "BDeadlayer",                 // its name
    logicGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  auto solidoutupDeadlayer = new G4Tubs("outupDeadlayer",
    dDeadlayerpRMax,
    dGepRMax,
    dBDeadlayerpDz,
    0,
    2*CLHEP::pi);
  
  G4double poszoutupDeadlayer = - dGepDz + dBDeadlayerpDz;
  G4ThreeVector posoutupDeadlayer = G4ThreeVector(0, 0, poszoutupDeadlayer);

  auto logicoutupDeadlayer = new G4LogicalVolume(solidoutupDeadlayer,  // its solid
    Ge_mat,                                        // its material
    "outupDeadlayer");                                         // its name
  
  auto physoutupDeadlayer = new G4PVPlacement(nullptr,  // no rotation
    posoutupDeadlayer,                     // at position
    logicoutupDeadlayer,              // its logical volume
    "outupDeadlayer",                 // its name
    logicGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  auto solidoutTDeadlayer = new G4Tubs("outTDeadlayer",
    dGepRMax - 2 * dBDeadlayerpDz,
    dGepRMax,
    dGepDz - dBDeadlayerpDz * 2,
    0,
    2*CLHEP::pi);
  
  G4ThreeVector posoutTDeadlayer = G4ThreeVector(0, 0, 0);

  auto logicoutTDeadlayer = new G4LogicalVolume(solidoutTDeadlayer,  // its solid
    Ge_mat,                                        // its material
    "outTDeadlayer");                                         // its name
  
  auto physoutTDeadlayer = new G4PVPlacement(nullptr,  // no rotation
    posoutTDeadlayer,                     // at position
    logicoutTDeadlayer,              // its logical volume
    "outTDeadlayer",                 // its name
    logicGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  auto solidoutBoDeadlayer = new G4Tubs("outBoDeadlayer",
    0,
    dGepRMax,
    dBDeadlayerpDz,
    0,
    2*CLHEP::pi);
  
  G4double poszoutBoDeadlayer = dGepDz - dBDeadlayerpDz;
  G4ThreeVector posoutBoDeadlayer = G4ThreeVector(0, 0, poszoutBoDeadlayer);

  auto logicoutBoDeadlayer = new G4LogicalVolume(solidoutBoDeadlayer,  // its solid
    Ge_mat,                                        // its material
    "outBoDeadlayer");                                         // its name
  
  auto physoutBoDeadlayer = new G4PVPlacement(nullptr,  // no rotation
    posoutBoDeadlayer,                     // at position
    logicoutBoDeadlayer,              // its logical volume
    "outBoDeadlayer",                 // its name
    logicGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upTWindow
  auto solidupTWindow = new G4Tubs("upTWindow",
    dTAlpRMin,
    dTAlpRMax,
    dupTAlpDz,
    0,
    2*CLHEP::pi);

  G4double poszupTWindow = -dupTAlpDz;
  G4ThreeVector posupTWindow = G4ThreeVector(0, 0, poszupTWindow);

  auto logicupTWindow = new G4LogicalVolume(solidupTWindow,  // its solid
  Window_mat,                                        // its material
  "upTWindow");                                         // its name

  auto physupTWindow = new G4PVPlacement(nullptr,  // no rotation
    posupTWindow,                     // at position
    logicupTWindow,              // its logical volume
    "upTWindow",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upBoWindow
  auto solidupBoWindow = new G4Tubs("upBoWindow",
    dupBoAlpRMin,
    dupBoAlpRMax,
    dupBoAlpDz,
    0,
    2*CLHEP::pi);

  G4double poszupBoWindow = - 2 * dupTAlpDz + dupBoAlpDz;
  G4ThreeVector posupBoWindow = G4ThreeVector(0, 0, poszupBoWindow);

  auto logicupBoWindow = new G4LogicalVolume(solidupBoWindow,  // its solid
  Window_mat,                                        // its material
  "upBoWindow");                                         // its name

  auto physupBoWindow = new G4PVPlacement(nullptr,  // no rotation
    posupBoWindow,                     // at position
    logicupBoWindow,              // its logical volume
    "upBoWindow",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upCoCup
  auto solidupCoCup = new G4Tubs("upCoCup",
    dupCupRMin,
    dupCupRMax,
    dupCupDz,
    0,
    2*CLHEP::pi);
  
  G4double poszupCoCup = - dupCupGeDistance - dupCupDz;
  G4ThreeVector posupCoCup = G4ThreeVector(0, 0, poszupCoCup);

  auto logicupCoCup = new G4LogicalVolume(solidupCoCup,  // its solid
    g4matCu,                                        // its material
    "upCoCup");                                         // its name
  
  auto physupCoCup = new G4PVPlacement(nullptr,  // no rotation
    posupCoCup,                     // at position
    logicupCoCup,              // its logical volume
    "upCoCup",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //TCoCup
  auto solidTCoCup = new G4Tubs("TCoCup",
    dTCupRMin,
    dTCupRMax,
    dTCupDz,
    0,
    2*CLHEP::pi);
  
  G4double poszTCoCup = dTCupDz - dupCupGeDistance - dCupCuthickness;
  G4ThreeVector posTCoCup = G4ThreeVector(0, 0, poszTCoCup);

  auto logicTCoCup = new G4LogicalVolume(solidTCoCup,  // its solid
    g4matCu,                                        // its material
    "TCoCup");                                         // its name
  
  auto physTCoCup = new G4PVPlacement(nullptr,  // no rotation
    posTCoCup,                     // at position
    logicTCoCup,              // its logical volume
    "TCoCup",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking
  
  //BoCoCup
  auto solidBoCoCup = new G4Tubs("BoCoCup",
    0,
    dupCupRMax,
    dupCupDz,
    0,
    2*CLHEP::pi);
  
  G4double poszBoCoCup = dGepDz * 2 + dupCupDz;
  G4ThreeVector posBoCoCup = G4ThreeVector(0, 0, poszBoCoCup);

  auto logicBoCoCup = new G4LogicalVolume(solidBoCoCup,  // its solid
    g4matCu,                                        // its material
    "BoCoCup");                                         // its name
  
  auto physBoCoCup = new G4PVPlacement(nullptr,  // no rotation
    posBoCoCup,                     // at position
    logicBoCoCup,              // its logical volume
    "BoCoCup",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upCoEndcup
  auto solidupCoEndcup = new G4Tubs("upCoEndcup",
    dupEndcupRMin,
    dupEndcupRMax,
    dupEndcupDz,
    0,
    2*CLHEP::pi);

  G4double poszupCoEndcup = poszupBoWindow;
  G4ThreeVector posupCoEndcup = G4ThreeVector(0, 0, poszupCoEndcup);

  auto logicupCoEndcup = new G4LogicalVolume(solidupCoEndcup,  // its solid
    g4matCu,                                        // its material
    "upCoEndcup");                                         // its name

  auto physupCoEndcup = new G4PVPlacement(nullptr,  // no rotation
    posupCoEndcup,                     // at position
    logicupCoEndcup,              // its logical volume
    "upCoEndcup",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking




  // Set HPGe detector as scoring volume
  //
  fScoringVolume = logicGe;



  G4VisAttributes* visGe = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.2));
  G4VisAttributes* visair = new G4VisAttributes(G4Colour(0.3,0.5,0.3,0.4));
  G4VisAttributes* visAl = new G4VisAttributes(G4Colour(0.,0.,0.5,0.5));
  G4VisAttributes* visDl = new G4VisAttributes(G4Colour(0.5,0.,0.,0.5));
  G4VisAttributes* visCu = new G4VisAttributes(G4Colour(0.5,0.5,0.,0.5));
  logicGe -> SetVisAttributes(visGe);
  logicWell -> SetVisAttributes(visGe);
  logicWindow -> SetVisAttributes(visAl);
  logicBWindow -> SetVisAttributes(visAl);
  logicHolder -> SetVisAttributes(visAl);
  logicDeadlayer -> SetVisAttributes(visDl);
  logicBDeadlayer -> SetVisAttributes(visDl);
  logicoutupDeadlayer -> SetVisAttributes(visDl);
  logicoutTDeadlayer -> SetVisAttributes(visDl);
  logicoutBoDeadlayer -> SetVisAttributes(visDl);
  logicupBoWindow -> SetVisAttributes(visAl);
  logicupTWindow -> SetVisAttributes(visAl);
  logicupCoCup -> SetVisAttributes(visCu);
  logicTCoCup -> SetVisAttributes(visCu);
  logicBoCoCup -> SetVisAttributes(visCu);

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
