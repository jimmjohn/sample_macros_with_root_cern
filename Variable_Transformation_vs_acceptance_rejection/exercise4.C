#include <iostream>
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
#include "TLorentzVector.h"
#include "TTree.h"
#include "TFile.h"
#include "TStyle.h"

#define PI 3.14159265
#ifdef __CINT__
#pragma link C++ class vector<float>+;
#pragma link C++ class vector<TLorentzVector>+;
#endif

//________________________________________________________________________________________________________________________________________
Double_t langaufun(Double_t *x, Double_t *par) {

//Fit parameters:
//par[0]=Width (scale) Breit-Wigner
//par[1]=Most Probable (MP, location) Breit mean
//par[2]=Total area (integral -inf to inf, normalization constant)
//par[3]=Width (sigma) of convoluted Gaussian function

// Numeric constants
Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)

// Control constants
Double_t np = 100.0;      // number of convolution steps
Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

// Variables
Double_t xx;
Double_t fland;
Double_t sum = 0.0;
Double_t xlow,xupp;
Double_t step;
Double_t i;


// Range of convolution integral
xlow = x[0] - sc * par[3];
xupp = x[0] + sc * par[3];

step = (xupp-xlow) / np;

// Convolution integral of Breit–Wigner and Gaussian by sum
for(i=1.0; i<=np/2; i++) {
  xx = xlow + (i-.5) * step;
  fland = TMath::BreitWigner(xx,par[1],par[0]);
   sum += fland * TMath::Gaus(x[0],xx,par[3]);

   xx = xupp - (i-.5) * step;
   fland = TMath::BreitWigner(xx,par[1],par[0]);
   sum += fland * TMath::Gaus(x[0],xx,par[3]);
}

return (par[2] * step * sum * invsq2pi / par[3]);

}


//________________________________________________________________________________________________________________________


void exercise4()
{
Double_t mass=91.2,width=2.5,massdist;


TCanvas* c1 = new TCanvas("c1","canvas",10,10,1000,1000);
c1->Divide(2,1);
TH1D* h1mass = new TH1D("h1mass","Variable Transformation Method",1000,0,200);


//Variable Transformation Method
for (int i = 0; i < 1000000; i++)
{
double u=gRandom->Uniform(0,1);
massdist=mass+((width/2.0)*tan(TMath::Pi()*(u)));
h1mass->Fill(massdist);
}
Char_t FunName[100];
sprintf(FunName,"Fitfcn");
TF1 *ffit = new TF1(FunName,langaufun,0,200,4);
//Fit parameters:
//par[0]=Width (scale) Breit-Wigner
//par[1]=Most Probable (MP, location) Breit mean
//par[2]=Total area (integral -inf to inf, normalization constant)
//par[3]=Width (sigma) of convoluted Gaussian function
Double_t chisqr;
Int_t    ndf;
Double_t fp[4], fpe[4];
Double_t par[4];
par[0] = 2;
  par[1] = 91.0;
par[2] = 200.0;
par[3] = 1;
ffit->SetParameters(par);
ffit->SetParNames("Width","MP","Area","GSigma");
h1mass->Fit(FunName,"RB0");   // fit within specified range, use ParLimits, do not plot
ffit->GetParameters(fp);    // obtain fit parameters
for (int i=0; i<4; i++) {
fpe[i] = ffit->GetParError(i);     // obtain fit parameter errors
}
chisqr=ffit->GetChisquare();  // obtain chi^2
ndf=ffit->GetNDF();           // obtain ndf
gStyle->SetOptStat(1111);
gStyle->SetOptFit(111);
gStyle->SetLabelSize(0.03,"x");
gStyle->SetLabelSize(0.03,"y");

c1->cd(1);
//h1mass->GetXaxis()->SetRange(0,1000);
h1mass->Draw();
ffit->Draw("lsame");


//Using Acceptance Rejection Method

TH1D* h2mass = new TH1D("h2mass","Acceptance Rejection Method",1000,0,200);


for(int loop=0;loop<1000000;loop++)
{
double r1=gRandom->Uniform(0,1);
double r2=gRandom->Uniform(0,1);
r1=r1*200;
//double modelfun=13241.269/(51984.0+(pow(pow(r1,2.0)-8317.44,2)));
double modelfun=13241.269/(51984.0+(pow(pow(r1,2.0)-8317.44,2)));
if(r2<modelfun)
 {
	h2mass->Fill(r1);
 }
}

sprintf(FunName,"Fitfcn2");
TF1 *ffit2 = new TF1(FunName,langaufun,0,200,4);
//Fit parameters:
//par[0]=Width (scale) Breit-Wigner
//par[1]=Most Probable (MP, location) Breit mean
//par[2]=Total area (integral -inf to inf, normalization constant)
//par[3]=Width (sigma) of convoluted Gaussian function

par[0] = 2;
par[1] = 91.0;
par[2] = 200.0;
par[3] = 1;
ffit2->SetParameters(par);
ffit2->SetParNames("Width","MP","Area","GSigma");
h2mass->Fit(FunName,"RB0");   // fit within specified range, use ParLimits, do not plot
ffit2->GetParameters(fp);    // obtain fit parameters
for (int i=0; i<4; i++) {
fpe[i] = ffit2->GetParError(i);     // obtain fit parameter errors
}
chisqr=ffit2->GetChisquare();  // obtain chi^2
ndf=ffit2->GetNDF();           // obtain ndf
gStyle->SetOptStat(1111);
gStyle->SetOptFit(111);
gStyle->SetLabelSize(0.03,"x");
gStyle->SetLabelSize(0.03,"y");

c1->cd(2);

h2mass->Draw();
ffit2->Draw("lsame");




}
