// ***************
// t_mkrf.C
// 2022/01/27
// kasumi
// ***************
// to make rootfile of 2vtx-of multitrk-vtx
// ***************
void t_mkrf(TString input="t_multi.txt",TString output="t_mult.root"){
	Int_t id, vph;
	Int_t dpl, upl, urid, cid, gid, nsg, npl, ph;
	Double_t ax, ay, x, y, z;
	Int_t eid, epl, ntrk;
	Double_t ex, ey, ez;
	Int_t tid;
	
	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"id/I:vph/I:tid/I:eid/I:epl/I:ntrk/I:ex/D:ey/D:ez/D:dpl/I:upl/I:urid/I:cid/I:gid/I:nsg/I:npl/I:ph/I:ax/D:ay/D:x/D:y/D:ipz/D");
	
	tree->Write();
	file->Close();
}