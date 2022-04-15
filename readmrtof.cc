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

#include "readmrtof.h"

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>


struct shmseg {
   int aval;
   int bval;
};

static TThread *main_thread = 0;
TString* ip_str = 0;
TString* port_str = 0;


TTree* tree = 0;
MRTOFdata* treedata;
TH1F *h1;
TH1F *h2;
TCanvas* c;

int pinit(char* ip, char* port){
    h1= new TH1F("h1","h1", 2000,122.96e6,123.1e6);
    h2= new TH1F("h2","h2", 2000,126.1e6,126.5e6);
    c = new TCanvas("c", "MRTOF TOF data", 800, 600);
    c->Divide(1,2);
    c->cd(1);
    c->cd(1)->SetLogy();
    h1->Draw();
    c->cd(2);
    c->cd(2)->SetLogy();
    h2->Draw();
    ip_str = new TString(ip);
    port_str = new TString(port);

    treedata = new MRTOFdata;
    tree =new TTree("tree","tree");
    tree->Branch("mrtof",treedata);
    return 0;
}

void pprocess(void * ptr)
{

    int shmid;
    struct shmseg *shmp;
    shmid = shmget(0x1233, sizeof(struct shmseg), 0644|IPC_CREAT);
    if (shmid == -1) {
       perror("Shared memory");
       exit(0);
    }
    // Attach to the segment to get a pointer to it.
    shmp = (shmseg*) shmat(shmid, NULL, 0);
    if (shmp == (void *) -1) {
       perror("Shared memory attach");
       exit(0);
    }
    shmp->aval = 0;
    shmp->bval = 0;

    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_PULL);
    char connection_str[500];
    sprintf(connection_str,"tcp://%s:%s",ip_str->Data(),port_str->Data());
    int rc = zmq_connect(subscriber, connection_str);
    assert(rc == 0);
//    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);

//    int size = 8;
//    zmq_setsockopt(subscriber, ZMQ_RCVBUF, &size,sizeof(size));

    char message[100] = "";

    Long64_t nevt = 0;

    while(1)
    {
        zmq_msg_t msg;
        zmq_msg_init(&msg);
        zmq_msg_recv(&msg,subscriber, 0);
        int size = zmq_msg_size(&msg);
        memcpy(message, zmq_msg_data(&msg), size);
        zmq_msg_close(&msg);
        std::stringstream ss;
        ss<<std::hex<<message;
//        std::cout<<message<<std::endl;
        ULong64_t fulldata;
        ss>>fulldata;
        treedata->ch = fulldata&0x7;
        treedata->edge = (fulldata&0x8)>>3;
        treedata->t = (fulldata&0xFFFFFFF0)>>4;
        treedata->sweeps = (fulldata&0xFFFF00000000)>>32;
        treedata->tag = (fulldata&0x7FFF000000000000)>>48;
        treedata->data_lost = (fulldata&0x8000000000000000)>>63;
        Double_t thickness = 4. /TMath::Cos(TMath::DegToRad()*shmp->bval*0.01);
        treedata->degt = thickness;
        treedata->runno = shmp->aval;

        tree->Fill();
        if (treedata->ch==1){
//            std::cout<<ch<<"\t"<<edge<<"\t"<<timedata<<"\t"<<sweeps<<"\t"<<tag<<"\t"<<data_lost<<std::endl;
            h1->Fill(treedata->t);
            h2->Fill(treedata->t);
            if (nevt%100000==0){
                c->cd(1)->Modified(); c->cd(1)->Update();
                c->cd(2)->Modified(); c->cd(2)->Update();
            }
            nevt++;
        }

    }

}

int pstart(){
    if (!main_thread)
      main_thread = new TThread (pprocess);
    main_thread->Run();
    return 0;
}
