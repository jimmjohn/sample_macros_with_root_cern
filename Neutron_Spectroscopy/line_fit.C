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

void line_fit()
{
float x[3]={2941.9,5309.5,6059.3};
float y[3]={2141.3,3851.1,4388.8};
float z[3]={661.7,1173.228,1332.492};

TGraph* gry1 = new TGraph(3,x,z);
gry1->SetTitle("");
TGraph* gry2 = new TGraph(3,y,z);
gry2->SetTitle("");

gStyle->SetOptStat(1111);
gStyle->SetOptFit(111);

TF1 *f1 = new TF1("f1","([0]*x)+[1]",0,10000);
f1->SetParameters(1,0);
gry1->Fit("f1");
gry2->Fit("f1");

gry1->SetMarkerColor(4);
gry1->SetMarkerStyle(21);
gry1->GetXaxis()->SetTitle("Channel Number");
gry1->GetYaxis()->SetTitle("Energy (KeV)");
gry1->GetYaxis()->CenterTitle();
gry1->GetXaxis()->CenterTitle();

gry2->SetMarkerColor(4);
gry2->SetMarkerStyle(21);
gry2->GetXaxis()->SetTitle("Channel Number ");
gry2->GetYaxis()->SetTitle("Energy (KeV)");
gry2->GetYaxis()->CenterTitle();
gry2->GetXaxis()->CenterTitle();

TText *abc = new TText();
abc->SetTextSize(0.05);
abc->SetNDC();

TCanvas *canvas= new TCanvas("canvas","Canvas",1500,750);
canvas->Divide(2,1);
canvas->cd(1);
gPad->SetLeftMargin(0.15);
gry1->Draw("AP");
abc->DrawText(0.2,0.8,"(a)");
canvas->cd(2);
gPad->SetLeftMargin(0.15);
gry2->Draw("AP");
abc->DrawText(0.2,0.8,"(b)");

}


