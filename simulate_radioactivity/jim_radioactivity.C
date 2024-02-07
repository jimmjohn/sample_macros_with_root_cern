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

Double_t poissonf(Double_t*x,Double_t*par)                                         
{                                                                              
  return par[0]*TMath::Poisson(x[0],par[1]);
}

void radioactivity()
{
int k,i=0,j,l;
k=0;
double u,A,lamda=22.4,num,den,sum,add;
TCanvas *c1 = new TCanvas("c1", "canvas",1000,2000);
c1->cd();
gStyle->SetOptFit(11111);
TH1D* fun1 = new TH1D("fun1","Radioactivity",50,0.5,50.5);
TF1 *pois = new TF1("pois",poissonf,0,50,2);
do
{
k=0;
A=exp(-1.0*lamda);
u=gRandom->Uniform(0,1);
for(j=0;j<100;j++)
{
 if(u<A)
  {fun1->Fill(k);
   i=i+1;
   break;
  }
 else
  {
   k=k+1;
   num=log(exp(-1.0*lamda)*pow(lamda,k));
   sum=1;
   for(l=2;l<k+1;l++)
   {
    sum=sum+log(l);
   }
   den=sum;
   add=num-den;
   add=exp(add);
   A=A+add;
//A=A+exp(-1.0*lamda)*pow(lamda,k)/factorial(k);
  }
}
}while(i<1000);

pois->SetParameter(0,1000);                                              
pois->SetParameter(1,22.4);    
fun1->Fit("pois"); 
fun1->Draw();



}

