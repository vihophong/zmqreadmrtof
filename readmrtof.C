#include "stdio.h"
#include "string.h"
void readmrtof()
{
    gROOT->ProcessLine(".L libreadmrtof.so");
    gROOT->ProcessLine("gSystem->Load(\"libreadmrtof\")");
    gROOT->ProcessLine("pinit(\"172.27.224.195\",\"5556\")");
    gROOT->ProcessLine("pstart()");
}
