
// Rectangular function
// Rectangular function is define as
//



#include <iostream>
#include <fstream>
using namespace std;
void rectPulse(int a, int t,int n);

int main()
{
    int a;
    int t;
    int n;

    cout << "Enter the height (A) of the rectangular pulse:";
    cin >> a ;
    cout << endl;

    cout << "Enter the period (T) of the rectangular pulse:";
    cin >> t;
    cout << endl;


    cout << "Enter the length (N) of the periodic rectangular pulse signal:";
    cin >> n;
    cout << endl;

    rectPulse(a,t,n);

    return 0;
}


void rectPulse(int a,int t, int n)
{
    ofstream myFile;
    myFile.open("rect.csv");
    int N = n; // the length of the signal

    int A = a; // height of pulse
    int T = t; // widht of pulse
    int x_t[t];// value of the pulse
    int T_0 = T/2;


    for (int i = 0; i<= T_0;i++)
        {
            x_t[i]=A;
        }

    for(int j =T_0;j<T;j++)
        {
            x_t[j]=0;

        }


    int arraySize = (sizeof(x_t)/sizeof(*x_t));


    for(int j =0;j<N/arraySize; j++)
    {
            for(int i =0; i<arraySize; i++)
        {
            cout << x_t[i] << endl;
            myFile << x_t[i] << endl;

        }

    }


}
