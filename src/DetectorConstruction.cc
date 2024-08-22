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
  G4Material* g4matB = nist->FindOrBuildMaterial("G4_B");

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

  G4double poszBWindow = dWellpDz - dBoAlpDz;
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
    dHolderpDz,
    0,
    2*CLHEP::pi);

  G4double poszHolder = dWellpDz - dHolderpDz - 2 * dBoAlpDz;
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

  // Set HPGe detector as scoring volume
  //
  fScoringVolume = logicGe;



  G4VisAttributes* visGe = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.2));
  G4VisAttributes* visair = new G4VisAttributes(G4Colour(0.3,0.5,0.3,0.4));
  G4VisAttributes* visAl = new G4VisAttributes(G4Colour(0.,0.,0.5,0.5));
  G4VisAttributes* visDl = new G4VisAttributes(G4Colour(0.5,0.,0.,0.5));
  logicGe -> SetVisAttributes(visGe);
  logicWell -> SetVisAttributes(visair);
  logicWindow -> SetVisAttributes(visAl);
  logicBWindow -> SetVisAttributes(visAl);
  logicHolder -> SetVisAttributes(visAl);
  logicDeadlayer -> SetVisAttributes(visDl);
  logicBDeadlayer -> SetVisAttributes(visDl);

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
