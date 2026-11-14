// mp+1 selection&discard fwd no mip&discard upstream mip
// output_txt_list_of_chain.C
// 2022/02/02
// kasumi
// **************************
// input format :pt.root
// output format:pt.txt
// **************************
void fwd_bwd_bm_classify.C(TString in="in.root"){
	
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
	
	
	
	// cut condition  -a*angle + b
	Double_t ang0,ang1;
	Double_t a0, b0, a1, b1, a2, b2, a3, b3;
	a0 = 102.5; b0 = 177.5;// 0.0-1.0
	a1 = 16.5; b1 = 91.5;// 1.0-2.0
	a2 = 12.0; b2 = 82.5;// 2.0-3.0
	a3 = -3.0; b3 = 37.5;//   3.0-
	//***************************
	// judge mark
	Int_t fmip=0;
	Int_t fblk=0;
	Int_t bmip=0;
	Int_t bblk=0;
	Int_t nmip=0;
	Int_t oth=0;
	Int_t blk=0;
	

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
	

	
	//std::string filename はダメだった。
	const char* filename = "fmip.txt";
	std::ofstream ofs3;
	ofs3.open(filename,std::ios::out);

	// linear mip-mip
	const char* lmm = "bb.txt";
	std::ofstream ofs1;
	ofs1.open(lmm,std::ios::out);

	// bwd mip
	const char* bwdm = "bm.txt";
	std::ofstream ofs2;
	ofs2.open(bwdm,std::ios::out);
	
	// bwd mip
	const char* bwdm = "mb.txt";
	std::ofstream ofs4;
	ofs4.open(bwdm,std::ios::out);
	
	// bwd mip
	const char* bwdm = "mm.txt";
	std::ofstream ofs5;
	ofs5.open(bwdm,std::ios::out);
	
		
	if(!ofs1.bad()){
		for (auto i=0; i < nt->GetEntries(); ++i){
    		nt->GetEntry(i); 
			
			ang0 = sqrt(ax0*ax0 + ay0*ay0);
			ang1 = sqrt(ax1*ax1 + ay1*ay1);
			
			if(upl0!=upl1){// bwd at least 1chain
				//upstream mip cut 	
				if(dpl0-upl1>0){// 0:bwd,1:fwd 
					// *** bwd:mip *** : discard
					if ((ang0 <= 1.0)&& (vph0 <= b0 - a0 * ang0)) {//mip
						bmip++;
						if ((ang1 <= 1.0)&& (vph1 <= b0 - a0 * ang1)) {//fwd:mip
							fmip++;
						}
						else if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//fmip
							fmip++;
						}
						else{//bwd:blk
							fblk++;
						}
					}
					else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
						bmip++;
						if ((ang1 <= 1.0)&& (vph1 <= b0 - a0 * ang1)) {//fwd:mip
							fmip++;
						}
						else if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//fmip
							fmip++;
						}
						else{//bwd:blk
							fblk++;
						}
					}
					else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
						bmip++;
						if ((ang1 <= 1.0)&& (vph1 <= b0 - a0 * ang1)) {//fwd:mip
							fmip++;
						}
						else if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//fmip
							fmip++;
						}
						else{//bwd:blk
							fblk++;
						}
					}
					else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
						bmip++;
						if ((ang1 <= 1.0)&& (vph1 <= b0 - a0 * ang1)) {//fwd:mip
							fmip++;
						}
						else if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//fmip
							fmip++;
						}
						else{//bwd:blk
							fblk++;
						}
					}
					else {// bwd:black:remain
						bblk++;
						if ((ang1 <= 1.0)&& (vph1 <= b0 - a0 * ang1)) {//fwd:mip
							fmip++;
						}
						else if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//fmip
							fmip++;
						}
						else if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//fmip
							fmip++;
						}
						else{//bwd:blk
							fblk++;
						}
							
					}
				}
				if(dpl1-upl0>0){// 0:fwd,1:bwd
					// *** bwd:mip(discard)***
					if ((ang1 <= 1.0)&& (vph1 <= b0 - a0 * ang1)) {//mip
						bmip++;
						if ((ang0 <= 1.0)&& (vph0 <= b0 - a0 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
							fmip++;
						}
						else{
							fblk++;
						}
					}
					else if ((ang1 > 1.0 && ang1 <= 2.0) &&(vph1 <= b1 - a1 * ang1)) {//mip
						bmip++;
						if ((ang0 <= 1.0)&& (vph0 <= b0 - a0 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
							fmip++;
						}
						else{
							fblk++;
						}
					}
					else if ((ang1 > 2.0 && ang1 <= 3.0) &&(vph1 <= b2 - a2 * ang1)) {//mip
						bmip++;
						if ((ang0 <= 1.0)&& (vph0 <= b0 - a0 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
							fmip++;
						}
						else{
							fblk++;
						}
					}
					else if ((ang1 > 3.0) &&(vph1 <= b3 - a3 * ang1)) {//mip
						bmip++;
						if ((ang0 <= 1.0)&& (vph0 <= b0 - a0 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
							fmip++;
						}
						else{
							fblk++;
						}
					}
					else {//*** bwd:black(remain) ***
						bblk++;
						if ((ang0 <= 1.0)&& (vph0 <= b0 - a0 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 1.0 && ang0 <= 2.0) &&(vph0 <= b1 - a1 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 2.0 && ang0 <= 3.0) &&(vph0 <= b2 - a2 * ang0)) {//mip
							fmip++;
						}
						else if ((ang0 > 3.0) &&(vph0 <= b3 - a3 * ang0)) {//mip
							fmip++;
						}
						else{
							fblk++;
						}
					}
				}
			}
			//request fwd:mip
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
			if(bmip==1&&fblk==1){
				//ofs1<<id<<" "<<pid<<" "<<eid<<" "<<epl<<" "<<ntrk<<" "<<ex<<" "<<ey<<" "<<ez<<" "<<vx<<" "<<vy<<" "<<dz<<" "<<oa<<" "<<md<<" "<<id0<<" "<<tid0<<" "<<vph0<<" "<<dpl0<<" "<<upl0<<" "<<urid0<<" "<<cid0<<" "<<gid0<<" "<<nsg0<<" "<<npl0<<" "<<ph0<<" "<<ax0<<" "<<ay0<<" "<<x0<<" "<<y0<<" "<<ipz0<<" "<<id1<<" "<<tid1<<" "<<vph1<<" "<<dpl1<<" "<<upl1<<" "<<urid1<<" "<<cid1<<" "<<gid1<<" "<<nsg1<<" "<<npl1<<" "<<ph1<<" "<<ax1<<" "<<ay1<<" "<<x1<<" "<<y1<<" "<<ipz1<<std::endl;//fwd:b&bwd:b
				ofs4<<id<<std::endl;
			}
			if(bmip==1&&fmip==1){
				//ofs2<<id<<" "<<pid<<" "<<eid<<" "<<epl<<" "<<ntrk<<" "<<ex<<" "<<ey<<" "<<ez<<" "<<vx<<" "<<vy<<" "<<dz<<" "<<oa<<" "<<md<<" "<<id0<<" "<<tid0<<" "<<vph0<<" "<<dpl0<<" "<<upl0<<" "<<urid0<<" "<<cid0<<" "<<gid0<<" "<<nsg0<<" "<<npl0<<" "<<ph0<<" "<<ax0<<" "<<ay0<<" "<<x0<<" "<<y0<<" "<<ipz0<<" "<<id1<<" "<<tid1<<" "<<vph1<<" "<<dpl1<<" "<<upl1<<" "<<urid1<<" "<<cid1<<" "<<gid1<<" "<<nsg1<<" "<<npl1<<" "<<ph1<<" "<<ax1<<" "<<ay1<<" "<<x1<<" "<<y1<<" "<<ipz1<<std::endl;//fwd:b&bwd:b
				ofs5<<id<<std::endl;
				//f:m&bwd:mip
			}
			if(bblk==1&&fblk==1){
				//ofs1<<id<<" "<<pid<<" "<<eid<<" "<<epl<<" "<<ntrk<<" "<<ex<<" "<<ey<<" "<<ez<<" "<<vx<<" "<<vy<<" "<<dz<<" "<<oa<<" "<<md<<" "<<id0<<" "<<tid0<<" "<<vph0<<" "<<dpl0<<" "<<upl0<<" "<<urid0<<" "<<cid0<<" "<<gid0<<" "<<nsg0<<" "<<npl0<<" "<<ph0<<" "<<ax0<<" "<<ay0<<" "<<x0<<" "<<y0<<" "<<ipz0<<" "<<id1<<" "<<tid1<<" "<<vph1<<" "<<dpl1<<" "<<upl1<<" "<<urid1<<" "<<cid1<<" "<<gid1<<" "<<nsg1<<" "<<npl1<<" "<<ph1<<" "<<ax1<<" "<<ay1<<" "<<x1<<" "<<y1<<" "<<ipz1<<std::endl;//fwd:b&bwd:b
				ofs1<<id<<std::endl;
			}
			if(bblk==1&&fmip==1){
				//ofs2<<id<<" "<<pid<<" "<<eid<<" "<<epl<<" "<<ntrk<<" "<<ex<<" "<<ey<<" "<<ez<<" "<<vx<<" "<<vy<<" "<<dz<<" "<<oa<<" "<<md<<" "<<id0<<" "<<tid0<<" "<<vph0<<" "<<dpl0<<" "<<upl0<<" "<<urid0<<" "<<cid0<<" "<<gid0<<" "<<nsg0<<" "<<npl0<<" "<<ph0<<" "<<ax0<<" "<<ay0<<" "<<x0<<" "<<y0<<" "<<ipz0<<" "<<id1<<" "<<tid1<<" "<<vph1<<" "<<dpl1<<" "<<upl1<<" "<<urid1<<" "<<cid1<<" "<<gid1<<" "<<nsg1<<" "<<npl1<<" "<<ph1<<" "<<ax1<<" "<<ay1<<" "<<x1<<" "<<y1<<" "<<ipz1<<std::endl;//fwd:b&bwd:b
				ofs2<<id<<std::endl;
				//f:m&bwd:mip
			}
			if(oth>0){//at least fwd 1 mip
				ofs3<<id<<std::endl;
				//ofs3<<id<<" "<<pid<<" "<<eid<<" "<<epl<<" "<<ntrk<<" "<<ex<<" "<<ey<<" "<<ez<<" "<<vx<<" "<<vy<<" "<<dz<<" "<<oa<<" "<<md<<" "<<id0<<" "<<tid0<<" "<<vph0<<" "<<dpl0<<" "<<upl0<<" "<<urid0<<" "<<cid0<<" "<<gid0<<" "<<nsg0<<" "<<npl0<<" "<<ph0<<" "<<ax0<<" "<<ay0<<" "<<x0<<" "<<y0<<" "<<ipz0<<" "<<id1<<" "<<tid1<<" "<<vph1<<" "<<dpl1<<" "<<upl1<<" "<<urid1<<" "<<cid1<<" "<<gid1<<" "<<nsg1<<" "<<npl1<<" "<<ph1<<" "<<ax1<<" "<<ay1<<" "<<x1<<" "<<y1<<" "<<ipz1<<std::endl;//fwd:b&bwd:b
			}
//id/I:pid/I:eid/I:epl/I:ntrk/I:ex/D:ey/D:ez/D:vx/D:vy/D:dz/D:oa/D:md/D:id0/I:tid0/I:vph0/I:dpl0/I:upl0/I:urid0/I:cid0/I:gid0/I:nsg0/I:npl0/I:ph0/I:ax0/D:ay0/D:x0/D:y0/D:ipz0/D:id1/I:tid1/I:vph1/I:dpl1/I:upl1/I:urid1/I:cid1/I:gid1/I:nsg1/I:npl1/I:ph1/I:ax1/D:ay1/D:x1/D:y1/D:ipz1/D
			//ofs <<id<<" "<<dpl0<<" "<<upl0<<" "<<cid0<<" "<<ax0<<" "<<ay0<<" "<<x0<<" "<<y0<<" "<<dpl1<<" "<<upl1<<" "<<cid1<<" "<<ax1<<" "<<ay1<<" "<<x1<<" "<<y1<< std::endl;
			fmip=0;
			bmip=0;
			fblk=0;
			bblk=0;	
			oth=0;
		}
		ofs3.close();
		ofs1.close();//bb
		ofs2.close();//bm
		ofs4.close();//mb
		ofs5.close();//mm
	
	}

}