#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

float seriesSumFloat(int n){
    float sum = 0;
    for(int k=1; k<=n; k++){
        sum+=(float)(1/pow(2, k+1));
    }
    return sum;
}

float seriesSumReversedFloat(int n){
    float sum = 0;
    for(int k=n; k>0; k--){
        sum+=(float)(1/pow(2, k+1));
    }
    return sum;
}

double seriesSumDouble(int n){
    double sum = 0;
    for(int k=1; k<=n; k++){
        sum+=(double)(1/pow(2, k+1));
    }
    return sum;
}

double seriesSumReversedDouble(int n){
    double sum = 0;
    for(int k=n; k>0; k--){
        sum+=(double)(1/pow(2, k+1));
    }
    return sum;
}

float seriesSumFloatKahan(int n){
    float sum = 0;
    float err = 0;
    for(int k=1; k<=n; k++){
        float y = (float)(1/pow(2, k+1)) - err;
        float temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}

float seriesSumReversedFloatKahan(int n){
    float sum = 0;
    float err = 0;
    for(int k=n; k>0; k--){
        float y = (float)(1/pow(2, k+1)) - err;
        float temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}

double seriesSumDoubleKahan(int n){
    double sum = 0;
    double err = 0;
    for(int k=1; k<=n; k++){
        double y = (double)(1/pow(2, k+1)) - err;
        double temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}

double seriesSumReversedDoubleKahan(int n){
    double sum = 0;
    double err = 0;
    for(int k=n; k>0; k--){
        double y = (double)(1/pow(2, k+1)) - err;
        double temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}

int main() {

    int arr[5] = {50, 100, 200, 500, 800};
    cout<<setprecision(5)<<fixed;
    for(int i = 0; i<5; i++){
        cout<<"~~~~~ N="<<arr[i]<<" ~~~~~"<<endl;
        cout<<"------REGULAR-SUM------"<<endl;
        cout<<"****Float****"<<endl;
        cout<<"Normal: "<<seriesSumFloat(arr[i])<<endl;
        cout<<"Reversed: "<<seriesSumReversedFloat(arr[i])<<endl;
        cout<<"****Double****"<<endl;
        cout<<"Normal: "<<seriesSumDouble(arr[i])<<endl;
        cout<<"Reversed: "<<seriesSumReversedDouble(arr[i])<<endl;
        cout<<"------KAHAN-SUM------"<<endl;
        cout<<"****Float****"<<endl;
        cout<<"Normal: "<<seriesSumFloatKahan(arr[i])<<endl;
        cout<<"Reversed: "<<seriesSumReversedFloatKahan(arr[i])<<endl;
        cout<<"****Double****"<<endl;
        cout<<"Normal: "<<seriesSumDoubleKahan(arr[i])<<endl;
        cout<<"Reversed: "<<seriesSumReversedDoubleKahan(arr[i])<<endl;
    }

}
