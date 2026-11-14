void cop_2(TString input="t_multi.txt",TString output="t_mult.root"){
	
	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"id/I:pl1/I:rid1/I:pl2/I:rid2/I:x/D:y/D:dz/D:oa/D:md/D:moa/D:cos/D:phi/D");
	
	tree->Write();
	file->Close();
}