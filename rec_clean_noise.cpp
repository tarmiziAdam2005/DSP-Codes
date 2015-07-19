// Created by Tarmizi Adam, 22/1/2015
// Update 1: 19/7/2015

// This simple program Creates a rectangular wave. Noisy or clean.
// For the noisy version, uncomment the relevent parts of the code.

// program output: Rectangular pulse (".txt") file.

#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include <cstdlib> // random number generator in cstdlib
#include <ctime>

using namespace std;

vector<int>generateRectFunc(size_t N);
vector<double>generateNoisyRect(size_t N);

int main()
{
    srand(time(NULL));
    ofstream s("RectData.txt");
    vector<int> rect;
    //vector<double>rectNoise;
    vector<int>::iterator it;
    //vector<double>::iterator itNoise; // change iterator depending on clean or noisy signal.
    int N = 16; // Play around with this

    rect = generateRectFunc(N); // generate noisy sine wave signal
    //rectNoise = generateNoisyRect(N);

    /*for(itNoise = rectNoise.begin(); itNoise < rectNoise.end(); itNoise++)
    {
        s << *itNoise << endl;
    }*/

    for(it= rect.begin(); it < rect.end(); it++)
    {
        s << *it << endl;
    }

    return 0;
}

vector<int>generateRectFunc(size_t N)
{
    //size_t N = 10;
    int valOne = 0;
    int valZero = 0;
    vector<int> rec;

    for(size_t i = 0; i < N; i++)
    {
        for(size_t n = 0; n < N/2; n++)
        {
          valOne = 1;
          rec.push_back(valOne);
        }

        for(size_t k = N/2; k < N; k++)
        {
          valZero = 0;
          rec.push_back(valZero);
        }
    }

    return rec;
}

vector<double>generateNoisyRect(size_t N)
{

    //size_t N = 10;
    double valOne = 0;
    double valZero = 0;
    double randomNoise;
    double maxOne = 0.2;
    double minOne = -0.2;

    double maxZero = 0.2;
    double minZero = -0.2;

    vector<double> recNoise;

    for(size_t i = 0; i < N; i++)
    {
        for(size_t n = 0; n < N/2; n++)
        {
          randomNoise = ((double(rand())/double(RAND_MAX))*(maxOne - minOne)) + minOne;
          valOne = 1 + randomNoise;
          recNoise.push_back(valOne);
        }

        for(size_t k = N/2; k < N; k++)
        {
          randomNoise = ((double(rand())/double(RAND_MAX))*(maxZero - minZero)) + minZero;
          valZero = 0 + randomNoise;
          recNoise.push_back(valZero);
        }
    }

    return recNoise;

}
