#include<iostream>
#include<fstream>
#include <opencv2/core/core.hpp>

// Created by Tarmizi Adam on 17/4/15. This simple program demostrate Linear prediction to predict future samples of
// a signal. This is a Re-conversion from the MATLAB code provided by the tutorial at
//     http://eeweb.poly.edu/iselesni/lecture_notes/least_squares/index.html

// Input: A signal with the length of 100.
// Output: predicted (future) samples with the length of 100.

// Dependencies: OpenCV for Matrix manipulation.

using namespace std;
using namespace cv;

Mat circulantMat(Mat &A, int N);

int main()
{
    ifstream fl("dataLP.txt");
    ofstream pr("predictedSample.txt");
    float dataVal = 0.0;
    Mat data;

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

    Mat y;
    data.copyTo(y);
    transpose(y,y);

    int N = 4; // Number of LPC coefficients to extract...
    int L = 100; // Number of samples to predict....

    Mat H = circulantMat(y,N);
    Mat b = Mat::zeros(1,y.cols-N,CV_32FC1); // Mat b (1 x 96)

    float val = 0.0;
    for(int i = 0; i < y.cols-N; i++)
    {
        val = y.at<float>(i+N) ;
        b.at<float>(i) = val; // Copy values from y[N+1] to end into Mat b.
        val = 0.0;
    }

    Mat H_t;        // H^t (H transpose)
    Mat b_t;        // b^t (b transpose)
    Mat H_tH;       // H^t * H
    Mat H_tH_inv;   // (H^t * H)^-1
    Mat H_tb;       // H^t * b
    Mat a;          // Matrix to store LPC coefficients (a);

    transpose(H,H_t); // Transpose are done to make the row and
    transpose(b,b_t); // columns the same, for matrix multiplication processes.

    H_tH = H_t*H;
    H_tb = H_t*b_t;

    invert(H_tH,H_tH_inv,DECOMP_LU); // Computing inverse (H^t * H)^-1

    a = H_tH_inv*H_tb;

    /*cout << "Size of H_tH_inv: " << H_tH_inv.size() << endl;
    cout << "Size of H_tH: " << H_tH.size() << endl;
    cout << "Size of H_tb: " << H_tb.size() << endl;
    cout << "Size of H_t: " << H_t.size() << endl;
    cout << "Size of H: " << H.size() << endl;
    cout << "Size of b: " << b.size() << endl;*/

    Mat g = Mat::zeros(1,y.cols + L, CV_32FC1);

    cout << g.size() << endl;

    for(int i = 0; i < g.cols-L; i++)
    {
        g.at<float>(i) = y.at<float>(i);
    }

    // Do the predition
    // This is y(n) =  a_1*y(n-1) + a_2*y(n-2) + a_3*y(n-3) + a_3*y(n-4)
    for(int i = L ; i < g.cols; i++)
    {
       g.at<float>(i) = a.at<float>(0)*g.at<float>(i-1) + a.at<float>(1)*g.at<float>(i-2) + a.at<float>(2)*g.at<float>(i-3) + a.at<float>(3)*g.at<float>(i-4);
       pr << g.at<float>(i) << endl;
    }

    transpose(g,g);
    cout << g << endl;

    return 0;

}

Mat circulantMat(Mat &A, int N)
{
    float val = 0.0;
    Mat circ = Mat::zeros(A.cols-N,N,CV_32FC1); // Declare our circulant matrix
                                               // Number of rows is input vector A rows - N
    int rowCirc = 0.0; //row index of the circular matrix
    int colCirc = 0.0; // column index of the circular matrix

    for(int l = N-1; l >= 0; l--) //Start from index N-1 of A and count downwards.
    {
        rowCirc = 0.0; // start with index 0

        for(int i = l; i < circ.rows+l; i++) // the element of the first row of our circular matrix is shifted
        {
            val = A.at<float>(i);
            circ.at<float>(rowCirc,colCirc)= val;
            rowCirc++; // increment the row index of circular matrix
        }

        colCirc++;
        val = 0.0;
    }

    return circ;
}


