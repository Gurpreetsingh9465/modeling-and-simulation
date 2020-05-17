#include<bits/stdc++.h>
using namespace std;

float round(float var, int num) 
{
    char str[40];  
    sprintf(str, "%.2f", var);  
    sscanf(str, "%f", &var);  
    return var;  
} 

void solve() {
    cout<<"Enter number of classes\n";
    int n;
    cin>>n;
    int N,chi,interval;
    N = chi = interval = 0;
    float step = (0.0+1.0)/(n*1.0);
    unordered_map<float,int> count;
    vector<float> ke;
    for(int i=0;i<n;i++) {
        interval += step;
        count[round(interval,2)] = 0;
        ke.push_back(round(interval,2));
    }
    cout<<"Enter Random sequence\n";
    vector<int> v(n);
    for(int i=0;i<n;i++) {
        cin>>v[i];
    }
    sort(v.begin(), v.end());
    sort(ke.begin(), ke.end());
    for(auto &x: v) {
        N += 1;
        for(auto &k: ke) {
            if(float(x) < k) {
                count[k] = count[k]+1;
                break;
            }
        }
    }
    float alpha;
    cout<<"Enter the critical value: \n";
    cin>>alpha;
    float Ei = (N*1.0)/(n*1.0);
    for(auto &i: count) {
        chi += (pow(i.second-Ei,2)/Ei);
    }
    if(round(chi,2) < alpha) {
        cout<<"\nRandom sequence is uniformly distributed\n";
    } else {
        cout<<"\nRandom sequence is not uniformly distributed\n";
    }
}

int main() {
    solve();
}
