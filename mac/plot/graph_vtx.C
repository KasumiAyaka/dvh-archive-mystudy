void graph_vtx()
{

TCanvas *c1=new TCanvas("c1","",700,700);
c1->Divide(2,2);

c1->cd(1);
TH2D = new TH2D("h1","pl:mul",200,115000,250000,200,-10000,100000);
tree->Project("h1","pl:mul");
h1->Draw("colz");

c1->cd(2);
TH2D = new TH2D("h2","y:x", 200,-3,3,200,-3,3);
tree->Project("h2","y:x");
h2->Draw("colz");

c1->cd(3);
TH2D = new TH2D("h3","y:z",100,-1,1,100,-60,60);
tree->Project("h3","y:z","flg==1");
h3->Draw("colz");

c1->cd(4);
TH2D = new TH2D("h4","x:z",100,-2,2,200,-100,100);
tree->Project("h4","x:z","flg==1");
h4->Draw("colz");



c1->SaveAs("../graph/2trk/vtx.pdf");



}