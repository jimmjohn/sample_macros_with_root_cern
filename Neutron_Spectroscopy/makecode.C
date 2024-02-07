{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Mon Jan  8 20:54:01 2018 by ROOT version6.10/02)
//   from TTree Eventtree/All the Info Excluding Histograms
//   found on file: treestoreblank.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("treestoreblank.root");
   if (!f) {
      f = new TFile("treestoreblank.root");
   }
    f->GetObject("Eventtree",tree);

//Declaration of leaves types
   UInt_t          file1_time1;
   Double_t        file1_energy1;
   UInt_t          file2_time2;
   Double_t        file2_energy2;
   UInt_t          file3_time3;
   Double_t        file3_energy3;

   // Set branch addresses.
   Eventtree->SetBranchAddress("file1",&file1_time1);
   Eventtree->SetBranchAddress("file1",&file1_energy1);
   Eventtree->SetBranchAddress("file2",&file2_time2);
   Eventtree->SetBranchAddress("file2",&file2_energy2);
   Eventtree->SetBranchAddress("file3",&file3_time3);
   Eventtree->SetBranchAddress("file3",&file3_energy3);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// Eventtree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = Eventtree->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += Eventtree->GetEntry(i);
//   }
}
