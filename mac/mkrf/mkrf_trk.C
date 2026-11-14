// ***************
// p_mkrf.C
// 2022/01/27
// kasumi
// ***************
// to make rootfile of 2vtx-of multitrk-vtx
// ***************
void mkrf_trk(TString input="p_multi.txt",TString output="p_mult.root"){

	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"id/I:pl/I:ntrk/I:x/D:y/D:z/D");
	
	tree->Write();
	file->Close();
}