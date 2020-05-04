#include<bits/stdc++.h>
using namespace std;

int congestion(int ri, int a, int b, int m) {
    return ((ri*a+b)%m);
}

void runCongestion(int r, int a, int b, int m) {
    unordered_set<int> s;
    while (s.size() < 1000) {
        cout<<r<<" ";
        if(s.find(r) != s.end()) {
            break;
        }
        s.insert(r);
        r = congestion(r,a,b,m);
    }
    cout<<endl;
}

int arithmatic(int r0, int r1, int m) {
    return (r0+r1)%m;
}

void runArithmatic(int r0, int r1, int m) {
    set<pair<int,int>> s;
    while (s.size() < 1000) {
        cout<<r0<<" ";
        pair<int,int> p = {r0, r1};
        if(s.find(p) != s.end()) {
            break;
        }
        s.insert(p);
        int r2 = arithmatic(r0,r1,m);
        r0 = r1;
        r1 = r2;
    }
    cout<<r1<<endl;
    cout<<endl;
}

int main() {
    cout<<"Press key to run generatio method - \n1: mixed type \n2: additive \n3: multiplicative \n4: arithmetic"<<endl;
    int choice;
    cin>>choice;
    int r, a, b, m, r_0, r_1;
    switch (choice)
    {
        case 1:
            cout<<"Enter r a b m"<<endl;
            cin>>r>>a>>b>>m;
            runCongestion(r,a,b,m);
            break;
        case 2:
            a = 1;
            cout<<"Enter r b m"<<endl;
            cin>>r>>b>>m;
            runCongestion(r,a,b,m);
            break;
        case 3:
            b = 0;
            cout<<"Enter r a m"<<endl;
            cin>>r>>a>>m;
            runCongestion(r,a,b,m);
            break;
        case 4:
            cout<<"Enter r0 r1 m"<<endl;
            cin>>r_0>>r_1>>m;
            runArithmatic(r_0,r_1,m);
            break;
        default:
            break;
    }
    return 0;
}