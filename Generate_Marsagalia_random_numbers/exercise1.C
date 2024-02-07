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

void exercise1()
{
static uint64_t r0,ri1,ri2,ri3,ri4,ri5,a,c,m;
double xm1,xm2,xm3,xm4,xm5;
UInt_t n=1000000,i;//n=4294967295

TGraph2D *g= new TGraph2D();

r0=4;
a=101;
c=0;
m=pow(10,8);

ri1=r0;
ri2=(a*ri1)%m;
ri3=(a*ri2)%m;
ri4=(a*ri3)%m;
ri5=(a*ri4)%m;

xm1=(double)ri1/(double)m;
xm2=(double)ri2/(double)m;
xm3=(double)ri3/(double)m;
xm4=(double)ri4/(double)m;
xm5=(double)ri5/(double)m;

for(i=0;i<n;i++)
{
g->SetPoint(i,xm1,xm2,xm3);
ri1=(a*ri3)%m;
ri2=(a*ri1)%m;
ri3=(a*ri2)%m;
ri4=(a*ri3)%m;
ri5=(a*ri4)%m;

xm1=(double)ri1/(double)m;
xm2=(double)ri2/(double)m;
xm3=(double)ri3/(double)m;
xm4=(double)ri4/(double)m;
xm5=(double)ri5/(double)m;

//std::cout<<xm1<<"\t"<<xm2<<"\t"<<xm3<<endl;

}

g->SetMarkerColor(kGreen);
g->SetTitle("a=5^15,m=2^47");

TCanvas *c1 = new TCanvas("c1","Marsaglia",0,0,600,400);
g->Draw("p");

}

