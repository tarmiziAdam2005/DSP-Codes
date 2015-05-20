#include<iostream>
#include<complex> // To use complex conjugation.
#include <opencv2/core/core.hpp>

// Created by Tarmizi Adam on 20/5/2015. Suggestions E-mail to tarmizi_adam2005@yahoo.com

// This is a simple program (Demo, quite messy) how to do complex conjugate of a complex Mat strucutre (Opencv matrix)
// The program generate a sequence of random number between 0 and 1, and compute the DFT of this
// random signal producing a complex array. Then, the complex conjugate of the array is done.
// Input: Complex valued DFT array
// Output: Complex Conjugate of the DFT array

using namespace std;
using namespace cv;

int main()
{

    int N = 64;                             // Size of the test signal
    Mat signal(N,1,CV_32FC1);               // Declare test signal
    Mat mean = Mat::zeros(1,1,CV_32FC1);
    Mat sigma = Mat::ones(1,1,CV_32FC1);

    cv::randn(signal,mean,sigma);           // Generate the random test signal

    Mat transformed(N,1,CV_32FC1);


    dft(signal,transformed,DFT_COMPLEX_OUTPUT); // Compute DFT. Produces a complex valued array.


    Mat_<std::complex<float> > matConj(transformed.rows,1); // Create a complex mat structure

    for(int i =0; i < transformed.rows;i++)
    {
        matConj.at< std::complex<float> >(i) = transformed.at< std::complex<float> >(i); // assign values of transformed
                                                                                        //  to newly created complex mat
    }

    cout << "Complex matrix: " << endl;
    cout << transformed << endl;
    cout << endl;
    cout << endl;

    for(int i =0; i < transformed.rows;i++)
    {
        matConj.at< std::complex<float> >(i) = std::conj( matConj.at< std::complex<float> >(i) ); // do Complex conjugate
    }                                                                                             // to our complex matrix "matConj"

    cout << "Complex conjugate: " << endl;
    cout << matConj << endl;

    return 0;
}
