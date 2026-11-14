void graph_pair()
{

TCanvas *c1=new TCanvas("c1","",1000,700);
c1->Divide(3,2);

c1->cd(1);
TH2D = new TH2D("h1","y:x",125,0,250000,125,0,250000);
tree->Project("h1","y:x");
h1->Draw("colz");

c1->cd(2);
TH2D = new TH2D("h2","oa-md",40,0,2.5,50,0,20);
tree->Project("h2","md:oa");
h2->Draw("colz");

c1->cd(3);
TH2D = new TH2D("h3","x-oa",125,0,250000,25,0,1);
tree->Project("h3","oa:x");
h3->Draw("colz");

c1->cd(4);
TH2D = new TH2D("h4","x-md",125,0,250000,40,0,10);
tree->Project("h4","md:x");
h4->Draw("colz");

c1->cd(5);
TH2D = new TH2D("h5","y-oa",125,0,250000,25,0,1);
tree->Project("h5","oa:y");
h5->Draw("colz");

c1->cd(6);
TH2D = new TH2D("h6","y-md",125,0,250000,40,0,10);
tree->Project("h6","md:y");
h6->Draw("colz");

/*
c1->cd(7);
TH2D = new TH2D("h7","oa-md",40,0,4.5,100,0,50);
tree->Project("h7","md:oa","ph< ");
h7->Draw("colz");

c1->cd(8);
TH2D = new TH2D("h8","y0-y1:x0",40,0,4.5,100,0,50);
tree->Project("h8","y0-y1:x0","ph>   && ph < ");
h8->Draw("colz");

*/

c1->SaveAs("../graph/2trk/pair.pdf");



}