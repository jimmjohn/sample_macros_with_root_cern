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


void gerrors2() {
   //Draw a graph with error bars
   // To see the output of this macro, click begin_html <a href="gif/gerrors.gif">here</a>. end_html
   //Author: Rene Brun

   TCanvas *c1 = new TCanvas("c1","Efficency Vs Energy of Europium",300,10,700,500);
   c1->SetGrid();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   

   const Int_t n=50;
   Float_t x[n];
   Float_t y[n];
   Float_t ex[n]= {0};
   Float_t ey[n];

   ifstream infile("efficency_Eu.txt");

   Int_t i=0;
   while(!infile.eof())
   {	
	infile>>x[i]>>y[i]>>ey[i];
	i++;
   }
  
   TF1 *f1 = new TF1("f1", "[0]+([1]/x)+([2]/(x*x))",0,1500);
   f1->SetParameters(1,100,1);

   TGraph *dt = new TGraph();
   gStyle->SetOptFit(11111);

  TGraphErrors *gr = new TGraphErrors(i-1,x,y,ex,ey);
   
   
   
    





   gr->SetTitle("Efficency Vs Energy of Europium");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(31);
   gr->GetXaxis()->SetTitle("Energy (KeV)");
   gr->GetXaxis()->CenterTitle();
   gr->GetYaxis()->SetTitle("Absolute Efficency");
   gr->GetYaxis()->CenterTitle();
   gr->Fit(f1);
   
  //f1->Draw();
   gr->Draw("AP");
 //  f2->Draw("surf1",same);

   c1->Update();
}

