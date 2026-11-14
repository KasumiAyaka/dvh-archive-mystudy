//mkroot.C--make rootfile
//A.Kasumi
//June 29 2021
//ok

//int makerootfile()
{
#include<TFile.h>
#include<Th1.h>
#include <fstream>

	ifstream data("../data/output.txt");
 	 //ifstream data("output.txt");
 
	int raw0, raw1,raw2,flg;
	double x0,y0, ax0 , ay0 ,  x1,y1, ax1,ay1, x2,y2, ax2,ay2;
 
 	TTree *tree = new TTree("vtx", "2 track info");
 


	tree->Branch("raw0", &raw0, "raw0/I");
	tree->Branch("x0", &x0, "x0/D");
	tree->Branch("y0", &y0, "y0/D");
	tree->Branch("ax0", &ax0, "ax0/D");
	tree->Branch("ay0", &ay0, "ay0/D");
	
	
	tree->Branch("flg", &flg, "flg/I");
	
	tree->Branch("raw1", &raw1, "raw1/I");
	tree->Branch("x1", &x1, "x1/D");
	tree->Branch("y1", &y1, "y1/D");
	tree->Branch("ax1", &ax1, "ax1/D");
	tree->Branch("ay1", &ay1, "ay1/D");
	
	tree->Branch("raw2", &raw2, "raw2/I");
 	tree->Branch("x2", &x2, "x2/D");
	tree->Branch("y2", &y2, "y2/D");
	tree->Branch("ax2", &ax2, "ax2/D");
	tree->Branch("ay2", &ay2, "ay2/D");
 
 while(data >> raw0 >> ax0 >> ay0 >> x0 >> y0 >> flg>>raw1 >> ax1 >> ay1 >> x1>>y1>>raw2 >> ax2 >> ay2 >> x2>>y2){

		tree->Fill();
	}
	data.close();
	
	TFile* fout = new TFile("../data/output.root","recreate");
	//tree->Write();
	fout->Write();  
	fout->Close();
	
	return 0;
}