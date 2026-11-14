// ***************
// p_mkrf.C
// 2022/01/27
// kasumi
// ***************
// to make rootfile of 2vtx-of multitrk-vtx
// ***************
void p_mkrf(TString input="p_multi.txt",TString output="p_mult.root"){
	Int_t id, pid;
	Int_t eid, epl, ntrk;
	Double_t ex, ey, ez;
	Int_t pl1, rid1, pl2, rid2;
	Double_t x, y, dz, oa, md;
	Int_t flg;
	
	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"pl1/I:rid1/I:pl2/I:rid2/I:x/D:y/D:dz/D:oa/D:md/D:cop/D:moa/D:flg/I");
	
	tree->Write();
	file->Close();
}