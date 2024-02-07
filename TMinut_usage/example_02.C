//A TYPICAL FIT EXAMPLE
//One of the most typical examples is to extract the signal out of a mixture of signal and background.

void example_02()
{
 TFile *fin = new TFile("example_data.root");
 TH1D *hist = (TH1D *)fin->Get("hist");

 hist->SetFillColor(kRed-9);
 hist->SetStats(false);
 hist->GetXaxis()->SetTitle("Mass");


//SIDEBAND SUBTRACTION Part
//Usually adopting a “sideband subtraction” is the simplest way to extract the yield of signal under the “peaking structure”
//However one still need to assume that “background is (nearly) flat” in the calculation of background.
//As far as the width of signal region is the same as the sideband regions, the # of signal can be extracted by:
//S = N_{signal region} - N_{sideband}

 TNtupleD *nt = (TNtupleD *)fin->Get("nt");
 const double MEAN = 1.0;
 const double SIGMA = 0.05;

 int count_sigregion = 0, count_sideband = 0;
 for(int evt=0; evt<nt->GetEntries(); evt++) {
 nt->GetEntry(evt);
 double mass = nt->GetArgs()[0];

 if (fabs(mass-MEAN)<SIGMA*3.) count_sigregion++;
 if (fabs(mass-MEAN)>SIGMA*3.5 &&
 fabs(mass-MEAN)<SIGMA*6.5) count_sideband++;
 }

 double S = count_sigregion - count_sideband;
 double dS = sqrt(count_sigregion+count_sideband);
 printf("N(sig) = %.1f +- %.1f\n",S,dS); 


//ESTIMATION WITH FITS (ESTIMATION WITH A LEAST-SQUARE FIT)
//Surely we are going to introduce something more sophisticated than a simple subtraction of sideband candidates.
//The result of the best fits can be obtained by minimizing a chi-2 value for N independent measurements:


 TF1 *f1 = new TF1("f1","[0]+[1]*x+[2]*gaus(2)");
 f1->SetParameters(100.,-30.,20.,1.,0.05);
 hist->Fit("f1"); 
 hist->Draw();
//comments
//How about the chi-2 value?
//Answer: The FCN value is exactly the final chi-2 (FCN=93.6468)
//Whats are the measurements and the associated uncertainties?
//Answer: the height of the bins in the histogram is the measurement; the error is just square-root of the height. This is the Poisson error
//N(degree of freedom) in the fit?
//Answer:  N(d.o.f.) = N(bins) – N(free parameters) = 100 – 5 = 95. 
//What's the confidence level?
//Answer: Use the ROOT TMath::Prob() command, it's ~52%.->Computation of the probability for a certain Chi-squared (chi2) and number of degrees of freedom (ndf)
//root [0] TMath::Prob(93.6468,95)
//(double) 0.520016


//BINNED LIKELIHOOD FIT? ->hist->Fit("f1","L");

}
