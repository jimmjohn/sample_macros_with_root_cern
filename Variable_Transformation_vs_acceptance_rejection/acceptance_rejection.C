#include <iostream>
#include <cmath>
#include <TRandom3.h>
#include <TH1F.h>
#include <TCanvas.h>

double generateGaussian(TRandom3 &randGen) {
    // Generate random numbers from a uniform distribution
    double x, y, z;
    do {
        x = 2.0 * randGen.Uniform() - 1.0;
        y = 2.0 * randGen.Uniform() - 1.0;
        z = x * x + y * y;
    } while (z >= 1.0 || z == 0.0);

    // Box-Muller transformation to convert uniform to Gaussian
    return x * sqrt(-2.0 * log(z) / z);
}

void acceptance() {
    const int numEvents = 10000;

    // Seed for random number generator
    unsigned int seed = 42;
    TRandom3 randGen(seed);

    // Histogram to store generated values
    TH1F *hist = new TH1F("hist", "Generated Gaussian", 100, -5, 5);

    // Generate Gaussian random variables and fill histogram
    for (int i = 0; i < numEvents; ++i) {
        double value = generateGaussian(randGen);
        hist->Fill(value);
    }

    // Plot the histogram
    TCanvas *canvas = new TCanvas("canvas", "Gaussian Distribution", 800, 600);
    hist->Draw();
    canvas->SaveAs("gaussian_distribution.png");

    return 0;
}
