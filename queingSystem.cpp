#include<bits/stdc++.h>
using namespace std;

bool comparator(pair<float,char> left, pair<float,char> right) {
    return right.first>left.first;
}

void printMerge(vector<pair<float, char>> combined) {
    for(auto &i: combined) {
        cout<<i.first<<" => "<<i.second<<endl;
    }
}

pair<pair<vector<float>,map<float, int>>,vector<pair<float,float>>> calculate(vector<pair<float, char>> combined) {
    queue<float> q;
    map<float, int> m;
    vector<float> delay;
    vector<pair<float, float>> utilization;
    bool isInService = false;
    for(auto &i: combined) {
        if(i.second == 'a') {
            if(!isInService) {
                m[i.first] = q.size();
                isInService = true;
                utilization.push_back({i.first, 0});
            } else {
                q.push(i.first);
                m[i.first] = q.size();
            }
        } else {
            if(!isInService) {
                m[i.first] = q.size();
                isInService = true;
            } else {
                if(q.size() == 0) { 
                    isInService = false;
                    utilization[utilization.size()-1].second = i.first;
                }
                if(q.size() > 0) {
                    delay.push_back(i.first-q.front());
                    q.pop();
                }
                m[i.first] = q.size();
            }
        }
    }
    if(utilization[utilization.size()-1].second == 0) {
        utilization[utilization.size()-1].second = combined[combined.size()-1].first;
    }
    return {{delay, m}, utilization};
}

float getArea(map<float, int> graph) {
    pair< float, int> prev = {0,0};
    float res = 0;
    for(auto &i: graph) {
        res += ((i.first-prev.first)*prev.second);
        prev= i;
    }
    return res;
}

vector<pair<float, char>> mergeArray(vector<float> arrival, vector<float> deparcher) {
    vector<pair<float, char>> combined(arrival.size()+deparcher.size());
    int index = 0;
    int aIndex = 0;
    int dIndex = 0;
    while (aIndex < arrival.size() && dIndex < deparcher.size()) {
        if(arrival[aIndex] > deparcher[dIndex]) {
            combined[index++] = {deparcher[dIndex++], 'd'};
        } else {
            combined[index++] = {arrival[aIndex++], 'a'};
        }
    }

    while (aIndex < arrival.size()) {
        combined[index++] = {arrival[aIndex++], 'a'};
    }
    
    while (dIndex < deparcher.size()) {
        combined[index++] = {deparcher[dIndex++], 'd'};
    }
    return combined;
}

unordered_map<string, float> getAns(pair<pair<vector<float>,map<float, int>>, vector<pair<float, float>>> ans, float totalTime) {
    auto utilization = ans.second;
    vector<float> delay = ans.first.first;
    map<float, int> graph = ans.first.second;
    float totalDelay = 0;
    float totalUtilization = 0.0;
    for(auto &i: utilization) {
        totalUtilization += (i.second-i.first);
    }
    for(auto &i: delay) {
        totalDelay+=i;
    }
    unordered_map<string, float> res;
    res["Area = "] = getArea(graph);
    res["Average no of customers = "] = (getArea(graph)/totalTime);
    res["Avergare delay = "] = delay.size() == 0?0:(totalDelay/delay.size());
    res["Average Utilization = "] = (totalUtilization/totalTime);
    return res;
}

void resultCalculator(vector<float> arrival, vector<float> deparcher) {
    vector<pair<float, char>> combined = mergeArray(arrival, deparcher);
    float totalTime = combined[combined.size()-1].first;
    pair<pair<vector<float>,map<float, int>>, vector<pair<float, float>>> ans = calculate(combined);
    auto result = getAns(ans, totalTime);
    for(auto &i: result) {
        cout<<i.first<<i.second<<endl;
    }
    cout<<"=================================="<<endl;
}

pair<vector<float>, vector<float>> getRandom(int n, int m) {
    vector<float> f;
    unordered_set<float> us;
    srand(time(NULL)+rand());
    while(us.size() < (n+m)) {
        float r = (rand()%100)*0.1;
        if(r<0)
            r = r*-1;
        auto inserted = us.insert(r);
        if(inserted.second == 1) {
            f.push_back(r);
        }
    }
    sort(f.begin(), f.end());
    vector<float> arrival;
    vector<float> deparcher;
    int index = 0;
    while (arrival.size() < n || deparcher.size() < m) {
        int decision = (rand()%2);
        if(decision == 1 && arrival.size() < n) {
            arrival.push_back(f[index++]);
        } else if(decision == 0 && deparcher.size() < m && deparcher.size() < arrival.size()){
            deparcher.push_back(f[index++]);
        }
    }
    return {arrival, deparcher};
}

void testSystem(int l, bool shouldPrintAD) {
    srand(time(0)+rand());
    for(int i=0;i<l;i++) {
        int n = rand()%15;
        int m = rand()%15;
        auto randomNum = n>m?getRandom(n, m):getRandom(m, n);
        vector<float> arrival = randomNum.first;
        vector<float> deparcher = randomNum.second;
        if(shouldPrintAD) {
            cout<<"arrival = ";
            for(auto &i: arrival) {
                cout<<i<<" ";
            }
            cout<<endl<<"deparcher = ";
            for(auto &i: deparcher) {
                cout<<i<<" ";
            }
            cout<<endl;
        }
        resultCalculator(arrival, deparcher);
    }
}

int main() {
    vector<float> arrival = {0.4, 1.6, 2.1, 3.8,4.0,5.6,5.8,7.2};
    vector<float> deparcher = {2.4,3.1,3.3,4.9,8.6};
    resultCalculator(arrival, deparcher);
    cout<<"Enter number of test case = ";
    int N;
    cin>>N;
    testSystem(N, true);
    return 0;
}
