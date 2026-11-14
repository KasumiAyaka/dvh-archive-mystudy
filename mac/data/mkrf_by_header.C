// mkrf_by_header
// A.Kasumi
// 2022/3/1
int mkrf_by_header(TString input="./stop.txt",TString output= "./stop.root",Int_t i=-1){

	TFile *file = TFile::Open(output,"RECREATE");
	TTree* tree = new TTree("tree","tree");

	if(i==0){
	tree->ReadFile(input.Data(),"id/I:pl/I:trk/I:x/D:y/D:z/D:nmip/I:gam/I:phi/I:rss/I:fmip/I");
	}
	if(i==1){
	tree->ReadFile(input.Data(),"id/I:pl1/I:rid1/I:pl2/I:rid2/I:x/D:y/D:dz/D:oa/D:md/D:oa_check/D:cos/D:phi/D");
	}
	if(i==2){
	tree->ReadFile(input.Data(),"id/I:dpl/I:upl/I:urid/I:cid/I:gid/I:nsg/I:npl/I:ph/I:ax/D:ay/D:x/D:y/D:ipz/D:dir/I:blk/I");
	}
	
	
	tree->Write();
	
	file->Close();
}
