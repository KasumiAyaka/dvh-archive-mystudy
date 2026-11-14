void oa_md(){
tree->Draw("md:oa>>h(100,0,2.8,100,0,450)","","colz");
h->SetTitle("OpeningAngle-MinimumDistance;oa;md[#mum]");

tree->Draw("md:oa>>h0(100,0,2.8,100,0,450)","pid==0","colz");
h0->SetTitle("OpeningAngle-MinimumDistance(shuffled data);oa;md[#mum]");
h0->SetMarkerStyle(3);
h0->SetMarkerColor(2);
h0->Draw();

	tree->Draw("md:oa>>h1(100,0,2.8,100,0,450)","pid==1","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==2","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==3","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==4","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==5","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==6","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==7","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==8","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==9","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==10","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==11","");
	tree->Draw("md:oa>>h2(100,0,2.8,100,0,450)","pid==12","");


	h1->SetMarkerStyle(3);
	h1->SetMarkerColor(3);

	h2->SetMarkerStyle(3);
	h2->SetMarkerColor(4);
	
	h3->SetMarkerStyle(3);
	h3->SetMarkerColor(5);

	h4->SetMarkerStyle(3);
	h4->SetMarkerColor(6);
	
	h5->SetMarkerStyle(3);
	h5->SetMarkerColor(7);
	
	h6->SetMarkerStyle(3);
	h6->SetMarkerColor(8);
	
	h7->SetMarkerStyle(3);
	h7->SetMarkerColor(9);
	
	h8->SetMarkerStyle(3);
	h8->SetMarkerColor(1);
	
	h9->SetMarkerStyle(29);
	h9->SetMarkerColor(40);
	
	h10->SetMarkerStyle(29);
	h10->SetMarkerColor(41);
	
	h11->SetMarkerStyle(29);
	h11->SetMarkerColor(30);
	
	h12->SetMarkerStyle(29);
	h12->SetMarkerColor(46);

h0->Draw();
h1->Draw("sames");
h2->Draw("sames");
	h3->Draw("sames");
	h4->Draw("sames");
	h5->Draw("sames");
	h6->Draw("sames");
	h7->Draw("sames");
	h8->Draw("sames");
	h9->Draw("sames");
	h10->Draw("sames");
	h11->Draw("sames");
	h12->Draw("sames");

c1->Print("oa_md_BG_estimation.pdf");
}