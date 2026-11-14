// ***************
// p_mkrf.C
// 2022/01/27
// kasumi
// ***************
// to make rootfile of 2vtx-of multitrk-vtx
// ***************
void track(TString input="p_multi.txt",TString output="p_mult.root"){

	TFile *file = TFile::Open(output,"RECREATE");
	TTree *tree = new TTree("tree", "tree");
 	
	TString data = input;
	tree->ReadFile(data.Data(),"id/I:ntrk/I:trkid/I:dpl/I:upl/I:urid/I:cid/I:gid/I:nsg/I:npl/I:ph/I:ax/D:ay/D:x/D:y/D:ipz/D:dflg/I:blkflg/I:blk/I:oamd/I:copl/I:fwdmip/I");
	
	tree->Write();
	file->Close();
}