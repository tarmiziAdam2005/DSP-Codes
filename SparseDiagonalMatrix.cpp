#include<iostream>
#include <opencv2/core/core.hpp>

//Created on 8/4/2015 by Tarmizi Adam. This simple snippet creates
//an m-by-n sparse matrix by taking the columns of e (Mat e) and placing them along the diagonals of D (Mat D).

// Dependencies: OpenCv for Mat sturcture

using namespace std;
using namespace cv;

int main()
{
    int N = 15;
    Mat D = Mat::zeros(N-2,N,CV_32FC1);
    float val = 0.0;

    Mat e = (Mat_<float>(1,3) << 1,-2,1);

    cout << D << endl;
    cout << endl;
    //cout << e << endl;

    for(int i = 0; i < D.rows; i++)
    {
        for(int j = 0; j < e.cols; j++)
        {
            val = e.at<float>(0,j);
            cout << "D(" << i <<","<< j <<") = " << val << " e(" << 0 <<"," << j <<")" << endl;
            D.at<float>(i,i+j) = val; // Put along the diagonal of matrix D. Note the index.
        }

    }

    cout << D << endl; // Print out our new diagonal sparse matrix

    return 0;
}
