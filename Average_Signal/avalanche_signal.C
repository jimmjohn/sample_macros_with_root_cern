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
#include <TRandom1.h>
#include <TF2.h>
#include <TH1.h>
#include <tgmath.h>
#include "TFile.h"

using namespace std;

int main()
{

  //Value of alpha eta and k
  const double alpha = 13.3;
  const double eta = 3.5;
  const double k = eta/alpha;
  const double nAvg = 2.8;
  const double vdrift = 0.140; //mm/ns
  const double lambda = 0.1; //mm
  const double d = 2.0; //mm

  double N0=d/lambda;


  // open a new ROOT file
  TFile *f = TFile::Open("Avalanche_Signal.root", "RECREATE");

  TGraph* current = new TGraph();
  TGraph* eleNum = new TGraph();

  double deltaT = 0.002;

  double I,Nt;

  I=0;
  Nt=0;

  int i,j;
  i=0;
  j=0;

  for(double t=0; t<20; t=t+deltaT) {
    //Find Average
    Nt=0;
    for(int n=1; n<=N0; n++) {
      double step=(d/vdrift)*(1.0-((double)n/N0));
      if(step>t){
        Nt=Nt + nAvg*exp((alpha-eta)*vdrift*t);
      }
    }
    eleNum->SetPoint(i,t,Nt);
    i++;
  }




  TCanvas *c1 = new TCanvas("c1", "canvas",1000,2000);
  c1->cd();
  c1->Divide(2,2,0,0);
  gStyle->SetOptFit(1111);
  c1->cd(1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.15);
  gPad->SetTopMargin(0.15);
  gPad->SetBottomMargin(0.15);
  eleNum->SetMarkerStyle(8);
  eleNum->SetMarkerSize(1);
  eleNum->Draw("AC");


  f->cd();
  current->Write("current");
  eleNum->Write("eleNum");


  f->Close();

  return 0;

}
