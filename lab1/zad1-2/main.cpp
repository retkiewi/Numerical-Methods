#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;

float sumIter (int N, float v, vector<float> &arr, ofstream &outputRelative, ofstream &outputAbsolute){
    float result = 0.0;

    for(unsigned int i = 0; i < arr.size(); i++) {
        result += arr[i];
        if((i+1)%2500 == 0) {
            float errorAbsolute = abs(result-(i+1)*v);
            outputAbsolute<<i<<"\t"<<errorAbsolute<<endl;
            float errorRelative = abs(result-(i+1)*v)/((i+1)*v);
            outputRelative<<i<<"\t"<<errorRelative<<endl;
        }
    }
    return result;
}

float sumRecursive (vector<float> &arr, int start, int end) {

    if(end-start<1)
        return 0;

    if(end-start==1){
        return arr[start];
    }

    return sumRecursive(arr, start, (start+end)/2) + sumRecursive(arr, (start+end)/2, end);
}

float sumKahan (vector<float> input) {
    float sum = 0.0;
    float err = 0.0;

    for (int i = 0; i < input.size(); i++) {
        float y = input[i] - err;
        float tmp = sum + y;
        err = (tmp - sum) - y;
        sum = tmp;
    }

    return sum;
}

int main () {
    int N = 10000000;
    float v = 0.3f;
    float expectedValue = v*N;

    ofstream  iterOutputAbsolute, iterOutputRelative;

    iterOutputAbsolute.open("wyniki_iteracji_bezwzgledne.dat");
    iterOutputRelative.open("wyniki_iteracji_wzgledne.dat");

    if(!(iterOutputRelative.is_open() && iterOutputAbsolute.is_open())){
        cout<<"Błąd otwarcia plików wyjściowych.";
        return 1;
    }

    vector<float> arr;

    for(int i = 0; i < N; i++)
        arr.push_back(v);



    float resultIter = sumIter(N, v, arr, iterOutputRelative, iterOutputAbsolute);
    float resultRec = sumRecursive(arr, 0, N);
    float resultKahan = sumKahan(arr);


    cout<<fixed<<setprecision(10);
    auto start = chrono::high_resolution_clock::now();
    cout<<"resultIter: "<<resultIter<<"\trelativeError: "<<abs(resultIter-expectedValue)/expectedValue<<"\tabsoluteError: "<<abs(resultIter-expectedValue)<<endl;
    auto end = chrono::high_resolution_clock::now();
    cout<<"Time: "<<chrono::duration<double>(end-start).count()<<endl;
    start = chrono::high_resolution_clock::now();
    cout<<"resultRec: "<<resultRec<<"\trelativeError: "<<abs(resultRec-expectedValue)/expectedValue<<"\tabsoluteError: "<<abs(resultRec-expectedValue)<<endl;
    end = chrono::high_resolution_clock::now();
    cout<<"Time: "<<chrono::duration<double>(end-start).count()<<endl;
    start = chrono::high_resolution_clock::now();
    cout<<"resultKahan: "<<resultKahan<<"\trelativeError: "<<abs(resultKahan-expectedValue)/expectedValue<<"\tabsoluteError: "<<abs(resultKahan-expectedValue)<<endl;
    end = chrono::high_resolution_clock::now();
    cout<<"Time: "<<chrono::duration<double>(end-start).count();

    iterOutputRelative.close();
    iterOutputAbsolute.close();

    return 0;
}