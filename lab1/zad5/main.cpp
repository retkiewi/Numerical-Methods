#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

float unstableAlgorithm(float x){
    return (1.0f-pow(cos(x) ,2.0f))/pow(x, 2.0f);
}

float stableAlgorithm(float x){
    return pow(sin(x), 2.0f)/pow(x, 2.0f);
}

int main() {
    ofstream output;

    output.open("wyniki.dat");

    int n=400;
    for(int i=-9; i<10; i++){
        float x = (float)(1.0/(i*n));
        cout<<fixed<<setprecision(10);
        cout<<"--- X = "<<x<<" ---\n";
        cout<<"Unstable: "<<unstableAlgorithm(x)<<"\t\t\tStable: "<<stableAlgorithm(x)<<endl;
        cout<<"Difference absolute: "<<abs(unstableAlgorithm(x)-stableAlgorithm(x))<<"\tDifference relative to stable: "<<abs(unstableAlgorithm(x)-stableAlgorithm(x))/stableAlgorithm(x)<<endl;

        output<<x<<'\t'<<unstableAlgorithm(x)<<'\t'<<stableAlgorithm(x)<<'\n';
    }
}
