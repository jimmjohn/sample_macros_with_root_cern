#include "TFile.h"
#include "TTree.h"
#include <cstdio>
#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <TMath.h>
#include "TF1.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include <TStyle.h>
#include <TGraph2D.h>
#include <TRandom.h>
#include <TF2.h>
#include <TH1.h>
#include "TStyle.h"

using namespace std;

void create_the_tree()
{
double t1=0,t2=0,t3=0;
double psd1, psd2,psd3;
UInt_t time1=0,time2=0,time3=0,temp1,temp2,temp3;
UShort_t ql1,ql2,ql3;
UInt_t ex1,ex2,ex3;
UShort_t qs1,qs2,qs3;

typedef struct {
UInt_t i;
double ts;
double energy;
} EVENT;
static EVENT br1;
static EVENT br2;
static EVENT br3;

ifstream fin1("AmBe_blank_026_ls_0.dat", ios::in | ios::binary);
ifstream fin2("AmBe_blank_026_ls_1.dat", ios::in | ios::binary);
ifstream fin3("AmBe_blank_026_ls_2.dat", ios::in | ios::binary);

if (!fin1) {
printf("Error :  File in channel 0 not found!\n");
return;
}
if (!fin2) {
printf("Error :  File in channel 1 not found!\n");
return;
}
if (!fin3) {
printf("Error :  File in channel 2 not found!\n");
return;
}

TFile *fout = TFile::Open("treestoreblank.root", "recreate");

TTree *eventtree1 = new TTree("eventtree1", "File1");
TTree *eventtree2 = new TTree("eventtree2", "File2");
TTree *eventtree3 = new TTree("eventtree3", "File3");

eventtree1->Branch("br1",&br1,"i/i:ts/D:energy/D");
eventtree2->Branch("br2",&br2,"i/i:ts/D:energy/D");
eventtree3->Branch("br3",&br3,"i/i:ts/D:energy/D");

br1.i=0;
while(!fin1.eof())
{
temp1=time1;
fin1.read((char*)&time1,4);  // read record
fin1.read((char*)&ql1,2);    // read record
fin1.read((char*)&ex1,4);    // read record
fin1.read((char*)&qs1,2);    // read record
psd1=double((ql1-qs1))/double(ql1);
br1.energy=double(ql1*0.2154)+28.36;
if(temp1>time1 && br1.i>2)
{
t1=t1+4294967296.0*pow(10,-9);
}
br1.ts=t1+(double(time1)*pow(10,-9));
eventtree1->Fill();
br1.i=br1.i+1;
}
eventtree1->Write();

br2.i=0;
while(!fin2.eof())
{
temp2=time2;
fin2.read((char*)&time2,4);  // read record
fin2.read((char*)&ql2,2);    // read record
fin2.read((char*)&ex2,4);    // read record
fin2.read((char*)&qs2,2);    // read record
psd2=double((ql2-qs2))/double(ql2);
br2.energy=double(ql2);
if(temp2>time2 && br2.i>2)
{
t2=t2+4294967296.0*pow(10,-9);
}
br2.ts=t2+(double(time2)*pow(10,-9));
eventtree2->Fill();
br2.i=br2.i+1;
}
eventtree2->Write();

br3.i=0;
while(!fin3.eof())
{
temp3=time3;
fin3.read((char*)&time3,4);  // read record
fin3.read((char*)&ql3,2);    // read record
fin3.read((char*)&ex3,4);    // read record
fin3.read((char*)&qs3,2);    // read record
psd3=double((ql3-qs3))/double(ql3);
br3.energy=double(ql3*0.2986)+22.41;
if(temp3>time3 && br3.i>2)
{
t3=t3+4294967296.0*pow(10,-9);
}
br3.ts=t3+(double(time3)*pow(10,-9));
eventtree3->Fill();
br3.i=br3.i+1;
}
eventtree3->Write();


eventtree1->Print();
eventtree2->Print();
eventtree3->Print();

fout->Write();

}


