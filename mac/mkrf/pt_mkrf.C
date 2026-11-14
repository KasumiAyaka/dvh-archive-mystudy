// ***************
// pt_mkrf.C
// 2022/01/31
// kasumi
// ***************
// to make rootfile of 2vtx-of multitrk-vtx
// ***************
void pt_mkrf(TString input="pt.txt",TString output="pt.root"){
	Int_t id, pid;
	Int_t eid, epl, ntrk;
	Double_t ex, ey, ez;
	Double_t vx, vy, dz, oa, md;
	
	Int_t id0,tid0,vph0;
	Int_t dpl0, upl0, urid0, cid0, gid0, nsg0, npl0, ph0;
	Double_t ax0, ay0, x0, y0, z0;
	
	Int_t id1,tid1, vph1;
	Int_t dpl1, upl1, urid1, cid1, gid1, nsg1, npl1, ph1;
	Double_t ax1, ay1, x1, y1, z1;

	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"id/I:pid/I:eid/I:epl/I:ntrk/I:ex/D:ey/D:ez/D:vx/D:vy/D:dz/D:oa/D:md/D:id0/I:tid0/I:vph0/I:dpl0/I:upl0/I:urid0/I:cid0/I:gid0/I:nsg0/I:npl0/I:ph0/I:ax0/D:ay0/D:x0/D:y0/D:ipz0/D:id1/I:tid1/I:vph1/I:dpl1/I:upl1/I:urid1/I:cid1/I:gid1/I:nsg1/I:npl1/I:ph1/I:ax1/D:ay1/D:x1/D:y1/D:ipz1/D");
	
	tree->Write();
	file->Close();
}