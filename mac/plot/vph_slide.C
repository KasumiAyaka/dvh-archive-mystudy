// phvを角度ごとに出力
// 2022/01/07
// all 2trk vtx track 
// kasumi
// 
// 2022/01/15 kansei
// 2022/01/25 edit
// 
void vph_slide(TString output="./figure/vphforslide.pdf"){

	TString name;
	name.Form("./fig/vph_slide.pdf");
	//TCanvas *c1 = new TCanvas(name.Data(), name.Data(), 800, 650);
	TCanvas *c1 = new TCanvas("c1","c1", 1600, 900);
	c1->Print(name + "[", "pdf");    // open "canv.pdf"
	
//	gStyle->SetOptStat("e"); 
	gStyle->SetStatX(0.99);       //統計boxの右上角のX座標（左下を(0,0),右上を(1,1)）
	gStyle->SetStatY(0.99); 
	gStyle->SetTitleXSize(0.05);
	gStyle->SetTitleYSize(0.05);

	//c1->SetRightMargin(0.5);
	//c1->SetLeftMargin(0.5);
	
//*** Page 1*** ********************************************
	//const Int_t nhist = 10;
	TString hname, htitle,con,hcon;
	TString h2name, h2title,con2,h2con;
	TString l;
	Int_t n = 41;
	Double_t x[16]=0;
	Double_t y[16]=0;
	Double_t ex[16]=0;
	Double_t ey[16]=0;
	
	Double_t x2[16]=0;
	Double_t y2[16]=0;
	Double_t ex2[16]=0;
	Double_t ey2[16]=0;
	//Int_t h[10];
		
	TH1D *h1 = new TH1D("h1","vph {0 <= (ax^2+ay^2) < 0.1};vph;" , 40, 0, 400);
	TH1D *h2 = new TH1D("h2","vph {0 <= (ax^2+ay^2) < 0.1};vph;" , 40, 0, 400);
	TH1D *h3 = new TH1D("h3","vph {0 <= (ax^2+ay^2) < 0.1};vph;" , 40, 0, 400);
	TH1D *h4 = new TH1D("h4","vph {0 <= (ax^2+ay^2) < 0.1};vph;" , 40, 0, 400);
	TH1D *h5 = new TH1D("h5","vph {0 <= (ax^2+ay^2) < 0.1};vph;" , 40, 0, 400);
	TH1D *h6 = new TH1D("h6","vph {0 <= (ax^2+ay^2) < 0.1};vph;" , 40, 0, 400);

	TH1D *hist1 = new TH1D("hist1","ph {0 <= (ax^2+ay^2) < 0.1};ph;" , 50, 0, 150);
	TH1D *hist2 = new TH1D("hist2","ph {0 <= (ax^2+ay^2) < 0.1};ph;" , 50, 0, 150);
	TH1D *hist3 = new TH1D("hist3","ph {0 <= (ax^2+ay^2) < 0.1};ph;" , 50, 0, 150);
	TH1D *hist4 = new TH1D("hist4","ph {0 <= (ax^2+ay^2) < 0.1};ph;" , 50, 0, 150);
	TH1D *hist5 = new TH1D("hist5","ph {0 <= (ax^2+ay^2) < 0.1};ph;" , 50, 0, 150);
	TH1D *hist6 = new TH1D("hist6","ph {0 <= (ax^2+ay^2) < 0.1};ph;" , 50, 0, 150);
	
	
	//TLine line=new TLine(0,0,3,5);
	//line->SetLineColor(3);
	//line->SetLineWidth(5);
	//line->SetLineStyle(3);//1=line,2=broken,3=dotted,4=broken-dot,5=long-broken-dot
	//line->Draw();
	
//for (Int_t i = 0; i < 21;i++){
	Int_t i = 0;
	while(i<12){
		std::cout<<"********** "<<i<<"th ********** "<<std::endl;
		c1->Divide(3,2);

		//--- vph ------------------------------------------------------------------------- vph ------
		if(i%6==0){
			c1->cd(1);
			// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h1->SetTitle(hname.Data());
		
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
			
			
			// Draw plot
			tree->Draw("ph%10000>>h1",hcon.Data());//vph
	
			// input of TGraphErrors
			y[i] = h1->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;
			//ey[i]=h1->GetRMS();
			ey[i]= h1->GetMeanError();
			//	h1->GetYaxis()->SetRangeUser(0,60000);
	
			// output for check
			std::cout << "rms  " <<h1->GetRMS()<<" : GetMean  "<<h1->GetMean()<<" : GetMeanError  "<<h1->GetMeanError()<<std::endl;
			i++;
		}
		if(i%6==1){
			c1->cd(2);
	
			// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h2->SetTitle(hname.Data());
		
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
	
			// Draw plot
			tree->Draw("ph%10000>>h2",hcon.Data());//vph
	
			// input of TGraphErrors
			y[i] = h2->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;

			//ey[i]=h2->GetRMS();
			ey[i]= h2->GetMeanError();
			//	h2->GetYaxis()->SetRangeUser(0,60000);
	
			// output for check
			std::cout << "rms  " <<h2->GetRMS()<<" : GetMean  "<<h2->GetMean()<<" : GetMeanError  "<<h2->GetMeanError()<<std::endl;
			i++;

		}
		if(i%6==2){
			c1->cd(3);

			// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h3->SetTitle(hname.Data());
		
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
	
			// Draw plot
			tree->Draw("ph%10000>>h3",hcon.Data());//vph
	
			// input of TGraphErrors
			y[i] = h3->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;
	
			//ey[i]=h3->GetRMS();
			ey[i]= h3->GetMeanError();
			//	h3->GetYaxis()->SetRangeUser(0,60000);
	
			// output for check
			std::cout << "rms  " <<h3->GetRMS()<<" : GetMean  "<<h3->GetMean()<<" : GetMeanError  "<<h3->GetMeanError()<<std::endl;
			i++;

		}	
		if(i%6==3){
			c1->cd(4);

			// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h4->SetTitle(hname.Data());
				
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
	
			// Draw plot
			tree->Draw("ph%10000>>h4",hcon.Data());//vph
	
			// input of TGraphErrors
			y[i] = h4->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;
	
			//ey[i]=h4->GetRMS();
			ey[i]= h4->GetMeanError();
			//	h4->GetYaxis()->SetRangeUser(0,60000);
	
			// output for check
			std::cout << "rms  " <<h4->GetRMS()<<" : GetMean  "<<h4->GetMean()<<" : GetMeanError  "<<h4->GetMeanError()<<std::endl;
			i++;

		}
		if(i%6==4){
			c1->cd(5);
					// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h5->SetTitle(hname.Data());
			
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
		
			// Draw plot
			tree->Draw("ph%10000>>h5",hcon.Data());//vph
		
			// input of TGraphErrors
			y[i] = h5->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;
			//ey[i]=h5->GetRMS();
			ey[i]= h5->GetMeanError();
			//	h5->GetYaxis()->SetRangeUser(0,60000);
		
			// output for check
			std::cout << "rms  " <<h5->GetRMS()<<" : GetMean  "<<h5->GetMean()<<" : GetMeanError  "<<h5->GetMeanError()<<std::endl;
			i++;

		}
		if(i%6==5){
			c1->cd(6);
					// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h6->SetTitle(hname.Data());
			
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
		
			// Draw plot
			tree->Draw("ph%10000>>h6",hcon.Data());//vph
		
			// input of TGraphErrors
			y[i] = h6->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;
			//ey[i]=h6->GetRMS();
			ey[i]= h6->GetMeanError();
			//	h6->GetYaxis()->SetRangeUser(0,60000);
		
			// output for check
			std::cout << "rms  " <<h6->GetRMS()<<" : GetMean  "<<h6->GetMean()<<" : GetMeanError  "<<h6->GetMeanError()<<std::endl;
			i++;

		}
	
		c1->Print(name, "pdf");
		c1->Clear();

	}
	i=12;
	// ang
	std::cout<<"********** "<<i<<"th ********** "<<std::endl;
		c1->Divide(3,2);

		//--- vph ------------------------------------------------------------------------- vph ------
		if(i%6==0){
			c1->cd(1);
			// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h1->SetTitle(hname.Data());
		
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
			
			
			// Draw plot
			tree->Draw("ph%10000>>h1",hcon.Data());//vph
	
			// input of TGraphErrors
			y[i] = h1->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;
			//ey[i]=h1->GetRMS();
			ey[i]= h1->GetMeanError();
			//	h1->GetYaxis()->SetRangeUser(0,60000);
	
			// output for check
			std::cout << "rms  " <<h1->GetRMS()<<" : GetMean  "<<h1->GetMean()<<" : GetMeanError  "<<h1->GetMeanError()<<std::endl;
			i++;
		}
		if(i%6==1){
			c1->cd(2);
	
			// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h2->SetTitle(hname.Data());
		
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
	
			// Draw plot
			tree->Draw("ph%10000>>h2",hcon.Data());//vph
	
			// input of TGraphErrors
			y[i] = h2->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;

			//ey[i]=h2->GetRMS();
			ey[i]= h2->GetMeanError();
			//	h2->GetYaxis()->SetRangeUser(0,60000);
	
			// output for check
			std::cout << "rms  " <<h2->GetRMS()<<" : GetMean  "<<h2->GetMean()<<" : GetMeanError  "<<h2->GetMeanError()<<std::endl;
			i++;

		}
		if(i%6==2){
			c1->cd(3);

			// Set Title
			hname.Form("%.1f <= tan#theta < %.1f", i*0.2,(i+1)*0.2); // set title
			h3->SetTitle(hname.Data());
		
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			hcon.Form("%s", con.Data()); // set condition
	
			// Draw plot
			tree->Draw("ph%10000>>h3",hcon.Data());//vph
	
			// input of TGraphErrors
			y[i] = h3->GetMean();
			x[i] = (2*i+1)*0.1;
			ex[i]=0.1;
	
			//ey[i]=h3->GetRMS();
			ey[i]= h3->GetMeanError();
			//	h3->GetYaxis()->SetRangeUser(0,60000);
	
			// output for check
			std::cout << "rms  " <<h3->GetRMS()<<" : GetMean  "<<h3->GetMean()<<" : GetMeanError  "<<h3->GetMeanError()<<std::endl;
			i++;

		}	
		if(i%6==3){
			c1->cd(4);

			// Set Title
			hname.Form("%.1f <= tan#theta", i*0.2); // set title
			h4->SetTitle(hname.Data());
				
			// Set Condition
			con.Form("sqrt( ax^2+ay^2 )>= %.1f ",i*0.2);
			hcon.Form("%s", con.Data()); // set condition
	
			// Draw plot
			tree->Draw("ph%10000>>h4",hcon.Data());//vph
	
			// input of TGraphErrors
			y[i] = h4->GetMean();
			x[i] = 3.5;
			ex[i]=0.5;
	
			//ey[i]=h4->GetRMS();
			ey[i]= h4->GetMeanError();
			//	h4->GetYaxis()->SetRangeUser(0,60000);
	
			// output for check
			std::cout << "rms  " <<h4->GetRMS()<<" : GetMean  "<<h4->GetMean()<<" : GetMeanError  "<<h4->GetMeanError()<<std::endl;
			i++;

		}
		if(i%6==4){
			c1->cd(5);
			i++;

		}
		if(i%6==5){
			c1->cd(6);
		auto gr = new TGraphErrors(16,x,y,ex,ey);
		gr->SetTitle("Volume Pulse Hight;tan #theta ;mean");
		gr->SetMarkerColor(4);
		gr->SetMarkerStyle(21);
		gr->SetMarkerSize(1);
		//gr->Draw("A2*");
		gr->GetYaxis()->SetRangeUser(0,200);
		gr->GetXaxis()->SetRangeUser(0,4);
		gr->Draw("A*");
	

		}
	
		c1->Print(name, "pdf");
		c1->Clear();
	
	
	
	// --- ph ----------------------------------------------------------------------ph----------
	i = 0;
	while(i<12){
		std::cout<<"*********  PH  *********"<<std::endl;
		std::cout<<"********** "<<i/6+1<<"th ********** "<<std::endl;
		c1->Divide(3,2);
		
		if(i%6==0){
			c1->cd(1);
			
			// Set Title
			h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
			hist1->SetTitle(h2name.Data());
		
			// Set Condition
			con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			h2con.Form("%s", con2.Data()); // set condition
			
			tree->Draw("npl>>hist1",h2con.Data());
			
			
			// TGraphErrors
			y2[i] = hist1->GetMean();
			x2[i] = (2*i+1)*0.1;
			ex2[i]=0.1;
			//ey[i]=hhist1->GetRMS();
			ey2[i]= hist1->GetMeanError();
			//hist1->GetYaxis()->SetRangeUser(0,60000);

			std::cout << "rms  " <<hist1->GetRMS()<<" : GetMean  "<<hist1->GetMean()<<" : GetMeanError  "<<hist1->GetMeanError()<<std::endl;
			i++;

		}
		if(i%6==0){
			c1->cd(1);
			
			// Set Title
			h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
			hist1->SetTitle(h2name.Data());
		
			// Set Condition
			con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			h2con.Form("%s", con2.Data()); // set condition
			
			tree->Draw("npl>>hist1",h2con.Data());
			
			
			// TGraphErrors
			y2[i] = hist1->GetMean();
			x2[i] = (2*i+1)*0.1;
			ex2[i]=0.1;
			//ey[i]=hist1->GetRMS();
			ey2[i]= hist1->GetMeanError();
			//hist1->GetYaxis()->SetRangeUser(0,60000);

			std::cout << "rms  " <<hist1->GetRMS()<<" : GetMean  "<<hist1->GetMean()<<" : GetMeanError  "<<hist1->GetMeanError()<<std::endl;
			i++;

		}
		if(i%6==1){
			c1->cd(2);
			
			// Set Title
			h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
			hist2->SetTitle(h2name.Data());
		
			// Set Condition
			con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			h2con.Form("%s", con2.Data()); // set condition
			
			tree->Draw("npl>>hist2",h2con.Data());
			
			
			// TGraphErrors
			y2[i] = hist2->GetMean();
			x2[i] = (2*i+1)*0.1;
			ex2[i]=0.1;
			//ey[i]=hist2->GetRMS();
			ey2[i]= hist2->GetMeanError();
			//hist2->GetYaxis()->SetRangeUser(0,60000);

			std::cout << "rms  " <<hist2->GetRMS()<<" : GetMean  "<<hist2->GetMean()<<" : GetMeanError  "<<hist2->GetMeanError()<<std::endl;
			i++;

		}
		if(i%6==2){
			c1->cd(3);
			
			// Set Title
			h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
			hist3->SetTitle(h2name.Data());
		
			// Set Condition
			con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			h2con.Form("%s", con2.Data()); // set condition
			
			tree->Draw("npl>>hist3",h2con.Data());
			
			
			// TGraphErrors
			y2[i] = hist3->GetMean();
			x2[i] = (2*i+1)*0.1;
			ex2[i]=0.1;
			//ey[i]=hist3->GetRMS();
			ey2[i]= hist3->GetMeanError();
			//hist3->GetYaxis()->SetRangeUser(0,60000);

			std::cout << "rms  " <<hist3->GetRMS()<<" : GetMean  "<<hist3->GetMean()<<" : GetMeanError  "<<hist3->GetMeanError()<<std::endl;
			i++;
		}
		if(i%6==3){
			c1->cd(4);
			
			// Set Title
			h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
			hist4->SetTitle(h2name.Data());
		
			// Set Condition
			con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			h2con.Form("%s", con2.Data()); // set condition
			
			tree->Draw("npl>>hist4",h2con.Data());
			
			
			// TGraphErrors
			y2[i] = hist4->GetMean();
			x2[i] = (2*i+1)*0.1;
			ex2[i]=0.1;
			//ey[i]=hist4->GetRMS();
			ey2[i]= hist4->GetMeanError();
			//hist4->GetYaxis()->SetRangeUser(0,60000);

			std::cout << "rms  " <<hist4->GetRMS()<<" : GetMean  "<<hist4->GetMean()<<" : GetMeanError  "<<hist4->GetMeanError()<<std::endl;
			i++;
		}
		if(i%6==4){
			c1->cd(5);
			
			// Set Title
			h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
			hist5->SetTitle(h2name.Data());
		
			// Set Condition
			con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			h2con.Form("%s", con2.Data()); // set condition
			
			tree->Draw("npl>>hist5",h2con.Data());
			
			
			// TGraphErrors
			y2[i] = hist5->GetMean();
			x2[i] = (2*i+1)*0.1;
			ex2[i]=0.1;
			//ey[i]=hist5->GetRMS();
			ey2[i]= hist5->GetMeanError();
			//hist5->GetYaxis()->SetRangeUser(0,60000);

			std::cout << "rms  " <<hist5->GetRMS()<<" : GetMean  "<<hist5->GetMean()<<" : GetMeanError  "<<hist5->GetMeanError()<<std::endl;
			i++;
		}
		if(i%6==5){
			c1->cd(6);
			
			// Set Title
			h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
			hist6->SetTitle(h2name.Data());
		
			// Set Condition
			con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
			h2con.Form("%s", con2.Data()); // set condition
			
			tree->Draw("npl>>hist6",h2con.Data());
			
			
			// TGraphErrors
			y2[i] = hist6->GetMean();
			x2[i] = (2*i+1)*0.1;
			ex2[i]=0.1;
			//ey[i]=hist6->GetRMS();
			ey2[i]= hist6->GetMeanError();
			//hist6->GetYaxis()->SetRangeUser(0,60000);

			std::cout << "rms  " <<hist6->GetRMS()<<" : GetMean  "<<hist6->GetMean()<<" : GetMeanError  "<<hist6->GetMeanError()<<std::endl;
			i++;
		}

	c1->Print(name, "pdf");
	c1->Clear();

	}
	i=12;
	std::cout<<"*********  PH  *********"<<std::endl;
	std::cout<<"********** "<<i/6+1<<"th ********** "<<std::endl;
	c1->Divide(3,2);
		
	if(i%6==0){
		c1->cd(1);
		
		// Set Title
		h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
		hist1->SetTitle(h2name.Data());
	
		// Set Condition
		con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
		h2con.Form("%s", con2.Data()); // set condition
		
		tree->Draw("npl>>hist1",h2con.Data());
		
		
		// TGraphErrors
		y2[i] = hist1->GetMean();
		x2[i] = (2*i+1)*0.1;
		ex2[i]=0.1;
		//ey[i]=hhist1->GetRMS();
		ey2[i]= hist1->GetMeanError();
		//hist1->GetYaxis()->SetRangeUser(0,60000);
			std::cout << "rms  " <<hist1->GetRMS()<<" : GetMean  "<<hist1->GetMean()<<" : GetMeanError  "<<hist1->GetMeanError()<<std::endl;
		i++;
		}
	if(i%6==0){
		c1->cd(1);
		// Set Title
		h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
		hist1->SetTitle(h2name.Data());
	
		// Set Condition
		con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
		h2con.Form("%s", con2.Data()); // set condition
		
		tree->Draw("npl>>hist1",h2con.Data());
		
		// TGraphErrors
		y2[i] = hist1->GetMean();
		x2[i] = (2*i+1)*0.1;
		ex2[i]=0.1;
		//ey[i]=hist1->GetRMS();
		ey2[i]= hist1->GetMeanError();
		//hist1->GetYaxis()->SetRangeUser(0,60000);
			std::cout << "rms  " <<hist1->GetRMS()<<" : GetMean  "<<hist1->GetMean()<<" : GetMeanError  "<<hist1->GetMeanError()<<std::endl;
		i++;
		}
	if(i%6==1){
		c1->cd(2);
		// Set Title
		h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
		hist2->SetTitle(h2name.Data());
	
		// Set Condition
		con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
		h2con.Form("%s", con2.Data()); // set condition
		tree->Draw("npl>>hist2",h2con.Data());
		
		// TGraphErrors
		y2[i] = hist2->GetMean();
		x2[i] = (2*i+1)*0.1;
		ex2[i]=0.1;
		//ey[i]=hist2->GetRMS();
		ey2[i]= hist2->GetMeanError();
		//hist2->GetYaxis()->SetRangeUser(0,60000);
		std::cout << "rms  " <<hist2->GetRMS()<<" : GetMean  "<<hist2->GetMean()<<" : GetMeanError  "<<hist2->GetMeanError()<<std::endl;
		i++;
		}
	if(i%6==2){
		c1->cd(3);
		// Set Title
		h2name.Form("%.1f <= (ax^2+ay^2) < %.1f", i*0.2,(i+1)*0.2); // set title
		hist3->SetTitle(h2name.Data());
	
		// Set Condition
		con2.Form("sqrt( ax^2+ay^2 )>= %.1f && sqrt(ax^2+ay^2) < %.1f ",i*0.2,(i+1)*0.2);
		h2con.Form("%s", con2.Data()); // set condition
		tree->Draw("npl>>hist3",h2con.Data());
		
		// TGraphErrors
	y2[i] = hist3->GetMean();
		x2[i] = (2*i+1)*0.1;
		ex2[i]=0.1;
		//ey[i]=hist3->GetRMS();
		ey2[i]= hist3->GetMeanError();
		//hist3->GetYaxis()->SetRangeUser(0,60000);
		std::cout << "rms  " <<hist3->GetRMS()<<" : GetMean  "<<hist3->GetMean()<<" : GetMeanError  "<<hist3->GetMeanError()<<std::endl;
		i++;
	}
	if(i%6==3){
		c1->cd(4);
		
		// Set Title
		h2name.Form("%.1f <= (ax^2+ay^2)", i*0.2); // set title
		hist4->SetTitle(h2name.Data());
	
		// Set Condition
		con2.Form("sqrt( ax^2+ay^2 )>= %.1f ",i*0.2);
		h2con.Form("%s", con2.Data()); // set condition
		
		tree->Draw("npl>>hist4",h2con.Data());
		
		// TGraphErrors
		y2[i] = hist4->GetMean();
		x2[i] = 3.5;
		ex2[i]=0.5;
		//ey[i]=hist4->GetRMS();
		ey2[i]= hist4->GetMeanError();
		//hist4->GetYaxis()->SetRangeUser(0,60000);
		std::cout << "rms  " <<hist4->GetRMS()<<" : GetMean  "<<hist4->GetMean()<<" : GetMeanError  "<<hist4->GetMeanError()<<std::endl;
		i++;
	}
	if(i%6==4){
		c1->cd(5);
		i++;
	}
	if(i%6==5){
		c1->cd(6);
		auto gr2 = new TGraphErrors(21,x2,y2,ex2,ey2);
		gr2->SetTitle("PH;tan #theta ;mean");
		gr2->SetMarkerColor(4);
		gr2->SetMarkerStyle(21);
		gr2->SetMarkerSize(1);
		//gr->Draw("A2*");
		gr2->GetYaxis()->SetRangeUser(0,80);
		gr2->GetXaxis()->SetRangeUser(0,4);
		gr2->Draw("A*");
	
		i++;
	}

	c1->Print(name, "pdf");

// graph ended -----------------------------------------------
 	c1->Print(name + "]", "pdf");    // ここで"canv.pdf"を閉じる感じ

}
