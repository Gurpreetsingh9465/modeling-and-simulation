#include<bits/stdc++.h>
using namespace std;
#define ll long long

int line = 1;
int a[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

void midSquare(ll seed, int n) {
    unordered_set<ll> s;
    int sqn = number * number, next_number = 0;
//     int t = (digit / 2);
//    sqn = sqn / a[t];
//    for (int i = 0; i < digit; i++) {
//       next_number += (sqn % (a[t])) * (a[i]);
//       sqn = sqn / 10;
//    }
    while (seed != 0 && s.find(seed) == s.end() )
    {
        s.insert(seed);
        cout<<line<<" "<<seed<<endl;
        if(seed == 0)
            break;
        seed = seed*seed;
        int curLen = ceil(log10(seed));
        if(!curLen < n) {
            vector<int> v(curLen);
            int index = curLen-1;
            ll seed2 = seed;
            while(seed2>0) {
                int l = seed2%10;
                seed2/=10;
                v[index--] = l;
            }
            int newSeed = 0;
            index = curLen/2-n/2;
            int i = 0;
            while (i<n) {
                newSeed = newSeed*10+v[index];
                index++;
                i++;
            }
            seed = newSeed;
        }
        line++;
        if(line>1000) {
            break;
        }
    }
    cout<<seed<<endl;
}


int main() {
    int seed;
    cout<<"Enter Seed"<<endl;
    cin>>seed;
    int n = ceil(log10(seed));
    midSquare(seed, n);
}