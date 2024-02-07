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


void gerrors1() {
   //Draw a graph with error bars
   // To see the output of this macro, click begin_html <a href="gif/gerrors.gif">here</a>. end_html
   //Author: Rene Brun

   TCanvas *c1 = new TCanvas("c1","Half Life Plotting",1000,400);

   //c1->GetFrame()->SetFillColor(21);
   //c1->GetFrame()->SetBorderSize(12);
   c1->Divide(3,1);
   c1->cd(1);
   const Int_t n=50;
   Float_t x[n];
   Float_t y[n];
   Float_t ex[n]= {0};
   Float_t ey[n];
   ifstream infile("Ten_Minutes.txt");
   Int_t i=0;
   while(!infile.eof())
   {	
	infile>>x[i]>>y[i]>>ey[i];
	i++;
   }
   TF1 *f1 = new TF1("f1", "[0]*exp(-1.0*[1]*x)",0,7200);
   f1->SetParameters(100,0.000045);
   gStyle->SetOptFit(11111);
   TGraphErrors *gr = new TGraphErrors(i-1,x,y,ex,ey);
   gr->SetTitle("Time Vs Counts");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->GetXaxis()->SetTitle("Time (Sec)");
   gr->GetYaxis()->SetTitle("Counts");
   gr->GetXaxis()->CenterTitle();
   gr->GetYaxis()->CenterTitle();
   gr->Fit(f1);
   


  //f1->Draw();
   gr->Draw("AP");
 //  f2->Draw("surf1",same);

   TLatex *l1 = new TLatex();
   l1->SetTextAlign(21);
   l1->SetTextFont(2);
   l1->SetTextSize(0.05);
   l1->SetNDC();
   l1->DrawLatex(0.25,0.83,"(a)");
   

   c1->cd(2);
   ifstream infile2("Fifteen_Minutes.txt");
    i=0;
    Float_t a[n];
   Float_t b[n];
   Float_t ea[n]= {0};
   Float_t eb[n];
   while(!infile2.eof())
   {	
	infile2>>a[i]>>b[i]>>eb[i];
	i++;
   }
   TF1 *f2 = new TF1("f2", "[0]*exp(-1.0*[1]*x)",0,7200);
   f2->SetParameters(100,0.000045);
   gStyle->SetOptFit(11111);
   TGraphErrors *gs = new TGraphErrors(i-1,a,b,ea,eb);
   gs->SetTitle("Time Vs Counts");
   gs->SetMarkerColor(4);
   gs->SetMarkerStyle(21);
   gs->GetXaxis()->SetTitle("Time (Sec)");
   gs->GetYaxis()->SetTitle("Counts");
   gs->GetXaxis()->CenterTitle();
   gs->GetYaxis()->CenterTitle();
   gs->Fit(f2);
   
  //f1->Draw();
   gs->Draw("AP");
 //  f2->Draw("surf1",same);

   TLatex *l2 = new TLatex();
   l2->SetTextAlign(21);
   l2->SetTextFont(2);
   l2->SetTextSize(0.05);
   l2->SetNDC();
   l2->DrawLatex(0.25,0.83,"(b)");

  c1->cd(3);
 ifstream infile3("Twenty_Minutes.txt");

   i=0;
    Float_t p[n];
   Float_t q[n];
   Float_t ep[n]= {0};
   Float_t eq[n];
   while(!infile3.eof())
   {	
	infile3>>p[i]>>q[i]>>eq[i];
	i++;
   }
  
   TF1 *f3 = new TF1("f3", "[0]*exp(-1.0*[1]*x)",0,7200);
   f3->SetParameters(100,0.000045);
   gStyle->SetOptFit(11111);

  TGraphErrors *gt = new TGraphErrors(i-1,p,q,ep,eq);
   
   
   
    





   gt->SetTitle("Time Vs Counts");
   gt->SetMarkerColor(4);
   gt->SetMarkerStyle(21);
   gt->GetXaxis()->SetTitle("Time (Sec)");
   gt->GetYaxis()->SetTitle("Counts");
   gt->GetXaxis()->CenterTitle();
   gt->GetYaxis()->CenterTitle();
   gt->Fit(f3);
   
  //f1->Draw();
   gt->Draw("AP");
 //  f2->Draw("surf1",same);

   TLatex *l3 = new TLatex();
   l3->SetTextAlign(21);
   l3->SetTextFont(2);
   l3->SetTextSize(0.05);
   l3->SetNDC();
   l3->DrawLatex(0.25,0.83,"(c)");

}

