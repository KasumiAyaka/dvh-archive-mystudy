void graph_track()
{

TCanvas *c1=new TCanvas("c1","",1000,700);
c1->Divide(4,2);

c1->cd(1);
TH2D = new TH2D("h1","y:x",250,0,250000,250,0,250000);
tree->Project("h1","y:x");
h1->Draw("colz");

c1->cd(2);
TH2D = new TH2D("h2","ax-ay",40,0,4,40,0,4);
tree->Project("h2","ay:ax");
h2->Draw("colz");

c1->cd(3);
TH2D = new TH2D("h3","nseg-ph",100,0,200,50,0,3);
tree->Project("h3","ph:nseg");
h3->Draw("colz");

c1->cd(4);
TH2D = new TH2D("h4","chain-ph",100,6000,15000,100,0,5);
tree->Project("h4","ph:chain");
h4->Draw("colz");

c1->cd(5);
TH2D = new TH2D("h5","sqrt(ax*ax+ay*ay)-ax",200,-1,1,100,-0.05,0.05);
tree->Project("h5","ax:sqrt(ax*ax+ay*ay)");
h5->Draw("colz");

c1->cd(6);
TH2D = new TH2D("h6","sqrt(ax*ax+ay*ay)-x",100,6000,15000,100,0,5);
tree->Project("h6","x:sqrt(ax*ax+ay*ay)");
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

c1->SaveAs("../graph/2trk/track.pdf");



}