
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

const G4double dEndcapCuthickness = 0.8 * CLHEP::mm;
const G4double dupEndcapRMin = dupBoAlpRMax;
const G4double dupEndcapRMax = 95.0 / 2 * CLHEP::mm;
const G4double dupEndcapDz = dEndcapCuthickness / 2.0;

const G4double dBoEndcapRMin = 0;
const G4double dBoEndcapRMax = dupEndcapRMax;
const G4double dBoEndcapDz = dupEndcapDz;

const G4double dTEndcapRMax = dupEndcapRMax;//const
const G4double dTEndcapRMin = dTEndcapRMax - dEndcapCuthickness;
const G4double dTEndcapDz = 20 / 2.0 * CLHEP::cm - dupEndcapDz - dBoEndcapDz;

const G4double dOFCuThickness = 5.0 * CLHEP::cm;
const G4double dLBPbThickness = 5.0 * CLHEP::cm;
const G4double dCdThickness = 1.0 * CLHEP::cm;
const G4double dPbThickness = 15.0 * CLHEP::cm;

const G4double dTOFCushieldRMin = 12.0 / 2 * CLHEP::cm;
const G4double dTOFCushieldRMax = dTOFCushieldRMin + dOFCuThickness;
const G4double dTOFCushieldDz = 50.0 / 2 * CLHEP::cm - dOFCuThickness;

const G4double dupOFCushieldRMin = 0;
const G4double dupOFCushieldRMax = dTOFCushieldRMax;
const G4double dupOFCushieldDz = dOFCuThickness / 2.0;

const G4double dBoOFCushieldRMin = 0;
const G4double dBoOFCushieldRMax = dTOFCushieldRMax;
const G4double dBoOFCushieldDz = dupOFCushieldDz;

const G4double dTLBPbshieldRMin = dTOFCushieldRMax;
const G4double dTLBPbshieldRMax = dTLBPbshieldRMin + dLBPbThickness;
const G4double dTLBPbshieldDz = dTOFCushieldDz + dOFCuThickness;

const G4double dupLBPbshieldRMin = 0;
const G4double dupLBPbshieldRMax = dTLBPbshieldRMax;
const G4double dupLBPbshieldDz = dLBPbThickness / 2.0;

const G4double dBoLBPbshieldRMin = 0;
const G4double dBoLBPbshieldRMax = dTLBPbshieldRMax;
const G4double dBoLBPbshieldDz = dupLBPbshieldDz;

const G4double dTCdshieldRMin = dTLBPbshieldRMax;
const G4double dTCdshieldRMax = dTCdshieldRMin + dCdThickness;
const G4double dTCdshieldDz = dTLBPbshieldDz + dLBPbThickness;

const G4double dupCdshieldRMin = 0;
const G4double dupCdshieldRMax = dTCdshieldRMax;
const G4double dupCdshieldDz = dCdThickness / 2.0;

const G4double dBoCdshieldRMin = 0;
const G4double dBoCdshieldRMax = dTCdshieldRMax;
const G4double dBoCdshieldDz = dupCdshieldDz;

const G4double dTPbshieldRMin = dTCdshieldRMax;
const G4double dTPbshieldRMax = dTPbshieldRMin + dPbThickness;
const G4double dTPbshieldDz = dTCdshieldDz + dCdThickness;

const G4double dupPbshieldRMin = 0;
const G4double dupPbshieldRMax = dTPbshieldRMax;
const G4double dupPbshieldDz = dPbThickness / 2.0;

const G4double dBoPbshieldRMin = 0;
const G4double dBoPbshieldRMax = dTPbshieldRMax;
const G4double dBoPbshieldDz = dupPbshieldDz;