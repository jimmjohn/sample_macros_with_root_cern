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


void coincidence()
{
double t1=0,t2=0;
double psd0, psd1,energy1,energy2;
UInt_t time1=0,time2=0,temp1,temp2,i=0,j=0;
UShort_t ql1,ql2;
UInt_t ex1,ex2;
UShort_t qs1,qs2;

ifstream fin1("AmBe_no_11_028_ls_0.dat", ios::in | ios::binary);
ifstream fin2("AmBe_no_11_028_ls_2.dat", ios::in | ios::binary);

ofstream myfile;
myfile.open ("time_comparison.txt");

auto h1a = new TH1F("h1a","Energy histogram channel 2 With Coincidence",4096,0,65536);
auto h1b = new TH1F("h1a","Energy histogram channel 2 Without Coincidence",4096,0,65536);

if (!fin1) {
printf("Error :  Channel 0 File  not found!\n");
return;
}
if (!fin2) {
printf("Error :  Channel 1 not found!\n");
return;
}



while(!fin1.eof())
{
	temp1=time1;
	fin1.read((char*)&time1,4);  // read record
	fin1.read((char*)&ql1,2);    // read record
	fin1.read((char*)&ex1,4);    // read record
	fin1.read((char*)&qs1,2);    // read record
	energy1=Long64_t(ql1*0.2157)+28.01;
	if(temp1>time1 && j>2)
	{
		t1=t1+4294967296.0*pow(10,-9);
	}
	//myfile<<t1+(double(time1)*pow(10,-9))<<"\n";
	if((energy1>4180.0) && (energy1<4270.0))           // Correct Values 4180.0 to 4270.0---- 
        {
	 while(t2+(double(time2)*pow(10,-9)) <= t1+((double(time1)+50.0)*pow(10,-9)) && !fin2.eof())
	 {
		temp2=time2;
		fin2.read((char*)&time2,4);  // read record
		fin2.read((char*)&ql2,2);    // read record
		fin2.read((char*)&ex2,4);    // read record
		fin2.read((char*)&qs2,2);    // read record
		energy2=Long64_t(ql2*0.2989)+22.62;
		h1b->Fill(energy2);
		if(temp2>time2 && i>2)
		{
			t2=t2+4294967296.0*pow(10,-9);
		}

		if(t2+(double(time2)*pow(10,-9)) >= (t1+(double(time1)-50.0)*pow(10,-9)))
		{
			h1a->Fill(energy2);
			//printf("%d %lf %.17g \n",i,t1+(double(time1)*pow(10,-9)),t2+(double(time2)*pow(10,-9)));
		myfile<<i<<"\t"<<t1+(double(time1)*pow(10,-9))<<"\t"<<t2+(double(time2)*pow(10,-9))<<"\t"<<energy1<<"\t"<<energy2<<"\n";
		
		}
		i++;
	 }
	}
	j++;
}



TCanvas *canvas= new TCanvas("canvas","Canvas",1000,1000);
h1a->Draw("colz");
h1b->Draw("same");

myfile.close();
}
