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


void neutron_number()
{
double psd0, psd1,energy;
UInt_t time;
UShort_t ql;
UInt_t ex;
UShort_t qs;

ifstream fin1("AmBe_blank_026_ls_1.dat", ios::in | ios::binary);
ifstream fin2("AmBe_HDPE_025_ls_1.dat", ios::in | ios::binary);
ifstream fin3("AmBe_no_10_027_ls_1.dat", ios::in | ios::binary);
ifstream fin4("AmBe_no_11_028_ls_1.dat", ios::in | ios::binary);
ifstream fin5("AmBe_no_7_029_ls_1.dat", ios::in | ios::binary);

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
if (!fin4) {
printf("Error :  File 4 not found!\n");
return;
}
if (!fin5) {
printf("Error :  File 4 not found!\n");
return;
}

auto h2a = new TH2F("h2a","",4096,0,65536,512,0,1);
auto h2b = new TH2F("h2b","",4096,0,65536,512,0,1);
auto h2c = new TH2F("h2c","",4096,0,65536,512,0,1);
auto h2d = new TH2F("h2d","",4096,0,65536,512,0,1);
auto h2e = new TH2F("h2e","",4096,0,65536,512,0,1);

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
while(!fin4.eof())
{
fin4.read((char*)&time,4);  // read record
fin4.read((char*)&ql,2);    // read record
fin4.read((char*)&ex,4);    // read record
fin4.read((char*)&qs,2);    // read record
psd1=double((ql-qs))/double(ql);
h2d->Fill(ql,psd1);
}

while(!fin5.eof())
{
fin5.read((char*)&time,4);  // read record
fin5.read((char*)&ql,2);    // read record
fin5.read((char*)&ex,4);    // read record
fin5.read((char*)&qs,2);    // read record
psd1=double((ql-qs))/double(ql);
h2e->Fill(ql,psd1);
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

TH1D *h1a=h2a->ProjectionX("AmBe_blank_026_ls_1",0,65536,"[CUTG]");
TH1D *h1b=h2b->ProjectionX("AmBe_HDPE_025_ls_1",0,65536,"[CUTG]");
TH1D *h1c=h2c->ProjectionX("AmBe_no_10_027_ls_1",0,65536,"[CUTG]");
TH1D *h1d=h2d->ProjectionX("AmBe_no_11_028_ls_1",0,65536,"[CUTG]");
TH1D *h1e=h2e->ProjectionX("AmBe_no_7_029_ls_1",0,65536,"[CUTG]");

h1a->GetXaxis()->SetTitle("Channel");
h1b->GetXaxis()->SetTitle("Channel");
h1c->GetXaxis()->SetTitle("Channel");
h1d->GetXaxis()->SetTitle("Channel");
h1e->GetXaxis()->SetTitle("Channel");

h1a->GetXaxis()->CenterTitle();
h1b->GetXaxis()->CenterTitle();
h1c->GetXaxis()->CenterTitle();
h1d->GetXaxis()->CenterTitle();
h1e->GetXaxis()->CenterTitle();

h1a->GetYaxis()->SetTitle("Counts");
h1b->GetYaxis()->SetTitle("Counts");
h1c->GetYaxis()->SetTitle("Counts");
h1d->GetYaxis()->SetTitle("Counts");
h1e->GetYaxis()->SetTitle("Counts");

h1a->GetYaxis()->CenterTitle();
h1b->GetYaxis()->CenterTitle();
h1c->GetYaxis()->CenterTitle();
h1d->GetYaxis()->CenterTitle();
h1e->GetYaxis()->CenterTitle();

h1a->SetAxisRange(0.,25000.,"X");
h1b->SetAxisRange(0.,25000.,"X");
h1c->SetAxisRange(0.,25000.,"X");
h1d->SetAxisRange(0.,25000.,"X");
h1e->SetAxisRange(0.,25000.,"X");

h2a->GetXaxis()->SetTitle("Channel");
h2b->GetXaxis()->SetTitle("Channel");
h2c->GetXaxis()->SetTitle("Channel");
h2d->GetXaxis()->SetTitle("Channel");
h2e->GetXaxis()->SetTitle("Channel");

h2a->GetXaxis()->CenterTitle();
h2b->GetXaxis()->CenterTitle();
h2c->GetXaxis()->CenterTitle();
h2d->GetXaxis()->CenterTitle();
h2e->GetXaxis()->CenterTitle();

h2a->GetYaxis()->SetTitle("PSD");
h2b->GetYaxis()->SetTitle("PSD");
h2c->GetYaxis()->SetTitle("PSD");
h2d->GetYaxis()->SetTitle("PSD");
h2e->GetYaxis()->SetTitle("PSD");

h2a->GetYaxis()->CenterTitle();
h2b->GetYaxis()->CenterTitle();
h2c->GetYaxis()->CenterTitle();
h2d->GetYaxis()->CenterTitle();
h2e->GetYaxis()->CenterTitle();

h2a->SetAxisRange(0.,30000.,"X");
h2b->SetAxisRange(0.,30000.,"X");
h2c->SetAxisRange(0.,30000.,"X");
h2d->SetAxisRange(0.,30000.,"X");
h2e->SetAxisRange(0.,30000.,"X");

h2a->SetAxisRange(0.,0.3,"Y");
h2b->SetAxisRange(0.,0.3,"Y");
h2c->SetAxisRange(0.,0.3,"Y");
h2d->SetAxisRange(0.,0.3,"Y");
h2e->SetAxisRange(0.,0.3,"Y");

gStyle->SetOptStat("ne");

h2a->SetStats(0); 
h2b->SetStats(0); 
h2c->SetStats(0); 
h2d->SetStats(0); 
h2e->SetStats(0); 

TText *label = new TText();
label->SetTextSize(0.05);
//label->SetTextFont(1);
label->SetNDC();

TCanvas *canvas= new TCanvas("canvas","Canvas",1000,1000);
canvas->Divide(2,2);
canvas->cd(1);
//gPad->SetRightMargin(0.15);
h1b->Draw("colz");
cutg->Draw("same");
label->DrawText(0.2,0.8,"(a)");
canvas->cd(2);
//gPad->SetRightMargin(0.15);
h1c->Draw("colz");
cutg->Draw("same");
label->DrawText(0.2,0.8,"(b)");
canvas->cd(3);
//gPad->SetRightMargin(0.15);
h1d->Draw("colz");
cutg->Draw("same");
label->DrawText(0.2,0.8,"(c)");
canvas->cd(4);
//gPad->SetRightMargin(0.15);
h1e->Draw("colz");
cutg->Draw("same");
label->DrawText(0.2,0.8,"(d)");



}
