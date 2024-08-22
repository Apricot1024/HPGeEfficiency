
#include "G4UnitsTable.hh"
#include <CLHEP/Units/PhysicalConstants.h>
#include <cmath>

const G4double dGepRMax = 77.3 / 2.0 * CLHEP::mm;
const G4double dGepDz = 75 / 2.0 * CLHEP::mm;
const G4double dWellpDz = 40 / 2.0 * CLHEP::mm;
// G4double tempR = sqrt((CLHEP::pi * dGepRMax * dGepRMax * dGepDz * 2 - 349000) / (dWellpDz * 2 * CLHEP::pi));
// const G4double dWellpRMax = sqrt((CLHEP::pi * dGepRMax * dGepRMax * dGepDz * 2 - 349000) / (dWellpDz * 2 * CLHEP::pi)) - 1;
const G4double dWellpRMax = 34.5 / 2 * CLHEP::mm;
const G4double dTAlpRMin = 15.5 / 2 * CLHEP::mm;
const G4double dTAlpRMax = dTAlpRMin + 0.75 * CLHEP::mm;
const G4double dTAlpDz = 39/2.0 * CLHEP::mm;

const G4double dBoAlpRMax = dTAlpRMax;
const G4double dBoAlpDz = 0.75/2.0 * CLHEP::mm;

const G4double dBDeadlayerpDz = 0.1 / 2 * CLHEP::um;


const G4double dHolderpDz = 0.09999999999999998 / 2.0 * CLHEP::mm;
