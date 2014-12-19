
// Created: 24/11/2012
// Updated/revisited: 19/12/2014
// function to generate random signal between a certain range.

#include <iostream>
#include <cstdlib> // random number generator in cstdlib
#include <ctime>
#include <vector>  // for use in vector.
#include <fstream> // for the use of 'fstream'to output file to csv

using namespace std; // using standard input output

//======Function declaration===================
float randomSignals(int min, int max); // Function to create a discrete signal with amplitude between min and max value.
void outputResult(const char* fileName, const vector<float> &signal); // Function to output the created discrete signal to a file
                                                                     // arguments are: fileName pointer, reference to our signal vector array.
//======End of Function declaration============

int main()
{
    int x, y;
    int N;

    vector<float> signal; // create a vector (standard template) called signal. values of our random signal
                          // will be stored in this vector array.
    srand(time(NULL));

    cout << "Enter minimum range(may take negative values):";
    cin >> x;

    cout << endl;

    cout << "Enter maximum range:";
    cin >>y;

    cout << endl;

    cout << "Enter the lenght of the signal:";
    cin >> N;

    for (size_t i = 0; i < N; i++)
    {
        signal.push_back(randomSignals(x,y)); // storing random samples of our Discrete Signal into
                                             // the vector array "signal".
    }

    outputResult("Discrete_Signal.csv", signal); // save the random signal to an output file

    return 0;
}

// ===================Function bodies====================

float randomSignals(int min, int max)
{
    float randomSample;

    randomSample = ((float(rand())/float(RAND_MAX))*(max - min)) + min; // Create the random signal between range min and max

    return randomSample;
}

void outputResult(const char* fileName, const vector<float>& signal)
{
    ofstream outFile(fileName);

    for(size_t i =0; i < signal.size(); i++)
    {
       outFile << signal[i] << endl; // Output the random signal to a file
    }

}






