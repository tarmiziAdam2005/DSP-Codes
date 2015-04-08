#include<iostream>
#include<fstream>
#include <opencv2/core/core.hpp>

//Created on 8/4/2015 by Tarmizi Adam. This is a simple example of weighted regularization
// for signal smoothing. This code is a C++ (OpenCV) conversion from Prov Ivan Selesnic MATLAB code available at:

// http://eeweb.poly.edu/iselesni/lecture_notes/least_squares/index.html

// For a nice introductory tutorial on weighted regularization, refer to Prof Ivan Selesenic notes.
// available at the same link as above.

// Dependencies: OpenCv for Mat sturcture and matrix manipulation.

using namespace std;
using namespace cv;

int main()
{
    ifstream fl("data.txt"); // Noisy sine wave
    ofstream sm("smoothed.txt"); // Output smoothed signal

    float val = 0.0;
    float dataVal = 0.0;

    Mat data;
    Mat e = (Mat_<float>(1,3) << 1,-2,1); // Coefficients of a second order derivative

    // Some checking...
    if(!fl)
    {
        cout << "Could not read data file !. Exiting..." << endl;
        return 1;
    }

    // Read our noisy data into a matrix
    while(fl >> dataVal)
    {
        data.push_back(dataVal);
    }

    transpose(data,data); // Transpose.

    Mat y;
    data.copyTo(y);

    int N = data.cols;
    Mat D = Mat::zeros(N-2,N,CV_32FC1);

    //Creating a band-diagonal matrix.(second order derivative matrix)
    for(int i = 0; i < D.rows; i++)
    {
        for(int j = 0; j < e.cols; j++)
        {
            val = e.at<float>(0,j);
            D.at<float>(i,i+j) = val; // Put along the diagonal of matrix D. Note the index.
        }
    }

    float lambda = 50; // lambda
    Mat D_t; // D transpose
    Mat I = Mat::eye(N,N,CV_32FC1); // Identitity matrix N by N;

    transpose(D,D_t);

    // These parts solves the weighted regularization for
    // min_x ||y - x||^2 + lambda||Dx||^2 -----------------(1)
    // The signal x minimizing (2) is:
    // x = (I + lambda*D_t*D)^-1*y -------------------------(2)

    Mat F = I + lambda*D_t*D; // (I + lambda*D_t*D)

    invert(F,F,DECOMP_LU); //(I + lambda*D_t*D)^-1. Inverse of F

    Mat x(F.cols,1,0.0); // output x

    transpose(y,y);

    x = F*y; // Overall of equation (2)

    //Output our smoothed signal to .txt file
    // Try plotting the output signal x using some plotting function
    for(int j = 0; j < x.rows; j++)
    {
        sm << x.at<float>(j) << endl;
    }

    cout << "Done smoothing the signal. Check output file..." << endl;
    return 0;
}
