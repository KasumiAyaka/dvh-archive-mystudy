// output_txt_list_of_chain.C
// 2022/02/01
// kasumi
// **************************
// t_vph.root
// **************************
void list(){
	
	auto file = new TFile("./data/t_multi.root", "read");
	auto nt = static_cast<TTree*>(file->Get("tree"));
	 
	Int_t cid,id,vph,tid;
	Double_t ax,ay;
	
	
	nt->SetBranchAddress("cid",&cid);
	nt->SetBranchAddress("id",&id);
	nt->SetBranchAddress("vph",&vph);
	nt->SetBranchAddress("tid",&tid);
	nt->SetBranchAddress("ax",&ax);
	nt->SetBranchAddress("ay",&ay);
	
	//std::string filename ÇÕÉ_ÉÅÇæÇ¡ÇΩÅB

	const char* filename = "chain.txt";
	std::ofstream ofs;
	ofs.open(filename,std::ios::out);
		
	if(!ofs.bad()){
		for (auto i=0; i < nt->GetEntries(); ++i){
    			nt->GetEntry(i); 
			ofs << cid <<" "<<id<<" "<< vph <<" "<<tid<<" "<<ax<<" "<<ay<< std::endl;
		}
		ofs.close();
	}
}