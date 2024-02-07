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

void read_spectra()
{

double psd0, psd1,energy;
UInt_t time;
UShort_t ql;
UInt_t ex;
UShort_t qs;

ifstream fin1("Co56_009_ls_0.dat", ios::in | ios::binary);
ifstream fin2("Co_CeBr3_2_cal_012_ls_2.dat", ios::in | ios::binary);

auto h2a = new TH2F("h2a","",4096,0,65536,512,0,1);
auto h2b = new TH2F("h2b","",4096,0,65536,512,0,1);

if (!fin1) {
printf("Error : File for channel 0 not found!\n");
return;
}
if (!fin2) {
printf("Error : File for channel 2 not found!\n");
return;
}


while(!fin1.eof())
{
fin1.read((char*)&time,4);  // read record
fin1.read((char*)&ql,2);    // read record
fin1.read((char*)&ex,4);    // read record
fin1.read((char*)&qs,2);    // read record
psd0=double((ql-qs))/double(ql);
energy=double(ql*0.2154)+28.36;
h2a->Fill(energy,psd0);
}

while(!fin2.eof())
{
fin2.read((char*)&time,4);  // read record
fin2.read((char*)&ql,2);    // read record
fin2.read((char*)&ex,4);    // read record
fin2.read((char*)&qs,2);    // read record
psd1=double((ql-qs))/double(ql);
energy=double(ql*0.2986)+22.41;
h2b->Fill(energy,psd1);
}


//auto h1a = new TH1F("h1a","Energy histogram channel 0",4096,0,65536);
TH1D *h1a=h2a->ProjectionX();
//auto h1b = new TH1F("h1b","Energy histogram channel 1",4096,0,65536);
TH1D *h1b=h2b->ProjectionX();


//TF1 *f1 = new TF1("f1","gaus",5600,6600);
//h1a->Fit("f1","R");

h1a->SetAxisRange(0.,6000.,"X");
h1b->SetAxisRange(0.,6000.,"X");
h1a->SetStats(0); 
h1b->SetStats(0); 

TText *label = new TText();
label->SetTextSize(0.05);
//label->SetTextFont(1);
label->SetNDC();

TCanvas *canvas= new TCanvas("canvas","Canvas",1000,700);
//canvas->Divide(2,2);
//canvas->cd(1);
//h2a->Draw("colz");
//canvas->cd(2);
//h2b->Draw("colz");
//canvas->cd(3);
//h1a->Draw("colz");
//canvas->cd(4);
//h1b->Draw("colz");

   
//h2b->Draw("colz[CUTG]");


//TH1D *hneutronproject=h2b->ProjectionX("neutron",0,65536,"[CUTG]");

canvas->Divide(2,1);
canvas->cd(1);
h1a->Draw("colz");
label->DrawText(0.2,0.8,"(a)");
canvas->cd(2);
h1b->Draw("colz");
label->DrawText(0.2,0.8,"(b)");
//h2b->Draw("colz");
//hneutronproject->Draw("colz");
//cutg->Draw("same");


}


