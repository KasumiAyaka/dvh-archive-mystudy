// output_txt_list_of_chain.C
// 2022/02/01
// kasumi
// **************************
// t_vph.root
// **************************
void make_event_list(){
	
	auto file = new TFile("t_mb.root", "read");
	auto nt = static_cast<TTree*>(file->Get("tree"));
	 
	Int_t chain,id;
	Double_t md,oa;
	
	
	nt->SetBranchAddress("chain",&chain);
	nt->SetBranchAddress("md",&md);
	nt->SetBranchAddress("oa",&oa);
	nt->SetBranchAddress("id",&id);
	nt->SetBranchAddress("vph",&vph);
	
	//std::string filename はダメだった。
	//gamma_like**************
	const char* filename = "chain_all.txt";
	std::ofstream ofs;
	ofs.open(filename,std::ios::out);
		
	if(!ofs.bad()){
		for (auto i=0; i < nt->GetEntries(); ++i){
    		nt->GetEntry(i); 
			ofs << chain <<" "<<id<< std::endl;
		}
	ofs.close();
	}
}