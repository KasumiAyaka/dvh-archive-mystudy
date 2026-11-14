void oa_md(){
	gStyle->SetOptStat(0000);
	
	tree->Draw("md:oa>>h(100,0,2.8,100,0,140)","","colz");
	h->SetTitle("OpeningAngle-MinimumDistance;oa;md[#mum]");

	tree->Draw("md:oa>>h0(100,0,2.8,100,0,140)","pid==0","colz");
	h0->SetTitle("OpeningAngle-MinimumDistance;oa;md[#mum]");
	h0->SetMarkerStyle(6);
	h0->SetMarkerColor(2);
	h0->Draw();

	tree->Draw("md:oa>>h1(100,0,2.8,100,0,140)","pid==1","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,140)","pid==2","");
	tree->Draw("md:oa>>h3(100,0,2.8,100,0,140)","pid==3","");
	tree->Draw("md:oa>>h4(100,0,2.8,100,0,140)","pid==4","");
	tree->Draw("md:oa>>h5(100,0,2.8,100,0,140)","pid==5","");
	tree->Draw("md:oa>>h6(100,0,2.8,100,0,140)","pid==6","");
	tree->Draw("md:oa>>h7(100,0,2.8,100,0,140)","pid==7","");
	tree->Draw("md:oa>>h8(100,0,2.8,100,0,140)","pid==8","");
	tree->Draw("md:oa>>h9(100,0,2.8,100,0,140)","pid==9","");
	tree->Draw("md:oa>>h10(100,0,2.8,100,0,140)","pid==10","");
	tree->Draw("md:oa>>h11(100,0,2.8,100,0,140)","pid==11","");
	tree->Draw("md:oa>>h12(100,0,2.8,100,0,140)","pid==12","");
	tree->Draw("md:oa>>h13(100,0,2.8,100,0,140)","pid>=13","");
	h13->SetTitle("OpeningAngle-MinimumDistance(MultiVtx);oa;md[#mum]");
	
	
	//h1->SetMarkerStyle(3);
	//h9->SetMarkerStyle(29);
	h1->SetMarkerStyle(6);
	h1->SetMarkerColor(3);

	h2->SetMarkerStyle(6);
	h2->SetMarkerColor(4);
	
	h3->SetMarkerStyle(6);
	h3->SetMarkerColor(5);

	h4->SetMarkerStyle(6);
	h4->SetMarkerColor(6);
	
	h5->SetMarkerStyle(6);
	h5->SetMarkerColor(7);
	
	h6->SetMarkerStyle(6);
	h6->SetMarkerColor(8);
	
	h7->SetMarkerStyle(6);
	h7->SetMarkerColor(9);
	
	h8->SetMarkerStyle(6);
	h8->SetMarkerColor(1);
	
	h9->SetMarkerStyle(6);
	h9->SetMarkerColor(30);
	
	h10->SetMarkerStyle(6);
	h10->SetMarkerColor(38);
	
	h11->SetMarkerStyle(6);
	h11->SetMarkerColor(40);
	
	h12->SetMarkerStyle(6);
	h12->SetMarkerColor(44);
	
	h13->SetMarkerStyle(6);
	h13->SetMarkerColor(46);
	
	
	 TLegend *legend0 = new TLegend( 0.88, 0.10, 0.98, 0.90) ; //（）の中は位置の指定（左下の x , y 、右上の x , y ）
	legend0->AddEntry(h0,"h0","p");
	legend0->AddEntry( h1, "h1" , "p") ; 
	legend0->AddEntry( h2, "h2" , "p") ; // "f"=box, "l"="L"=line, "p"=marker
	legend0->AddEntry( h3, "h3" , "p") ;
	legend0->AddEntry( h4, "h4" , "p") ;
	legend0->AddEntry( h5, "h5" , "p") ;
	legend0->AddEntry( h6, "h6" , "p") ;
	legend0->AddEntry( h7, "h7" , "p") ;
	legend0->AddEntry( h8, "h8" , "p") ;
	legend0->AddEntry( h9, "h9" , "p") ;
	legend0->AddEntry( h10, "h10" , "p") ;
	legend0->AddEntry( h11, "h11" , "p") ;
	legend0->AddEntry( h12, "h12" , "p") ;
	legend0->AddEntry( h13, "h13" , "p") ;
	legend0->SetFillColor(0);
	

	h13->Draw();
	h12->Draw("sames");
	h11->Draw("sames");
	h10->Draw("sames");
	h9->Draw("sames");
	h8->Draw("sames");
	h7->Draw("sames");
	h6->Draw("sames");
	h5->Draw("sames");
	h4->Draw("sames");
	h3->Draw("sames");
	h2->Draw("sames");
	h1->Draw("sames");
	h0->Draw("sames");
	legend0->Draw("sames") ;

	c1->Print("oa_md_BG_estimation.pdf");
}