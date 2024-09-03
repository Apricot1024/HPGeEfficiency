
#include "G4UnitsTable.hh"
#include <CLHEP/Units/PhysicalConstants.h>
#include <cmath>

const G4double dGepRMax = 79.3 / 2.0 * CLHEP::mm;
const G4double dGepDz = 79.5 / 2.0 * CLHEP::mm; //const
const G4double dWellpDz = 50 / 2.0 * CLHEP::mm; //const
// G4double tempR = sqrt((CLHEP::pi * dGepRMax * dGepRMax * dGepDz * 2 - 349000) / (dWellpDz * 2 * CLHEP::pi));
const G4double dWellpRMax = sqrt((CLHEP::pi * dGepRMax * dGepRMax * dGepDz * 2 - 349000) / (dWellpDz * 2 * CLHEP::pi));
// const G4double dWellpRMax = 34.5 / 2 * CLHEP::mm;

const G4double dAlthickness = 0.65 * CLHEP::mm;
const G4double dTAlpRMin = 15.5 / 2 * CLHEP::mm;
const G4double dTAlpRMax = dTAlpRMin + dAlthickness;//const
const G4double dTAlpDz = 40/2.0;

const G4double dBoAlpRMax = dTAlpRMax;
const G4double dBoAlpDz = dAlthickness/2.0;

const G4double dBDeadlayerpDz = 0.6 / 2.0 * CLHEP::um;


const G4double dAlHolderpDz = 0.25  / 2.0 * CLHEP::mm; //const
const G4double dSourceHolderpDz = 1 / 2.0 * CLHEP::mm;


const G4double dupTAlpDz = 10 / 2.0 * CLHEP::mm;

const G4double dupBoAlpDz = dAlthickness/2.0;
const G4double dupBoAlpRMin = dTAlpRMax;
const G4double dupBoAlpRMax = dTAlpRMax + 5.0 * CLHEP::mm;

const G4double dCupCuthickness = 0.8 * CLHEP::mm;
const G4double dupCupGeDistance = 5 * CLHEP::mm;
const G4double dupCupRMin = dWellpRMax + 1 * CLHEP::mm;
const G4double dupCupRMax = dGepRMax;
const G4double dupCupDz = dCupCuthickness / 2.0;

const G4double dTCupRMin = dGepRMax;
const G4double dTCupRMax = dTCupRMin + dCupCuthickness;//const
const G4double dTCupDz = dGepDz + dupCupGeDistance / 2.0 + dCupCuthickness;

const G4double dEndcupCuthickness = 0.8 * CLHEP::mm;
const G4double dupEndcupRMin = dupBoAlpRMax;
const G4double dupEndcupRMax = 95.0 / 2 * CLHEP::mm;
const G4double dupEndcupDz = dEndcupCuthickness / 2.0;

