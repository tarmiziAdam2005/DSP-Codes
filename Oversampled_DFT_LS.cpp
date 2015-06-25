#include<iostream>
#include<fstream>
#include<complex>
#include <opencv2/core/core.hpp>
#include <vector>

// Created by Tarmizi Adam 24/6/2015. This is a demo program to demostrate how the Oversampled DFT Spectrum
// of a signal can be obtained using Least Squares method. Note that the spectrum will exhibit leakage.
// The Least Squares method is obtained using the conjuage transpose A^T.

// The Code here is a port from Prof Ivan Selesnick Matlab Code that can be obtained at the following link:
//http://eeweb.poly.edu/iselesni/teaching/lecture_notes/sparsity_intro/index.html
// This code is in no where original from me. Porting to C++ is just for me to understand the process.

// Input: Data/Signal (in this demo a sine wave)
// Output: DFT spectrum

// Dependencies: OpenCV, for Matrix manipulation and some Matrix related computations.

using namespace std;
using namespace cv;

Mat AT(Mat &data, int M,int N); // creates c = A^Ty (A^T is conjugate transpose)
Mat A(Mat &c, int M, int N); // create y = Ac
void errorEstimate(Mat &data, Mat &y);

int main()
{
    ifstream fl("sine.txt");
    ofstream out2("LS_Spectrum.csv");
    float dataVal = 0.0;
    int M = 100;
    int N = 256;

    Mat data;

    // Some checking...
    if(!fl)
    {
        cout << "Could not read data file !. Exiting..." << endl;
        return 1;
    }

    // Read our data into a matrix
    while(fl >> dataVal)
    {
        data.push_back(dataVal);
    }

    cout << data.size() << endl;

    Mat outDFT;

    dft(data,outDFT,DFT_REAL_OUTPUT); // Compute the DFT of our data

    // Oversampled DFT using the Least Squares. Least squares solution obtained by
    // Conjugate transpose.
    Mat c = (float)1/N*AT(data,M,N);

    for(int i = 0; i < outDFT.rows; i++)
    {
        out2 << abs(c.at<float>(i)) << "," << endl;
    }

    Mat y2 = A(c,M,N);

    cout << y2.size() << endl;

    errorEstimate(data, y2);

    return 0;
}

Mat AT(Mat &data, int M, int N)
{
    Mat dataPad = Mat::zeros(N,1,CV_32FC1);

    //****************Zero Padding*********************
    for(int i = 0; i < data.rows; i++)
    {
        dataPad.at<float>(i) = data.at<float>(i);
    }
    //****************End zero Padding******************

    Mat planes[] = {Mat_<float>(dataPad),Mat::zeros(dataPad.size(),CV_32FC1)}; // Complex values are stored in a separate channel
    Mat complexI;
    Mat c;

    merge(planes,2,complexI); // Merge the real and complex channels;
    dft(complexI,c,DFT_COMPLEX_OUTPUT);

    complexI.release();
    return c;

}

Mat A(Mat &c, int M, int N)
{
    Mat v;
    Mat y = Mat::zeros(M,1,CV_32FC1);;
    dft(c,v,DFT_INVERSE | DFT_REAL_OUTPUT);

    for(int i = 0; i < M; i++)
    {
        y.at<float>(i) = v.at<float>(i);
    }

    return y;
}

void errorEstimate(Mat &data, Mat &y)
{
    Mat reconErr = data-y;
    double min;
    double max;

    minMaxLoc(reconErr,&min,&max);

    cout << "Maximum error:" << max << endl;
}

