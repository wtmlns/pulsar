#include "Random1.h"
#include <iostream>
#include <cmath>
using namespace std;

double SimpleMonteCarlo1(double Expiry,
                        double Strike,
                        double Spot,
                        double Vol,
                        double r,
                        unsigned long NumberOfPaths)
{
    double variance = Vol*Vol*Expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5*variance;
    double movedSpot = Spot*exp(r*Expiry +itoCorrection);
    double thisSpot;
    double runningSum=0;

    for (unsigned long i=0; i < NumberOfPaths; i++)
    {
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot = movedSpot*exp(rootVariance*thisGaussian);
        double thisPayoff = thisSpot - Strike;
        thisPayoff = thisPayoff >0 ? thisPayoff : 0;
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r*Expiry);
    return mean;
}

int main()
{
    // Preset values
    double Expiry = 1.0;        // 1 year
    double Strike = 100.0;      // Strike price of $100
    double Spot = 100.0;        // Current price of $100
    double Vol = 0.2;           // 20% volatility
    double r = 0.05;            // 5% interest rate
    unsigned long NumberOfPaths = 100000;  // Number of simulations

    cout << "\nUsing the following values:" << endl;
    cout << "Expiry: " << Expiry << " years" << endl;
    cout << "Strike: $" << Strike << endl;
    cout << "Spot: $" << Spot << endl;
    cout << "Volatility: " << Vol*100 << "%" << endl;
    cout << "Interest Rate: " << r*100 << "%" << endl;
    cout << "Number of Paths: " << NumberOfPaths << endl;

    double result = SimpleMonteCarlo1(Expiry,
                                    Strike,
                                    Spot,
                                    Vol,
                                    r,
                                    NumberOfPaths);
    
    cout << "\nThe calculated option price is: $" << result << "\n";
    
    // Pause to see results
    cout << "\nPress any key and Enter to exit";
    char tmp;
    cin >> tmp;

    return 0;
}