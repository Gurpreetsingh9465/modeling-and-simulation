#include<bits/stdc++.h>
using namespace std;

int getDemand() {
    srand(time(0)+rand());
    return rand()%20;
}

int getOrder(int I, int S, int s) {
    int offset = s-I;
    return offset;
}

unordered_map<string, float> calculate(int S, int s, int days, float holdingCostPerItem, float orderingCostPerItem) {
    srand(time(0)+rand());
    int I = rand()%S;
    if(I<s)
        I+=s;
    vector<pair<int, int>> graph; // days,I
    float perdayCost = holdingCostPerItem/30.0;
    graph.push_back({0,I});
    pair<int, int> order; //day,time;
    float orderingCost = 0.0;
    for(int i=1;i<=days;i++) {
        int shouldDemand = rand()%2;
        if(shouldDemand == 1 && i%5 == 0) {
            I-=getDemand();
        }
        if(order.second != 0 && i-order.first >= 15 && (!shouldDemand || i-order.first < 25)) {
            I+=order.second;
            order = {0,0};
        }
        if(i%30 == 0 && I<s) {
            order = {i, getOrder(I, S, s)};
            orderingCost+=(order.second*orderingCostPerItem + 32);
        }
        graph.push_back({i,I});
    }
    float positiveArea = 0;
    float negetiveArea = 0;
    for(auto i: graph) {
        if(i.second>0) {
            positiveArea+=i.second;
        } else {
            negetiveArea+=i.second;
        }
    }
    unordered_map<string, float> ans;
    ans["Positive area = "] = positiveArea;
    ans["Negetive area = "] = negetiveArea*-1;
    ans["ordering cost = "] = orderingCost;
    ans["holding cost = "] = positiveArea * perdayCost;
    ans["shortage cost = "] = negetiveArea * (5/30.0) * -1;
    ans["total cost = "] = orderingCost + positiveArea * perdayCost + negetiveArea * (5/30.0) * -1;
    return ans;
}


int main() {
    vector<int> S = {80,70,100};
    vector<int> s = {20,30,10};
    srand(time(0)+rand());
    int policyPicked = rand()%3;
    auto ans = calculate(S[policyPicked], s[policyPicked], 80, 1, 3); 
    for(auto &i: ans) {
        cout<<i.first<<" "<<i.second<<endl;
    }
    return 0;
}