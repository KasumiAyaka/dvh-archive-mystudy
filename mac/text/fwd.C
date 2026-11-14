// output_txt_list_of_chain.C
// 2022/02/01
// kasumi
// **************************
// t_vph.root
// **************************
void fwd(){
	
	auto file = new TFile("./data/3pt.root", "read");
	auto nt = static_cast<TTree*>(file->Get("tree"));
	 
	Int_t id;

	Int_t dpl0, upl0, cid0;
	Double_t ax0, ay0, x0, y0;

	Int_t dpl1, upl1, cid1;
	Double_t ax1, ay1, x1, y1;
	

	nt->SetBranchAddress("id",&id);

	nt->SetBranchAddress("dpl0",&dpl0);
	nt->SetBranchAddress("upl0",&upl0);
	nt->SetBranchAddress("cid0",&cid0);
	nt->SetBranchAddress("ax0",&ax0);
	nt->SetBranchAddress("ay0",&ay0);
	nt->SetBranchAddress("x0",&x0);
	nt->SetBranchAddress("y0",&y0);

	nt->SetBranchAddress("dpl1",&dpl1);
	nt->SetBranchAddress("upl1",&upl1);
	nt->SetBranchAddress("cid1",&cid1);
	nt->SetBranchAddress("ax1",&ax1);
	nt->SetBranchAddress("ay1",&ay1);
	nt->SetBranchAddress("x1",&x1);
	nt->SetBranchAddress("y1",&y1);
	

	
	//std::string filename ÇÕÉ_ÉÅÇæÇ¡ÇΩÅB
	//gamma_like**************
	const char* filename = "fwdid.txt";
	std::ofstream ofs;
	ofs.open(filename,std::ios::out);

	const char* f = "fwd_allpair.txt";
	std::ofstream of;
	of.open(f,std::ios::out);
		
	if(!ofs.bad()){
		for (auto i=0; i < nt->GetEntries(); ++i){
    			nt->GetEntry(i); 
			of<<id<<" "<<cid0<<" "<<id<<" "<<cid1<<std::endl;
			if((dpl0-upl1>0)||(dpl1-upl0>0)){
			if(sqrt((x1-x0)**2+(y1-y0)**2)>19000-255000*acos((ax1*ax0+ay1*ay0+1)/(sqrt(ax1**2+ay1**2+1)*sqrt(ay0**2+ax0**2+1)))){
				ofs <<id<<std::endl;
			}
			}
		}
	ofs.close();
	}
}