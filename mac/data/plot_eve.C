// plot_eve.C
// 2022/3/1
// kasumi
void plot_eve(TString input="input.root",TString output="output.pdf"){
	
	auto file=new TFile(input,"read");
	
	TCanvas *c1=new TCanvas("c1","c1",500,400);
	c1->Print(output+"[","pdf");
	
	gStyle->SetStatX(0.99);       //統計boxの右上角のX座標（左下を(0,0),右上を(1,1)）
	gStyle->SetStatY(0.99); 
	gStyle->SetTitleXSize(0.05);
	gStyle->SetTitleYSize(0.05);
	//c1->SetRightMargin(0.5);
	//c1->SetLeftMargin(0.5);
	
	
	
	TLatex *   tex = new TLatex(0.20,0.50,"2track vertex");
	tex->SetNDC();
	tex->SetTextSize(0.07);
	tex->Draw();
	c1->Print(output,"pdf");
	c1->Clear();
	
		
	tree->Draw("pl>>h(130,4.5,134.5)","trk==2");
	h->GetYaxis()->SetRangeUser(0,1500);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk==2&&nmip==0");
	h->GetYaxis()->SetRangeUser(0,900);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk==2&&nmip==0&&gam==1");
	h->GetYaxis()->SetRangeUser(0,800);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk==2&&nmip==1");
	h->GetYaxis()->SetRangeUser(0,700);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk==2&&nmip==1&&gam==1");
	h->GetYaxis()->SetRangeUser(0,700);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk==2&&nmip==1&&gam==1&&phi==1");
	h->GetYaxis()->SetRangeUser(0,60);
	c1->Print(output,"pdf");
	c1->Clear();

	tree->Draw("pl>>h(130,4.5,134.5)","trk==2&&nmip==2");
	h->GetYaxis()->SetRangeUser(0,220);
	c1->Print(output,"pdf");
	c1->Clear();
	
	
	TLatex *   tex = new TLatex(0.20,0.50,"multitrack vertex");
	tex->SetNDC();
	tex->SetTextSize(0.07);
	tex->Draw();
	c1->Print(output,"pdf");
	c1->Clear();


	tree->Draw("pl>>h(130,4.5,134.5)","trk>2");
	h->GetYaxis()->SetRangeUser(0,130);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk>2&&nmip==0");
	h->GetYaxis()->SetRangeUser(0,80);
	c1->Print(output,"pdf");
	c1->Clear();

	tree->Draw("pl>>h(130,4.5,134.5)","trk>2&&nmip==0&&gam==1");
	h->GetYaxis()->SetRangeUser(0,40);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk>2&&nmip==1");
	h->GetYaxis()->SetRangeUser(0,70);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk>2&&nmip==1&&gam==1");
	h->GetYaxis()->SetRangeUser(0,50);
	c1->Print(output,"pdf");
	c1->Clear();
	
	
	tree->Draw("pl>>h(130,4.5,134.5)","trk>2&&nmip==1&&gam==1&&phi==1");
	h->GetYaxis()->SetRangeUser(0,50);
	c1->Print(output,"pdf");

	tree->Draw("pl>>h(130,4.5,134.5)","trk>2&&nmip==2");
	h->GetYaxis()->SetRangeUser(0,15);
	c1->Print(output,"pdf");
	c1->Clear();
	
	
	
	//pl>25
	
	TLatex *   tex = new TLatex(0.20,0.50,"2track vertex");
	tex->SetNDC();
	tex->SetTextSize(0.07);
	tex->Draw();
	
	TLatex *   tex = new TLatex(0.20,0.40,"more than PL025");
	tex->SetNDC();
	tex->SetTextSize(0.07);
	tex->Draw();
	c1->Print(output,"pdf");
	c1->Clear();
	
		
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk==2");
	h->GetYaxis()->SetRangeUser(0,1200);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk==2&&nmip==0");
	h->GetYaxis()->SetRangeUser(0,900);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk==2&&nmip==0&&gam==1");
	h->GetYaxis()->SetRangeUser(0,900);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk==2&&nmip==1");
	h->GetYaxis()->SetRangeUser(0,500);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk==2&&nmip==1&&gam==1");
	h->GetYaxis()->SetRangeUser(0,500);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk==2&&nmip==1&&gam==1&&phi==1");
	h->GetYaxis()->SetRangeUser(0,50);
	c1->Print(output,"pdf");
	c1->Clear();

	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk==2&&nmip==2");
	h->GetYaxis()->SetRangeUser(0,130);
	c1->Print(output,"pdf");
	c1->Clear();
	
	
	
	TLatex *   tex = new TLatex(0.20,0.50,"multitrack vertex");
	tex->SetNDC();
	tex->SetTextSize(0.07);
	tex->Draw();
	TLatex *   tex = new TLatex(0.20,0.40,"more than PL025");
	tex->SetNDC();
	tex->SetTextSize(0.07);
	tex->Draw();
	c1->Print(output,"pdf");
	c1->Clear();


	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk>2");
	h->GetYaxis()->SetRangeUser(0,120);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk>2&&nmip==0");
	h->GetYaxis()->SetRangeUser(0,100);
	c1->Print(output,"pdf");
	c1->Clear();

	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk>2&&nmip==0&&gam==1");
	h->GetYaxis()->SetRangeUser(0,80);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk>2&&nmip==1");
	h->GetYaxis()->SetRangeUser(0,50);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk>2&&nmip==1&&gam==1");
	h->GetYaxis()->SetRangeUser(0,60);
	c1->Print(output,"pdf");
	c1->Clear();
	
	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk>2&&nmip==1&&gam==1&&phi==1");
	h->GetYaxis()->SetRangeUser(0,25);
	c1->Print(output,"pdf");

	tree->Draw("pl>>h(130,4.5,134.5)","(pl<85||pl>93)&&pl>25&&trk>2&&nmip==2");
	h->GetYaxis()->SetRangeUser(0,10);
	c1->Print(output,"pdf");
	c1->Clear();
	
	
	
	c1->Print(output+"]","pdf");
}