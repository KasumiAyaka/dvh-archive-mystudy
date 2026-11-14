// ***************
// t_mkrf.C
// 2022/01/27
// kasumi
// ***************
// to make rootfile of 2vtx-of multitrk-vtx
// ***************
void mb2_cop(TString input="t_multi.txt",TString output="t_mult.root"){
	
	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"dpl/I:upl/I:urid/I:cid/I:gid/I:nsg/I:npl/I:ph/I:ax/D:ay/D:x/D:y/D:ipz/D:bwd/D:blk/D");
	
	tree->Write();
	file->Close();
}