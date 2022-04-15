#ifndef __READMRTOF__
#define __READMRTOF__

#include <TVirtualPad.h>
#include <TThread.h>

class MRTOFdata : public TObject {
public:
    MRTOFdata(){Clear("");}
    virtual ~MRTOFdata(){}
    virtual void Clear(Option_t* opt){
        ch = -9999;
        edge = -9999;
        t = -9999;
        sweeps = -9999;
        tag = -9999;
        data_lost = -9999;
        degt = -9999;
        runno = -9999;
    }
    Int_t ch;
    Int_t edge;
    Int_t t;
    Int_t sweeps;
    Int_t tag;
    Int_t data_lost;
    Double_t degt;
    Int_t runno;
    /// \cond CLASSIMP
    ClassDef(MRTOFdata,1)
    /// \endcond
};

class BIGRIPSData : public TObject {
public:
    BIGRIPSData(){Clear("");}
    virtual ~BIGRIPSData(){}
    virtual void Clear(Option_t* opt){
        zet = -9999;
        aoq = -9999;
        A = -9999;
        Z = -9999;
	F11PlalongL = -9999;
	F11PlalongR = -9999;
	GCveto = -9999;
        sweeps = -9999;
    }
    Double_t aoq;
    Double_t zet;
    Int_t A;
    Int_t Z;
    Int_t F11PlalongL;
    Int_t F11PlalongR;
    Int_t GCveto;
    Int_t sweeps;
    /// \cond CLASSIMP
    ClassDef(BIGRIPSData,1)
    /// \endcond
};
int pstart();
int pinit(char* ip, char* port);

#endif
