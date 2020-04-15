#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

double k = 2;
double m = 3;

struct point{
    point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    double x;
    double y;
};

double f1 (double x) {
    return sin((k * x) / M_PI) * exp(-(m * x) / M_PI);
}

double f2 (double x) {
    return exp(k * cos(m * x));
}

double f2Prim (double x) {
    return k*m*sin(m*x)*(-exp(k*cos(m*x)));
}

double f2Bis (double x) {
    double output = k*pow(m,3)*sin(m*x)*(-exp(k*cos(m*x)))*(pow(k, 2)*pow(sin(m*x),2) - 3*k*cos(m*x) - 1);
    return output;
}

vector<double> tripleVector(vector<double> input){
    vector<double> output;
    for(int i=0; i<input.size(); i++){
        for(int j=0; j<3; j++){
            output.push_back(input[i]);
        }
    }
    return output;
}

vector<double> chebyshevyfi(int n, double left, double right){
    vector<double> chebyshevNodes;
    double length = (right-left)/2, middle = (left+right)/2;
    for(int l=1; l<=n; l++){
        chebyshevNodes.push_back(middle + length*cos(((2*l-1)*M_PI)/(2*n)));
    }
    sort(chebyshevNodes.begin(), chebyshevNodes.end());

    return chebyshevNodes;
}

vector<double> regularify(int n, double left, double right){
    vector<double> nodes;
    double step = (right-left)/n;
    for(int i=1; i<=n; i++){
        nodes.push_back(left+step*i);
    }
    return nodes;
}

double newtonsPolly(vector<double> X, vector<double> B, double x){
    double value = 0;
    for(int i=0; i<B.size(); i++){
        double temp =1;
        for(int j=0; j<i; j++){
            temp*=(x-X[j]);
        }
        value+=B[i]*temp;
    }
    return value;
}

vector<double> newtonsInterpolation(vector<double> X, double (*f)(double)){
    vector<double> B, newTemp, temp = X;
    for(int i=0; i<temp.size(); i++){
        temp[i] = f(temp[i]);
    }
    int iter = 1;
    B.push_back(temp[0]);
    while(temp.size()>1) {
        for (int j = 0; j < temp.size()-1; j ++) {
            newTemp.push_back((temp[j + 1] - temp[j]) / (X[j + iter] - X[j]));
        }
        temp.clear();
        for (int j = 0; j < newTemp.size(); j++) {
            temp.push_back(newTemp[j]);
        }
        newTemp.clear();
        B.push_back(temp[0]);
        iter++;
    }
    return B;
}

double lagrangesInterpolation (vector<double> X, double x, double (*f)(double)) {
    double sum = 0.0;
    for(int i = 0; i < X.size(); i++) {
        double temp = 1.0;
        for(int j = 0; j < X.size(); j++) {
            if(j != i)
                temp *= (x - X[j])/(X[i] - X[j]);
        }
        sum += f(X[i]) * temp;
    }
    return sum;
}

double hermitePolly(vector<double> X, vector<double> B, double x){
    double sum=0;
    double multiplier = 1;
    for(int i=0; i<B.size(); i++){
        sum+=B[i]*multiplier;
        multiplier*=(x-X[i]);
    }
    return sum;
}

vector<double> hermiteInterpolation (vector<double> X, double (*f)(double), double (*fPrim)(double), double (*fBis)(double)) {
    vector<double> B;
    vector<point> temp, newTemp;
    int offset = 0;
    for(int i=0; i<X.size(); i++){
        temp.push_back(point(X[i], f(X[i])));
    }
    offset++;
    for(int i=1; i+offset<X.size(); i++){
        if(i%3==0){
            newTemp.push_back(point(temp[i - 1].x, (temp[i].y - temp[i - 1].y) / (temp[i].x - temp[i - 1].x)));
        }else{
            newTemp.push_back(point(X[i+offset], fPrim(X[i+offset])));
        }
    }
    B.push_back(newTemp[0].y);
    temp.swap(newTemp);
    newTemp.clear();
    offset++;
    for(int i=1; i+offset<X.size(); i++){
        if(i%3==2){
            newTemp.push_back(point(X[i+offset], fBis(X[i+offset])));
        }else{
            newTemp.push_back(point(temp[i - 1].x, (temp[i].y - temp[i - 1].y) / (temp[i].x - temp[i - 1].x)));
        }
    }
    B.push_back(newTemp[0].y);
    temp.swap(newTemp);
    newTemp.clear();
    offset++;
    while(offset<X.size()){
        for(int i=1; i+offset<X.size(); i++){
            newTemp.push_back(point(temp[i - 1].x, (temp[i].y - temp[i - 1].y) / (temp[i].x - temp[i - 1].x)));
        }
        B.push_back(newTemp[0].y);
        temp.swap(newTemp);
        newTemp.clear();
        offset++;
    }

    return B;
}

int main() {
    int n = 20;
    vector<double> cheby = chebyshevyfi(n, -1, 1);
    vector<double> regular = regularify(n, -1, 1);
    vector<double> regularX3 = tripleVector(regular);
    vector<double> chebyX3 = tripleVector(cheby);

    ofstream newtonRegular, lagrangeRegular, hermiteRegular, newtonCheby, lagrangeCheby, hermiteCheby;

    newtonRegular.open("newtonRegular" + to_string(n) + ".txt");
    lagrangeRegular.open("lagrangeRegular" + to_string(n) + ".txt");
    hermiteRegular.open("hermiteRegular" + to_string(n) + ".txt");
    newtonCheby.open("newtonCheby" + to_string(n) + ".txt");
    lagrangeCheby.open("lagrangeCheby" + to_string(n) + ".txt");
    hermiteCheby.open("hermiteCheby" + to_string(n) + ".txt");

    if(!newtonRegular.is_open() || !lagrangeRegular.is_open() || !hermiteRegular.is_open() || !newtonCheby.is_open() || !lagrangeCheby.is_open() || !hermiteCheby.is_open()){
        cout<<"Couldn't open some(XD) file.";
        return 0;
    }

    vector<double> bRegular = newtonsInterpolation(regular, f2);
    vector<double> bCheby = newtonsInterpolation(cheby, f2);
    vector<double> b2Regular = hermiteInterpolation(regularX3, f2, f2Prim, f2Bis);
    vector<double> b2Cheby = hermiteInterpolation(chebyX3, f2, f2Prim, f2Bis);

    vector<double> test = regularify(1000, -1, 1);

    for(int i=0; i<test.size(); i++){
        newtonRegular<<test[i]<<"\t"<<newtonsPolly(regular, bRegular, test[i])<<endl;
        newtonCheby<<test[i]<<"\t"<<newtonsPolly(cheby, bCheby, test[i])<<endl;
        lagrangeRegular<<test[i]<<"\t"<<lagrangesInterpolation(regular, test[i], f2)<<endl;
        lagrangeCheby<<test[i]<<"\t"<<lagrangesInterpolation(cheby, test[i], f2)<<endl;
        hermiteRegular<<test[i]<<"\t"<<hermitePolly(regular, bRegular, test[i])<<endl;
        hermiteCheby<<test[i]<<"\t"<<hermitePolly(cheby, bCheby, test[i])<<endl;
    }

    return 0;
}
