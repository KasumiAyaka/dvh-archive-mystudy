// mp+1 selection&discard fwd no mip&discard upstream mip
// output_txt_list_of_chain.C
// 2022/02/02
// kasumi
// **************************
// input format :pt.root
// output format:pt.txt
// **************************
void mdoa_cut(TString in="in.root"){
	
	auto file = new TFile(in, "read");
	auto nt = static_cast<TTree*>(file->Get("tree"));
	 
	Int_t id,pid;
	Int_t eid, epl, ntrk;

	Double_t ex, ey, ez;
	Double_t vx, vy, dz, oa, md;

	
	Int_t id0,tid0,vph0;
	Int_t dpl0, upl0,urid0,cid0,ph0;
	Double_t ax0, ay0, x0, y0,ipz0;
	Int_t  gid0, nsg0, npl0;

	Int_t dpl1, upl1, cid1,ph1;
	Int_t id1,tid1, vph1;
	Int_t urid1,gid1, nsg1, npl1;
	Double_t ax1, ay1, x1, y1,ipz1;
	
	nt->SetBranchAddress("id",&id);
	nt->SetBranchAddress("pid",&pid);
	
	nt->SetBranchAddress("eid",&eid);
	nt->SetBranchAddress("epl",&epl);
	nt->SetBranchAddress("ntrk",&ntrk);
	nt->SetBranchAddress("ex",&ex);
	nt->SetBranchAddress("ey",&ey);
	nt->SetBranchAddress("ez",&ez);
	nt->SetBranchAddress("vx",&vx);
	nt->SetBranchAddress("vy",&vy);
	nt->SetBranchAddress("dz",&dz);
	nt->SetBranchAddress("oa",&oa);
	nt->SetBranchAddress("md",&md);


	nt->SetBranchAddress("dpl0",&dpl0);
	nt->SetBranchAddress("upl0",&upl0);
	nt->SetBranchAddress("cid0",&cid0);
	nt->SetBranchAddress("vph0",&vph0);
	nt->SetBranchAddress("ax0",&ax0);
	nt->SetBranchAddress("ay0",&ay0);
	nt->SetBranchAddress("x0",&x0);
	nt->SetBranchAddress("y0",&y0);
	nt->SetBranchAddress("ipz0",&ipz0);
	nt->SetBranchAddress("vph0",&vph0);
	nt->SetBranchAddress("urid0",&urid0);
	nt->SetBranchAddress("gid0",&gid0);
	nt->SetBranchAddress("nsg0",&nsg0);
	nt->SetBranchAddress("npl0",&npl0);

	nt->SetBranchAddress("vph1",&vph1);
	nt->SetBranchAddress("urid1",&urid1);
	nt->SetBranchAddress("gid1",&gid1);
	nt->SetBranchAddress("nsg1",&nsg1);
	nt->SetBranchAddress("npl1",&npl1);

	nt->SetBranchAddress("dpl1",&dpl1);
	nt->SetBranchAddress("upl1",&upl1);
	nt->SetBranchAddress("cid1",&cid1);
	nt->SetBranchAddress("ax1",&ax1);
	nt->SetBranchAddress("ay1",&ay1);
	nt->SetBranchAddress("ipz1",&ipz1);
	nt->SetBranchAddress("x1",&x1);
	nt->SetBranchAddress("y1",&y1);
	


	const char* bwdm = "oamd_cut.txt";
	std::ofstream ofs5;
	ofs5.open(bwdm,std::ios::out);
	
		
	if(!ofs5.bad()){
		for (auto i=0; i < nt->GetEntries(); ++i){
    			nt->GetEntry(i); 
			if(md>60-600*oa){
					ofs5<<id<<std::endl;
			}
		}
	}
	ofs5.close();
}