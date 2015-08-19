#ifndef FUNCBODY_H
#define FUNCBODY_H

#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<fstream>

#include "funcDef.h"

using std::cout;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;

template<class T> void printArray2D(vector< vector<T> > &I)
{
    // This is how we iterate using an iterator for 2d vectors
    typename vector< vector<T> >::iterator row; // Iterator for row of 2d vector
    typename vector<T>::iterator col; // Iterator for columns of 2d vector
    ofstream out("mat.csv");

    cout << "Matrix size: " << "[" << I.size() << "x" << I[0].size() << "]" << endl; // print the row and columns

    for(row = I.begin(); row !=I.end(); row++)
    {
        for(col = row->begin(); col != row->end(); col++)
        {
            //cout << *col << ","; // print the value contained in each row of our 2d vector.
            out << *col << ",";
        }

        //cout << endl;
        out << endl;
    }
}

vector< vector<double> > doubleBandMat(vector<double> &e,int N)
{
    // Do some checking, Only tridiagonals are allowed.
    if(e.size()>2)
    {
        cout << "Only bidiagonal are allowed. Input vector to function must be only 3 elements." << endl;
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

    int k =0; // index


    for(size_t i =0; i < D.size()-1;i++)
    {
        D[i+1][k] = e[0]; // put value of e[2] as the lower diagonal
        k = k+1;
    }

    return D;
}

void diffOperator(vector< vector<double> > &B, vector< vector<double> > &Bt, vector< vector<double> > &BtB,  size_t N)
{
    int n = (int)sqrt(N)+1;
    //int n = (int)N;


    vector<double> e = {-1,1}; // first order difference

    vector< vector<double> > D = doubleBandMat(e,n);
    D[0][0] = 0.0;

    vector< vector<double> > I = eye(D.size());
    //vector< vector<double> > B;
    auto T = kron(I,D);
    auto R = kron(D,I);

    verCatMatrix(B, T);
    verCatMatrix(B,R);

    Bt = transpose(B);



    BtB = matrixMuliply(Bt,B);

    //printArray2D(Bt);

}

vector< vector<double> > eye(size_t N)
{
    vector < vector<double> > identity(N,vector<double>(N,0.0));

    for(size_t row =0; row < N ; row++)
    {
        identity[row][row] = 1.0;
    }

    return identity;

}

vector< vector<double> > kron(vector< vector<double> > &A, vector< vector<double> > &B)
{
    size_t krnProdRow = A.size()*B.size();
    size_t krnProdCol = A[0].size()*B[0].size();
    size_t nRowA = A.size();
    size_t nColA = A[0].size();
    size_t nRowB = B.size();
    size_t nColB = B[0].size();

    vector< vector<double> > krnProd(krnProdRow,vector<double>(krnProdCol,0.0));

    size_t i,j,k,l;
    double valA =0.0;
    double valB = 0.0;

    // Looping for kronecker tensor products of A and B
    // Trace the index of the loops to understand the kronecker tensor product
    for(i = 0; i <nRowA ; i++)
    {
        for(j = 0; j < nColA; j++)
        {
            valA = A[i][j];

            for(k = 0; k < nRowB; k++)
            {
                for(l = 0; l < nColB; l++)
                {
                    valB = B[k][l];
                    krnProd[nRowB*i+k][nColB*j+l] = valA * valB;
                }
            }
        }
    }

    return krnProd;
}

template<class T> void verCatMatrix(vector< vector<T> > &res, vector < vector<T> > &A)
{
    if(res.size() == 0)
    {
       res = A;
    }
    else
    {
       res.insert(res.end(),A.begin(),A.end()); // concatenate
    }
}

vector< vector<double> > transpose(vector< vector<double> > &tr)
{
    vector< vector<double> > tmp(tr[0].size(),vector<double>(tr.size(),0.0)); // declare a temporary matrix

    for(size_t i = 0; i < tmp.size(); i++)
    {
        for(size_t j =0; j < tmp[0].size(); j++)
        {
            tmp[i][j] = tr[j][i]; // Transpose changes the index
        }

    }

    return tmp;
}

vector< vector<double> > matrixMuliply(vector< vector<double> > &A, vector< vector<double> > &B)
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
        exit(EXIT_FAILURE);
    }

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
            //cout << Y[i][j] <<",";
        }
        //cout << endl;
    }

    return Y;
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

vector<double> vecSubtract(vector<double> &a, vector<double> &b)
{
    vector<double> C(a.size(),0.0);

    if(a.size() != b.size())
    {
        cout << "Error, vector dimension are not the same" << endl;
        exit(EXIT_FAILURE);
    }

    for(int i =0; i < a.size(); i++)
    {
            C[i] = a[i] - b[i];
    }

    return C;
}

vector<double> matrixVectMuliply(vector<double>&a, vector< vector<double> > &B)
{
    vector<double> Y(B.size(),0.0); // We must initialize our resultant matrix to 0
    int n = a.size();
    int m = a.size();
    int p = B.size();


    // Here we do some checking.
    // If the Column of A is not the same as the Row of B
    // multiplication cannot be done !
    if(a.size() != B[0].size())
    {
        cout << "Matrix dimension are not the same !" << endl;
        exit(EXIT_FAILURE);
    }

    for(int j = 0; j < p; j++)
    {
        double sum = 0.0;

        for(int k = 0; k < m; k++)
        {
            sum = sum + B[j][k]*a[k];
        }

        Y[j] = sum;
    }

    return Y;
}

vector<double> scalarMultVec(double lambda, vector<double>  &a)
{
    vector<double> res(a.size(),0.0);

        for(int i =0; i < res.size(); i++)
        {
            res[i] = (lambda)*a[i];
        }

    return res;
}

vector<double> vecAdd(vector<double> &a, vector<double> &b)
{
    vector<double> C(a.size(),0.0);

    if(a.size() != b.size())
    {
        cout << "Error, vector dimension are not the same" << endl;
        exit(EXIT_FAILURE);
    }

    for(int i =0; i < a.size(); i++)
    {
            C[i] = a[i] + b[i];
    }

    return C;
}

double norm_2(vector<double>&a)
{
    // function for l2 norm
    double normVal =0.0;

    for(size_t i =0; i < a.size(); i++)
    {
      normVal = normVal + pow(a[i],2.0);
    }

    return sqrt(normVal);

}

vector<double> shrink(vector<double> &a, double mu, double lambda)
{
    double val = mu/lambda;
    vector<double> res(a.size(),0.0);


    res = absVal(a);  // |a|

    for(int i = 0; i < res.size(); i++)
    {
        res[i] = res[i]-val;    // (|a|-regularization parameter)
    }

    auto aSign = sign(a); // sign(a)

    res = clamp(res); // max(|a|-regularization parameter)

    res = vecVecMult(res,aSign); // max(|a|-regularization parameter)*sign(a)

    return res;
}

vector<double> sign(vector<double> &a)
{
    vector<double> aSigned(a.size(),0.0);

    for(int i = 0; i < aSigned.size(); i++)
    {
        if(a[i] > 0.0)
        {
            aSigned[i] = 1.0;
        }

        if(a[i] < 0.0)
        {
            aSigned[i] = -1.0;
        }

        if(a[i] == 0.0)
        {
            aSigned[i] = 0.0;
        }
    }

    return aSigned;
}

vector<double>  absVal(vector<double> &sig)
{
    vector<double> absSig(sig.size(),0.0);

    for(size_t i =0; i < sig.size(); i++)
    {
        absSig[i] = std::abs(sig[i]);
    }

    return absSig;
}

vector<double> clamp(vector<double> &a)
{
    vector<double> aClam(a.size(),0.0);

    for(int i = 0; i < aClam.size(); i++)
    {
        if(a[i] > 0.0)
        {
            aClam[i] = a[i];
        }
        if(a[i] <= 0.0)
        {
            aClam[i] = 0.0;
        }
    }

    return aClam;
}

vector<double> vecVecMult(vector<double> &a, vector<double> &b)
{
    vector<double> ab(a.size(),0.0);

    if(a.size() != b.size())
    {
        cout << "Vector size not the same..." << endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < ab.size(); i++)
    {
        ab[i] = a[i]*b[i];
    }

    return ab;
}

#endif // FUNCDEFINITION_H
