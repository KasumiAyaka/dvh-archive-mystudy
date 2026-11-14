// phvを角度ごとに出力
// 2021/10/13
// kasumi
//2021/10/18 add angle-mean plot
// 2021/10/25 変則的なヒスと
void test_v3(){

	TString name;
	name.Form("phv_test_v3.pdf");
	//TCanvas *c1 = new TCanvas(name.Data(), name.Data(), 800, 650);
	TCanvas *c1 = new TCanvas("c1","c1", 700, 650);
	c1->Print(name + "[", "pdf");    // open "canv.pdf"
	
	gStyle->SetOptStat("e"); 
	gStyle->SetStatX(0.99);       //統計boxの右上角のX座標（左下を(0,0),右上を(1,1)）
	gStyle->SetStatY(0.99); 
	gStyle->SetTitleXSize(0.05);
	gStyle->SetTitleYSize(0.05);

	//c1->SetRightMargin(0.5);
	//c1->SetLeftMargin(0.5);
	
//*** Page 1*** ********************************************
	//const Int_t nhist = 10;
	TString hname, htitle,con,hcon;
	//Int_t n=40;
	Double_t x[40];
	Double_t y[40];
	Double_t ex[40];
	Double_t ey[40];
	
	TH1D *h1 = new TH1D("h1","phv {0 <= (ax^2+ay^2) < 0.1};phv;" , 36, -0.5, 35.5);
	
	
	const Int_t N = tree->GetEntries();
	Int_t i = 0;
	hname.Form("%.1f <= Sqrt(ax^2+ay^2) < %.1f", i*0.1,(i+4)*0.1); // set title
	con.Form("sqrt( ax^2+ay^2) >= %.1f && sqrt(ax^2+ay^2) < %.1f",i*0.1,(i+4)*0.1);
	hcon.Form("%s", con.Data()); // set condition

	h1->SetTitle(hname.Data());
	tree->Draw("phv*0.0001>>h1",hcon.Data()); 
	y[i] = h1->GetMean();
	x[i] = (2*i+4)*0.05;
	ex[i]=0.2;
	ey[i]=h1->GetRMS();
	h1->GetYaxis()->SetRangeUser(0,20000);
	
	c1->Print(name, "pdf");
	c1->Clear();
	

for (Int_t i = 1; i < 21;i++){
	hname.Form("%.1f <= Sqrt(ax^2+ay^2) < %.1f", (i+3)*0.1,(i+4)*0.1); // set title
	con.Form("sqrt( ax^2+ay^2) >= %.1f && sqrt(ax^2+ay^2) < %.1f",(i+3)*0.1,(i+4)*0.1);
	hcon.Form("%s", con.Data()); // set condition

	h1->SetTitle(hname.Data());
	tree->Draw("phv*0.0001>>h1",hcon.Data()); 
	y[i] = h1->GetMean();
	x[i] = (2*i+7)*0.05;
	ex[i]=0.05;
	ey[i]=h1->GetRMS();
	h1->GetYaxis()->SetRangeUser(0,20000);
	
	c1->Print(name, "pdf");
	c1->Clear();
	
}
	
	Int_t i = 21;//2.4~2.6, ... ~3.0
	hname.Form("%.1f <= Sqrt(ax^2+ay^2) < %.1f", (i+3)*0.1,(i+5)*0.1); // set title
	con.Form("sqrt( ax^2+ay^2) >= %.1f && sqrt( ax^2+ay^2) < %.1f",(i+3)*0.1,(i+5)*0.1);
	hcon.Form("%s", con.Data()); // set condition

	h1->SetTitle(hname.Data());
	tree->Draw("phv*0.0001>>h1",hcon.Data()); 
	y[i] = h1->GetMean();
	x[i] = (2*i+8)*0.05;
	ex[i]=0.1;
	ey[i]=h1->GetRMS();
	h1->GetYaxis()->SetRangeUser(0,20000);
	
	c1->Print(name, "pdf");
	c1->Clear();
		
	Int_t i = 22;//2.6
	hname.Form("%.1f <= Sqrt(ax^2+ay^2) < %.1f", (i+4)*0.1,(i+6)*0.1); // set title
	con.Form("sqrt( ax^2+ay^2)>= %.1f && sqrt( ax^2+ay^2)< %.1f",(i+4)*0.1,(i+6)*0.1);
	hcon.Form("%s", con.Data()); // set condition

	h1->SetTitle(hname.Data());
	tree->Draw("phv*0.0001>>h1",hcon.Data()); 
	y[i] = h1->GetMean();
	x[i] = (2*i+10)*0.05;
	ex[i]=0.1;
	ey[i]=h1->GetRMS();
	h1->GetYaxis()->SetRangeUser(0,20000);
	
	c1->Print(name, "pdf");
	c1->Clear();
	
	Int_t i = 23;//2.8
	hname.Form("%.1f <= Sqrt(ax^2+ay^2) < %.1f", (i+5)*0.1,(i+7)*0.1); // set title
	con.Form("sqrt( ax^2+ay^2)>= %.1f && sqrt( ax^2+ay^2) < %.1f",(i+5)*0.1,(i+7)*0.1);
	hcon.Form("%s", con.Data()); // set condition

	h1->SetTitle(hname.Data());
	tree->Draw("phv*0.0001>>h1",hcon.Data()); 
	y[i] = h1->GetMean();
	x[i] = (2*i+12)*0.05;
	ex[i]=0.1;
	ey[i]=h1->GetRMS();
	h1->GetYaxis()->SetRangeUser(0,20000);
	
	c1->Print(name, "pdf");
	c1->Clear();
	
	
	Int_t i = 24;//3.0
	hname.Form("%.1f <= Sqrt(ax^2+ay^2) < %.1f", (i+6)*0.1,(i+11)*0.1); // set title
	con.Form("sqrt( ax^2+ay^2)>= %.1f &&sqrt( ax^2+ay^2) < %.1f",(i+6)*0.1,(i+11)*0.1);
	hcon.Form("%s", con.Data()); // set condition

	h1->SetTitle(hname.Data());
	tree->Draw("phv*0.0001>>h1",hcon.Data()); 
	y[i] = h1->GetMean();
	x[i] = (2*i+17)*0.05;
	ex[i]=0.25;
	ey[i]=h1->GetRMS();
	h1->GetYaxis()->SetRangeUser(0,20000);
	
	c1->Print(name, "pdf");
	c1->Clear();
	
	Int_t i = 25;//3.5
	hname.Form("%.1f <= Sqrt(ax^2+ay^2) < %.1f", (i+10)*0.1,(i+15)*0.1); // set title
	con.Form("sqrt( ax^2+ay^2)>= %.1f && sqrt( ax^2+ay^2) < %.1f",(i+10)*0.1,(i+15)*0.1);
	hcon.Form("%s", con.Data()); // set condition

	h1->SetTitle(hname.Data());
	tree->Draw("phv*0.0001>>h1",hcon.Data()); 
	y[i] = h1->GetMean();
	x[i] = (2*i+25)*0.05;
	ex[i]=0.25;
	ey[i]=h1->GetRMS();
	h1->GetYaxis()->SetRangeUser(0,20000);
	
	c1->Print(name, "pdf");
	c1->Clear();

	//TGraph *gr = 
	{
// auto c2 = new TCanvas("c2","A Simple Graph with error bars",200,10,700,500);
// c2->SetFillColor(42);
//c2->SetGrid();
//c2->GetFrame()->SetFillColor(21);
//c2->GetFrame()->SetBorderSize(12);
//const Int_t n = 10;

   auto gr = new TGraphErrors(26,x,y,ex,ey);
   gr->SetTitle("tan#theta - MeanValue;tan #theta ;mean");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
	gr->SetMarkerSize(1);
	gr->GetYaxis()->SetRangeUser(0,33);
   //gr->Draw("A2*");
		gr->Draw("A*");
	}

	c1->Print(name, "pdf");
	
// graph ended -----------------------------------------------
 	c1->Print(name + "]", "pdf");    // ここで"canv.pdf"を閉じる感じ

}
