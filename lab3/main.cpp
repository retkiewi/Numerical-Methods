#include <iostream>
#include <cmath>
#include <limits>
#include <cfloat>

using namespace std;

long double f1(long double x){
    return cos(x)*cosh(x)-1;
}

long double f1_derivative(long double x){
    return -cosh(x)*sin(x) + cos(x)*sinh(x);
}

long double f2(long double x){
    return 1/x - tan(x);
}

long double f2_derivative(long double x){
    return -1/pow(x, 2) - pow(1/cosh(x), 2);
}

long double f3(long double x){
    return pow(2.0, -x) + exp(x) + 2*cos(x) - 6;
}

long double f3_derivative(long double x){
    return pow(2.0, -x)*log(2) + exp(x) - 2*sin(x);
}


long double bisection_method(long double (*f)(long double), long double from, long double to, long double abs_err) {
    long double x1 = (from + to) / 2;
    long int i = 0;
    while (abs((*f)(x1)) > abs_err) {
        if ((*f)(from) * (*f)(x1) < 0) {
            to = x1;
        } else {
            from = x1;
        }
        long double last_x1 = x1;
        x1 = (from + to) / 2;
        if(last_x1==x1){
            cout<<"Precision is to small.\n";
            break;
        }
        i++;
    }
    cout << "Ilosc iteracji: " << i << endl;
    return x1;
}

long double newtons_method(long double (*f)(long double), long double (*f_derivative)(long double), int max_iters, long double epsilon){
    long double x0 = 0.1;
    long double xn;
    int i;
    for(i=0; i<max_iters; i++){
        xn = x0 - (f(x0))/f_derivative(x0);
        if(abs(x0-xn)<epsilon){
            x0=xn;
            break;
        }
        x0=xn;
    }
    cout << "Ilosc iteracji: " << i << endl;
    return x0;
}

long double secant_method(long double (*f)(long double), int max_iters, long double epsilon){
    long double x0 = 0.1, x1 = 1, x2;
    for(int i=0; i<max_iters; i++){
        x2 = x1 - f(x1)*(x1-x0)/(f(x1)-f(x0));
        if(isinf(x2)){
            x2 = x1;
            break;
        }
        if(abs(x2-x1)<epsilon){
            break;
        }
        x0 = x1;
        x1 = x2;
    }
    return x2;
}

int main() {
    long double precissions[3] = {pow(10.0, -7), pow(10.0, -15), pow(10.0, -33)};
    cout<<"~~~~~~F1~~~~~~\n";
    cout<<"-----BISECTION-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<bisection_method(f1, 3*M_PI/2, 2*M_PI, precissions[i])<<endl;
    }
    cout<<"-----NEWTONS-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<newtons_method(f1, f1_derivative, 100, precissions[i])<<endl;
    }
    cout<<"-----SECANT-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<secant_method(f1, 100, precissions[i])<<endl;
    }

    cout<<"~~~~~~F2~~~~~~\n";
    cout<<"-----BISECTION-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<bisection_method(f2, 3*M_PI/2, 2*M_PI, precissions[i])<<endl;
    }
    cout<<"-----NEWTONS-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<newtons_method(f2, f2_derivative, 100, precissions[i])<<endl;
    }
    cout<<"-----SECANT-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<secant_method(f2, 100, precissions[i])<<endl;
    }

    cout<<"~~~~~~F3~~~~~~\n";
    cout<<"-----BISECTION-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<bisection_method(f3, 3*M_PI/2, 2*M_PI, precissions[i])<<endl;
    }
    cout<<"-----NEWTONS-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<newtons_method(f3, f3_derivative, 100, precissions[i])<<endl;
    }
    cout<<"-----SECANT-METHOD-----"<<endl;
    for(int i=0; i<3; i++){
        cout<<"Precision: "<<precissions[i]<<endl;
        cout<<secant_method(f3, 100, precissions[i])<<endl;
    }

    return 0;
}
