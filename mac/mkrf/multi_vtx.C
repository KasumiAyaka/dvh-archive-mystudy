// ***************
// p_mkrf.C
// 2022/01/27
// kasumi
// ***************
// to make rootfile of 2vtx-of multitrk-vtx
// ***************
void multi_vtx(TString input="p_multi.txt",TString output="p_mult.root"){

	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"event_id/I:pair_id/I:ntrk/I:pl1/I:rid1/I:pl2/I:rid2/I:x/D:y/D:dz/D:oa/D:md/D:cop/D:flg/I");
	
	tree->Write();
	file->Close();
}