void v_mkrf(TString input="v.txt",TString output="v.root"){

	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"id/I:pl/I:ntrk/I:x/D:y/D:z/D:oa/D:md/D:cop/D:blk/I:vid/I:bg/I");
	
	tree->Write();
	file->Close();
}