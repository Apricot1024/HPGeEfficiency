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

#include "G4GDMLParser.hh"

void ExportGeometryToGDML(const G4VPhysicalVolume* worldVolume, const std::string& filename) {
    G4GDMLParser parser;
    parser.Write(filename, worldVolume);
}

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
  G4Material* g4matPb = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* g4matCd = nist->FindOrBuildMaterial("G4_Cd");
  G4Material* g4matTa = nist->FindOrBuildMaterial("G4_Ta");

  // Envelope parameters
  //
  G4double env_sizeXY = 20 * dGepRMax, env_sizeZ = 40 * dGepDz;
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

  #if 1
  // Fe source holder of Target
  G4double dSourceHolderpRMin = 0;
  G4double dSourceHolderpRMax = 13.7 / 2.0 * CLHEP::mm;
  auto solidSourceHolder = new G4Tubs("SourceHolder",
    dSourceHolderpRMin,
    dSourceHolderpRMax,
    dSourceHolderpDz,
    0,
    2*CLHEP::pi);

  G4double poszSourceHolder = dTAlpDz - dWellpDz + dTAlpDz - 2 * dAlHolderpDz - dSourceHolderpDz;
  G4ThreeVector posSourceHolder = G4ThreeVector(0, 0, poszSourceHolder);
  G4Material* SourceHolder_mat = g4matTa;
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

  std::cout<< "rmaxcout" << dWellpRMax << std::endl;
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

  //upCuCup
  auto solidupCuCup = new G4Tubs("upCuCup",
    dupCupRMin,
    dupCupRMax,
    dupCupDz,
    0,
    2*CLHEP::pi);
  
  G4double poszupCuCup = - dupCupGeDistance - dupCupDz;
  G4ThreeVector posupCuCup = G4ThreeVector(0, 0, poszupCuCup);

  auto logicupCuCup = new G4LogicalVolume(solidupCuCup,  // its solid
    g4matCu,                                        // its material
    "upCuCup");                                         // its name
  
  auto physupCuCup = new G4PVPlacement(nullptr,  // no rotation
    posupCuCup,                     // at position
    logicupCuCup,              // its logical volume
    "upCuCup",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //TCuCup
  auto solidTCuCup = new G4Tubs("TCuCup",
    dTCupRMin,
    dTCupRMax,
    dTCupDz,
    0,
    2*CLHEP::pi);
  
  G4double poszTCuCup = dTCupDz - dupCupGeDistance - dCupCuthickness;
  G4ThreeVector posTCuCup = G4ThreeVector(0, 0, poszTCuCup);

  auto logicTCuCup = new G4LogicalVolume(solidTCuCup,  // its solid
    g4matCu,                                        // its material
    "TCuCup");                                         // its name
  
  auto physTCuCup = new G4PVPlacement(nullptr,  // no rotation
    posTCuCup,                     // at position
    logicTCuCup,              // its logical volume
    "TCuCup",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking
  
  //BoCuCup
  auto solidBoCuCup = new G4Tubs("BoCuCup",
    0,
    dupCupRMax,
    dupCupDz,
    0,
    2*CLHEP::pi);
  
  G4double poszBoCuCup = dGepDz * 2 + dupCupDz;
  G4ThreeVector posBoCuCup = G4ThreeVector(0, 0, poszBoCuCup);

  auto logicBoCuCup = new G4LogicalVolume(solidBoCuCup,  // its solid
    g4matCu,                                        // its material
    "BoCuCup");                                         // its name
  
  auto physBoCuCup = new G4PVPlacement(nullptr,  // no rotation
    posBoCuCup,                     // at position
    logicBoCuCup,              // its logical volume
    "BoCuCup",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upCuEndcap
  auto solidupCuEndcap = new G4Tubs("upCuEndcap",
    dupEndcapRMin,
    dupEndcapRMax,
    dupEndcapDz,
    0,
    2*CLHEP::pi);

  G4double poszupCuEndcap = poszupBoWindow;
  G4ThreeVector posupCuEndcap = G4ThreeVector(0, 0, poszupCuEndcap);

  auto logicupCuEndcap = new G4LogicalVolume(solidupCuEndcap,  // its solid
    g4matCu,                                        // its material
    "upCuEndcap");                                         // its name

  auto physupCuEndcap = new G4PVPlacement(nullptr,  // no rotation
    posupCuEndcap,                     // at position
    logicupCuEndcap,              // its logical volume
    "upCuEndcap",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //TCuEndcap
  auto solidTCuEndcap = new G4Tubs("TCuEndcap",
    dTEndcapRMin,
    dTEndcapRMax,
    dTEndcapDz,
    0,
    2*CLHEP::pi);

  G4double poszTCuEndcap = dTEndcapDz - (0 - poszupBoWindow - dupEndcapDz);
  G4ThreeVector posTCuEndcap = G4ThreeVector(0, 0, poszTCuEndcap);

  auto logicTCuEndcap = new G4LogicalVolume(solidTCuEndcap,  // its solid
    g4matCu,                                        // its material
    "TCuEndcap");                                         // its name

  auto physTCuEndcap = new G4PVPlacement(nullptr,  // no rotation
    posTCuEndcap,                     // at position
    logicTCuEndcap,              // its logical volume
    "TCuEndcap",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking


  //BoCuEndcap
  auto solidBoCuEndcap = new G4Tubs("BoCuEndcap",
    dBoEndcapRMin,
    dBoEndcapRMax,
    dBoEndcapDz,
    0,
    2*CLHEP::pi);

  G4double poszBoCuEndcap = dTEndcapDz + poszTCuEndcap + dBoEndcapDz;
  G4ThreeVector posBoCuEndcap = G4ThreeVector(0, 0, poszBoCuEndcap);

  auto logicBoCuEndcap = new G4LogicalVolume(solidBoCuEndcap,  // its solid
    g4matCu,                                        // its material
    "BoCuEndcap");                                         // its name

  auto physBoCuEndcap = new G4PVPlacement(nullptr,  // no rotation
    posBoCuEndcap,                     // at position
    logicBoCuEndcap,              // its logical volume
    "BoCuEndcap",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //TOFCushield
  auto solidTOFCushield = new G4Tubs("TOFCushield",
    dTOFCushieldRMin,
    dTOFCushieldRMax,
    dTOFCushieldDz,
    0,
    2*CLHEP::pi);
  
  G4double poszTOFCushield = 10 * CLHEP::cm;
  G4ThreeVector posTOFCushield = G4ThreeVector(0, 0, poszTOFCushield);

  auto logicTOFCushield = new G4LogicalVolume(solidTOFCushield,  // its solid
    g4matCu,                                        // its material
    "TOFCushield");                                         // its name

  auto physTOFCushield = new G4PVPlacement(nullptr,  // no rotation
    posTOFCushield,                     // at position
    logicTOFCushield,              // its logical volume
    "TOFCushield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upOFCushield
  auto solidupOFCushield = new G4Tubs("upOFCushield",
    dupOFCushieldRMin,
    // 0,
    dupOFCushieldRMax,
    dupOFCushieldDz,
    0,
    2*CLHEP::pi);

  G4double poszupOFCushield = poszTOFCushield - dTOFCushieldDz - dupOFCushieldDz;
  G4ThreeVector posupOFCushield = G4ThreeVector(0, 0, poszupOFCushield);

  auto logicupOFCushield = new G4LogicalVolume(solidupOFCushield,  // its solid
    g4matCu,                                        // its material
    "upOFCushield");                                         // its name

  auto physupOFCushield = new G4PVPlacement(nullptr,  // no rotation
    posupOFCushield,                     // at position
    logicupOFCushield,              // its logical volume
    "upOFCushield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //BoOFCushield
  auto solidBoOFCushield = new G4Tubs("BoOFCushield",
    dBoOFCushieldRMin,
    dBoOFCushieldRMax,
    dBoOFCushieldDz,
    0,
    2*CLHEP::pi);

  G4double poszBoOFCushield = poszTOFCushield + dTOFCushieldDz + dBoOFCushieldDz;
  G4ThreeVector posBoOFCushield = G4ThreeVector(0, 0, poszBoOFCushield);

  auto logicBoOFCushield = new G4LogicalVolume(solidBoOFCushield,  // its solid
    g4matCu,                                        // its material
    "BoOFCushield");                                         // its name

  auto physBoOFCushield = new G4PVPlacement(nullptr,  // no rotation
    posBoOFCushield,                     // at position
    logicBoOFCushield,              // its logical volume
    "BoOFCushield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking


  //TLBPbshield
  auto solidTLBPbshield = new G4Tubs("TLBPbshield",
    dTLBPbshieldRMin,
    dTLBPbshieldRMax,
    dTLBPbshieldDz,
    0,
    2*CLHEP::pi);

  G4double poszTLBPbshield = 10 * CLHEP::cm;
  G4ThreeVector posTLBPbshield = G4ThreeVector(0, 0, poszTLBPbshield);

  auto logicTLBPbshield = new G4LogicalVolume(solidTLBPbshield,  // its solid
    g4matPb,                                        // its material
    "TLBPbshield");                                         // its name

  auto physTLBPbshield = new G4PVPlacement(nullptr,  // no rotation
    posTLBPbshield,                     // at position
    logicTLBPbshield,              // its logical volume
    "TLBPbshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upLBPbshield
  auto solidupLBPbshield = new G4Tubs("upLBPbshield",
    dupLBPbshieldRMin,
    dupLBPbshieldRMax,
    dupLBPbshieldDz,
    0,
    2*CLHEP::pi);

  G4double poszupLBPbshield = poszTLBPbshield - dTLBPbshieldDz - dupLBPbshieldDz;
  G4ThreeVector posupLBPbshield = G4ThreeVector(0, 0, poszupLBPbshield);

  auto logicupLBPbshield = new G4LogicalVolume(solidupLBPbshield,  // its solid
    g4matPb,                                        // its material
    "upLBPbshield");                                         // its name

  auto physupLBPbshield = new G4PVPlacement(nullptr,  // no rotation
    posupLBPbshield,                     // at position
    logicupLBPbshield,              // its logical volume
    "upLBPbshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  
  //BoLBPbshield
  auto solidBoLBPbshield = new G4Tubs("BoLBPbshield",
    dBoLBPbshieldRMin,
    dBoLBPbshieldRMax,
    dBoLBPbshieldDz,
    0,
    2*CLHEP::pi);

  G4double poszBoLBPbshield = poszTLBPbshield + dTLBPbshieldDz + dBoLBPbshieldDz;
  G4ThreeVector posBoLBPbshield = G4ThreeVector(0, 0, poszBoLBPbshield);

  auto logicBoLBPbshield = new G4LogicalVolume(solidBoLBPbshield,  // its solid
    g4matPb,                                        // its material
    "BoLBPbshield");                                         // its name

  auto physBoLBPbshield = new G4PVPlacement(nullptr,  // no rotation
    posBoLBPbshield,                     // at position
    logicBoLBPbshield,              // its logical volume
    "BoLBPbshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking
  
  //TCdshield
  auto solidTCdshield = new G4Tubs("TCdshield",
    dTCdshieldRMin,
    dTCdshieldRMax,
    dTCdshieldDz,
    0,
    2*CLHEP::pi);

  G4double poszTCdshield = 10 * CLHEP::cm;
  G4ThreeVector posTCdshield = G4ThreeVector(0, 0, poszTCdshield);

  auto logicTCdshield = new G4LogicalVolume(solidTCdshield,  // its solid
    g4matCd,                                        // its material
    "TCdshield");                                         // its name

  auto physTCdshield = new G4PVPlacement(nullptr,  // no rotation
    posTCdshield,                     // at position
    logicTCdshield,              // its logical volume
    "TCdshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upCdshield
  auto solidupCdshield = new G4Tubs("upCdshield",
    dupCdshieldRMin,
    dupCdshieldRMax,
    dupCdshieldDz,
    0,
    2*CLHEP::pi);

  G4double poszupCdshield = poszTCdshield - dTCdshieldDz - dupCdshieldDz;
  G4ThreeVector posupCdshield = G4ThreeVector(0, 0, poszupCdshield);

  auto logicupCdshield = new G4LogicalVolume(solidupCdshield,  // its solid
    g4matCd,                                        // its material
    "upCdshield");                                         // its name

  auto physupCdshield = new G4PVPlacement(nullptr,  // no rotation
    posupCdshield,                     // at position
    logicupCdshield,              // its logical volume
    "upCdshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //BoCdshield
  auto solidBoCdshield = new G4Tubs("BoCdshield",
    dBoCdshieldRMin,
    dBoCdshieldRMax,
    dBoCdshieldDz,
    0,
    2*CLHEP::pi);
  
  G4double poszBoCdshield = poszTCdshield + dTCdshieldDz + dBoCdshieldDz;
  G4ThreeVector posBoCdshield = G4ThreeVector(0, 0, poszBoCdshield);

  auto logicBoCdshield = new G4LogicalVolume(solidBoCdshield,  // its solid
    g4matCd,                                        // its material
    "BoCdshield");                                         // its name

  auto physBoCdshield = new G4PVPlacement(nullptr,  // no rotation
    posBoCdshield,                     // at position
    logicBoCdshield,              // its logical volume
    "BoCdshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking


  //TPbshield
  auto solidTPbshield = new G4Tubs("TPbshield",
    dTPbshieldRMin,
    dTPbshieldRMax,
    dTPbshieldDz,
    0,
    2*CLHEP::pi);

  G4double poszTPbshield = 10 * CLHEP::cm;
  G4ThreeVector posTPbshield = G4ThreeVector(0, 0, poszTPbshield);

  auto logicTPbshield = new G4LogicalVolume(solidTPbshield,  // its solid
    g4matPb,                                        // its material
    "TPbshield");                                         // its name
  
  auto physTPbshield = new G4PVPlacement(nullptr,  // no rotation
    posTPbshield,                     // at position
    logicTPbshield,              // its logical volume
    "TPbshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //upPbshield
  auto solidupPbshield = new G4Tubs("upPbshield",
    dupPbshieldRMin,
    dupPbshieldRMax,
    dupPbshieldDz,
    0,
    2*CLHEP::pi);

  G4double poszupPbshield = poszTPbshield - dTPbshieldDz - dupPbshieldDz;
  G4ThreeVector posupPbshield = G4ThreeVector(0, 0, poszupPbshield);

  auto logicupPbshield = new G4LogicalVolume(solidupPbshield,  // its solid
    g4matPb,                                        // its material
    "upPbshield");                                         // its name

  auto physupPbshield = new G4PVPlacement(nullptr,  // no rotation
    posupPbshield,                     // at position
    logicupPbshield,              // its logical volume
    "upPbshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //BoPbshield
  auto solidBoPbshield = new G4Tubs("BoPbshield",
    dBoPbshieldRMin,
    dBoPbshieldRMax,
    dBoPbshieldDz,
    0,
    2*CLHEP::pi);

  G4double poszBoPbshield = poszTPbshield + dTPbshieldDz + dBoPbshieldDz;
  G4ThreeVector posBoPbshield = G4ThreeVector(0, 0, poszBoPbshield);

  auto logicBoPbshield = new G4LogicalVolume(solidBoPbshield,  // its solid
    g4matPb,                                        // its material
    "BoPbshield");                                         // its name

  auto physBoPbshield = new G4PVPlacement(nullptr,  // no rotation
    posBoPbshield,                     // at position
    logicBoPbshield,              // its logical volume
    "BoPbshield",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  







  // Set HPGe detector as scoring volume
  //
  fScoringVolume = logicGe;



  G4VisAttributes* visGe = new G4VisAttributes(G4Colour(0.52, 0.61, 0.68, 0.2));
  G4VisAttributes* visair = new G4VisAttributes(G4Colour(0.68, 0.85, 0.90, 0.2));
  G4VisAttributes* visAl = new G4VisAttributes(G4Colour(0.86, 0.86, 0.86, 0.3));
  G4VisAttributes* visDl = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.15));
  G4VisAttributes* visCu = new G4VisAttributes(G4Colour(0.72, 0.45, 0.2, 0.15));
  G4VisAttributes* visCu1 = new G4VisAttributes(G4Colour(0.72, 0.45, 0.2, 0.15));
  G4VisAttributes* visPb = new G4VisAttributes(G4Colour(0.27, 0.27, 0.31, 0.4));
  G4VisAttributes* visPb1 = new G4VisAttributes(G4Colour(0.27, 0.27, 0.31, 0.6));
  G4VisAttributes* visCd = new G4VisAttributes(G4Colour(0.78, 0.78, 0.82, 0.5));
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
  logicupCuCup -> SetVisAttributes(visCu);
  logicTCuCup -> SetVisAttributes(visCu);
  logicBoCuCup -> SetVisAttributes(visCu);
  logicupCuEndcap -> SetVisAttributes(visCu1);
  logicTCuEndcap -> SetVisAttributes(visCu1);
  logicBoCuEndcap -> SetVisAttributes(visCu1);
  logicTOFCushield -> SetVisAttributes(visCu1);
  logicupOFCushield -> SetVisAttributes(visCu1);
  logicBoOFCushield -> SetVisAttributes(visCu1);
  logicTLBPbshield -> SetVisAttributes(visPb);
  logicupLBPbshield -> SetVisAttributes(visPb);
  logicBoLBPbshield -> SetVisAttributes(visPb);
  logicTCdshield -> SetVisAttributes(visCd);
  logicupCdshield -> SetVisAttributes(visCd);
  logicBoCdshield -> SetVisAttributes(visCd);
  logicTPbshield -> SetVisAttributes(visPb1);
  logicupPbshield -> SetVisAttributes(visPb1);
  logicBoPbshield -> SetVisAttributes(visPb1);


  // ExportGeometryToGDML(physWorld, "geometry.gdml");

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  
}
