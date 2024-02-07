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

void read_binary()
{

double psd0, psd1,energy;
UInt_t time;
UShort_t ql;
UInt_t ex;
UShort_t qs;

ifstream fin1("AmBe_HDPE_025_ls_0.dat", ios::in | ios::binary);
ifstream fin2("AmBe_HDPE_025_ls_2.dat", ios::in | ios::binary);

auto h2a = new TH2F("h2a","Energy_0 Vs PSD",4096,0,65536,512,0,1);
auto h2b = new TH2F("h2b","Energy_1 Vs PSD",4096,0,65536,512,0,1);

if (!fin1) {
printf("Error :  File in channel 0 not found!\n");
return;
}
if (!fin2) {
printf("Error :  File in channel 1 not found!\n");
return;
}



while(!fin1.eof())
{
fin1.read((char*)&time,4);  // read record
fin1.read((char*)&ql,2);    // read record
fin1.read((char*)&ex,4);    // read record
fin1.read((char*)&qs,2);    // read record
psd0=double((ql-qs))/double(ql);
energy=double(ql*0.2157)+28.01;
h2a->Fill(energy,psd0);
}

while(!fin2.eof())
{
fin2.read((char*)&time,4);  // read record
fin2.read((char*)&ql,2);    // read record
fin2.read((char*)&ex,4);    // read record
fin2.read((char*)&qs,2);    // read record
psd1=double((ql-qs))/double(ql);
energy=double(ql*0.2989)+22.62;
h2b->Fill(energy,psd1);
}



//auto h1a = new TH1F("h1a","Energy histogram channel 0",4096,0,65536);
TH1D *h1a=h2a->ProjectionX();
//auto h1b = new TH1F("h1b","Energy histogram channel 1",4096,0,65536);
TH1D *h1b=h2b->ProjectionX();

TCanvas *canvas= new TCanvas("canvas","Canvas",1000,1000);
//canvas->Divide(2,2);
//canvas->cd(1);
//h2a->Draw("colz");
//canvas->cd(2);
//h2b->Draw("colz");
//canvas->cd(3);
//h1a->Draw("colz");
//canvas->cd(4);
//h1b->Draw("colz");





   TCutG *cutg = new TCutG("CUTG",18);
   cutg->SetVarX("Energy_1 Vs PSD");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,976.649,0.248257);
   cutg->SetPoint(1,3092.84,0.208285);
   cutg->SetPoint(2,8183.14,0.189222);
   cutg->SetPoint(3,9584.4,0.182457);
   cutg->SetPoint(4,14360.1,0.183072);
   cutg->SetPoint(5,18649.7,0.191681);
   cutg->SetPoint(6,20222.6,0.191681);
   cutg->SetPoint(7,20594.3,0.184302);
   cutg->SetPoint(8,20594.3,0.174463);
   cutg->SetPoint(9,20422.7,0.168313);
   cutg->SetPoint(10,19536.2,0.159704);
   cutg->SetPoint(11,17477.2,0.146175);
   cutg->SetPoint(12,12558.5,0.126496);
   cutg->SetPoint(13,9184.04,0.115427);
   cutg->SetPoint(14,4150.94,0.111737);
   cutg->SetPoint(15,1062.44,0.126496);
   cutg->SetPoint(16,1062.44,0.245182);
   cutg->SetPoint(17,976.649,0.248257);


   
//h2b->Draw("colz[CUTG]");


TH1D *hneutronproject=h2b->ProjectionX("neutron",0,65536,"[CUTG]");

//canvas->Divide(2,1);
//canvas->cd(1);
//h2a->Draw("colz");
//h1b->Draw("colz");
//canvas->cd(2);
//h2b->Draw("colz");
//hneutronproject->Draw("colz");
//cutg->Draw("same");

gStyle->SetOptStat(1111);
gStyle->SetOptFit(111);

TF1 *f1 = new TF1("f1","gaus",4125,4350);
//h1a->Fit("f1","R");


h1b->Draw("colz");

}


