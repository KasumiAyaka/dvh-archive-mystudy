// zmd_analy.C
// 2022/01/27
// kasumi
void dzmd_analy(){
	TString name;
	name.Form("zmd_analy.pdf");	
	
	TCanvas *c1=new TCanvas("c1","c1",600,400);
	
	gStyle->SetOptStat(1111);
	
	c1->Print(name+"[","pdf");
	
	// Water
	tree->Draw("md:z>>h0(200,-3250,50,140,0,140)","pl%2==1","colz");
	h0->SetTitle("MinimumDistance-Zdepth(Water);z:md");
	
	c1->Print(name,"pdf");
	c1->Clear();
	// z<-3180
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-3250,50,140,0,140)","pl%2==1&&z<-3180","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==1&&z<-3180","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(h3150,-10000,260000,150,-10000,260000)","pl%2==1&&z<-3180","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,140,0,140)","pl%2==1&&z<-3180","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	
	// z>-10
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-3250,50,140,0,140)","pl%2==1&&z>-10","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==1&&z>-10","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==1&&z>-10","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,140,0,140)","pl%2==1&&z>-10","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	
	// -1300<z<-200
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-3250,50,140,0,140)","pl%2==1&&z>-1300&&z<-200&&md<20","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==1&&z>-1300&&z<-200&&md<20","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==1&&z>-1300&&z<-200&&md<20","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,140,0,140)","pl%2==1&&z>-1300&&z<-200&&md<20","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	
	// -3000<z-1500
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-3250,50,140,0,140)","pl%2==1&&z>-3000&&z<-1500&&md<20","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==1&&z>-3000&&z<-1500&&md<20","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==1&&z>-3000&&z<-1500&&md<20","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,140,0,140)","pl%2==1&&z>-3000&&z<-1500&&md<20","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	
	// md>50
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-3250,50,140,0,140)","pl%2==1&&md>50","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==1&&md>50","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==1&&md>50","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,140,0,140)","pl%2==1&&md>50","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	
	// md<-600*oa+60
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-3250,50,140,0,140)","pl%2==1&&md<-600*oa+60","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==1&&md<-600*oa+60","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==1&&md<-600*oa+60","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,140,0,140)","pl%2==1&&md<-600*oa+60","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	
	// md>-600*oa+60
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-3250,50,140,0,140)","pl%2==1&&md>-600*oa+60","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==1&&md>-600*oa+60","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==1&&md>-600*oa+60","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,140,0,140)","pl%2==1&&md>-600*oa+60","colz");
	
	
	//tree->Draw("npl","pl%2==1&&z>-10","colz");
	c1->Print(name,"pdf");
	c1->Clear();

	// Fe *****************************************************************
	tree->Draw("md:z>>h1(200,-1050,50,140,0,70)","pl%2==0","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	// z<-990
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-1050,50,140,0,70)","pl%2==0&&z<-990","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==0&&z<-990","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==0&&z<-990","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,70,0,70)","pl%2==0&&z<-990","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	// z>-10
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-1050,50,140,0,70)","pl%2==0&&z>-10","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==0&&z>-10","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==0&&z>-10","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,70,0,20)","pl%2==0&&z>-10","colz");
		
	c1->Print(name,"pdf");
	c1->Clear();
	c1->Divide(2,2);
	// -400 < z < -10, md<8
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-1050,50,140,0,70)","pl%2==0&&z>-400&&z<-10&&md<8","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==0&&z>-400&&z<-10&&md<8","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==0&&z>-400&&z<-10&&md<8","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,70,0,20)","pl%2==0&&z<-10&&z>-400&&z<-10&&md<8","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();
	// -950<z<-400, md<8
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-1050,50,140,0,70)","pl%2==0&&z>-950&&z<-400&&md<8","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==0&&z>-950&&z<-400&&md<8","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==0&&z>-950&&z<-400&&md<8","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,70,0,20)","pl%2==0&&z>-950&&z<-400&&md<8","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();

	// md>20
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-1050,50,140,0,70)","pl%2==0&&md>15","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==0&&md>15","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==0&&md>15","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,70,0,70)","pl%2==0&&md>15","colz");
	
	c1->Print(name,"pdf");
	c1->Clear();

	// md<-600*oa+60
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-1050,50,140,0,70)","pl%2==0&&md<-600*oa+60","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==0&&md<-600*oa+60","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==0&&md<-600*oa+60","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,70,0,70)","pl%2==0&&md<-600*oa+60","colz");

	c1->Print(name,"pdf");
	c1->Clear();

	// &&md>-600*oa+60
	c1->Divide(2,2);
	c1->cd(1);
	tree->Draw("md:z>>h1(200,-1050,50,140,0,70)","pl%2==0&&md>-600*oa+60","colz");
	
	c1->cd(2);
	tree->Draw("ay:ax>>h2(80,-4,4,80,-4,4)","pl%2==0&&md>-600*oa+60","colz");
	
	c1->cd(3);
	tree->Draw("y:x>>h3(150,-10000,260000,150,-10000,260000)","pl%2==0&&md>-600*oa+60","colz");
	
	c1->cd(4);
	tree->Draw("md:oa>>h4(140,0,2.8,70,0,70)","pl%2==0&&md>-600*oa+60","colz");

	
	//tree->Draw("npl","pl%2==1&&z>-10","colz");
	
	
	c1->Print(name,"pdf");
	c1->Print(name+"]","pdf");
	
}