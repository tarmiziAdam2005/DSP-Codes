#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>

//Tarmizi Adam 14/6/2015. Simple function to generate an overcomplete cosine dictionary.
// Overcomplete dictionary are use mainly in sparse signal processing
// Input:
//         N: Number of row of dictionary
//         L: number of column of dictionary

// Output: Returns a N x L overcomplete Cosine dictionary.
// Dependencies: This function depends on OpenCV

using namespace std;
using namespace cv;

void OverCompleteCosDict(int N,int L);

const double pi = 3.1415923;

int main()
{

    OverCompleteCosDict(64,64);

    return 0;
}

void OverCompleteCosDict(int N,int L)
{
    ofstream fl("odctDict.csv");
    float value =0.0;
    Mat D = Mat::zeros(N,L,CV_32FC1);

    for(int i = 0; i < D.rows; i++)
    {
        D.at<float>(i,0) = 1/sqrt(N); // first column of cosine dictionary. DC value
    }

    // Generate cosine atoms for each column
    for(float i = 0; i < L; i++)
    {
        for (int n = 1; n<N; n++)
        {
            value = std::cos(pi*n*(i)/L);
            D.at<float>(i,n) = value;
        }
    }

    // Each column of the dictionary (execpt the first) must be normilize to unit L2 norm
    // Normalizations are done column wise
    for(int i = 1; i < D.cols; i++)
    {
          D.col(i) = D.col(i)-mean(D.col(i));
          D.col(i) = D.col(i)/norm(D.col(i),NORM_L2);
    }

    // Output to file
    for(float i = 0; i < D.rows; i++)
    {
        for (int j = 0; j<D.cols; j++)
        {

            fl << D.at<float>(i,j) << ",";
        }

        fl << endl;
    }

    cout << "Check output file..." << endl;
}

