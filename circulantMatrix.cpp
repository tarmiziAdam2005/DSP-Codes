#include<iostream>
#include <opencv2/core/core.hpp>

// Created by Tarmizi Adam on 15/4/2015. This simple program creates an M x N circulant matrix. It is a special
// case of a toeplitz matrix. Given an input vector A, we take N first elements in A as the first row of the
// circulant matrix and shift by as we move from each row of the circulant matrix.
// Input: A (a 1 x L element vector)
// Output: circ ( a L x N matrix)

// E.g.   Given A = {1,2,2,1,5,6,8,9,10,4} to the function we get:

//        circ = {{1,2,2,1},
//                {5,1,2,2},
//                {6,5,1,2},
//                {8,6,5,1},
//                {9,8,6,5},
//                {10,9,8,6}}

// Dependencies: OpenCv for Mat structure. Try converting this to 2D array or Vector
// to get rid of this dependency.

using namespace std;
using namespace cv;

Mat circulantMat(Mat &A, int N);

int main()
{

    Mat data;
    Mat A = (Mat_<float>(1,10) << 1,2,2,1,5,6,8,9,10,4); // Test signal to transform into circulant matrix

    cout << circulantMat(A,4) << endl;

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
