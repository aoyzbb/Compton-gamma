{
    TFile f("neutronFlux.root", "recreate");
    
    vector<double> neutronPlot = {
3.165336, 	0.0651832 ,
3.183462, 	0.1216085 ,
3.201588, 	0.2010222 ,
3.219714, 	0.3009613 ,
3.237839, 	0.4115736 ,
3.255965, 	0.5238278 ,
3.274091, 	0.6352611 ,
3.292216, 	0.7335581 ,
3.310342, 	0.8261081 ,
3.328468, 	0.9030587 ,
3.346593, 	0.9504529 ,
3.364719, 	0.9847108 ,
3.382845, 	1.0082955 ,
3.400970, 	1.0532266 ,
3.419096, 	1.1162200 ,
3.437222, 	1.2128750 ,
3.455348, 	1.3119930 ,
3.473473, 	1.4176792 ,
3.491599, 	1.5332175 ,
3.509725, 	1.6701023 ,
3.527850, 	1.8266913 ,
3.545976, 	2.0152999 ,
3.564102, 	2.2088346 ,
3.582227, 	2.3916962 ,
3.600353, 	2.5745577 ,
3.617655, 	2.7715882 ,
3.633309, 	2.9665609 ,
3.647315, 	3.1586684 ,
3.660497, 	3.3475622 ,
3.673680, 	3.5432294 ,
3.686862, 	3.7400255 ,
3.700044, 	3.9334349 ,
3.713227, 	4.1279731 ,
3.725585, 	4.3246555 ,
3.737944, 	4.5182737 ,
3.751126, 	4.7139409 ,
3.764308, 	4.9050925 ,
3.778314, 	5.1005867 ,
3.794792, 	5.3047072 ,
3.812918, 	5.4719694 ,
3.831044, 	5.5489201 ,
3.849169, 	5.5347382 ,
3.866471, 	5.4259408 ,
3.881301, 	5.2245935 ,
3.892012, 	5.0225807 ,
3.900251, 	4.8198074 ,
3.908490, 	4.6188404 ,
3.916729, 	4.4016173 ,
3.924968, 	4.1735567 ,
3.932383, 	3.9708310 ,
3.938974, 	3.7807964 ,
3.945565, 	3.5726995 ,
3.952156, 	3.3713759 ,
3.958748, 	3.1610212 ,
3.965339, 	2.9393776 ,
3.971930, 	2.7132184 ,
3.978521, 	2.4848014 ,
3.985112, 	2.2563843 ,
3.991703, 	2.0257095 ,
3.998294, 	1.7905191 ,
4.004886, 	1.5621021 ,
4.011477, 	1.3540052 ,
4.018068, 	1.1549395 ,
4.024659, 	0.9603893 ,
4.032074, 	0.7554058 ,
4.041137, 	0.5567995 ,
4.051848, 	0.3385736 ,
4.065854, 	0.1393381 



};
    
    TGraph *graph = new TGraph();
    for(int i=0; i<neutronPlot.size()/2; i++)
    {
        graph->SetPoint(i, neutronPlot[2*i], neutronPlot[2*i+1]);
    }
    //
    //graph->Draw();

vector<double>ModNeutronPlot ;
TH1F *fhist = new TH1F("fhist", "neutron flux", neutronPlot.size()/2, neutronPlot[0], neutronPlot[neutronPlot.size()-2]);
    for(int i=0; i<neutronPlot.size()/2; i++)
    {
        fhist->SetBinContent(i,neutronPlot[2*i+1]);
    }
    double step = 0.001;
    double bin =0.002;
    for(int i=0; i<neutronPlot.size()/2; i++){
        if (neutronPlot[2*i]<(bin+step)&&neutronPlot[2*i]>(bin-step)){
            ModNeutronPlot.push_back(neutronPlot[2*i]);
            ModNeutronPlot.push_back(neutronPlot[2*i+1]);
            bin=bin+2*step;
            printf("debug:i is %d, bin is %f\n ", i,bin);
        }
         while (neutronPlot[2*i]>(bin+step)){
             bin=bin+2*step;
              ModNeutronPlot.push_back(neutronPlot[2*i]);
            ModNeutronPlot.push_back(neutronPlot[2*i+1]);

         }
    }
    printf("\n%zu\n",ModNeutronPlot.size());
   
   //TH1F* fhist2= graph->GetHistogram();
    //fhist2->Draw();
    
    /*
    TH1F *fhist = new TH1F("fhist", "neutron flux", ModNeutronPlot.size()/2, ModNeutronPlot[0], ModNeutronPlot[ModNeutronPlot.size()-2]);
    for(int i=0; i<ModNeutronPlot.size()/2; i++)
    {
        fhist->SetBinContent(i,ModNeutronPlot[2*i+1]);
    }
    */
    //TH1F *h =  new TH1F("h", "flux", 123, neutronPlot[0], neutronPlot[234]);
    //for(int i=0; i<100000000; i++){
     //   h->Fill(fhist->GetRandom());
    //}
    //h->Draw();
   fhist->Draw();
   fhist->Write();

    f.Close();
}
