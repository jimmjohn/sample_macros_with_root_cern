#include <iostream>
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
#include <tgmath.h>

using namespace std;

void exercise5()
{
unsigned int i;
double x,normalization;
TCanvas *c1 = new TCanvas("c1", "canvas",1000,2000);
c1->cd();
c1->Divide(2,1,0,0);
gStyle->SetOptFit(1111);


// The Gaussian Transformation
c1->cd(1);
gPad->SetLeftMargin(0.15);
gPad->SetRightMargin(0.15);
gPad->SetTopMargin(0.15);
gPad->SetBottomMargin(0.15);
double x1,x2,x3,y1,y2, ran[12];
auto fun4 = new TH1D("fun4","Box Muller Transformation",10000,-10,10);
for(i=0;i<1000000;i++)
{
x1=((double) rand() / (RAND_MAX));
x2=((double) rand() / (RAND_MAX));
y1=sqrt(-2.0*log(x1))*cos(2.0*3.14*x2);
y2=sqrt(-2.0*log(x1))*sin(2.0*3.14*x2);
fun4->Fill(y2);
}
normalization = fun4->GetEntries();
fun4->Scale(1/normalization);
TF1  *f4 = new TF1("f4","[0]*exp(-0.5*pow(x,2))",-10,10);
f4->SetParameter(0,10);
fun4->Fit(f4);
fun4->Draw("");


//Central Limit Theorem

double tau1=0.5,tau2=-1.0,t1,t2,t3,u1,u2;

auto fun10 = new TH1D("fun10","Central Limit Theorem",10000,-10,10);


for(i=0;i<1000000;i++)
{

x1=((double) rand() / (RAND_MAX));
x2=((double) rand() / (RAND_MAX));
y1=sqrt(-2.0*log(x1))*cos(2.0*3.14*x2);
y2=sqrt(-2.0*log(x1))*sin(2.0*3.14*x2);


x1=(double)gRandom->Uniform(0,1);
x2=(double)gRandom->Uniform(0,1);
x3=0.;
for(int ij=0; ij<12;ij++) {
  x3 += (double)gRandom->Uniform(0,1);
}

t1=-1.0*tau1*log(x1);
t2=-1.0*tau2*log(x1);
//fun10->Fill(x1+x2+t1+t2+y1+y2);
fun10->Fill(x3-6);




//cout<<t1-t2<<endl;
}
c1->cd(2);
normalization = fun10->GetEntries();
fun10->Scale(1/normalization);

TF1  *f10 = new TF1("f10","[0]*exp(-0.5*pow(x,2))",-10,10);
f10->SetParameter(0,10);
fun10->Fit("gaus");


fun10->Draw("");



}
