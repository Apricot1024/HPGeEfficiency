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

#include <CLHEP/Units/PhysicalConstants.h>

namespace B1
{
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //user define material --vaccum
  //
  G4String name, symbol; // a=mass of a mole;
  G4double a, z, density; // z=mean number of protons;
  G4int iz, n; // iz=nb of protons in an isotope;
              // n=nb of nucleons in an isotope;
  G4int ncomponents, natoms;
  G4double abundance, fractionmass;
  G4double temperature, pressure;

  density = CLHEP::universe_mean_density; //from PhysicalConstants.h
  pressure = 1.e-19*pascal;
  temperature = 0.1*kelvin;
  new G4Material(name="Galactic", z=1., a=1.01*g/mole, density,
  kStateGas,temperature,pressure);

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 10*cm, env_sizeZ = 20*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("Galactic");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("Galactic");

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

  new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),          // at (0,0,0)
    logicEnv,                 // its logical volume
    "Envelope",               // its name
    logicWorld,               // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //
  // HPGe detector tub without hole
  //
  G4Material* HPGe_mat = nist->FindOrBuildMaterial("G4_Ge");
  G4ThreeVector posHPGe = G4ThreeVector(0, 0, 0);

  // Trapezoid shape
  G4double HPGe_pRMin = 0;
  G4double HPGe_pRMax = 79.3 / 2;
  G4double HPGe_pDz = 77 / 2;
  G4double HPGe_pSPhi = 0;
  G4double HPGe_pDPhi = 2*CLHEP::pi;
  auto solidHPGe = new G4Tubs("HPGe",
    HPGe_pRMin,
    HPGe_pRMax,
    HPGe_pDz,
    HPGe_pSPhi,
    HPGe_pDPhi);

  auto logicHPGe = new G4LogicalVolume(solidHPGe,  // its solid
  HPGe_mat,                                        // its material
  "HPGe");                                         // its name

  new G4PVPlacement(nullptr,  // no rotation
    posHPGe,                     // at position
    logicHPGe,              // its logical volume
    "HPGe",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  //
  // Hole of HPGe detector
  //
  G4Material* hole_mat = nist->FindOrBuildMaterial("G4_AIR");

  // Trapezoid shape
  G4double hole_pRMin = 0;
  G4double hole_pRMax = 15.5 / 2;
  G4double hole_pDz = 40 / 2;
  G4double hole_pSPhi = 0;
  G4double hole_pDPhi = 2*CLHEP::pi;
  auto solidhole = new G4Tubs("hole",
    hole_pRMin,
    hole_pRMax,
    hole_pDz,
    hole_pSPhi,
    hole_pDPhi);


  G4double poszhole = hole_pDz - HPGe_pDz;
  G4ThreeVector poshole = G4ThreeVector(0, 0, poszhole);

  auto logichole = new G4LogicalVolume(solidhole,  // its solid
  hole_mat,                                        // its material
  "hole");                                         // its name

  new G4PVPlacement(nullptr,  // no rotation
    poshole,                     // at position
    logichole,              // its logical volume
    "hole",                 // its name
    logicHPGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking


  // Dead Layer of detector
  G4double layerthick = 0.3*um;
  G4Material* deadLayer_mat = nist->FindOrBuildMaterial("G4_B");

  // Trapezoid shape
  G4double innerdeadlayerpRMin = hole_pRMax;
  G4double innerdeadlayerpRMax = hole_pRMax + layerthick;
  G4double innerdeadlayerpDz = hole_pDz;
  G4double innerdeadlayerpSPhi = 0;
  G4double innerdeadlayerpDPhi = 2*CLHEP::pi;
  auto solidinnerdeadlayer = new G4Tubs("innerDeadLayer",
        innerdeadlayerpRMin,
        innerdeadlayerpRMax,
        innerdeadlayerpDz,
        innerdeadlayerpSPhi,
        innerdeadlayerpDPhi);

  G4ThreeVector posinnerdeadlayer = poshole;
  auto logicinnerdeadlayer = new G4LogicalVolume(solidinnerdeadlayer,  // its solid
  deadLayer_mat,                                        // its material
  "innerdeadlayer");                                         // its name

  new G4PVPlacement(nullptr,  // no rotation
    posinnerdeadlayer,                     // at position
    logicinnerdeadlayer,              // its logical volume
    "innerdeadlayer",                 // its name
    logicHPGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking


  // Trapezoid shape
  G4double outerdeadlayerpRMin = HPGe_pRMax - layerthick;
  G4double outerdeadlayerpRMax = HPGe_pRMax;
  G4double outerdeadlayerpDz = HPGe_pDz;
  G4double outerdeadlayerpSPhi = 0;
  G4double outerdeadlayerpDPhi = 2*CLHEP::pi;
  auto solidouterdeadlayer = new G4Tubs("outerDeadLayer",
        outerdeadlayerpRMin,
        outerdeadlayerpRMax,
        outerdeadlayerpDz,
        outerdeadlayerpSPhi,
        outerdeadlayerpDPhi);

  G4ThreeVector posouterdeadlayer = posHPGe;

  auto logicouterdeadlayer = new G4LogicalVolume(solidouterdeadlayer,  // its solid
  deadLayer_mat,                                        // its material
  "outerdeadlayer");                                         // its name

  new G4PVPlacement(nullptr,  // no rotation
    posouterdeadlayer,                     // at position
    logicouterdeadlayer,              // its logical volume
    "outerdeadlayer",                 // its name
    logicHPGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

  // Trapezoid shape
  G4double upperdeadlayerpRMin = 0;
  G4double upperdeadlayerpRMax = hole_pRMax;
  G4double upperdeadlayerpDz = 0.5*layerthick;
  G4double upperdeadlayerpSPhi = 0;
  G4double upperdeadlayerpDPhi = 2*CLHEP::pi;
  auto solidupperdeadlayer = new G4Tubs("upperDeadLayer",
        upperdeadlayerpRMin,
        upperdeadlayerpRMax,
        upperdeadlayerpDz,
        upperdeadlayerpSPhi,
        upperdeadlayerpDPhi);

  G4double poszupperdeadlayer = 0.5*layerthick;
  G4ThreeVector posupperdeadlayer = G4ThreeVector(0, 0, poszupperdeadlayer);

  auto logicupperdeadlayer = new G4LogicalVolume(solidupperdeadlayer,  // its solid
  deadLayer_mat,                                        // its material
  "upperdeadlayer");                                         // its name

  new G4PVPlacement(nullptr,  // no rotation
    posupperdeadlayer,                     // at position
    logicupperdeadlayer,              // its logical volume
    "upperdeadlayer",                 // its name
    logicHPGe,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking


  //bottom deadlayer in the out of HPGe,which have low effect in out test
  //for time saving, i have not written the bottom dead layer


  // Set HPGe detector as scoring volume
  //
  fScoringVolume = logicHPGe;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
