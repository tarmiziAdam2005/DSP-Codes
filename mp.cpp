#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<cstdlib>
#include<cmath>

// Created by Tarmizi Adam 5/7/2015. Implementation of matching pursuit by zhang and mallat. For matching pursuit
// we are trying to solve
//                          y = Dx
// where y is our observed signal. D is an overcomplete dictionary (Cosine dictionary in this code). x is the
// sparse coefficients that we are after.
//We are trying to model y as a linear combination of sparse coefficients
// x and dictionary D.
// This is done in the function matchingPursuit(vector<double> &y, vector <vector<double> > &D, int iterations, double threshold)
// input: observed signal y;
//        Overcomplete dictionary D;
//        number of iterations (how many times you want in to loop)
//        threshold value (if residual is smaller than this value, the algorithms stops)

// output: our sparse coefficients x.

// version 1.0, there is no warranty that this program will yield/produce accurate solutions. Pleas email me
// at tarmizi_adam2005@yahoo.com if you find and bugs, wrong/steps in calculating the matching pursuit algorithm

using std::cin;
using std::vector;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::endl;

void matchingPursuit(vector<double> &y, vector <vector<double> > &D, int iterations, double threshold);
vector<double> matrixVectMuliply(vector<double>&A, vector< vector<double> > &B);
double innerProd(vector<double>&A, vector<double> &B);
double norm_2(vector<double>&a);

void transpose(vector< vector<double> > &tr);
template<class T> void printArray2D(vector< vector<T> > &I);
vector<double> getRow(vector <vector<double> > A, size_t rowIndex);
vector<double> updateResidual(vector<double> &res, double innProdVal, vector <vector<double> > A, size_t colIndex);
void absVal(vector<double> &i);

int main()
{
    ifstream fl_1("odctDict.txt");
    ifstream fl_2("y.txt");

    //int N = 4; // signal length
    int dictSize = 100;
    double dataVal =0.0;
    double threshold = 1.0e-6;

    vector<double> y;//(N,0.0);
    //vector<double> x(N,0);
    vector< vector<double> > D(dictSize, vector<double>(dictSize,0)); // initialize Dictionary

    // Read in dictionary values
    // Some checking...
    if(!fl_1)
    {
        cout << "Could not read dictionary file !. Exiting..." << endl;
        return 1;
    }

    // Read our Dictionary;
    while(fl_1)
    {
        for(int i =0; i < dictSize; i++)
        {
            for(int j = 0; j <dictSize; j++)
            {
                fl_1 >> D[i][j];
            }
        }
    }

    if(!fl_2)
    {
        cout << "Could not read input file !. Exiting..." << endl;
        return 1;
    }

    while(fl_2 >> dataVal)
    {
        y.push_back(dataVal);
    }

    cout << "Dictionary size: " << "[" << D.size() << "x" << D[0].size() << "]" << endl;
    cout << "Signal size: " << "[" << y.size() << "x" << 1 << "]" << endl;
    matchingPursuit(y,D, 1000, threshold);

    return 0;
}

void matchingPursuit(vector<double> &y, vector <vector<double> > &D, int iterations, double threshold)
{
    ofstream out_1("x.txt");
    vector<double> residual = y;
    vector< vector<double> > D_t = D;
    vector<double> x(y.size(),0.0);
    vector<double> idx;
    vector<double>::iterator lar;

   //int l;
    int iter = 0;
    transpose(D_t);

    vector<double> rowDict(y.size(),0.0);
    double norm_res = 0.0;

    // Main loop of our matching pursuit algorithm
    do
    {
        //cout << "first iteration: ";
        for(size_t i =0; i < y.size(); i++)
        {
            int l =0;

            idx = matrixVectMuliply(residual,D_t);
            absVal(idx);
            lar = std::max_element(std::begin(idx), std::end(idx)); // Find the largest value in vector idx
            l = std::distance(std::begin(idx), lar); // find the position (index) of the largest value in vector idx
            rowDict = getRow(D_t,i);

            x[i] = x[i]+ innerProd(rowDict,residual);

            residual = updateResidual(residual, innerProd(rowDict,residual),D,i);
        }
        norm_res = norm_2(residual);
        if(norm_res < threshold)
            break;
        //cout << norm_res << endl;

        iter++;

    }while(iter < iterations);

    for(size_t i = 0; i < x.size(); i++)
    {
      out_1 << x[i] << endl;
    }

}

vector<double> matrixVectMuliply(vector<double>&A, vector< vector<double> > &B)
{
    // Function to do matrix vector multiplication i.e. Ax
    vector<double> Y(A.size(),0.0); // We must initialize our resultant matrix to 0
    //int n = A.size();
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

    // Matrix vector multiplication
    for(int j = 0; j < p; j++)
    {
        double sum = 0.0;

        for(int k = 0; k < m; k++)
        {
            sum = sum + B[j][k]*A[k];
        }

        Y[j] = sum;
    }

    return Y;
}

double innerProd(vector<double>&A, vector<double> &B)
{
    // innder product/dot product i.e. xy
    double sum = 0.0;

    if(A.size() != B.size())
    {
        cout << "Inner product could not be done. Vector size differ !";
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < A.size(); i++)
    {
        sum = sum + B[i]*A[i];
    }

    return sum;
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

void transpose(vector< vector<double> > &tr)
{
    vector< vector<double> > tmp = tr; // declare a temporary matrix

     for(size_t i = 0; i < tr.size(); i++)
    {
        for(size_t j =0; j < tr[0].size(); j++)
        {
            tr[i][j] = tmp[j][i]; // Transpose changes the index
        }
    }

    tmp.clear();
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

vector<double> getRow(vector <vector<double> > A, size_t rowIndex)
{
   // function to get just the ith row of a matrix.
   vector<double> row(A[0].size(),0.0);

   if(rowIndex >= A[0].size())
   {
       cout << "Index supplied exeed matrix size !...";
       exit(EXIT_FAILURE);
   }

   for(size_t j = 0; j < A[0].size();j++)
   {
      row[j] = A[rowIndex][j];
   }

    return row;
}

vector<double> updateResidual(vector<double> &res, double innProdVal, vector <vector<double> > A, size_t colIndex)
{
   // function to update our residual values.
   vector<double> col(A[0].size(),0.0);
   vector<double> update(res.size(),0.0);

   if(colIndex >= A[0].size())
   {
       cout << "Index supplied exeed matrix size !...";
       exit(EXIT_FAILURE);
   }

   for(size_t j = 0; j < A[0].size();j++)
   {
      col[j] = innProdVal*A[j][colIndex];
      //cout << col[j] << endl;
   }

   for(size_t k =0; k < col.size(); k++)
   {
       update[k] = res[k] - col[k];
       //cout << update[k] << endl;
   }

    return update;
}

void absVal(vector<double> &sig)
{
    for(size_t i =0; i < sig.size(); i++)
    {
        sig[i] = std::abs(sig[i]);
    }
}

