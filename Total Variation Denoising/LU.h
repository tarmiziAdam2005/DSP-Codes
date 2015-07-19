#ifndef LU_H
#define LU_H

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<cstdlib>
#include<cmath>

// 13/7/15 by Tarmizi Adam
// When modeling signal processing problems we can model them as a linear system of the form
//              Ax = b
// where b is the observed signal (i.e, convoluted, noisy signal etc). A is the system that causes the observed
// signal to be convoluted, noisy etc. x is the original signal to be recovered.
// A direct solution to this type of problem is computing the invers of A as
//              x = A^-1*b
// obtaining our desired original signal x. However, finding the inverse of A is often computationaly
// expensive for large matrices. To solve this, we use LU factorization to find the solution x.

// This code is an implementation of LU decomposition method for solving Ax=b. The code is taken almost VERBATIM
// from the book:
//                  Numerical Recipes: The art of scientific computing by Press, Teukolsky, Vetterling
//                  and Flannery.
// Section 2.3: LU Decomposition and its Application

// Include this LU.h with main.cpp for Total Variation denoising program.


using std::cin;
using std::vector;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::endl;

template<class T> void printArray2D(vector< vector<T> > &I);

struct LUdcmp
{
    int n;
    double d;
    vector< vector<double> > lu; // Store the decomposition
    vector<double> indx;

    LUdcmp(vector< vector<double> >  &A);
    void solve(vector<double> &b, vector<double> &x);
    void solve(vector< vector<double> > &B, vector< vector<double> > &X);
    void inverse(vector< vector<double> > &Ainv);

};

LUdcmp::LUdcmp(vector< vector<double> > &A):n(A.size()),lu(A),indx(n)
{
    const double TINY = 1.0e-40;
    double big = 0.0;
    double temp = 0.0;
    int imax;
    vector<double> vv(n,0.0);
    d = 1.0;

    for(int i=0; i<n; i++)
    {
        big = 0.0;

        for(int j=0; j<n; j++)
        {
            if((temp = abs(lu[i][j]))> big)
            {
                big = temp;
            }
        }

        if(big == 0.0)
        {
            throw("Signular matrix in LUdcmp");
        }
        vv[i]=1.0/big;
    }

    for(int k =0; k<n; k++)
    {
        big =0.0;

        for(int i = k; i<n; i++)
        {
            temp = vv[i]*abs(lu[i][k]);
            if(temp > big)
            {
                big = temp;
                imax = i;
            }
        }

        if(k != imax)
        {
            for(int j =0; j<n; j++)
            {
                temp = lu[imax][j];
                lu[imax][j] = lu[k][j];
                lu[k][j] = temp;
            }

            d = -d;
            vv[imax] = vv[k];
        }

        indx[k] = imax;

        if(lu[k][k] == 0.0)
        {
            lu[k][k] = TINY;
        }

        for(int i = k+1; i<n; i++)
        {
           temp = lu[i][k] /= lu[k][k];

           for(int j = k+1; j<n; j++)
           {
               lu[i][j] -= temp*lu[k][j];
           }
        }
    }

}

void LUdcmp::solve(vector<double> &b, vector<double> &x)
{
    int ip =0;
    int ii =0;
    double sum =0.0;
    if(b.size() != n || x.size() !=n)
    {
        throw("LUdcmp::solve bad sizes");
    }

    for(int i =0; i<n; i++)
    {
        x[i] = b[i];
    }

    for(int i = 0; i < n; i++)
    {
      ip = indx[i];
      sum = x[ip];
      x[ip] = x[i];

      if(ii != 0)
      {
          for(int j = ii-1; j<i; j++)
          {
              sum -= lu[i][j]*x[j];
          }
      }
      else if(sum != 0.0)
      {
          ii = i+1;
      }

      x[i]= sum;

    }

    for(int i = n-1; i >= 0; i--)
    {
        sum = x[i];

        for(int j =i+1; j<n; j++)
        {
            sum -= lu[i][j]*x[j];
        }

        x[i]= sum/lu[i][i];
    }
}

void LUdcmp::solve(vector< vector<double> > &B, vector< vector<double> > &X)
{
    if(B.size() != n || B.size() !=n || B[0].size() !=X[0].size())
    {
        throw("LUdcmp::solve bad sizes");
    }

    vector<double> xx(n,0.0);

    for(int j =0; j < n; j++)
    {
        for(int i =0; i < n; i++)
        {
            xx[i] = B[i][j];
        }

        solve(xx,xx);

        for(int i =0; i < n; i++)
        {
            X[i][j] = xx[i];
        }
    }

}

void LUdcmp::inverse(vector< vector<double> > &Ainv)
{
    for(int i =0; i < n; i++)
    {
        for(int j =0; j < n; j++)
        {
            Ainv[i][j] = 0.0;
        }

        Ainv[i][i] = 1.0;
    }

    solve(Ainv,Ainv);

}


/*int main()
{
    const int n = 4;

    vector< vector<double> > A = {{1,3,2,2},
                                    {2,1,0,0},
                                    {2,2,6,8},
                                    {1,3,2,6}};

    vector<double> b = {1,4,8,6};
    vector<double> x(n,0.0);

    LUdcmp alu(A);

    printArray2D(A);
    cout << endl;

    alu.solve(b,x);
    alu.inverse(A);


    /*for(int i =0; i < n; i++)
    {
        cout << x[i] << ",";
    }

    cout << endl;

    printArray2D(A);

    return 0;
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
}*/

#endif // LU_H
