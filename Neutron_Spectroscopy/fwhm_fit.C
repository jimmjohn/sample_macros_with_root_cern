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
float a[12]={121.8,244.6,344.269,411.051,779.082,867.628,964.007,1085.79,1112.062,1212.935,1764.806,2614.850};
float b[12]={2.019,2.089,2.118,2.241,2.307,2.336,2.375,2.454,2.468,2.6,2.915,3.393};
float c[3]={661.7,1173.228,1332.492};
float d[3]={29.75,38.08,43.39};

TGraph* gry1 = new TGraph(12,a,b);
gry1->SetTitle("");
TGraph* gry2 = new TGraph(3,c,d);
gry2->SetTitle("");
TGraph* gry3 = new TGraph(3,c,d);
gry3->SetTitle("");

//gStyle->SetOptStat(1111);
//gStyle->SetOptFit(111);

TF1 *f1 = new TF1("f1","([0]*x)+[1]",0,10000);
f1->SetParameters(0,0);

TF1 *f2 = new TF1("f2","([0]*x)+[1]",0,10000);
f2->SetParameters(0,0);
gry1->Fit("f1");
gry2->Fit("f2");

gry1->SetMarkerColor(4);
gry1->SetMarkerStyle(21);
gry1->GetYaxis()->SetTitle("FWHM");
gry1->GetXaxis()->SetTitle("Energy (KeV)");
gry1->GetYaxis()->CenterTitle();
gry1->GetXaxis()->CenterTitle();

gry2->SetMarkerColor(4);
gry2->SetMarkerStyle(21);
gry2->GetYaxis()->SetTitle("FWHM ");
gry2->GetXaxis()->SetTitle("Energy (KeV)");
gry2->GetYaxis()->CenterTitle();
gry2->GetXaxis()->CenterTitle();

TMultiGraph* mg = new TMultiGraph();
mg->Add(gry1);
mg->Add(gry2);

//mg->SetMarkerColor(4);
//mg->SetMarkerStyle(21);
//mg->GetXaxis()->SetTitle("FWHM");
//mg->GetXaxis()->SetTitle("Energy (KeV)");
//mg->GetYaxis()->CenterTitle();
//mg->GetXaxis()->CenterTitle();
TLatex *l = new TLatex();
l->SetTextSize(0.03);
TCanvas *canvas= new TCanvas("canvas","Canvas",700,700);
gPad->SetLeftMargin(0.15);
//gry1->Draw("AP");
mg->Draw("AP");
mg->GetXaxis()->SetTitle("Energy (KeV)");
mg->GetYaxis()->SetTitle("FWHM");
mg->GetYaxis()->CenterTitle();
mg->GetXaxis()->CenterTitle();
mg->GetYaxis()->SetTitleOffset(1.2);
l->DrawLatex(2000,7," HPGe");
l->DrawLatex(1000,32," CeBr3");   
}


