#define gauss_200GeV_cxx
#include "gauss_200GeV.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <fstream>

using std::cout;

void gauss_200GeV::Loop()
{
				//   In a ROOT session, you can do:
				//      root> .L gauss_200GeV.C
				//      root> gauss_200GeV t
				//      root> t.GetEntry(12); // Fill t data members with entry number 12
				//      root> t.Show();       // Show values of entry 12
				//      root> t.Show(16);     // Read and show values of entry 16
				//      root> t.Loop();       // Loop on all entries
				//

				//     This is the loop skeleton where:
				//    jentry is the global entry number in the chain
				//    ientry is the entry number in the current Tree
				//  Note that the argument to GetEntry must be:
				//    jentry for TChain::GetEntry
				//    ientry for TTree::GetEntry and TBranch::GetEntry
				//
				//       To read only selected branches, Insert statements like:
				// METHOD1:
				//    fChain->SetBranchStatus("*",0);  // disable all branches
				//    fChain->SetBranchStatus("branchname",1);  // activate branchname
				// METHOD2: replace line
				//    fChain->GetEntry(jentry);       //read all branches
				//by  b_branchname->GetEntry(ientry); //read only this branch
				if (fChain == 0) return;

				Long64_t nentries = fChain->GetEntriesFast();

				Long64_t nbytes = 0, nb = 0;

				ofstream ofs ("e_loss_lay_200GeV.txt");

				int eventID;

				const int cell_z = 30;
				const int cell_xy = 144;

				vector<vector<double>> itr;
				vector<vector<double>> cell_lay(cell_z, vector<double>(0));
				vector<double> energy_lay(cell_z, 0);
				vector<double> energy_cell(cell_xy, 0);
				vector<double> energy_xz(cell_z, 0);

				string cell_lay_1;
				string cell_lay_2;
				string z = "z";

				string cell_xy_1;
				string cell_xy_2;
				string cell_xy_3;
				string under_bar = "_";

				int lay_number_1, lay_number_2;
				int cell_number_1_1, cell_number_1_2, cell_number_1_3;
				int cell_number_2_1, cell_number_2_2, cell_number_2_3;
				int cell_number;

				int l = lay_number_1;

				double hit_x_cell, hit_y_cell, hit_z_cell;
				double average_x_weighted_E, average_y_weighted_E;

				int x_l, y_k;

				double e_loss_at_cell = 0;
				double e_loss_cell_SUM = 0;
				double e_cell_vec_SUM = 0;
				double xE_cell_SUM = 0, yE_cell_SUM = 0;

				double energy_SUM_77 = 0;

				double p_truth = 0;
				double p_T = 0, p_T_2 = 0;

				double dir_y;

				double dir_x_truth, dir_y_truth;
				double pos_x_truth, pos_y_truth;

				TH1D* e_loss_hist = new TH1D("", "energy loss at ZDC 200GeV neutron", 221, 0, 220);

				TH1D* energy_layer = new TH1D("", "energy loss at each layer", 30, 36750, 38250);
				TH1D* energy_xz_hist = new TH1D("", "energy loss at each layer xz", 30, 36750, 38250);
				TH2D* energy_cell_lego = new TH2D("", "energy loss at each cell 200GeV neutron", 12, 660, 1260, 12, -300, 300);
				TH2D* energy_cell_hist = new TH2D("", "distriution cell ", 12, 660, 1260, 12, -300, 300);

				TH2D* hit_dist = new TH2D("", "hit distribution", 6001, 660, 1260, 6001, -300, 300); 

				TH1D* p_T_dist = new TH1D("", "p_T^2 distribution", 100, 0, 1.0);

				TH2D* truth_dist = new TH2D("", "truth dist at ZDC", 6001, 660, 1260, 6001, -300, 300);	
				TH2D* hit_position = new TH2D("", "hit position weighted energy", 1001, 500, 1500, 1001, -500, 500);

				for (Long64_t jentry=0; jentry<nentries;jentry++) {
								Long64_t ientry = LoadTree(jentry);
								if (ientry < 0) break;
								nb = fChain->GetEntry(jentry);   nbytes += nb;
								// if (Cut(ientry) < 0) continue;

								cout << "Event ID" << "\t" << jentry << "\n";

								eventID = jentry;

								e_loss_cell_SUM = 0;
								e_cell_vec_SUM = 0;

								xE_cell_SUM = 0;
								yE_cell_SUM = 0;

								vector<double> energy_lay(cell_z, 0);
								vector<double> energy_cell(cell_xy, 0);
								vector<double> energy_xz(cell_z, 0);

								for(int i=0; i<hit_count; i++){

												string vol_name = hit_vol_name->at(i);
												TString zdc_name = "ffi_ZDC_HCAL_Phys";
												bool StartWith( zdc_name );

												if( vol_name.find( zdc_name ) == 0 ){

																e_loss_at_cell = hit_e_loss->at(i);
																e_loss_cell_SUM += e_loss_at_cell;

																hit_x_cell = hit_x->at(i);
																hit_y_cell = hit_y->at(i);
																hit_z_cell = hit_z->at(i);

																xE_cell_SUM += (e_loss_at_cell)*(hit_x_cell);
																yE_cell_SUM += (e_loss_at_cell)*(hit_y_cell);

																//cout << "hit_x_cell" << "\t" << hit_x_cell << "\t" << "hit_y_cell" << "\t" << hit_y_cell << "\n";

																cell_lay_1 = vol_name.substr(vol_name.length() - 2, 1);
																cell_lay_2 = vol_name.substr(vol_name.length() - 3, 1);

																cell_xy_1 = vol_name.substr(19, 1);
																cell_xy_2 = vol_name.substr(20, 1);
																cell_xy_3 = vol_name.substr(21, 1);


																//cout << "vol_name" << "\t" << vol_name << "\n";

																bool layer_1 = ( lay_number_1 == 2 );
																bool layer_2 = ( lay_number_1 == 3 );

																bool lay_1_if = ( cell_lay_1 == z );
																bool lay_2_if = ( cell_lay_2 == z );

																bool cell_xy_1_if = ( cell_xy_1 == under_bar );
																bool cell_xy_2_if = ( cell_xy_2 == under_bar );
																bool cell_xy_3_if = ( cell_xy_3 == under_bar );

																bool cell_x_u = ( hit_x_cell > 960 );
																bool cell_x_d = ( hit_x_cell < 1010 );

																bool hit_0 = ( cell_number_1_2 == 77 );

																if( lay_1_if ){

																				string lay_num_1 = vol_name.substr(vol_name.length() - 1, 1);
																				lay_number_1 = atoi(lay_num_1.c_str());

																				energy_lay[lay_number_1] += e_loss_at_cell;
																				cell_lay[lay_number_1].push_back(e_loss_at_cell);

																				if( cell_x_u && cell_x_d ){

																								energy_xz[lay_number_1] += e_loss_at_cell;

																				}

																				//cout << "lay_number_1" << "\t" << lay_number_1 << "\n";

																				if( layer_1 ){

																								if( cell_xy_1_if ){

																												string cell_num_1_1 = vol_name.substr(18, 1);
																												cell_number_1_1 = atoi(cell_num_1_1.c_str());
																												energy_cell[cell_number_1_1] += e_loss_at_cell;

																												//cout << "order of cell number 1" << "\t" << cell_number_1_1 << "\n";
																												//cout << "cell_number_1_1" << "\t" << cell_number_1_1 << "\n";

																								}

																								if( cell_xy_2_if ){

																												string cell_num_1_2 = vol_name.substr(18, 2);
																												cell_number_1_2 = atoi(cell_num_1_2.c_str());
																												energy_cell[cell_number_1_2] += e_loss_at_cell;

																												if( hit_0 ){

																																hit_dist->Fill(hit_x_cell, hit_y_cell);

																																//cout << "vol_name" << "\t" << vol_name << "\n";
																																//cout << "order of cell number 2" << "\t" << cell_number_1_2 << "\n";

																												}

																												//cout << "order of cell number 2" << "\t" << cell_number_1_2 << "\n";
																												//cout << "cell_num_1_2" << "\t" << cell_num_1_2 << "\n";

																								}

																								if( cell_xy_3_if ){

																												string cell_num_1_3 = vol_name.substr(18, 3);
																												cell_number_1_3 = atoi(cell_num_1_3.c_str());
																												energy_cell[cell_number_1_3] += e_loss_at_cell;

																												//cout << "order of cell number 3" << "\t" << cell_number_1_3 << "\n";
																												//cout << "cell_num_1_3" << "\t" << cell_num_1_3 << "\n";

																								}		

																				}

																				//cout << "order of lay number is 1" << "\t" << lay_number_1 << "\n";

																}

																else{

																				string lay_num_2 = vol_name.substr(vol_name.length() - 2);
																				lay_number_2 = atoi(lay_num_2.c_str());

																				energy_lay[lay_number_2] += e_loss_at_cell;
																				cell_lay[lay_number_2].push_back(e_loss_at_cell);

																				if( cell_x_u && cell_x_d ){

																								energy_xz[lay_number_2] += e_loss_at_cell;

																				}

																				if( cell_xy_1_if ){

																								string cell_num_2_1 = vol_name.substr(18, 1);
																								cell_number_2_1 = atoi(cell_num_2_1.c_str());
																								//energy_cell[lay_number_2][cell_number_2_1] += e_loss_at_cell;

																				}

																				else if( cell_xy_2_if ){

																								string cell_num_2_2 = vol_name.substr(18, 2);
																								cell_number_2_2 = atoi(cell_num_2_2.c_str());
																								//energy_cell[lay_number_2][cell_number_2_2] += e_loss_at_cell;

																				}

																				else{

																								string cell_num_2_3 = vol_name.substr(18, 3);
																								cell_number_2_3 = atoi(cell_num_2_3.c_str());
																								//energy_cell[lay_number_2][cell_number_2_3] += e_loss_at_cell;

																				}		

																				//cout << "order of lay number is 2" << "\t" << lay_number_2 << "\n";

																}

												}

												else continue;

								}

								average_x_weighted_E = (xE_cell_SUM)/(e_loss_cell_SUM);
								average_y_weighted_E = (yE_cell_SUM)/(e_loss_cell_SUM);

								for(int n=0; n<gen_prt_count; n++){

												p_truth = gen_prt_tot_mom->at(n);

												dir_y = gen_prt_dir_y->at(n);

												p_T = (p_truth)*(dir_y);
												p_T_2 = p_T * p_T;

												dir_x_truth = gen_prt_dir_x->at(n);
												dir_y_truth = gen_prt_dir_y->at(n);

												pos_x_truth = (dir_x_truth)*37500;
												pos_y_truth = (dir_y_truth)*37500;

								}

								//truth_dist->Fill(pos_x_truth, pos_y_truth);

								bool e_not_0 = ( e_loss_cell_SUM != 0 );

								if( e_not_0 ){

												e_loss_hist->Fill(e_loss_cell_SUM);

												hit_position->Fill(average_x_weighted_E, average_y_weighted_E);

												for(int j=0; j<cell_z; j++){

																//itr = energy_lay[j].end() - 1;
																double energy_SUM_lay = energy_lay[j];
																//double energy_SUM_lay = *itr;
																double energy_SUM_lay_xz = energy_xz[j];

																double z_j = 36775 + j*50;

																energy_layer->Fill(z_j, energy_SUM_lay);
																energy_xz_hist->Fill(z_j, energy_SUM_lay_xz);

																ofs << z_j << "\t" << energy_SUM_lay*0.001012 << "\n";

																//cout << "energy_SUM_lay" << "\t" << j << "\t" << energy_SUM_lay << "\n";

												}

												for(int k=0; k<12; k++){

																y_k = 275 - k*50;

																for(int l=0; l<12; l++){

																				int m = l + k*12;
																				double energy_SUM_cell = energy_cell[m];

																				x_l = 1235 - l*50;

																				energy_cell_lego->Fill(x_l, y_k, energy_SUM_cell);

																				//cout << "cell number" << "\t" << m << "\t" << "x_l" << "\t" << x_l << "\t" << "y_k" << "\t" << y_k << "\t" << energy_SUM_cell << "\n";

																				if( m==77 ){

																								energy_SUM_77 += energy_SUM_cell;
																								//energy_cell_lego->Fill(x_l, y_k, energy_SUM_cell);
																								//cout << "pos of cell77" << "\t" << x_l << "\t" << y_k << "\t" << energy_SUM_cell << "\n";
																								//cout << "cell number of over 250" << "\t" << m << "\n";

																				}

																}

												}

												truth_dist->Fill(pos_x_truth, pos_y_truth);

								}

								p_T_dist->Fill(p_T_2);
								//truth_dist->Fill(pos_x_truth, pos_y_truth);

				}

				ofs.close();

				energy_layer->Scale(0.001012);
				energy_xz_hist->Scale(0.001012);
				energy_cell_lego->Scale(0.001012);
				//energy_layer->SetFillColor(kBlue);
				int bin = energy_layer->GetNbinsX();
				double sum = energy_layer->Integral();
				double sum_cell = energy_cell_lego->Integral();
				double max = energy_cell_lego->GetBinContent(energy_cell_lego->GetMaximumBin());

				cout << "sum_cell" << "\t" << sum_cell << "\n";
				//cout << "sum of energy cell77" << "\t" << energy_SUM_77 << "\n";
				cout << "maximum of deposited energy each cell" << "\t" << max << "\n";

				TCanvas* c1 = new TCanvas("c1", "", 600, 600);
				TCanvas* c2 = new TCanvas("c2", "", 600, 600);
				TCanvas* c3 = new TCanvas("c3", "", 600, 600);
				TCanvas* c4 = new TCanvas("c4", "", 600, 600);
				TCanvas* c5 = new TCanvas("c5", "", 600, 600);
				TCanvas* c6 = new TCanvas("c6", "", 600, 600);
				TCanvas* c7 = new TCanvas("c7", "", 600, 600);
				//TCanvas* c8 = new TCanvas("c8", "", 600, 600);

				c1->cd();
				e_loss_hist->Draw();
				c2->cd();
				energy_layer->Sumw2(0);
				energy_layer->Draw();
				c3->cd();
				energy_cell_lego->Sumw2(0);
				energy_cell_lego->Draw("lego2z");
				c4->cd();
				p_T_dist->Sumw2(0);
				p_T_dist->Draw();
				c5->cd();
				truth_dist->Draw();
				c6->cd();
				energy_cell_lego->Sumw2(0);
				energy_cell_lego->Draw("contz");
				truth_dist->Draw("sames");
				c7->cd();
				energy_xz_hist->Sumw2(0);
				energy_xz_hist->Draw();
				//c8->cd();
				//hit_dist->Draw();

}
