// stop trackの基本的な情報をplごとにplot
// 2021/10/21
// kasumi
void stop_pos_ang(){
//*** variables *********************************************
	TString name;
	name.Form("stop_position_angle.pdf");
	const Int_t N = tree->GetEntries();
	TString hname,h2name,h3name,h4name,htitle,con,hcon,con1,hcon1;


//**:Tcanvas ************************************************
	//TCanvas *c1 = new TCanvas(name.Data(), name.Data(), 800, 650);
	TCanvas *c1 = new TCanvas("c1","c1", 1400, 700);
	
//	
	c1->Print(name + "[", "pdf");    // open "canv.pdf"
	
	gStyle->SetOptStat("e"); 
	gStyle->SetStatX(0.99);       //統計boxの右上角のX座標（左下を(0,0),右上を(1,1)）
	gStyle->SetStatY(0.99); 
	gStyle->SetTitleXSize(0.05);
	gStyle->SetTitleYSize(0.05);

	//c1->SetRightMargin(0.5);
	//c1->SetLeftMargin(0.5);
	
//*** gragh *** ********************************************
	//const Int_t nhist = 10;

	TH2D *h1 = new TH2D("h1","position;x;y",130,-5000,255000,130,-5000,255000);
	TH2D *h2 = new TH2D("h2","angle;ax;ay",80,-4,4,80,-4,4);
	TH2D *h3 = new TH2D("h3","position up;x;y",130,-5000,255000,130,-5000,255000);
	TH2D *h4 = new TH2D("h4","angle up;ax;ay",80,-4,4,80,-4,4);

	TH1D *hist0 = new TH1D("hist0","pl0;PL;",134,-0.5,133.5);
	TH1D *hist1 = new TH1D("hist1","pl1 (stop pl);PL;",134,-0.5,133.5);
	
//*** Page 1*** ********************************************
	c1->Divide(2,1);

	c1->cd(1);
	tree->Draw("pl0>>hist0"); 

	c1->cd(2);
	tree->Draw("pl1>>hist1");
	
	c1->Print(name, "pdf");
	c1->Clear();
	
//*** Loop Page *** ********************************************
	for (Int_t i = 1; i < 134;i++){
		hname.Form("PL%03d Position (Stop Track)", i); // set title
		h2name.Form("PL%03d Angle (Stop Track)",i);
		h3name.Form("PL%03d Position (upstream)", i); // set title
		h4name.Form("PL%03d Angle (upstream)",i);
		con.Form("pl0==%d",i);
		hcon.Form("%s", con.Data()); // set condition
		con1.Form("pl1==%d",i);
		hcon1.Form("%s", con1.Data()); // set condition
		

		c1->Divide(2,1);
		
		c1->cd(1);
		h1->SetTitle(hname.Data());
		tree->Draw("y:x>>h1",hcon1.Data()); 
		h1->Draw("colz");

		c1->cd(2);
		h2->SetTitle(h2name.Data());
		tree->Draw("ay:ax>>h2",hcon1.Data());
		h2->Draw("colz");
		
	/*	c1->cd(3);
		h3->SetTitle(h3name.Data());
		tree->Draw("y:x>>h3",hcon1.Data()); 
		h3->Draw("colz");

		c1->cd(4);
		h4->SetTitle(h4name.Data());
		tree->Draw("ay:ax>>h4",hcon1.Data());
		h4->Draw("colz");
		*/

		c1->Print(name, "pdf");
		c1->Clear();
}
	c1->Print(name, "pdf");
	
// graph ended -----------------------------------------------
 	c1->Print(name + "]", "pdf");    // ここで"canv.pdf"を閉じる感じ

}
