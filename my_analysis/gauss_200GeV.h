//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Feb 20 14:34:08 2021 by ROOT version 6.16/00
// from TTree events/Flattened root tree with event data
// found on file: ang_gauss_200GeV.root
//////////////////////////////////////////////////////////

#ifndef gauss_200GeV_h
#define gauss_200GeV_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class gauss_200GeV {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   ULong64_t       event_id;
   ULong64_t       hit_count;
   vector<long>    *hit_id;
   vector<unsigned long> *hit_trk_id;
   vector<long>    *hit_ptr_id;
   vector<string>  *hit_vol_name;
   vector<double>  *hit_x;
   vector<double>  *hit_y;
   vector<double>  *hit_z;
   vector<unsigned long> *hit_i_rep;
   vector<unsigned long> *hit_j_rep;
   vector<double>  *hit_e_loss;
   ULong64_t       trk_count;
   vector<unsigned long> *trk_id;
   vector<unsigned long> *trk_pdg;
   vector<unsigned long> *trk_parent_id;
   vector<double>  *trk_vtx_x;
   vector<double>  *trk_vtx_y;
   vector<double>  *trk_vtx_z;
   vector<double>  *trk_vtx_dir_x;
   vector<double>  *trk_vtx_dir_y;
   vector<double>  *trk_vtx_dir_z;
   vector<double>  *trk_mom;
   ULong64_t       gen_prt_count;
   vector<unsigned long> *gen_prt_id;
   vector<unsigned long> *gen_prt_vtx_id;
   vector<long>    *gen_prt_pdg;
   vector<unsigned long> *gen_prt_trk_id;
   vector<double>  *gen_prt_charge;
   vector<double>  *gen_prt_dir_x;
   vector<double>  *gen_prt_dir_y;
   vector<double>  *gen_prt_dir_z;
   vector<double>  *gen_prt_tot_mom;
   vector<double>  *gen_prt_tot_e;
   vector<double>  *gen_prt_time;
   vector<double>  *gen_prt_polariz_x;
   vector<double>  *gen_prt_polariz_y;
   vector<double>  *gen_prt_polariz_z;
   ULong64_t       gen_vtx_count;
   vector<unsigned long> *gen_vtx_id;
   vector<unsigned long> *gen_vtx_part_count;
   vector<double>  *gen_vtx_x;
   vector<double>  *gen_vtx_y;
   vector<double>  *gen_vtx_z;
   vector<double>  *gen_vtx_time;
   vector<double>  *gen_vtx_weight;

   // List of branches
   TBranch        *b_event_id;   //!
   TBranch        *b_hit_count;   //!
   TBranch        *b_hit_id;   //!
   TBranch        *b_hit_trk_id;   //!
   TBranch        *b_hit_ptr_id;   //!
   TBranch        *b_hit_vol_name;   //!
   TBranch        *b_hit_x;   //!
   TBranch        *b_hit_y;   //!
   TBranch        *b_hit_z;   //!
   TBranch        *b_hit_i_rep;   //!
   TBranch        *b_hit_j_rep;   //!
   TBranch        *b_hit_e_loss;   //!
   TBranch        *b_trk_count;   //!
   TBranch        *b_trk_id;   //!
   TBranch        *b_trk_pdg;   //!
   TBranch        *b_trk_parent_id;   //!
   TBranch        *b_trk_vtx_x;   //!
   TBranch        *b_trk_vtx_y;   //!
   TBranch        *b_trk_vtx_z;   //!
   TBranch        *b_trk_vtx_dir_x;   //!
   TBranch        *b_trk_vtx_dir_y;   //!
   TBranch        *b_trk_vtx_dir_z;   //!
   TBranch        *b_trk_mom;   //!
   TBranch        *b_gen_prt_count;   //!
   TBranch        *b_gen_prt_id;   //!
   TBranch        *b_gen_prt_vtx_id;   //!
   TBranch        *b_gen_prt_pdg;   //!
   TBranch        *b_gen_prt_trk_id;   //!
   TBranch        *b_gen_prt_charge;   //!
   TBranch        *b_gen_prt_dir_x;   //!
   TBranch        *b_gen_prt_dir_y;   //!
   TBranch        *b_gen_prt_dir_z;   //!
   TBranch        *b_gen_prt_tot_mom;   //!
   TBranch        *b_gen_prt_tot_e;   //!
   TBranch        *b_gen_prt_time;   //!
   TBranch        *b_gen_prt_polariz_x;   //!
   TBranch        *b_gen_prt_polariz_y;   //!
   TBranch        *b_gen_prt_polariz_z;   //!
   TBranch        *b_gen_vtx_count;   //!
   TBranch        *b_gen_vtx_id;   //!
   TBranch        *b_gen_vtx_part_count;   //!
   TBranch        *b_gen_vtx_x;   //!
   TBranch        *b_gen_vtx_y;   //!
   TBranch        *b_gen_vtx_z;   //!
   TBranch        *b_gen_vtx_time;   //!
   TBranch        *b_gen_vtx_weight;   //!

   gauss_200GeV(TTree *tree=0);
   virtual ~gauss_200GeV();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef gauss_200GeV_cxx
gauss_200GeV::gauss_200GeV(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ang_gauss_200GeV.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ang_gauss_200GeV.root");
      }
      f->GetObject("events",tree);

   }
   Init(tree);
}

gauss_200GeV::~gauss_200GeV()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t gauss_200GeV::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t gauss_200GeV::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void gauss_200GeV::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   hit_id = 0;
   hit_trk_id = 0;
   hit_ptr_id = 0;
   hit_vol_name = 0;
   hit_x = 0;
   hit_y = 0;
   hit_z = 0;
   hit_i_rep = 0;
   hit_j_rep = 0;
   hit_e_loss = 0;
   trk_id = 0;
   trk_pdg = 0;
   trk_parent_id = 0;
   trk_vtx_x = 0;
   trk_vtx_y = 0;
   trk_vtx_z = 0;
   trk_vtx_dir_x = 0;
   trk_vtx_dir_y = 0;
   trk_vtx_dir_z = 0;
   trk_mom = 0;
   gen_prt_id = 0;
   gen_prt_vtx_id = 0;
   gen_prt_pdg = 0;
   gen_prt_trk_id = 0;
   gen_prt_charge = 0;
   gen_prt_dir_x = 0;
   gen_prt_dir_y = 0;
   gen_prt_dir_z = 0;
   gen_prt_tot_mom = 0;
   gen_prt_tot_e = 0;
   gen_prt_time = 0;
   gen_prt_polariz_x = 0;
   gen_prt_polariz_y = 0;
   gen_prt_polariz_z = 0;
   gen_vtx_id = 0;
   gen_vtx_part_count = 0;
   gen_vtx_x = 0;
   gen_vtx_y = 0;
   gen_vtx_z = 0;
   gen_vtx_time = 0;
   gen_vtx_weight = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("hit_count", &hit_count, &b_hit_count);
   fChain->SetBranchAddress("hit_id", &hit_id, &b_hit_id);
   fChain->SetBranchAddress("hit_trk_id", &hit_trk_id, &b_hit_trk_id);
   fChain->SetBranchAddress("hit_ptr_id", &hit_ptr_id, &b_hit_ptr_id);
   fChain->SetBranchAddress("hit_vol_name", &hit_vol_name, &b_hit_vol_name);
   fChain->SetBranchAddress("hit_x", &hit_x, &b_hit_x);
   fChain->SetBranchAddress("hit_y", &hit_y, &b_hit_y);
   fChain->SetBranchAddress("hit_z", &hit_z, &b_hit_z);
   fChain->SetBranchAddress("hit_i_rep", &hit_i_rep, &b_hit_i_rep);
   fChain->SetBranchAddress("hit_j_rep", &hit_j_rep, &b_hit_j_rep);
   fChain->SetBranchAddress("hit_e_loss", &hit_e_loss, &b_hit_e_loss);
   fChain->SetBranchAddress("trk_count", &trk_count, &b_trk_count);
   fChain->SetBranchAddress("trk_id", &trk_id, &b_trk_id);
   fChain->SetBranchAddress("trk_pdg", &trk_pdg, &b_trk_pdg);
   fChain->SetBranchAddress("trk_parent_id", &trk_parent_id, &b_trk_parent_id);
   fChain->SetBranchAddress("trk_vtx_x", &trk_vtx_x, &b_trk_vtx_x);
   fChain->SetBranchAddress("trk_vtx_y", &trk_vtx_y, &b_trk_vtx_y);
   fChain->SetBranchAddress("trk_vtx_z", &trk_vtx_z, &b_trk_vtx_z);
   fChain->SetBranchAddress("trk_vtx_dir_x", &trk_vtx_dir_x, &b_trk_vtx_dir_x);
   fChain->SetBranchAddress("trk_vtx_dir_y", &trk_vtx_dir_y, &b_trk_vtx_dir_y);
   fChain->SetBranchAddress("trk_vtx_dir_z", &trk_vtx_dir_z, &b_trk_vtx_dir_z);
   fChain->SetBranchAddress("trk_mom", &trk_mom, &b_trk_mom);
   fChain->SetBranchAddress("gen_prt_count", &gen_prt_count, &b_gen_prt_count);
   fChain->SetBranchAddress("gen_prt_id", &gen_prt_id, &b_gen_prt_id);
   fChain->SetBranchAddress("gen_prt_vtx_id", &gen_prt_vtx_id, &b_gen_prt_vtx_id);
   fChain->SetBranchAddress("gen_prt_pdg", &gen_prt_pdg, &b_gen_prt_pdg);
   fChain->SetBranchAddress("gen_prt_trk_id", &gen_prt_trk_id, &b_gen_prt_trk_id);
   fChain->SetBranchAddress("gen_prt_charge", &gen_prt_charge, &b_gen_prt_charge);
   fChain->SetBranchAddress("gen_prt_dir_x", &gen_prt_dir_x, &b_gen_prt_dir_x);
   fChain->SetBranchAddress("gen_prt_dir_y", &gen_prt_dir_y, &b_gen_prt_dir_y);
   fChain->SetBranchAddress("gen_prt_dir_z", &gen_prt_dir_z, &b_gen_prt_dir_z);
   fChain->SetBranchAddress("gen_prt_tot_mom", &gen_prt_tot_mom, &b_gen_prt_tot_mom);
   fChain->SetBranchAddress("gen_prt_tot_e", &gen_prt_tot_e, &b_gen_prt_tot_e);
   fChain->SetBranchAddress("gen_prt_time", &gen_prt_time, &b_gen_prt_time);
   fChain->SetBranchAddress("gen_prt_polariz_x", &gen_prt_polariz_x, &b_gen_prt_polariz_x);
   fChain->SetBranchAddress("gen_prt_polariz_y", &gen_prt_polariz_y, &b_gen_prt_polariz_y);
   fChain->SetBranchAddress("gen_prt_polariz_z", &gen_prt_polariz_z, &b_gen_prt_polariz_z);
   fChain->SetBranchAddress("gen_vtx_count", &gen_vtx_count, &b_gen_vtx_count);
   fChain->SetBranchAddress("gen_vtx_id", &gen_vtx_id, &b_gen_vtx_id);
   fChain->SetBranchAddress("gen_vtx_part_count", &gen_vtx_part_count, &b_gen_vtx_part_count);
   fChain->SetBranchAddress("gen_vtx_x", &gen_vtx_x, &b_gen_vtx_x);
   fChain->SetBranchAddress("gen_vtx_y", &gen_vtx_y, &b_gen_vtx_y);
   fChain->SetBranchAddress("gen_vtx_z", &gen_vtx_z, &b_gen_vtx_z);
   fChain->SetBranchAddress("gen_vtx_time", &gen_vtx_time, &b_gen_vtx_time);
   fChain->SetBranchAddress("gen_vtx_weight", &gen_vtx_weight, &b_gen_vtx_weight);
   Notify();
}

Bool_t gauss_200GeV::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void gauss_200GeV::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t gauss_200GeV::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef gauss_200GeV_cxx
