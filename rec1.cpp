// Created by Tarmizi Adam, 22/1/2015
// Updated: 19/7/15

// This simple program Creates a rectangular wave.

// program output: Rectangular pulse (".txt") file.

#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>

using namespace std;

vector<int>generateRectFunc(size_t N);

int main()
{
    ofstream s("RectData.txt");
    vector<int> rect;
    vector<int>::iterator it;
    int N = 10; // Play around with this

    rect = generateRectFunc(N); // generate noisy sine wave signal

    for(it = rect.begin(); it < rect.end(); it++)
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
