#include <TCanvas.h>
#include <TH2.h>
#include <TF1.h>
#include <TROOT.h>
#include <TChain.h>
#include <TH1.h> // Include the TH1 header
#include <TFile.h>

using namespace std;

void toHis()
{
    // int numa = 10000000;
    string path;
    path = "AnaEx01.root";
    const char* c_path = path.c_str();
    TFile *ipf = new TFile(c_path, "UPDATE");

    if (ipf->IsZombie()) {
    cout << "Error opening file!" << endl;
    exit(-1);
    }

    // ipf->Delete("h;1");
    // ipf->Delete("h;2");

    TTree *ipt=(TTree*)ipf->Get("Ntuple");

    double fEdep;

    ipt->SetBranchAddress("fEdep", &fEdep);

    // Create a histogram
    double beginE = 0;
    double endE = 3500;
    TH1F *h = new TH1F("h", "Energy Deposition", (endE - beginE)/0.2, beginE, endE);

    Long64_t nentries = ipt->GetEntries();
    // double d = static_cast<double>(numa) / 1000;
    for(Long64_t jentry = 0; jentry < nentries; jentry++) {
    
        ipt->GetEntry(jentry);
        
    
        h->Fill(fEdep*1000); // Fill the histogram
    
    }

    h->Write(); // Write the histogram to file
    ipf->Close();
}