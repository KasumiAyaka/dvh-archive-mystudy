// phvを角度ごとに出力
// 2021/10/13
// kasumi
//2021/10/18 add angle-mean plot
//2021/10/19 copy test_v2.C->phv.C
//2021/11/03 ey:0->GetMeanError=GetMean(11)
void phv_v2(TString input="in.root",TString name="out.pdf"){
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
	Int_t n=41;
	Double_t x[n];
	Double_t y[n];
	Double_t ex[n];
	Double_t ey[n];
	
	TH1D *h1 = new TH1D("h1","phv {0 <= sqrt(ax^2+ay^2) < 0.1};phv;" , 36, -0.5, 35.5);
		
	//const Int_t N = tree->GetEntries();
for (Int_t i = 0; i < n;i++){
	hname.Form("%.1f <= Sqrt(ax^2+ay^2) < %.1f", i*0.1,(i+1)*0.1); // set title
	con.Form("sqrt(ax^2+ay^2 )>= %.1f && sqrt( ax^2+ay^2) < %.1f",i*0.1,(i+1)*0.1);
	hcon.Form("%s", con.Data()); // set condition

	h1->SetTitle(hname.Data());
	tree->Draw("phv*0.0001>>h1",hcon.Data()); 
	y[i] = h1->GetMean(1);
	x[i] = (i+i+1)*0.05;
	ex[i]=0.05;
	ey[i]=h1->GetMean(11);
	std::cout<<"y = "<<y[i]<<",x = "<<x[i]<<",ey = "<<ey[i]<<",ex = "<<ex[i]<<std::endl;
	c1->Print(name, "pdf");
	c1->Clear();
	
}
	//TGraph *gr = 
	{
// auto c2 = new TCanvas("c2","A Simple Graph with error bars",200,10,700,500);
// c2->SetFillColor(42);
//c2->SetGrid();
//c2->GetFrame()->SetFillColor(21);
//c2->GetFrame()->SetBorderSize(12);
//const Int_t n = 10;

   auto gr = new TGraphErrors(n,x,y,ex,ey);
   gr->SetTitle("tan - MeanValue;tan #theta ;mean");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
	gr->SetMarkerSize(1);
   gr->Draw("A*");
}

	c1->Print(name, "pdf");
	
// graph ended -----------------------------------------------
 	c1->Print(name + "]", "pdf");    // ここで"canv.pdf"を閉じる感じ

}
