#include <iostream>
#include <math.h>
#include <fstream>

// 18/7/2013
// This code is an example of Discrete-Time Sinusoidal Signals
//It plots a Cosine Function
//As we know, a discrete-time sinusoidal signal can be expressed as

//==============> x(n) = A*cos(omega*n*f) for n from plus to minus infinity <=================
//==============> where, omega = 2*PI/N where f is the frequency of the sinusoid  <=================
//==============> and A is the amplitude of the sinusoid                          <=================                                  <=================
//==============> Thus we have, x(n) = A*cos(2*PI/N*f*n)                    <=================

using namespace std;

void drawCosine(int N, double omega, double PI, double value, double frequency, double amplitude);

int main()
{
    int N;
    double omega, PI, value, frequency, amplitude;

    cout <<"Enter the sinusoid frequency: ";
    cin >> frequency;

    cout << endl;

    cout << "Enter number of samples (N): ";
    cin >> N;

    cout << endl;

    cout << "Enter the sinusoid amplitude (A):";
    cin >> amplitude;

    cout << "Table of sine function\n\n";

    drawCosine(N,omega, PI, value, frequency, amplitude);

    return 0;
}


void drawCosine(int N, double omega, double PI, double value, double frequency, double amplitude)
{
    ofstream myFile;
    myFile.open("cosine.txt");

    PI = M_PI;

    cout << "Value of PI: "<<PI<< endl;
    cout << "Sample (n) \t Cosine\n";
    myFile << "Sample (n) \t Cosine\n";

    omega =2*PI/N;

    for (int n = 0; n<N; n++)
    {
        value = amplitude*cos(omega*frequency*n);
        cout << n <<"\t"<<"\t"<< value << endl;

        //Display to the output text file
        myFile << n <<"\t"<<"\t" << value << endl;
    }
}
