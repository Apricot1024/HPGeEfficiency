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
/// \file B1/src/EventAction.cc
/// \brief Implementation of the B1::EventAction class

#include "EventAction.hh"
#include "RunAction.hh"
// #include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "HistoManager.hh"

#include "Randomize.hh"

#include "G4UnitsTable.hh"


G4double particleEnergy = 15*CLHEP::keV;
namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction, HistoManager* histo)
: fRunAction(runAction),fHistoManager(histo)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
  // //accumulates statistic
  // //
  // fRunAct->FillPerEvent(fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap);

  // //fill histograms
  // //
  // fHistoManager->FillHisto(0, fEnergyAbs);
  // fHistoManager->FillHisto(1, fEnergyGap);
  // fHistoManager->FillHisto(2, fTrackLAbs);
  // fHistoManager->FillHisto(3, fTrackLGap);

  // //fill ntuple
  // //
  // fHistoManager->FillNtuple(fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap);


  // const auto generatorAction = static_cast<const PrimaryGeneratorAction*>(
  // G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  // if (generatorAction)
  // {
  //   const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
  //   G4double particleEnergy = particleGun->GetParticleEnergy();
  // }
  // G4cout << "energy of this particle is "<< particleEnergy <<G4endl;
  // accumulate statistics in run action
  // //高斯展宽


  if(fEdep>10*CLHEP::keV){
    double fwhm = 1.2*CLHEP::keV + 0.0000009091 * fEdep;
    // double sigma=(0.001+0.05086*sqrt(0.030486*fEdep*fEdep+fEdep))/2.35482;
    double sigma = fwhm / 2.35482;
    fEdep= G4RandGauss::shoot(0,1)*sigma+fEdep;
    // if(fEdep>10*CLHEP::keV)
    fRunAction->AddEdep(fEdep);
    // G4int eventID = fpEventManager->GetConstCurrentEvent()->GetEventID();
    // G4cout << "EventID is "<< eventID <<","<<"deposit energy of this event is "<< G4BestUnit(fEdep,"Energy") <<G4endl;
  }

  if (fEdep >= 0.001 * CLHEP::keV)
  {
    // fHistoManager->FillHisto(0, fEdep);
    fHistoManager->FillNtuple(fEdep);

  }

  // fHistoManager->FillHisto(0, fEdep);
  // fHistoManager->FillNtuple(fEdep);
  if (fEdep >= particleEnergy-0.1*CLHEP::keV)
  {
    fRunAction->Addfepn(1);
  }
}
  
  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
