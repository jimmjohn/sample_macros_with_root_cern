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


void source_strength()
{
double psd0, psd1,energy;
UInt_t time;
UShort_t ql;
UInt_t ex;
UShort_t qs;

ifstream fin1("AmBe_ss_030_ls_1.dat", ios::in | ios::binary);
ifstream fin2("PuC_ss_032_ls_1.dat", ios::in | ios::binary);
ifstream fin3("Cf_ss_033_ls_1.dat", ios::in | ios::binary);

if (!fin1) {
printf("Error : File 1 not found!\n");
return;
}
if (!fin2) {
printf("Error : File 2 not found!\n");
return;
}
if (!fin3) {
printf("Error :  File 3 not found!\n");
return;
}


auto h2a = new TH2F("h2a","",4096,0,65536,512,0,1);
auto h2b = new TH2F("h2b","",4096,0,65536,512,0,1);
auto h2c = new TH2F("h2c","",4096,0,65536,512,0,1);


while(!fin1.eof())
{
fin1.read((char*)&time,4);  // read record
fin1.read((char*)&ql,2);    // read record
fin1.read((char*)&ex,4);    // read record
fin1.read((char*)&qs,2);    // read record
psd0=double((ql-qs))/double(ql);
h2a->Fill(ql,psd0);
}
while(!fin2.eof())
{
fin2.read((char*)&time,4);  // read record
fin2.read((char*)&ql,2);    // read record
fin2.read((char*)&ex,4);    // read record
fin2.read((char*)&qs,2);    // read record
psd1=double((ql-qs))/double(ql);
h2b->Fill(ql,psd1);
}
while(!fin3.eof())
{
fin3.read((char*)&time,4);  // read record
fin3.read((char*)&ql,2);    // read record
fin3.read((char*)&ex,4);    // read record
fin3.read((char*)&qs,2);    // read record
psd0=double((ql-qs))/double(ql);
h2c->Fill(ql,psd0);
}

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

TH1D *h1a=h2a->ProjectionX("AmBe_ss_030_ls_1",0,65536,"[CUTG]");
TH1D *h1b=h2b->ProjectionX("PuC_ss_032_ls_1",0,65536,"[CUTG]");
TH1D *h1c=h2c->ProjectionX("Cf_ss_033_ls_1",0,65536,"[CUTG]");


h1a->GetXaxis()->SetTitle("Channel");
h1b->GetXaxis()->SetTitle("Channel");
h1c->GetXaxis()->SetTitle("Channel");


h1a->GetXaxis()->CenterTitle();
h1b->GetXaxis()->CenterTitle();
h1c->GetXaxis()->CenterTitle();

h1a->GetYaxis()->SetTitle("Counts");
h1b->GetYaxis()->SetTitle("Counts");
h1c->GetYaxis()->SetTitle("Counts");

h1a->GetYaxis()->CenterTitle();
h1b->GetYaxis()->CenterTitle();
h1c->GetYaxis()->CenterTitle();

h1a->SetAxisRange(0.,25000.,"X");
h1b->SetAxisRange(0.,25000.,"X");
h1c->SetAxisRange(0.,25000.,"X");


gStyle->SetOptStat("ne");

TText *label = new TText();
label->SetTextSize(0.05);
//label->SetTextFont(1);
label->SetNDC();

TCanvas *canvas= new TCanvas("canvas","Canvas",1000,1000);
canvas->Divide(3,1);
canvas->cd(1);

h1a->Draw("colz");
label->DrawText(0.2,0.8,"(a)");
canvas->cd(2);
h1b->Draw("colz");
label->DrawText(0.2,0.8,"(b)");
canvas->cd(3);
h1c->Draw("colz");
label->DrawText(0.2,0.8,"(c)");


}
