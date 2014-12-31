
// Created by Tarmizi Adam, 30/12/2014, Updated 31/12/2014

// This simple program demostrates a simple moving average filter.

// Filter input: Noisy sine wave
// Filter output: A filtered sine wave

// This small program also creates two output file One is the noisy sine signal, second is the filtered sine signal.
// The values in the text files can then be used to plot in a plotting software to see the results...

// Points of interest: If we increase the n-points of the moving average filter,
// the filtering will become better. Try out 3 10, etc points and see the results (the variabl size_t N).

#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>

#include<cmath>
#include <cstdlib> // random number generator in cstdlib
#include <ctime>

using namespace std;

vector<double>generateSine(); // Function to generate noisy sine wave
vector<double>movingAverageFilter(vector<double> &sine, size_t N); // function to filter our noisy sine wave

const double pi = 3.1415923;

int main()
{
    ofstream s("SineData.txt");
    ofstream f("FilteredData.txt");

    vector<double> sine;
    vector<double>filtered;
    size_t N; // number of n-points to average out.

    srand(time(NULL));

    sine = generateSine(); // generate noisy sine wave signal

    vector<double>::iterator it;

    for(it = sine.begin(); it < sine.end(); it++)
    {
        s << *it << endl;
    }

    cout << "How many n-points ? (+ve value only): ";
    cin >> N;

    filtered = movingAverageFilter(sine, N); // Filter the signal !!

    for(it = filtered.begin(); it < filtered.end(); it++)
    {
        f << *it << endl;
    }

    return 0;
}

vector<double>generateSine()
{
    int N = 256;
    double value;
    double omega =2*pi/N;
    vector<double> sin;
    const int period = 3;

    double randomNoise;
    int max = 1.00;
    int min = -1.00;

    for(int i = 0; i < period; i++)
    {
        for (int n = 0; n<N; n++)
        {
            randomNoise = ((double(rand())/double(RAND_MAX))*(max - min)) + min; // generate random sample value between -1 and 1
            value = std::sin(omega*n) + randomNoise; // Add noise to the sine wave
            sin.push_back(value); // store our signal values.
        }
    }

    return sin;
}

vector<double>movingAverageFilter(vector<double> &sine, size_t N)
{
    vector<double>filteredSine((int)N/2+sine.size(),0.0); // Initialize our vector to zeros. the (int)N/2 size of the original
                                                   // sine signal is just to padd the filtered signal when the
                                                  // filtering goes out of bounds.

    // Here we start the n-point moving average filter.
    for(size_t n  =0 ; n < sine.size(); n++)
    {

        double sumPoints = 0;

        for(size_t k  =0; k < N; k++)
        {
            sumPoints += sine[n+k]; // accumulate the N number of points to average
        }

        filteredSine[n] = (double)(sumPoints)/N;

        // Try this one below also. If so, delete the loop with the k index.
        //filteredSine[n] = (double)1/8*(sine[n]+sine[n+1]+sine[n+2]+sine[n+3]+sine[n+4]+sine[n+5]+ sine[n+6]+sine[n+7]+ sine[n+8]);
    }

    return filteredSine;
}







