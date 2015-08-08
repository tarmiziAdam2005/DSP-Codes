#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<cmath>

#include"LU.h"

//Created by Tarmizi Adam on 19/7/2015.
// Update 1: 9/8/2015 
//This program implements the Total Variation Denoising (TVD) using
// Maximization-Minimization (MM) for 1D signals. The codes herein are developed based on the authors understanding/study of
// the notes [1] and Matlab program [2] by Prof Ivan Selesnick.

//  [1] Total Variation Denoising (an MM algorithm)
//  [2] http://eeweb.poly.edu/iselesni/lecture_notes/TVDmm/

// This is a pure C++ version of TVD-MM without depending on any non standard C++ libraries. The function
// for computing matrix inverse is adapted from the book:

//                  Numerical Recipes: The art of scientific computing by Press, Teukolsky, Vetterling
//                  and Flannery.

// Section 2.3: LU Decomposition and its Application

// Input: y, a noisy 1D signal
// Output: denoised version of y (outputed to a ".txt" file)

// Notes: 1) As the program outputs the denoised signal to a ".txt" file, plot the results
//           using a plotting utility i.e. excel or Matlab.
//        2) The program is quite slow if the signal size is large. This is the result of the
//           system to be solved being increased. Future works include, converting this code
//           to store sparse banded systems or matrices.
//        3) To run the code, Create a C++ project with main.cpp and LU.h

// The author is trying his best to produce error free code, however we do not guarantee that this code
// is 100% error free. Any bugs, errors or suggestions mail to: tarmizi_adam2005@yahoo.com

using namespace std;

vector<double> diff1D(vector<double> &y);
vector< vector<double> > bandedMat(vector<double> &e,int N);
void matrixSize(vector< vector<double> > &A);
void absVal(vector<double> &i);
vector< vector<double> > sparseDiag(vector<double> &Diag);
vector< vector<double> > addMatrix(vector< vector<double> > &A, vector< vector<double> > &B);
vector< vector<double> > scalarMultMatrix(double regParam, vector< vector<double> > &A);
void matrixMuliply(vector< vector<double> > &A, vector< vector<double> > &B);
vector<double> matrixVectMuliply(vector<double>&A, vector< vector<double> > &B);
vector<double> vecSubtract(vector<double> &a, vector<double> &b);
vector<double> DT(vector<double> &a);
template<class T> void printArray2D(vector< vector<T> > &I); // Function to show our created matrix

int main()
{
    ifstream in("RectDataNoisy.txt");

    vector<double> y;
    vector<double> x;
    vector<double> Dx;
    vector< vector<double> > DDT;
    vector<double> e = {-1,2,-1}; // first order difference

    double vals =0.0;
    int nIt =10;
    int k =0;

    if(!in)
    {
        cout << "No such input file" << endl;
        return 1;
    }

    while(in >> vals)
    {
        y.push_back(vals);
    }

    cout << "Size of input signal: " << y.size() << endl;

    int N = y.size();
    DDT = bandedMat(e,N);

    cout << "Size of DDT: ";
    matrixSize(DDT);
    cout << endl;

    x = y; //-----------
           //           |----> Initialization of x, and Dx
    Dx = diff1D(x);//---
    
    double regParam = 5.0;
    vector< vector<double> > F;
    vector< vector<double> > Lambda;
    vector<double> Dy;
    vector<double> FDy;
    vector<double>y_minus_DTFDy;
    vector<double> Dt;

    do
    {
        absVal(Dx);

        Lambda = sparseDiag(Dx);
        F = scalarMultMatrix(regParam,Lambda); //F = (1/regParameter)*Lambda
        F = addMatrix(F,DDT); // F + DDT
        Dy = diff1D(y);            // Dy

        LUdcmp lu(F);
        lu.inverse(F); // F^-1

        FDy = matrixVectMuliply(Dy,F); //(F^-1)Dy
        Dt = DT(FDy); // DT(F^-1)Dy

        x = vecSubtract(y,Dt); // y - DT(F^-1)Dy

        Dx = diff1D(x); // update value of Dx

        Dx.push_back(0); // zero pad a sample, because diff1D() decreases signal (x) sample by one.

        k++;

        cout << "Iteration: " << k << endl;
    }while (k != nIt);

    ofstream f("result.txt");

    cout << Dx.size() << endl;
    for(int i =0; i < x.size(); i++)
    {
        f << x[i] << endl;
    }

    return 0;
}

vector<double> diff1D(vector<double> &y)
{
    vector<double> Y;
    double diff =0.0;

    for(int i =0; i < y.size()-1; i++)
    {
        diff = y[i+1]-y[i];
        Y.push_back(diff);
        diff = 0.0;
    }

    return Y;
}

void matrixSize(vector< vector<double> > &A)
{
    cout << "Matrix size: " << "[" << A.size() << "x" << A[0].size() << "]" << endl;
}

vector< vector<double> > bandedMat(vector<double> &e,int N)
{
    // Do some checking, Only tridiagonals are allowed.
    if(e.size()>3)
    {
        cout << "Only tridiagonals are allowed. Input vector to function must be only 3 elements." << endl;
        exit(EXIT_FAILURE);
    }

    vector< vector<double> > D(N-1, vector<double>(N-1,0.0));

    for(size_t i = 0; i < D.size(); i++)
    {
        for(size_t j = 0; j < D.size(); j++)
        {
            if(i == j)
            {
                D[i][j] = e[1]; // put value of e[1] as the main diagonal of D
            }
        }
    }

    int j =0; // index
    int k =0; // index

    for(size_t i =0; i < D.size()-1;i++)
    {
        D[i][j+1] = e[0]; // put value e[0] as the upper diagonal
        j = j+1;
    }

    for(size_t i =0; i < D.size()-1;i++)
    {
        D[i+1][k] = e[2]; // put value of e[2] as the lower diagonal
        k = k+1;
    }

    return D;
}

void absVal(vector<double> &sig)
{
    for(size_t i =0; i < sig.size(); i++)
    {
        sig[i] = std::abs(sig[i]);
    }
}

vector< vector<double> > sparseDiag(vector<double> &Diag)
{
    vector< vector<double> > D(Diag.size(), vector<double>(Diag.size(),0.0));

    for(size_t i = 0; i < D.size(); i++)
    {
        for(size_t j = 0; j < D.size(); j++)
        {
            if(i == j)
            {
                D[i][j] = Diag[j]; // put value of e[1] as the main diagonal of D
            }
        }
    }

    return D;
}

vector< vector<double> > addMatrix(vector< vector<double> > &A, vector< vector<double> > &B)
{
    vector< vector<double> > C(A.size(), vector<double>(A[0].size(),0.0));

    if(A.size() != B.size() || A[0].size()!= B[0].size())
    {
        cout << "Error, Matrix dimension are not the same" << endl;
        exit(EXIT_FAILURE);
    }

    for(int i =0; i < A.size(); i++)
    {
        for(int j =0; j < A[0].size(); j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

vector< vector<double> > scalarMultMatrix(double regParam, vector< vector<double> > &A)
{
    vector< vector<double> > B(A.size(),vector<double>(A[0].size(),0.0));
    for(int i =0; i < A.size(); i++)
    {
        for(int j =0; j< A[0].size(); j++)
        {
            B[i][j] = (2.0/regParam)*A[i][j];
        }
    }

    return B;
}

void matrixMuliply(vector< vector<double> > &A, vector< vector<double> > &B)
{
    vector< vector<double> > Y(A.size(),vector<double>(B[0].size(),0.0)); // We must initialize our resultant matrix to 0
    int n = A.size();
    int m = A[0].size();
    int p = B[0].size();

    // Here we do some checking.
    // If the Column of A is not the same as the Row of B
    // multiplication cannot be done !
    if(A[0].size() != B.size())
    {
        cout << "Matrix dimension are not the same !" << endl;
        return;
    }

    // Matrix multiplication

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < p; j++)
        {
            double sum = 0;

            for(int k = 0; k < m; k++)
            {
                sum = sum + A[i][k]*B[k][j];
            }

            Y[i][j] = sum;
            cout << Y[i][j] <<",";
        }
        cout << endl;
    }
}

vector<double> matrixVectMuliply(vector<double>&A, vector< vector<double> > &B)
{
    vector<double> Y(A.size(),0.0); // We must initialize our resultant matrix to 0
    int n = A.size();
    int m = A.size();
    int p = B[0].size();

    // Here we do some checking.
    // If the Column of A is not the same as the Row of B
    // multiplication cannot be done !
    if(A.size() != B.size())
    {
        cout << "Matrix dimension are not the same !" << endl;
        exit(EXIT_FAILURE);
    }

    for(int j = 0; j < p; j++)
    {
        double sum = 0;

        for(int k = 0; k < m; k++)
        {
            sum = sum + B[j][k]*A[k];
        }

        Y[j] = sum;
    }

    return Y;
}

vector<double> vecSubtract(vector<double> &a, vector<double> &b)
{
    vector<double> C(a.size()-1,0.0);

    if(a.size() != b.size())
    {
        cout << "Error, vector dimension are not the same" << endl;
        exit(EXIT_FAILURE);
    }

    for(int i =0; i < a.size()-1; i++)
    {
            C[i] = a[i] - b[i];
    }

    return C;
}

vector<double> DT(vector<double> &a)
{
    vector<double> tmp;
    double val = 0.0;

    tmp.push_back(a[0]);

    for(int i = 0; i < a.size(); i++)
    {
        val = -1*(a[i+1]-a[i]);
        tmp.push_back(val);
    }

    return tmp;
}

template<class T> void printArray2D(vector< vector<T> > &I)
{
    // This is how we iterate using an iterator for 2d vectors
    typename vector< vector<T> >::iterator row; // Iterator for row of 2d vector
    typename vector<T>::iterator col; // Iterator for columns of 2d vector

    cout << "Matrix size: " << "[" << I.size() << "x" << I[0].size() << "]" << endl; // print the row and columns

    for(row = I.begin(); row !=I.end(); row++)
    {
        for(col = row->begin(); col != row->end(); col++)
        {
            cout << *col << ","; // print the value contained in each row of our 2d vector.
        }

        cout << endl;
    }
}



