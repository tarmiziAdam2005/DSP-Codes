#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

//Tarmizi Adam 11/6/2015. Simple program to generate a sine function.
// Input: --
// Output: csv file of sine function values.

using namespace std;

vector<double>generateSine();

const double pi = 3.1415923;

int main()
{
    ofstream s("Sine.csv");

    vector<double>compExp;

    compExp = generateSine();

    vector<double>::iterator it;

    for(it = compExp.begin(); it<compExp.end(); it++)
    {
        s << *it << endl;
    }

    cout << "Check output file..." << endl;

    return 0;
}

vector<double>generateSine()
{
    int N = 10; // One period has N samples
    double value;
    double omega =2*pi/N;
    vector<double> sin;
    const int period = 11;
    //double f1 = 10.5;

    for(int i = 0; i < period; i++)
    {
        for (int n = 0; n<N; n++)
        {
            value = std::cos(omega*n); //+ std::sin(omega*n);
            sin.push_back(value); // store our signal values.
        }
    }

    return sin;
}

