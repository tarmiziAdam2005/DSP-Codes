#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<fstream>

#include "gausSiedl.h"
#include "funcDef.h"
#include "funcBody.h"

// Created by Tarmizi on 17/8/2015. This is an implementation of Split Bregman total variation denoising (TVD)
// Apply the Anisotropic Split bregman to a signal.

// Input: Noisy signal (only signal length N = 256 allowed. Stored in a .txt file)

// output: Denoised signal(Output as a .txt file)

// To understand and write the program the following references were consulted:

//           1) Goldstein, T., Osher. s, The Split Bregman method for L1-regularized problems. SIAM J. Imaging Sci,
//              2(2), 323-343 (2009).

//           2) Getreuer, P. Rudin-Osher-Fatemi Total Variation Denoising using Split Bregman. Image Processing Online
//              2, 74-95 (2012) Available at: http://dx.doi.org/10.5201/ipol.2012.g-tvd

//           3)  Micchelli, C. A., Shen, L., and Xu, Yuesheng. Proximity algorithms for image models: Denoising
//               Inverse Problems (27).1-29 (2011)

//           4) Matlab Implementation for simple understanding of the Algorithm
//              Available at : http://www.mathworks.com/matlabcentral/fileexchange/36278-split-bregman-method-for-total-variation-denoising
//              written by Benjamin Tremoulheac

// Notes: This program can only do TVD on signal size 256. i.e. N = 256. Future improvements/updates will be done to
//        accomodate larger signals.

//        Each iteration of the split bregman iteration does the gauss-siedel algorithm to solve the corresponding linear system.

using std::cout;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;

int main()
{
    ifstream in("data.txt");
    ofstream out("denoised.txt");
    ofstream con("Convergence.txt");

    double vals = 0.0;

    vector<double> y;

    vector< vector<double> > B;
    vector< vector<double> > Bt;
    vector< vector<double> > BtB;

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

    size_t N = y.size();
    int k = 0.0;

    vector<double> b(2*N,0.0);
    vector<double> up;
    auto d = b;
    auto u = y;

    double error = 1.0;
    double err1 = 0.0;
    double err2 = 0.0;
    double tol = 1.0e-10;
    double lambda = 1.0;
    double mu = 6.0;

    diffOperator(B, Bt, BtB, N);

    // Main loop that does the split bregman iterations.
    while(error > tol)
    {
        up = u;
        auto I = eye(N);
        //cout << I.size() << endl;
        //cout << BtB.size() << endl;
        auto I_BtB = addMatrix(I,BtB);

        auto c = vecSubtract(b,d);

        auto Btc = matrixVectMuliply(c,Bt);
        auto H = scalarMultVec(lambda,Btc);

        auto T = vecSubtract(y,H);

        GausSied gs(I_BtB);
        gs.solve(u,T);     // Solve the linear system using Gauss-Siedel method

        auto Bu = matrixVectMuliply(u,B);
        auto Bub = vecAdd(Bu,b);

        d = shrink(Bub,mu,lambda); // Proximal/Shrinkage operator

        b = vecSubtract(Bub,d);

        auto upu = vecSubtract(up,u);
        err1 = norm_2(upu);
        err2 = norm_2(u);
        error = err1/err2;
        cout << "Iteration: " << k << "  Error: " << error << endl;
        con << error << endl;

        k++;
    }

    for(int i = 0; i < u.size(); i++)
    {
        out << u[i] << endl; // Output denoised signal to .txt file.
    }

    return 0;
}




