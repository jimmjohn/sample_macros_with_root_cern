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

  // open a new ROOT file
  TFile *f = TFile::Open("Avalanche_Size.root", "RECREATE");

  TGraph* avlan_size_1 = new TGraph();
  TGraph* avlan_size_2 = new TGraph();
  TGraph* avlan_size_3 = new TGraph();
  TGraph* avlan_size_4 = new TGraph();

  TRandom1 *r3  = new TRandom1();
  TRandom1 *r15 = new TRandom1();
  TRandom1 *r16 = new TRandom1();
  TRandom1 *r17 = new TRandom1();

  double deltaX = 0.0002;

  for(int iiter=0; iiter<4; iiter++) {

    int i=0;
    double n1=1;

    for(double x=0; x<2.0; x=x+deltaX) {

      double n2=0;
      double nBar = exp((alpha-eta)*deltaX);

      for(double eleNo=0;eleNo<n1;eleNo++) {

	//double s3 = r3->Uniform(0,1);
	//cout<<"s3="<<s3<<endl;
	int selector=0;
	//if(s3<1.0/3.0){selector=0;}
	//if(s3<2.0/3.0 && s3>=1.0/3.0){selector=1;}
	//if(s3>2.0/3.0){selector=2;}

	if(alpha == eta){selector=1;}
	if(alpha == 0){selector=2;}

	double n15=0;
	double n16=0;
	double n17=0;

	switch(selector) {
	case 0: {
	  //Generating Equation 7=>15
	  double s15 = r15->Uniform(0,1);
	  //cout<<"Number15="<<s15<<endl;
	  double limit15 = k*(nBar-1)/(nBar-k);
	  if(s15<limit15) {
	    n15 = 0;
	    //cout<<"n15="<<n15<<endl;
	  }
	  if(s15>limit15) {
	    n15 = 1.0 + (int)(log((nBar-k)*(1-s15)/(nBar*(1-k)))/log(1.0-((1-k)/(nBar-k))));
	    //cout<<"n15="<<n15<<endl;
	  }
	  n2 = n2 + n15;
	  break;
	}

	case 1: {
	  //Generating Equation 11=>16
	  double s16 = r16->Uniform(0,1);
	  //cout<<"Number16="<<s16<<endl;
	  double limit16 = (alpha*x)/(1.0+(alpha*x));
	  if(s16<limit16) {
	    n16 = 0;
	    //cout<<"n16="<<n16<<endl;
	  }
	  if(s16>limit16) {
	    n16 = 1.0 + (int)(log((1.0-s16)*(1.0+(alpha*x)))/log((alpha*x)/(1.0+(alpha*x))));
	    //cout<<"n16="<<n16<<endl;
	  }
	  n2 = n2 + n16;
	  break;
	}
	case 2: {
	  //Generating Equation 13=>17
	  double s17 = r17->Uniform(0,1);
	  //cout<<"Number17="<<s17<<endl;
	  double limit17 = exp(-1.0*eta*x);
	  if(s17>limit17) {
	    n17 = 0;
	    //cout<<"n17="<<n17<<endl;
	  }
	  if(s17<limit17) {
	    n17 = 1.0;
	    //cout<<"n17="<<n17<<endl;
	  }
	  n2 = n2 + n17;
	  break;
	}
	} // switch case ending
      }//eleNo loop ending

      switch(iiter){
      case 0:
	     avlan_size_1->SetPoint(i,x,n1);
	     break;
      case 1:
	     avlan_size_2->SetPoint(i,x,n1);
	     break;
      case 2:
	     avlan_size_3->SetPoint(i,x,n1);
	     break;
      case 3:
	     avlan_size_4->SetPoint(i,x,n1);
	     break;
      }

      //cout<<"x="<<x<<"\tn1="<<n1<<endl;
      n1 = n2;
      i++;
    }//x loop ending

  }//iiter loop ending


  TCanvas *c1 = new TCanvas("c1", "canvas",1000,2000);
  c1->cd();
  c1->Divide(2,2,0,0);
  gStyle->SetOptFit(1111);
  c1->cd(1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.15);
  gPad->SetTopMargin(0.15);
  gPad->SetBottomMargin(0.15);
  avlan_size_1->SetMarkerStyle(8);
  avlan_size_1->SetMarkerSize(1);
  avlan_size_1->Draw("AP");


  f->cd();
  avlan_size_1->Write("Avalanche_Size_1");
  avlan_size_2->Write("Avalanche_Size_2");
  avlan_size_3->Write("Avalanche_Size_3");
  avlan_size_4->Write("Avalanche_Size_4");

  f->Close();

  return 0;

}
