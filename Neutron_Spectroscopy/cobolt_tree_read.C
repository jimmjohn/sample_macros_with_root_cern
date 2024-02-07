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

void read_the_tree()
{
Int_t j,k=0;

typedef struct {
UInt_t i;
double ts;
double energy;
} EVENT;
static EVENT br1;
static EVENT br2;

TCanvas *canvas= new TCanvas("canvas","Canvas",1000,1000);
canvas->Divide(3,1);

auto h1a = new TH1F("h1a","BGO",4096,0,65536);
auto h1b = new TH1F("h1b","LaBr3_Without_coincidence",4096,0,65536);
auto h1c = new TH1F("h1c","LaBr3_With_coincidence",4096,0,65536);


TFile* fin = new TFile("cobolt_coincidence.root", "read");
TTree *eventtree2 = (TTree*)fin->Get("eventtree1");
TTree *eventtree1 = (TTree*)fin->Get("eventtree2");


eventtree1->SetBranchAddress("br2",&br1);
eventtree2->SetBranchAddress("br1",&br2);

Int_t nentries1 = (Int_t)eventtree1->GetEntries();
Int_t nentries2 = (Int_t)eventtree2->GetEntries();

br2.ts=0;
br2.energy=0;
for(j=0;j<nentries1;j++)
{
eventtree1->GetEntry(j);
h1a->Fill(br1.energy);
if((br1.energy>700.0) && (br1.energy<950.0)) 
{
while(br2.ts<(br1.ts+10.0*pow(10,-9)) && j<nentries1-200)
{
if(br2.ts>(br1.ts-10.0*pow(10,-9)))
{
cout<<j<<"\t"<<br2.ts<<"\t"<<br1.ts<<endl;
h1c->Fill(br2.energy);
}
if(k<nentries2)
{
eventtree2->GetEntry(k);
}
k=k+1;
}
k=k-30;
if(k<nentries2)
{
eventtree2->GetEntry(k);
}
}
}
for(k=0;k<nentries2;k++)
{
eventtree2->GetEntry(k);
h1b->Fill(br2.energy);
}
canvas->cd(1);
h1a->Draw("colz");
canvas->cd(2);
h1b->Draw("colz");
canvas->cd(3);
h1c->Draw("colz");
}










