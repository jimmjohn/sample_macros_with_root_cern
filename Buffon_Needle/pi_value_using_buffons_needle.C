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
using namespace std;


void buffons()
{

Double_t theta,x1,y1,x2,y2,l,a,P,pivalue;
int x1int,x2int,diff1,diff2,success,n;

l=0.7;
a=1.0;
success=0;
n=1000000;
TCanvas *c1 = new TCanvas("c1","canvas",10,10,1000,1000);

TMultiGraph* mg = new TMultiGraph();
TGraph *g[n];
TGraph *grline[21];

for (int i = 0; i <= 20; i++)
{
Double_t xval=(Double_t)i;
Double_t x[2]={xval,xval};
Double_t y[2]={0,20};
grline[i]=new TGraph(2, x, y);
grline[i]->SetLineWidth(3);
grline[i]->SetLineColor(kRed);
mg->Add(grline[i]);
}
for (int i = 0; i < n; i++)
{
x1=gRandom->Uniform(0,20);
y1=gRandom->Uniform(0,20);
theta=gRandom->Uniform(0,2*PI);
x2=x1+l*cos(theta);
y2=y1+l*sin(theta);
x1int=(int)x1;
x2int=(int)x2;
diff1=x1int-x2int;
diff2=x2int-x1int;
if(diff1==1 || diff2 == 1)
{
success=success+1;
}

Double_t x[2]={x1,x2};
Double_t y[2]={y1,y2};
g[i] = new TGraph(2, x, y);
mg->Add(g[i]);
}
P=(Double_t)((Double_t)success/(Double_t)n);

pivalue=(2.0*l)/(P*a);


mg->Draw("AL");
cout <<"Value of success = " << success <<endl;
cout <<"Value of l = " << l <<endl;
cout <<"Value of P = " << P <<endl;
cout <<"Value of a = " << a <<endl;
cout <<"Value of Pi = " << pivalue <<endl;






}
