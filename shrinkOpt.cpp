#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>

// Created by Tarmizi Adam on 17/8/2015. This program applies the shrinkage operator to a vector. The shrinkage operator
// is also known as the proximal operator and used widely in Iterative Shrinkage Thresholding Algorithms (ISTA).
// The shrkinkage operator is defined as:

//          shrink(a) = max(|a| - regularization param)*sign(a)

// The max(.) functions clamps vector a between 0 and 1. If the values in a are 0 or smaller than 0, it returns 0. Otherwise
// the value is retained.

// Note: the main function is shrink(). Other functions are used as the building block inside the shrink() function.

using namespace std;

vector<double> shrink(vector<double> &a, double mu, double lambda);
vector<double> sign(vector<double> &a);
vector<double> absVal(vector<double> &sig);
vector<double> clamp(vector<double> &a);
vector<double> vecVecMult(vector<double> &a, vector<double> &b);

int main()
{

    vector<double> tst = {0.8637,0,-1.2141,-1.1135,-0.0068};

    auto T = shrink(tst,1,1);

    for(int i = 0; i < T.size(); i++)
    {
        cout << T[i] << ",";
    }

    return 0;
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


