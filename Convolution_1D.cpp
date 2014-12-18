#include <iostream>
#include <vector>

//Direct method Linear convolution.
// Created by tarmizi, 18/12/2014
// For further reading on convolution, refer to any DSP text. Example, Digital Signal Processing:
// Principles, Algorithms and Applications 4th Ed by Proakis and Manolakis

using namespace std;

void conv1D(vector<double> &h_k, vector<double> &x_n);

int main()
{
    vector<double> h_n; // Impulse responce
    vector<double> x_n; // Input signal

    size_t N;
    double val;

    cout << "Enter length of h(n):" ;
    cin >> N;
    cout << endl;
    cout << "Enter h(n) values:";

    for(size_t i = 0; i < N; i++)
    {
        cin >> val;
        h_n.push_back(val);
        cout <<",";
    }

    cout << "Enter length of x(n):" ;
    cin >> N;
    cout << endl;
    cout << "Enter x(n) values:";

    for(size_t i = 0; i < N; i++)
    {
        cin >> val;
        x_n.push_back(val);
        cout <<",";
    }

    cout << endl;
    cout << endl;
    cout << "Signal h(n): ";

    for(size_t n = 0; n < h_n.size(); n++)
    {
        cout << h_n[n] << ",";
    }

    cout << endl;
    cout << "Signal x(n): ";

    for(size_t n = 0; n < x_n.size(); n++)
    {
        cout << x_n[n] << ",";
    }

    // Perform Convolution of the two signals.
    conv1D(h_n,x_n);

    return 0;
}

void conv1D(vector<double> &h_k, vector<double> &x_n)
{

    size_t N = h_k.size()+ x_n.size()-1; // Linear convolution takes two signals h(n) and x(n) and producess a third signal y(n).
                                        // The output signal y(n) has length of lenght h(n) + lenght x(n) -1.
    vector<double> y_n(N,0.0); // Output, The conolved signal y(n)

    // We need to pad the values to avoid the convolution going out of bounds
    h_k.resize(N,0.0); // Use the resize function in std::vector to resize h(n) and x(n)
    x_n.resize(N,0.0); // by resizing we are padding zeros.


//******************************** The main snippet for Linear convolution**************************
    for(size_t n = 0; n < N; n++)
    {
       y_n[n]=0;

       for(size_t k = 0; k <= n; k++)
        {
            y_n[n] += h_k[k]*x_n[n-k]; // Convolution sum
        }
    }
//****************************************************************************************************

    cout << endl;
    cout << endl;

    cout << "Output signal y(n):" << endl;

    for(size_t n = 0; n < y_n.size(); n++)
    {
        cout << y_n[n] << ",";
    }

    cout << endl;

}



