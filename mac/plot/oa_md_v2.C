void oa_md_v2(TString in="in.root",TString out="out.pdf"){
	
	
	auto file = new TFile(in, "read");
	
	
	TCanvas *c1 = new TCanvas("c1","c1", 500, 400);
	c1->Print(out + "[", "pdf");
	
	//mm
	tree->Draw("md:oa>>h(140,0,2.8,140,0,280)","pair_id==0&&flg==0","colz");
	h->SetTitle("OpeningAngle-MinimumDistance(all mip);OA;MD");
	c1->Print(out, "pdf");
	c1->Clear();
	
	tree->Draw("md:oa>>h(140,0,2.8,140,0,280)","pair_id==0&&flg==0&&md>60-600*oa","colz");
	h->SetTitle("OpeningAngle-MinimumDistance(all mip,#gamma like cut);OA;MD");
	c1->Print(out, "pdf");
	c1->Clear();

		tree->Draw("md:oa>>h(140,0,2.8,140,0,280)","pair_id==0&&flg==0&&md<=60-600*oa","colz");
	h->SetTitle("OpeningAngle-MinimumDistance(all mip,BG);OA;MD");
	c1->Print(out, "pdf");
	c1->Clear();

	//mb
	tree->Draw("md:oa>>h(140,0,2.8,140,0,280)","pair_id==0&&flg>0&&pair_id==0&&flg<ntrk","colz");
	h->SetTitle("OpeningAngle-MinimumDistance(mip+black);OA;MD");
	c1->Print(out, "pdf");
	c1->Clear();
	
	tree->Draw("md:oa>>h(140,0,2.8,140,0,280)","pair_id==0&&flg>0&&pair_id==0&&flg<ntrk&&md>60-600*oa","colz");
	h->SetTitle("OpeningAngle-MinimumDistance(mip+black,#gamma like cut);OA;MD");
	c1->Print(out, "pdf");
	c1->Clear();

		tree->Draw("md:oa>>h(140,0,2.8,140,0,280)","pair_id==0&&flg>0&&pair_id==0&&flg<ntrk&&md<=60-600*oa","colz");
	h->SetTitle("OpeningAngle-MinimumDistance(mip+black,BG);OA;MD");
	c1->Print(out, "pdf");
	c1->Clear();

		// no cut bb
	tree->Draw("md:oa>>h(140,0,2.8,140,0,280)","pair_id==0&&flg==ntrk","colz");
	h->SetTitle("OpeningAngle-MinimumDistance(all black);OA;MD");
	c1->Print(out, "pdf");
	c1->Clear();


	
	c1->Print(out + "]", "pdf");
	
}