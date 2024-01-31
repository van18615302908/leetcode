#include<bits/stdc++.h>

using namespace std;

long long repairCars(vector<int>& ranks, int cars) {
    long long upper_bound = ranks[0]*cars*cars;
    long long lower_bound = 0;
    int times = -1;
    long long middle = 0;
    do{
        times = 0;
        middle = (upper_bound + lower_bound) >> 1;
        for(auto i : ranks){
            times += sqrt(middle/i);
        }
        if(times >= cars){
            upper_bound = middle;
        }else{
            lower_bound = middle +1;
        }
    }while(upper_bound != lower_bound || upper_bound < lower_bound);
    return upper_bound;
}

int main(){
    vector<int> miao = {4,2,3,1};
    repairCars(miao,10);
    return 0;
}