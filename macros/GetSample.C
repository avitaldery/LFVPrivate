#include "LFVPrivate/SimData.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void GetSample(TString infile,TString outfile, int repetitions)
{
	const int kMaxTrack = 10;	// maximal number of particles in a single event. @@@
	
	
	int evt = -999;	// probably a flag
	
	
	// definitions for the braches in the tree. some are scalars (# of particles prob) and some are vectors (info. for each particle)
	int nPhoton = 0;
	float photonPt[kMaxTrack];
	float photonEta[kMaxTrack];
	float photonPhi[kMaxTrack];
	
	int nElectron = 0;
	float electronPt[kMaxTrack];
	float electronEta[kMaxTrack];
	float electronPhi[kMaxTrack];
	int electronQ[kMaxTrack];
	int electronTag[kMaxTrack];
	float electronCal02[kMaxTrack];
	float electronCal03[kMaxTrack];
	float electronCal04[kMaxTrack];
	float electronTrk02[kMaxTrack];
	float electronTrk03[kMaxTrack];
	float electronTrk04[kMaxTrack];
	float electronSign[kMaxTrack];
	
	int nMuon = 0;
	float muonPt[kMaxTrack];
	float muonEta[kMaxTrack];
	float muonPhi[kMaxTrack];
	int muonQ[kMaxTrack];
	int muonTag[kMaxTrack];
	float muonCal02[kMaxTrack];
	float muonCal03[kMaxTrack];
	float muonCal04[kMaxTrack];
	float muonTrk02[kMaxTrack];
	float muonTrk03[kMaxTrack];
	float muonTrk04[kMaxTrack];
	float muonSign[kMaxTrack];
	
	int nTau = 0;
	float tauPt[kMaxTrack];
	float tauEta[kMaxTrack];
	float tauPhi[kMaxTrack];
	int tauQ[kMaxTrack];
	int tauTag[kMaxTrack];
	float tauCal02[kMaxTrack];
	float tauCal03[kMaxTrack];
	float tauCal04[kMaxTrack];
	float tauTrk02[kMaxTrack];
	float tauTrk03[kMaxTrack];
	float tauTrk04[kMaxTrack];
	float tauSign[kMaxTrack];
	
	int nJet = 0;
	float jetPt[kMaxTrack];
	float jetEta[kMaxTrack];
	float jetPhi[kMaxTrack];
	int jetQ[kMaxTrack];
	int jetTag[kMaxTrack];
	float jetCal02[kMaxTrack];
	float jetCal03[kMaxTrack];
	float jetCal04[kMaxTrack];
	float jetTrk02[kMaxTrack];
	float jetTrk03[kMaxTrack];
	float jetTrk04[kMaxTrack];
	
	float metPt = -999.;
	float metEta = -999.;
	float metPhi = -999.;

	
	TFile f(outfile,"recreate");	// the file and tree
	TTree *t = new TTree("t","Reconst ntuple");
	
	
	// adding branches:
	// t->Branch(Branch name in the browser, pointer to the variable, variable name)
	
	t->Branch("evt",&evt,"evt/I");

	t->Branch("nPhoton",&nPhoton,"nPhoton/I");
	t->Branch("photonPt",photonPt,"photonPt[nPhoton]/F");
	t->Branch("photonEta",photonEta,"photonEta[nPhoton]/F");
	t->Branch("photonPhi",photonPhi,"photonPhi[nPhoton]/F");

	t->Branch("nElectron",&nElectron,"nElectron/I");
	t->Branch("electronPt",electronPt,"electronPt[nElectron]/F");
	t->Branch("electronEta",electronEta,"electronEta[nElectron]/F");
	t->Branch("electronPhi",electronPhi,"electronPhi[nElectron]/F");
	t->Branch("electronQ",electronQ,"electronQ[nElectron]/I");
	t->Branch("electronTag",electronTag,"electronTag[nElectron]/I");
	t->Branch("electronCal02",electronCal02,"electronCal02[nElectron]/F");
	t->Branch("electronCal03",electronCal03,"electronCal03[nElectron]/F");
	t->Branch("electronCal04",electronCal04,"electronCal04[nElectron]/F");
	t->Branch("electronTrk02",electronTrk02,"electronTrk02[nElectron]/F");
	t->Branch("electronTrk03",electronTrk03,"electronTrk03[nElectron]/F");
	t->Branch("electronTrk04",electronTrk04,"electronTrk04[nElectron]/F");
	t->Branch("electronSign",electronSign,"electronSign[nElectron]/F");
	
	t->Branch("nMuon",&nMuon,"nMuon/I");
	t->Branch("muonPt",muonPt,"muonPt[nMuon]/F");
	t->Branch("muonEta",muonEta,"muonEta[nMuon]/F");
	t->Branch("muonPhi",muonPhi,"muonPhi[nMuon]/F");
	t->Branch("muonQ",muonQ,"muonQ[nMuon]/I");
	t->Branch("muonTag",muonTag,"muonTag[nMuon]/I");
	t->Branch("muonCal02",muonCal02,"muonCal02[nMuon]/F");
	t->Branch("muonCal03",muonCal03,"muonCal03[nMuon]/F");
	t->Branch("muonCal04",muonCal04,"muonCal04[nMuon]/F");
	t->Branch("muonTrk02",muonTrk02,"muonTrk02[nMuon]/F");
	t->Branch("muonTrk03",muonTrk03,"muonTrk03[nMuon]/F");
	t->Branch("muonTrk04",muonTrk04,"muonTrk04[nMuon]/F");
	t->Branch("muonSign",muonSign,"muonSign[nMuon]/F");
	
	t->Branch("nTau",&nTau,"nTau/I");
	t->Branch("tauPt",tauPt,"tauPt[nTau]/F");
	t->Branch("tauEta",tauEta,"tauEta[nTau]/F");
	t->Branch("tauPhi",tauPhi,"tauPhi[nTau]/F");
	t->Branch("tauQ",tauQ,"tauQ[nTau]/I");
	t->Branch("tauTag",tauTag,"tauTag[nTau]/I");
	t->Branch("tauCal02",tauCal02,"tauCal02[nTau]/F");
	t->Branch("tauCal03",tauCal03,"tauCal03[nTau]/F");
	t->Branch("tauCal04",tauCal04,"tauCal04[nTau]/F");
	t->Branch("tauTrk02",tauTrk02,"tauTrk02[nTau]/F");
	t->Branch("tauTrk03",tauTrk03,"tauTrk03[nTau]/F");
	t->Branch("tauTrk04",tauTrk04,"tauTrk04[nTau]/F");
	t->Branch("tauSign",tauSign,"tauSign[nTau]/F");
	
	t->Branch("nJet",&nJet,"nJet/I");
	t->Branch("jetPt",jetPt,"jetPt[nJet]/F");
	t->Branch("jetEta",jetEta,"jetEta[nJet]/F");
	t->Branch("jetPhi",jetPhi,"jetPhi[nJet]/F");
	t->Branch("jetQ",jetQ,"jetQ[nJet]/I");
	t->Branch("jetTag",jetTag,"jetTag[nJet]/I");
	t->Branch("jetCal02",jetCal02,"jetCal02[nJet]/F");
	t->Branch("jetCal03",jetCal03,"jetCal03[nJet]/F");
	t->Branch("jetCal04",jetCal04,"jetCal04[nJet]/F");
	t->Branch("jetTrk02",jetTrk02,"jetTrk02[nJet]/F");
	t->Branch("jetTrk03",jetTrk03,"jetTrk03[nJet]/F");
	t->Branch("jetTrk04",jetTrk04,"jetTrk04[nJet]/F");
	
	t->Branch("metPt",&metPt,"metPt/F");
	t->Branch("metEta",&metEta,"metEta/F");
	t->Branch("metPhi",&metPhi,"metPhi/F");
	
	
	// This next part is taken from looper.
	
	TChain* chain = new TChain("t");
	chain->Add("../run/"+infile+"/t");
	TTree* tree = chain;
	
	SimData* data = new SimData(tree);

    if(data->fChain == 0) {
		cout << " fchain is empty" << endl;
	}
    Int_t nentries = Int_t(data->fChain->GetEntries());
    cout << " Reading data ..." << nentries << " in physics tree" << endl;

    Int_t nTen = nentries/10;
    Int_t nbytes = 0, nb = 0;

    float effMax = 0;

    for (Int_t jentry=0; jentry<nentries; jentry++) {

		Int_t ientry = data->LoadTree(jentry);
		if (ientry < 0) break;
		
		nb = data->fChain->GetEntry(jentry);
		nbytes += nb;
		
		if (nTen!=0) if (jentry%nTen==0) cout << " " << 10*(jentry/nTen) << "%-" <<flush;

		
		evt = data->evt;

		nPhoton = data->nPhoton;
		nElectron = data->nElectron;
		nMuon = data->nMuon;
		nTau = data->nTau;
		nJet = data->nJet;

//		cout<<"nElectron = "<<nElectron<<endl;

		for (int i = 0; i < kMaxTrack; i++) {

			if (data->sf_el_reco_eff[i] > effMax) effMax = data->sf_el_reco_eff[i];

			photonPt[i] = data->photonPt[i];
			photonEta[i] = data->photonEta[i];
			photonPhi[i] = data->photonPhi[i];
			
			electronPt[i] = data->electronPt[i];
			electronEta[i] = data->electronEta[i];
			electronPhi[i] = data->electronPhi[i];
			electronQ[i] = data->electronQ[i];
			electronTag[i] = data->electronTag[i];
			electronCal02[i] = data->electronCal02[i];
			electronCal03[i] = data->electronCal03[i];
			electronCal04[i] = data->electronCal04[i];
			electronTrk02[i] = data->electronTrk02[i];
			electronTrk03[i] = data->electronTrk03[i];
			electronTrk04[i] = data->electronTrk04[i];
			electronSign[i] = data->electronSign[i];
			
			muonPt[i] = data->muonPt[i];
			muonEta[i] = data->muonEta[i];
			muonPhi[i] = data->muonPhi[i];
			muonQ[i] = data->muonQ[i];
			muonTag[i] = data->muonTag[i];
			muonCal02[i] = data->muonCal02[i];
			muonCal03[i] = data->muonCal03[i];
			muonCal04[i] = data->muonCal04[i];
			muonTrk02[i] = data->muonTrk02[i];
			muonTrk03[i] = data->muonTrk03[i];
			muonTrk04[i] = data->muonTrk04[i];
			muonSign[i] = data->muonSign[i];

			tauPt[i] = data->tauPt[i];
			tauEta[i] = data->tauEta[i];
			tauPhi[i] = data->tauPhi[i];
			tauQ[i] = data->tauQ[i];
			tauTag[i] = data->tauTag[i];
			tauCal02[i] = data->tauCal02[i];
			tauCal03[i] = data->tauCal03[i];
			tauCal04[i] = data->tauCal04[i];
			tauTrk02[i] = data->tauTrk02[i];
			tauTrk03[i] = data->tauTrk03[i];
			tauTrk04[i] = data->tauTrk04[i];
			tauSign[i] = data->tauSign[i];
			
			jetPt[i] = data->jetPt[i];
			jetEta[i] = data->jetEta[i];
			jetPhi[i] = data->jetPhi[i];
			jetQ[i] = data->jetQ[i];
			jetTag[i] = data->jetTag[i];
			jetCal02[i] = data->jetCal02[i];
			jetCal03[i] = data->jetCal03[i];
			jetCal04[i] = data->jetCal04[i];
			jetTrk02[i] = data->jetTrk02[i];
			jetTrk03[i] = data->jetTrk03[i];
			jetTrk04[i] = data->jetTrk04[i];
		}

		metPt = data->metPt;
		metEta = data->metEta;
		metPhi = data->metPhi;


		if (repetitions > 0) {// placeholder for this: for (int i = 0; i < repetitions; i++) {

			// electron deletion
			int i_source = 0; // index that will run on the original data
			int i_dest = 0; // index that will run (and create) the new sparser data

			while (i_source < nElectron) {
//				cout<<"i= "<<i_source<<", sf_el = "<<data->sf_el_reco_eff[i_source]<<endl;
				if (float(rand())/RAND_MAX < data->sf_el_reco_eff[i_source]) { // @@@ manual due to bug. actual: data->sf_el_reco_eff[i_source]) { // if we don't throw the particle out
					// set all the necesary data:
					electronPt[i_dest] = data->electronPt[i_source];
					electronEta[i_dest] = data->electronEta[i_source];
					electronPhi[i_dest] = data->electronPhi[i_source];
					electronQ[i_dest] = data->electronQ[i_source];
					electronTag[i_dest] = data->electronTag[i_source];
					electronCal02[i_dest] = data->electronCal02[i_source];
					electronCal03[i_dest] = data->electronCal03[i_source];
					electronCal04[i_dest] = data->electronCal04[i_source];
					electronTrk02[i_dest] = data->electronTrk02[i_source];
					electronTrk03[i_dest] = data->electronTrk03[i_source];
					electronTrk04[i_dest] = data->electronTrk04[i_source];
					electronSign[i_dest] = data->electronSign[i_source];

					i_dest++; // go to the next index in the destination
				}
				i_source++; // it doesn't matter whether we used the original particle or not.
			}
			nElectron = i_dest; // update nParticle to the correct, sparse data.

			// muon deletion
			i_source = 0;
			i_dest = 0;
			while (i_source < nMuon) {
				if (float(rand())/RAND_MAX <  data->sf_mu_reco_eff[i_source]) { // @@@ manual due to bug. actual: data->sf_mu_reco_eff[i_source]) {

					muonPt[i_dest] = data->muonPt[i_source];
					muonEta[i_dest] = data->muonEta[i_source];
					muonPhi[i_dest] = data->muonPhi[i_source];
					muonQ[i_dest] = data->muonQ[i_source];
					muonTag[i_dest] = data->muonTag[i_source];
					muonCal02[i_dest] = data->muonCal02[i_source];
					muonCal03[i_dest] = data->muonCal03[i_source];
					muonCal04[i_dest] = data->muonCal04[i_source];
					muonTrk02[i_dest] = data->muonTrk02[i_source];
					muonTrk03[i_dest] = data->muonTrk03[i_source];
					muonTrk04[i_dest] = data->muonTrk04[i_source];
					muonSign[i_dest] = data->muonSign[i_source];

					i_dest++;
				}
				i_source++;
			}
			nMuon = i_dest;

			t->Fill();

		}

	}

	cout << "max: " << effMax << endl;

	f.cd();
	t->Write("",TObject::kOverwrite);
	
	
	delete data;
}
