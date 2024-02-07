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

void source_psd()
{

double psd,energy;
UInt_t time;
UShort_t ql;
UInt_t ex;
UShort_t qs;

ifstream fin1("AmBe_ss_030_ls_1.dat", ios::in | ios::binary);
ifstream fin2("PuC_ss_032_ls_1.dat", ios::in | ios::binary);
ifstream fin3("Cf_ss_033_ls_1.dat", ios::in | ios::binary);



auto h2a = new TH2F("h2a","",4096,0,65536,512,0,1);
auto h2b = new TH2F("h2b","",4096,0,65536,512,0,1);
auto h2c = new TH2F("h2b","",4096,0,65536,512,0,1);

if (!fin1) {
printf("Error :  AmBe Not Found!\n");
return;
}
if (!fin2) {
printf("Error :  PuC Not found!\n");
return;
}
if (!fin3) {
printf("Error :  Cf Not found!\n");
return;
}

while(!fin1.eof())
{
fin1.read((char*)&time,4);  // read record
fin1.read((char*)&ql,2);    // read record
fin1.read((char*)&ex,4);    // read record
fin1.read((char*)&qs,2);    // read record
psd=double((ql-qs))/double(ql);
//energy=double(ql*0.2157)+28.01;
h2a->Fill(ql,psd);
}

while(!fin2.eof())
{
fin2.read((char*)&time,4);  // read record
fin2.read((char*)&ql,2);    // read record
fin2.read((char*)&ex,4);    // read record
fin2.read((char*)&qs,2);    // read record
psd=double((ql-qs))/double(ql);
//energy=double(ql*0.2989)+22.62;
h2b->Fill(ql,psd);
}

while(!fin3.eof())
{
fin3.read((char*)&time,4);  // read record
fin3.read((char*)&ql,2);    // read record
fin3.read((char*)&ex,4);    // read record
fin3.read((char*)&qs,2);    // read record
psd=double((ql-qs))/double(ql);
//energy=double(ql*0.2989)+22.62;
h2c->Fill(ql,psd);
}


TH1D *h1a=h2a->ProjectionX();
TH1D *h1b=h2b->ProjectionX();
TH1D *h1c=h2c->ProjectionX();



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


TText *label = new TText();
TLatex *l = new TLatex();
TText *abc = new TText();
abc->SetTextSize(0.05);
abc->SetNDC();

h2a->SetAxisRange(0.,30000.,"X");
h2b->SetAxisRange(0.,30000.,"X");
h2c->SetAxisRange(0.,30000.,"X");

h2a->SetAxisRange(0.,0.7,"Y");
h2b->SetAxisRange(0.,0.7,"Y");
h2c->SetAxisRange(0.,0.7,"Y");

TCanvas *canvas= new TCanvas("canvas","Canvas",1000,500);

canvas->Divide(3,1);

canvas->cd(1);
h2a->GetYaxis()->SetTitle("PSD");
h2a->GetYaxis()->CenterTitle();
h2a->GetYaxis()->SetTitleSize(0.04);
h2a->GetXaxis()->SetTitle("Channel");
h2a->GetXaxis()->CenterTitle();
h2a->GetXaxis()->SetTitleSize(0.04);
h2a->SetStats(0); 
gPad->SetRightMargin(0.15); 
h2a->Draw("colz");
cutg->Draw("same");
label->SetTextSize(0.03);
label->SetTextFont(2);
label->SetTextColor(kRed);
label->DrawText(20000,0.22,"neutrons");
abc->DrawText(0.2,0.8,"(a)");
l->SetTextSize(0.03);
l->SetTextFont(2);
l->SetTextColor(kGreen+2);
l->DrawLatex(20000,0.08,"#gamma-rays");


canvas->cd(2);
h2b->GetYaxis()->SetTitle("PSD");
h2b->GetYaxis()->CenterTitle();
h2b->GetYaxis()->SetTitleSize(0.04);
h2b->GetXaxis()->SetTitle("Channel");
h2b->GetXaxis()->CenterTitle();
h2b->GetXaxis()->SetTitleSize(0.04);
h2b->SetStats(0); 
gPad->SetRightMargin(0.15); 
h2b->Draw("colz");
cutg->Draw("same");
label->SetTextSize(0.03);
label->SetTextFont(2);
label->SetTextColor(kRed);
label->DrawText(20000,0.22,"neutrons");
abc->DrawText(0.2,0.8,"(b)");
l->SetTextSize(0.03);
l->SetTextFont(2);
l->SetTextColor(kGreen+2);
l->DrawLatex(20000,0.08,"#gamma-rays");

canvas->cd(3);
h2c->GetYaxis()->SetTitle("PSD");
h2c->GetYaxis()->CenterTitle();
h2c->GetYaxis()->SetTitleSize(0.04);
h2c->GetXaxis()->SetTitle("Channel");
h2c->GetXaxis()->CenterTitle();
h2c->GetXaxis()->SetTitleSize(0.04);
h2c->SetStats(0); 
gPad->SetRightMargin(0.15); 
h2c->Draw("colz");
cutg->Draw("same");
label->SetTextSize(0.03);
label->SetTextFont(2);
label->SetTextColor(kRed);
label->DrawText(20000,0.22,"neutrons");
abc->DrawText(0.2,0.8,"(c)");
l->SetTextSize(0.03);
l->SetTextFont(2);
l->SetTextColor(kGreen+2);
l->DrawLatex(20000,0.08,"#gamma-rays");
}


