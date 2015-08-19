#ifndef GAUSSIEDL_H
#define GAUSSIEDL_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>

//Created by Tarmizi Adam on 10/08/2015.
// This program applies the Gauss-Siedel iterative method to solve the linear system Ax = b
// This program is a slight modification in structure, adapted from the book:

//          Computing for Numerical Methods Using Visual C++ by Shaharuddin Salleh, Albert Y Zomaya
//          and Sakhinah Abu Bakar.

// Section 5.5: Gauss-Siedel Method

// Notes: The Gauss-Siedel method solves Ax = b provided that the matrix A is diagonally dominant. In this program
// A is checked in the constructor GausSied() for diagonally dominance. If A is not diagonally dominant, the program
// aborts. Future works to improve this code is to be able to perform the method where A is not diagonally dominant.
// This could be done by writing code to re-order A to be diagonally dominant.

// Dependencies: None

using std::cout;
using std::endl;
using std::vector;


struct GausSied
{
    int nrows;

    vector< vector<double> > tmpA;
    vector<double> xOld;

    GausSied(vector< vector<double> > &A);
    void solve(vector<double> &x, vector<double> &b);

};

GausSied::GausSied(vector< vector<double> > &A):nrows(A.size()),tmpA(A),xOld(nrows,0.0)
{
    int i,j;

    double sum = 0.0;


    // Check if matrix A is diagonal dominant
    for(i = 0; i < nrows; i++)
    {
        sum = 0.0;

        for(j = 0; j < nrows; j++)
        {
            if(i != j)
            {
                sum += fabs(A[i][j]);
            }

            if(fabs(A[i][i]) <= sum)
            {
                cout << "Unsuccessfull, Matrix A is not diagonally dominant ! Aborting...";
                exit(EXIT_FAILURE);
            }
        }
    }

}

void GausSied::solve(vector<double> &x, vector<double> &b)
{
    int i,j,k;
    int its = 25;

    double error = 0.0;
    double sum = 0.0;

    if(b.size() != nrows || x.size() !=nrows)
    {
        cout << "GausSied::solve bad sizes";
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < its; i++)
    {
        error = 0.0;

        // print out iteration
        //cout << "i = " << i << ": ";

        for(j = 0; j < nrows; j++)
        {
          sum = 0.0;
          for(k = 0; k < nrows; k++)
          {
              if(j != k)
              {
                  sum += tmpA[j][k]*x[k];
              }
          }

          xOld[j] = x[j];
          x[j] = (b[j]-sum)/tmpA[j][j];
          // print out value of x at each iteration
          //cout << x[j] << " ";
          error = ((error > fabs(x[j]-xOld[j])) ? error: fabs(x[j]-xOld[j]));

        }

        // If want, print out the error
        //cout << "Error: " << error << endl;
    }

    xOld.clear();
}




#endif // GAUSSIEDL_H
