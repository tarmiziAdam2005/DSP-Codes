#ifndef FUNCDEF_H
#define FUNCDEF_H

#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<fstream>

using std::cout;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;

template<class T> void printArray2D(vector< vector<T> > &I); // Function to show our created matrix
void diffOperator(vector< vector<double> > &B, vector< vector<double> > &Bt, vector< vector<double> > &BtB ,size_t N);
vector< vector<double> > doubleBandMat(vector<double> &e,int N);
vector< vector<double> > eye(size_t N);
vector< vector<double> > kron(vector< vector<double> > &A, vector< vector<double> > &B);
template<class T> void verCatMatrix(vector< vector<T> > &res, vector< vector<T> > &A);
vector< vector<double> > transpose(vector< vector<double> > &tr);
vector< vector<double> > matrixMuliply(vector< vector<double> > &A, vector< vector<double> > &B);
vector< vector<double> > addMatrix(vector< vector<double> > &A, vector< vector<double> > &B);
vector<double> vecSubtract(vector<double> &a, vector<double> &b);
vector<double> matrixVectMuliply(vector<double>&a, vector< vector<double> > &B);
vector<double> scalarMultVec(double lambda, vector<double>  &a);
vector<double> vecAdd(vector<double> &a, vector<double> &b);
double norm_2(vector<double>&a);

vector<double> shrink(vector<double> &a, double mu, double lambda);
vector<double> sign(vector<double> &a);
vector<double> absVal(vector<double> &sig);
vector<double> clamp(vector<double> &a);
vector<double> vecVecMult(vector<double> &a, vector<double> &b);

#endif // FUNCDEF_H
