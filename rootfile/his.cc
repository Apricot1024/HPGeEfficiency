#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TF1.h>
#include <TROOT.h>
#include <TChain.h>

using namespace std;

void his(){
    TH1D *spe = new TH1D("spe","gamma 3MeV",400,0.01,3.1);  
    TCanvas *c1 = new TCanvas("c1","c1");

    TFile *ipf = new TFile("ana3000.root");

        if (ipf->IsZombie()) {
            cout << "Error opening file!" << endl;
            exit(-1);
        }
        // ipf->cd();
    TTree *ipt=(TTree*)ipf->Get("Ntuple");

    double fEdep;

    ipt->SetBranchAddress("fEdep", &fEdep);

    Long64_t nentries = ipt->GetEntries();
    for(Long64_t jentry = 0; jentry < nentries; jentry++) {
    
        ipt->GetEntry(jentry);

        spe -> Fill(fEdep);

    }
    
    spe -> Draw();
    c1->Draw();
}