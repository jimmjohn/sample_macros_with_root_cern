double gausX(double* x,double* par){
  return par[0]*(TMath::Gaus(x[0], par[1], par[2], kFALSE));
}

void constrained_fit(){

    // Generate 2 angles, x and y, randomly between 20 and 80 degrees with a
    // flat distribution and a third angle using the relation z = 180 - (x + y)

    TH1F* x0dist = new TH1F("x0dist","x0dist",100,-10,10);
    TH1F* y0dist = new TH1F("y0dist","y0dist",100,-10,10);
    TH1F* z0dist = new TH1F("z0dist","z0dist",100,-10,10);

    TH1F* x1dist = new TH1F("x1dist","x1dist",100,-10,10);
    TH1F* y1dist = new TH1F("y1dist","y1dist",100,-10,10);
    TH1F* z1dist = new TH1F("z1dist","z1dist",100,-10,10);

    TCanvas* c1 = new TCanvas("c1","c1" , 600, 700);
    c1->Divide(3,2);

    for(int ij=0; ij<100000; ij++) {
        double x, y, z;

        x = gRandom->Uniform(20,80);
        y = gRandom->Uniform(20,80);
        z = 180.0 - (x+y);

        //Assume the uncertainties of x, y and z to be the same (2 degree)
        double sigma1 = 2.;
        double sigma2 = 2.;
        double sigma3 = 2.;
        //Smear x, y and z with these uncertainties assuming Gaussian distributions to get measured values x1, y1 and z1
        double x1, y1, z1;
        x1 = x+gRandom->Gaus(0,sigma1);
        y1 = y+gRandom->Gaus(0,sigma2);
        z1 = z+gRandom->Gaus(0,sigma3);

        //Re-determine x, y and z from the smeared values x1, y1 and z1 using the constraint equation to get x0, y0, z0
        double x0, y0, z0;

        double lambda  = (180. - (x1+y1+z1))/(sigma1*sigma1 + sigma2*sigma2 + sigma3*sigma3);

        x0 = x1 +  lambda*sigma1*sigma1;
        y0 = y1 +  lambda*sigma2*sigma2;
        z0 = z1 +  lambda*sigma3*sigma3;

        cout << "x="<< x <<"\ty="<< y << "\tz=" << z << "\tx1="<< x1 <<"\ty1="<< y1 << "\tz1=" << z1 << "\tx0="<< x0 <<"\ty0="<< y0 << "\tz0=" << z0 <<endl;

        //Repeat this for 1000 events and plot distributions for x-x0, y-y0, z-z0 to be compared with x-x1, y-y1, z-z1
        x0dist->Fill(x-x0);
        y0dist->Fill(y-y0);
        z0dist->Fill(z-z0);
        x1dist->Fill(x-x1);
        y1dist->Fill(y-y1);
        z1dist->Fill(z-z1);

    }
    
    c1->cd(1);
    x1dist->Draw();
    c1->cd(2);
    y1dist->Draw();
    c1->cd(3);
    z1dist->Draw();
    c1->cd(4);
    x0dist->Draw();
    c1->cd(5);
    y0dist->Draw();
    c1->cd(6);
    z0dist->Draw();
 


}
