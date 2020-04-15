#include <iostream>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double epsilon = 1.0;
    double value = 1.0;
    while(value+epsilon != value){
        epsilon/=2;
    }

    epsilon *=2;

    cout<<"Epsilon: "<<epsilon;

    return 0;
}
