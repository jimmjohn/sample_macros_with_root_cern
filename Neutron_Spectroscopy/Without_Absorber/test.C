//
// test500ped.cxx
//
// Usage:
//  root [0] .x test500ped.cxx
//  root [1] TFile *f = TFile::Open("test500ped.root", "read");
//  root [2] f->ls();
//  root [3] tree->Print();
//  root [4] tree->Draw("ped");
//  root [5] tree->Draw("ped[0]");
//  root [6] tree->Draw("ped[1]");
//  root [7] tree->Draw("ped[1023]");
//
#include "TFile.h"
#include "TTree.h"
#include <cstdio>
void test500ped(void) {
  UShort_t ped[1024]; // an array of 16 bit unsigned integers
  FILE *fin = fopen("test500ped.dat", "r");
  if (!fin) {
    printf("Error : test500ped.dat not found!\n");
    return;
  }
  TFile *fout = TFile::Open("test500ped.root", "recreate");
  TTree *tree = new TTree("tree", "A TTree from test500ped.dat");
  // "==> Case A" in http://root.cern.ch/root/html/TTree.html
  tree->Branch("ped", ped, "ped[1024]/s"); // "/s" = "UShort_t"
  while ( sizeof(ped) == fread(ped, 1, sizeof(ped), fin) ) {
#if 0 /* 0 or 1 */
    // swap the high and low bytes (endianness correction)
    for (Int_t i = 0; i < ((Int_t)sizeof(ped)); i += 2) {
      UChar_t c = *((UChar_t *)ped + i);
      *((UChar_t *)ped + i) = *((UChar_t *)ped + i + 1);
      *((UChar_t *)ped + i + 1) = c;
    }
#endif /* 0 or 1 */
    tree->Fill();
  }
  fclose(fin); // no longer needed
  tree->Write();
  delete fout; // automatically deletes the "tree", too
  return;
}
