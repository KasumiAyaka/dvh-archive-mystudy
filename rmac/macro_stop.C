//macro.C--make rootfile
//A.Kasumi
//June 10 2021
// macro_stop.C
// 2021/11/03
// kasumi
// to make rootfile
int macro_stop(){


	Int_t chainid,nseg,pl0,pl1,groupid,rawid,ph;
	Double_t ax, ay, x, y, z;

	TString input = "../mfile/stop.txt";
	TString output= "../rootfile/stop.root";
	
	TFile *file = TFile::Open(output,"RECREATE");
	TTree* tree = new TTree("tree","tree");

	tree->ReadFile(input.Data(),"chainid/I:nseg/I:pl0/I:pl1/I:groupid/I:rawid/I:ph/I:ax/D:ay/D:x/D:y/D:z/D");
	tree->Write();
	
	file->Close();
}
