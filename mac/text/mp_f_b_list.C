// mp+1 selection&discard fwd no mip&discard upstream mip
// output_txt_list_of_chain.C
// 2022/02/02
// kasumi
// **************************
// t_vph.root
// **************************
void mp_f_b_list(){
	
	auto file = new TFile("./data/3pt.root", "read");
	auto nt = static_cast<TTree*>(file->Get("tree"));
	 
	Int_t id;

	Int_t dpl0, upl0, cid0,ph0;
	Double_t ax0, ay0, x0, y0;

	Int_t dpl1, upl1, cid1,ph1;
	Double_t ax1, ay1, x1, y1;
	
	// cut condition  -a*angle + b
	Double_t ang0,ang1;
	Int_t a0, b0, a1, b1, a2, b2, a3, b3;
	a0 = 70; b0 = 190;//0  -1.0
	a1 = 30; b1 = 150;// 1.0-2.0
	a2 = 10; b2 = 110;// 2.0-3.0
	a3 = 5; b3 = 95;//  3.0-
	//***************************
	// judge mark
	Int_t mip=0;
	Int_t nmip=0;
	Int_t oth=0;
	Int_t blk=0;
	

	nt->SetBranchAddress("id",&id);

	nt->SetBranchAddress("dpl0",&dpl0);
	nt->SetBranchAddress("upl0",&upl0);
	nt->SetBranchAddress("cid0",&cid0);
	nt->SetBranchAddress("ph0",&ph0);
	nt->SetBranchAddress("ax0",&ax0);
	nt->SetBranchAddress("ay0",&ay0);
	nt->SetBranchAddress("x0",&x0);
	nt->SetBranchAddress("y0",&y0);

	nt->SetBranchAddress("dpl1",&dpl1);
	nt->SetBranchAddress("upl1",&upl1);
	nt->SetBranchAddress("cid1",&cid1);
	nt->SetBranchAddress("ph1",&ph1);
	nt->SetBranchAddress("ax1",&ax1);
	nt->SetBranchAddress("ay1",&ay1);
	nt->SetBranchAddress("x1",&x1);
	nt->SetBranchAddress("y1",&y1);
	

	
	//std::string filename はダメだった。
	const char* filename = "bb.txt";
	std::ofstream ofs;
	ofs.open(filename,std::ios::out);

	// linear mip-mip
	const char* lmm = "lmm_id.txt";
	std::ofstream ofs1;
	ofs1.open(lmm,std::ios::out);

	// bwd mip
	const char* bwdm = "bwd_mip_id.txt";
	std::ofstream ofs2;
	ofs2.open(bwdm,std::ios::out);
	
	
	
	if(!ofs.bad()){
		for (auto i=0; i < nt->GetEntries(); ++i){
    		nt->GetEntry(i); 
			
			ang0 = sqrt(ax0*ax0 + ay0*ay0);
			ang1 = sqrt(ax1*ax1 + ay1*ay1);
			vph0=ph0%10000;
			vph1=ph1%10000;
			
			if(upl0!=upl1){// bwd at least 1chain
				//judge linearity (mip-mip) linear -> discard) m-m=>mip==2
				//judgement of m-b or b-m is next if-func
				if(sqrt((x1-x0)**2+(y1-y0)**2)>6000-92307*acos((ax1*ax0+ay1*ay0+1)/(sqrt(ax1**2+ay1**2+1)*sqrt(ay0**2+ax0**2+1)))){
					//mip==2->skip mip!=2->remain
					// tracl0 judge mip/black
					if((dpl1-upl0>0)||(dpl0-upl1>0)){ 
						if ((ang0 <= 1.0)&& (vph0 <= b0 - a0 * ang0)) {//mip
							mip++;
						}
						else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
							mip++;
						}
						else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
							mip++;
						}
						else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
							mip++;
						}
						else {//black
							
						}
						
						// tracl1 judge mip/black
						if ((ang1 <= 1.0)&& (vph1 <= b0 - a0 * ang1)) {//mip
							mip++;
						}
						else if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//mip
							mip++;
						}
						else if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//mip
							mip++;
						}
						else if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//mip
							mip++;
						}
						else {//black
							
						}
					}
				}
					
				//upstream mip cut 	
				if(dpl0-upl1>0){//0:upsteram
					if ((ang0 <= 1.0)& (vph <= b0 - a0 * ang0)) {//mip
						nmip1++;
					}
					else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
						nmip++;
					}
					else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
						nmip++;
					}
					else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
						nmip++;
					}
				}

				if(dpl1-upl0>0){
					if ((ang1 <= 1.0)& (vph1 <= b0 - a0 * ang1)) {//mip
						nmip++;
					}
					if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//mip
						nmip++;
					}
					if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//mip
						nmip++;
					}
					if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//mip
						nmip++;
					}
				}
			}
			
			//the other track->remain
			if(upl0==upl1){// both fwd
				if ((ang0 <= 1.0)& (vph0 <= b0 - a0 * ang0)) {//mip
					oth++;
				}
				else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
					oth++;
				}
				else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
					oth++;
				}
				else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
					oth++;
				}
				
				else if ((ang1 <= 1.0)& (vph1 <= b0 - a0 * ang1)) {//mip
					oth++;
				}
				else if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//mip
					oth++;
				}
				else if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//mip
					oth++;
				}
				else if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//mip
					oth++;
				}
				else {//black
					blk++;
				}
			}
			if(mip==2){
				ofs1<<id<<std::endl;//fwd:mip&bwd:mip &linear
			}
			if(nmip>0){
				ofs2<<id<<std::endl;//bwd:mip
			}
			if(blk=1){
				ofs<<id<<std::endl;//all fwd&atleast1black
			}
			//ofs <<id<<" "<<dpl0<<" "<<upl0<<" "<<cid0<<" "<<ax0<<" "<<ay0<<" "<<x0<<" "<<y0<<" "<<dpl1<<" "<<upl1<<" "<<cid1<<" "<<ax1<<" "<<ay1<<" "<<x1<<" "<<y1<< std::endl;
			mip=0;
			nmip=0;
			blk=0;
		}
		ofs.close();
		ofs1.close();
		ofs2.close();
	}

}