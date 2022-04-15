//  Read MRTOF
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>


#include "TString.h"

#include "TH1F.h"

#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TRootCanvas.h"
#include "sstream"

#include <TThread.h>
#include <TGClient.h>
#include <pthread.h>
#include <TTree.h>
#include <TMath.h>
#include <TFile.h>

#include "readmrtof.h"

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#include<map>

using namespace std;
int pinit(char* ip, char* port){
    return 0;
}
int pstart(){
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc!=5) return 0;
    Int_t runno = atoi(argv[1]);
    cout<<runno<<endl;

    //! time maps
    std::multimap < Int_t,  MRTOFdata*> mrtofdatamap;
    std::multimap < Int_t,  MRTOFdata*>::iterator mrtofdatamap_it;

    std::multimap < Int_t,  BIGRIPSData*> bigripsdatamap;
    std::multimap < Int_t,  BIGRIPSData*>::iterator bigripsdatamap_it;


    TFile* bigripsfile = TFile::Open(argv[2]);
    TTree* treebigrips = (TTree*) bigripsfile->Get("tree");

    Int_t           RunNum;
    Long64_t        TSnew;
    Long64_t        TS;
    Double_t        TSm;
    Int_t           neve;
    Double_t        F3X;
    Double_t        F3A;
    Double_t        F3Y;
    Double_t        F3B;
    Double_t        F5X;
    Double_t        F5A;
    Double_t        F5Y;
    Double_t        F5B;
    Double_t        F7X;
    Double_t        F7A;
    Double_t        F7Y;
    Double_t        F7B;
    Double_t        F8X;
    Double_t        F8A;
    Double_t        F8Y;
    Double_t        F8B;
    Double_t        F9X;
    Double_t        F9A;
    Double_t        F9Y;
    Double_t        F9B;
    Double_t        F10X;
    Double_t        F10A;
    Double_t        F10Y;
    Double_t        F10B;
    Double_t        F11X;
    Double_t        F11A;
    Double_t        F11Y;
    Double_t        F11B;
    Double_t        F3PLA_TL_raw;
    Double_t        F3PLA_TR_raw;
    Double_t        F3PLA_TL;
    Double_t        F3PLA_TR;
    Double_t        F3PLA_T;
    Double_t        F7PLA_TL_raw;
    Double_t        F7PLA_TR_raw;
    Double_t        F7PLA_TL;
    Double_t        F7PLA_TR;
    Double_t        F7PLA_T;
    Double_t        F8PLA_TL_raw;
    Double_t        F8PLA_TR_raw;
    Double_t        F8PLA_TL;
    Double_t        F8PLA_TR;
    Double_t        F8PLA_T;
    Double_t        F11PLA_TL_raw;
    Double_t        F11PLA_TR_raw;
    Double_t        F11PLA_TL;
    Double_t        F11PLA_TR;
    Double_t        F11PLA_T;
    Double_t        F3PLA_QL_raw;
    Double_t        F3PLA_QR_raw;
    Double_t        F3PLA_Q_ave;
    Double_t        F7PLA_QL_raw;
    Double_t        F7PLA_QR_raw;
    Double_t        F7PLA_Q_ave;
    Double_t        F8PLA_QL_raw;
    Double_t        F8PLA_QR_raw;
    Double_t        F8PLA_Q_ave;
    Double_t        F11PLA_QL_raw;
    Double_t        F11PLA_QR_raw;
    Double_t        F11PLA_Q_ave;
    Double_t        F7ICNumHit;
    Double_t        F7ICEnergySqSum;
    Double_t        F7ICEnergyAvSum;
    Double_t        F11ICNumHit;
    Double_t        F11ICEnergySqSum;
    Double_t        F11ICEnergyAvSum;
    Int_t           F11ICRawADC[8];
    Int_t           F11PlalongL;
    Int_t           F11PlalongR;
    Int_t           DegAng;
    Int_t           GCveto;
    Int_t           Clock10M;
    Int_t           SweepNo;
    Int_t           aval;
    Int_t           bval;
    Double_t        tof37;
    Double_t        tof811;
    Double_t        beta35;
    Double_t        beta57;
    Double_t        beta810;
    Double_t        beta1011;
    Double_t        Energy35;
    Double_t        Energy57;
    Double_t        Energy810;
    Double_t        Energy1011;
    Double_t        brho35;
    Double_t        brho57;
    Double_t        brho810;
    Double_t        brho1011;
    Double_t        zet35;
    Double_t        zet57;
    Double_t        zet37;
    Double_t        zet37_f11ic;
    Double_t        zet810;
    Double_t        zet1011;
    Double_t        zet811;
    Double_t        aoq35;
    Double_t        aoq57;
    Double_t        aoq37;
    Double_t        aoq810;
    Double_t        aoq1011;
    Double_t        aoq811;
    Double_t        zet35c;
    Double_t        zet57c;
    Double_t        zet37c;
    Double_t        zet37c_f11ic;
    Double_t        zet810c;
    Double_t        zet1011c;
    Double_t        zet811c;
    Double_t        aoq35c;
    Double_t        aoq57c;
    Double_t        aoq37c;
    Double_t        aoq810c;
    Double_t        aoq1011c;
    Double_t        aoq811c;
    Int_t           nclean;
    Int_t           Z;
    Int_t           A;
    Int_t           N;

    // Set branch addresses.
    treebigrips->SetBranchAddress("RunNum",&RunNum);
    treebigrips->SetBranchAddress("TSnew",&TSnew);
    treebigrips->SetBranchAddress("TS",&TS);
    treebigrips->SetBranchAddress("TSm",&TSm);
    treebigrips->SetBranchAddress("neve",&neve);
    treebigrips->SetBranchAddress("F3X",&F3X);
    treebigrips->SetBranchAddress("F3A",&F3A);
    treebigrips->SetBranchAddress("F3Y",&F3Y);
    treebigrips->SetBranchAddress("F3B",&F3B);
    treebigrips->SetBranchAddress("F5X",&F5X);
    treebigrips->SetBranchAddress("F5A",&F5A);
    treebigrips->SetBranchAddress("F5Y",&F5Y);
    treebigrips->SetBranchAddress("F5B",&F5B);
    treebigrips->SetBranchAddress("F7X",&F7X);
    treebigrips->SetBranchAddress("F7A",&F7A);
    treebigrips->SetBranchAddress("F7Y",&F7Y);
    treebigrips->SetBranchAddress("F7B",&F7B);
    treebigrips->SetBranchAddress("F8X",&F8X);
    treebigrips->SetBranchAddress("F8A",&F8A);
    treebigrips->SetBranchAddress("F8Y",&F8Y);
    treebigrips->SetBranchAddress("F8B",&F8B);
    treebigrips->SetBranchAddress("F9X",&F9X);
    treebigrips->SetBranchAddress("F9A",&F9A);
    treebigrips->SetBranchAddress("F9Y",&F9Y);
    treebigrips->SetBranchAddress("F9B",&F9B);
    treebigrips->SetBranchAddress("F10X",&F10X);
    treebigrips->SetBranchAddress("F10A",&F10A);
    treebigrips->SetBranchAddress("F10Y",&F10Y);
    treebigrips->SetBranchAddress("F10B",&F10B);
    treebigrips->SetBranchAddress("F11X",&F11X);
    treebigrips->SetBranchAddress("F11A",&F11A);
    treebigrips->SetBranchAddress("F11Y",&F11Y);
    treebigrips->SetBranchAddress("F11B",&F11B);
    treebigrips->SetBranchAddress("F3PLA_TL_raw",&F3PLA_TL_raw);
    treebigrips->SetBranchAddress("F3PLA_TR_raw",&F3PLA_TR_raw);
    treebigrips->SetBranchAddress("F3PLA_TL",&F3PLA_TL);
    treebigrips->SetBranchAddress("F3PLA_TR",&F3PLA_TR);
    treebigrips->SetBranchAddress("F3PLA_T",&F3PLA_T);
    treebigrips->SetBranchAddress("F7PLA_TL_raw",&F7PLA_TL_raw);
    treebigrips->SetBranchAddress("F7PLA_TR_raw",&F7PLA_TR_raw);
    treebigrips->SetBranchAddress("F7PLA_TL",&F7PLA_TL);
    treebigrips->SetBranchAddress("F7PLA_TR",&F7PLA_TR);
    treebigrips->SetBranchAddress("F7PLA_T",&F7PLA_T);
    treebigrips->SetBranchAddress("F8PLA_TL_raw",&F8PLA_TL_raw);
    treebigrips->SetBranchAddress("F8PLA_TR_raw",&F8PLA_TR_raw);
    treebigrips->SetBranchAddress("F8PLA_TL",&F8PLA_TL);
    treebigrips->SetBranchAddress("F8PLA_TR",&F8PLA_TR);
    treebigrips->SetBranchAddress("F8PLA_T",&F8PLA_T);
    treebigrips->SetBranchAddress("F11PLA_TL_raw",&F11PLA_TL_raw);
    treebigrips->SetBranchAddress("F11PLA_TR_raw",&F11PLA_TR_raw);
    treebigrips->SetBranchAddress("F11PLA_TL",&F11PLA_TL);
    treebigrips->SetBranchAddress("F11PLA_TR",&F11PLA_TR);
    treebigrips->SetBranchAddress("F11PLA_T",&F11PLA_T);
    treebigrips->SetBranchAddress("F3PLA_QL_raw",&F3PLA_QL_raw);
    treebigrips->SetBranchAddress("F3PLA_QR_raw",&F3PLA_QR_raw);
    treebigrips->SetBranchAddress("F3PLA_Q_ave",&F3PLA_Q_ave);
    treebigrips->SetBranchAddress("F7PLA_QL_raw",&F7PLA_QL_raw);
    treebigrips->SetBranchAddress("F7PLA_QR_raw",&F7PLA_QR_raw);
    treebigrips->SetBranchAddress("F7PLA_Q_ave",&F7PLA_Q_ave);
    treebigrips->SetBranchAddress("F8PLA_QL_raw",&F8PLA_QL_raw);
    treebigrips->SetBranchAddress("F8PLA_QR_raw",&F8PLA_QR_raw);
    treebigrips->SetBranchAddress("F8PLA_Q_ave",&F8PLA_Q_ave);
    treebigrips->SetBranchAddress("F11PLA_QL_raw",&F11PLA_QL_raw);
    treebigrips->SetBranchAddress("F11PLA_QR_raw",&F11PLA_QR_raw);
    treebigrips->SetBranchAddress("F11PLA_Q_ave",&F11PLA_Q_ave);
    treebigrips->SetBranchAddress("F7ICNumHit",&F7ICNumHit);
    treebigrips->SetBranchAddress("F7ICEnergySqSum",&F7ICEnergySqSum);
    treebigrips->SetBranchAddress("F7ICEnergyAvSum",&F7ICEnergyAvSum);
    treebigrips->SetBranchAddress("F11ICNumHit",&F11ICNumHit);
    treebigrips->SetBranchAddress("F11ICEnergySqSum",&F11ICEnergySqSum);
    treebigrips->SetBranchAddress("F11ICEnergyAvSum",&F11ICEnergyAvSum);
    treebigrips->SetBranchAddress("F11ICRawADC",F11ICRawADC);
    treebigrips->SetBranchAddress("F11PlalongL",&F11PlalongL);
    treebigrips->SetBranchAddress("F11PlalongR",&F11PlalongR);
    treebigrips->SetBranchAddress("DegAng",&DegAng);
    treebigrips->SetBranchAddress("GCveto",&GCveto);
    treebigrips->SetBranchAddress("Clock10M",&Clock10M);
    treebigrips->SetBranchAddress("SweepNo",&SweepNo);
    treebigrips->SetBranchAddress("aval",&aval);
    treebigrips->SetBranchAddress("bval",&bval);
    treebigrips->SetBranchAddress("tof37",&tof37);
    treebigrips->SetBranchAddress("tof811",&tof811);
    treebigrips->SetBranchAddress("beta35",&beta35);
    treebigrips->SetBranchAddress("beta57",&beta57);
    treebigrips->SetBranchAddress("beta810",&beta810);
    treebigrips->SetBranchAddress("beta1011",&beta1011);
    treebigrips->SetBranchAddress("Energy35",&Energy35);
    treebigrips->SetBranchAddress("Energy57",&Energy57);
    treebigrips->SetBranchAddress("Energy810",&Energy810);
    treebigrips->SetBranchAddress("Energy1011",&Energy1011);
    treebigrips->SetBranchAddress("brho35",&brho35);
    treebigrips->SetBranchAddress("brho57",&brho57);
    treebigrips->SetBranchAddress("brho810",&brho810);
    treebigrips->SetBranchAddress("brho1011",&brho1011);
    treebigrips->SetBranchAddress("zet35",&zet35);
    treebigrips->SetBranchAddress("zet57",&zet57);
    treebigrips->SetBranchAddress("zet37",&zet37);
    treebigrips->SetBranchAddress("zet37_f11ic",&zet37_f11ic);
    treebigrips->SetBranchAddress("zet810",&zet810);
    treebigrips->SetBranchAddress("zet1011",&zet1011);
    treebigrips->SetBranchAddress("zet811",&zet811);
    treebigrips->SetBranchAddress("aoq35",&aoq35);
    treebigrips->SetBranchAddress("aoq57",&aoq57);
    treebigrips->SetBranchAddress("aoq37",&aoq37);
    treebigrips->SetBranchAddress("aoq810",&aoq810);
    treebigrips->SetBranchAddress("aoq1011",&aoq1011);
    treebigrips->SetBranchAddress("aoq811",&aoq811);
    treebigrips->SetBranchAddress("zet35c",&zet35c);
    treebigrips->SetBranchAddress("zet57c",&zet57c);
    treebigrips->SetBranchAddress("zet37c",&zet37c);
    treebigrips->SetBranchAddress("zet37c_f11ic",&zet37c_f11ic);
    treebigrips->SetBranchAddress("zet810c",&zet810c);
    treebigrips->SetBranchAddress("zet1011c",&zet1011c);
    treebigrips->SetBranchAddress("zet811c",&zet811c);
    treebigrips->SetBranchAddress("aoq35c",&aoq35c);
    treebigrips->SetBranchAddress("aoq57c",&aoq57c);
    treebigrips->SetBranchAddress("aoq37c",&aoq37c);
    treebigrips->SetBranchAddress("aoq810c",&aoq810c);
    treebigrips->SetBranchAddress("aoq1011c",&aoq1011c);
    treebigrips->SetBranchAddress("aoq811c",&aoq811c);
    treebigrips->SetBranchAddress("nclean",&nclean);
    treebigrips->SetBranchAddress("Z",&Z);
    treebigrips->SetBranchAddress("A",&A);
    treebigrips->SetBranchAddress("N",&N);

    Int_t roll = 0;
    Int_t prev_sweepno = -1;
    for (Long64_t entry = 0;entry<treebigrips->GetEntries();entry++){
        treebigrips->GetEntry(entry);
        //if (runno==aval){
	if (runno==aval&&F11PlalongL+F11PlalongR>300&&GCveto<=280){ // loosen the condition
	  //if (runno==aval&&F11PlalongL>300&&F11PlalongR>300&&GCveto<=140){
//            cout<<aoq37c<<"\t"<<zet37c<<endl;
            BIGRIPSData* data = new BIGRIPSData;
            data->sweeps = SweepNo;
	    //            if (SweepNo<prev_sweepno){
	    //	      cout<<"br roll "<<roll<<"\t"<<data->sweeps<<"\t"<<prev_sweepno<<endl;
	    //                roll++;
	    //            }
            prev_sweepno = SweepNo;
            data->aoq = aoq37c;
            data->zet = zet37c;
            data->A = A;
            data->Z = Z;
            data->F11PlalongL = F11PlalongL;
            data->F11PlalongR = F11PlalongR;
            data->GCveto = GCveto;
            if (aval==213) bigripsdatamap.insert(make_pair(data->sweeps+roll*65536+441077-311428,data));    // sweep offset correction
	    //else if (aval==252) bigripsdatamap.insert(make_pair(data->sweeps+roll*65536+1447171-1447171,data));
            else bigripsdatamap.insert(make_pair(data->sweeps,data));
//            bigripsdatamap.insert(make_pair(data->sweeps+roll*65536+maxsweep_mt-maxsweep_br,data)); // general sweep offset correction
        }
    }
    cout<<bigripsdatamap.size()<<"\t"<<prev_sweepno<<endl;

    TFile* mrtoffile = TFile::Open(argv[3]);
    TTree* treemrtof = (TTree*) mrtoffile->Get("tree");
    MRTOFdata * mrtofdata = new MRTOFdata;
    treemrtof->SetBranchAddress("mrtof",&mrtofdata);

    prev_sweepno = -1;
    roll = 0;
    for (Long64_t entry = 0;entry<treemrtof->GetEntries();entry++){
        treemrtof->GetEntry(entry);
        MRTOFdata* data = (MRTOFdata*) mrtofdata->Clone();
        if (prev_sweepno-mrtofdata->sweeps>60000){
            cout<<roll<<"\t"<<mrtofdata->sweeps<<"\t"<<prev_sweepno<<endl;
            roll++;
        }
        prev_sweepno = mrtofdata->sweeps;
        mrtofdatamap.insert(make_pair(data->sweeps+roll*65536,data));
    }
    cout<<mrtofdatamap.size()<<"\t"<<prev_sweepno<<endl;

    TFile* ofile = new TFile(argv[4],"recreate");
    ofile->cd();

    TTree* tree=new TTree("tree","tree");
    Int_t ncoin = 0;
    Int_t t=-9999;
    Int_t sweepsn=-9999;
    Double_t aoq[1000];
    Double_t zet[1000];
    Int_t F11PlaL[1000];
    Int_t F11PlaR[1000];
    Int_t GCVeto[1000];
    Int_t sweepscorr[1000];
    Int_t sweepsdiff[1000];
    Int_t AAA[1000];
    Int_t ZZZ[1000];
    tree->Branch("t",&t,"t/I");
    tree->Branch("sweeps",&sweepsn,"sweeps/I");
    tree->Branch("ncoin",&ncoin,"ncoin/I");
    tree->Branch("aoq[ncoin]",aoq,"aoq[ncoin]/D");
    tree->Branch("zet[ncoin]",zet,"zet[ncoin]/D");
    tree->Branch("A[ncoin]",AAA,"A[ncoin]/I");
    tree->Branch("Z[ncoin]",ZZZ,"Z[ncoin]/I");
    tree->Branch("F11PlaL[ncoin]",F11PlaL,"F11PlaL[ncoin]/I");
    tree->Branch("F11PlaR[ncoin]",F11PlaR,"F11PlaR[ncoin]/I");
    tree->Branch("GCVeto[ncoin]",GCVeto,"GCVeto[ncoin]/I");
    tree->Branch("sweepscorr[ncoin]",sweepscorr,"sweepscorr[ncoin]/I");
    tree->Branch("sweepsdiff[ncoin]",sweepsdiff,"sweepsdiff[ncoin]/I");

    for (mrtofdatamap_it=mrtofdatamap.begin();mrtofdatamap_it!=mrtofdatamap.end();mrtofdatamap_it++){
        Int_t sweeps = mrtofdatamap_it->first;
        MRTOFdata* data = mrtofdatamap_it->second;
        if (data->ch==1&&data->tag==0){
            Int_t sweeps1,sweeps2;
            sweeps1 = sweeps - 200;
            sweeps2 = sweeps + 200; // loosen the condition
            bigripsdatamap_it = bigripsdatamap.lower_bound(sweeps1);
            t = data->t;
            sweepsn = sweeps;
            ncoin = 0;
            while(bigripsdatamap_it!=bigripsdatamap.end()&&bigripsdatamap_it->first<=sweeps2){
                Int_t corrsweeps = bigripsdatamap_it->first;
                BIGRIPSData* bigdata = bigripsdatamap_it->second;
                aoq[ncoin]= bigdata->aoq;
                zet[ncoin]= bigdata->zet;
                AAA[ncoin] = bigdata->A;
                ZZZ[ncoin] = bigdata->Z;
                F11PlaL[ncoin]= bigdata->F11PlalongL;
                F11PlaR[ncoin]= bigdata->F11PlalongR;
                GCVeto[ncoin]= bigdata->GCveto;
                sweepscorr[ncoin] = corrsweeps;
                sweepsdiff[ncoin] = sweeps-corrsweeps;
                ncoin++;
                bigripsdatamap_it++;
            }
            tree->Fill();
        }
    }

    tree->Write();
    ofile->Close();
    return 0;
}
