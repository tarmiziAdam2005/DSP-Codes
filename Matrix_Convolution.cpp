#include<iostream>
#include<vector>

// Created by Tarmizi Adam 11/4/2015. This simple snippet demostrates
// the computation of the linear convolution using
// the matrix multiplication method.

// Input: h(n) and x(n)
// Output: y(n)

using namespace std;

void matrixMuliply(vector< vector<double> > &A, vector< vector<double> > &B);

int main()
{
    vector< vector<double> > x_n = {{4},
                                    {2},
                                    {1},
                                    {3}};

    // Note that h_n the impulse response is a Toeplitz matrix (constant along every diagonal)
    vector< vector<double> > h_n = {{1,0,0,0},
                                    {2,1,0,0},
                                    {2,2,1,0},
                                    {1,2,2,1},
                                    {0,1,2,2},
                                    {0,0,1,2},
                                    {0,0,0,1}};

    matrixMuliply(h_n, x_n); // Multiply h(n) and x(n). Convolution using matrix multiplication method.

    cout << endl;
    return 0;
}

void matrixMuliply(vector< vector<double> > &A, vector< vector<double> > &B)
{
    vector< vector<double> > Y(A.size(),vector<double>(B[0].size(),0.0)); // We must allocate the output signal length
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

    // This is how we do a matrix multiplication !
    // In this snippet, our multiplication is done to get the convolution...

    cout << "Output y(n): ";

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
    }

}
