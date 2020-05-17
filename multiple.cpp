#include<bits/stdc++.h>
using namespace std;

void check(vector<int> &q, int curTime, int &maximum, int pos){
	if(!q.size()) return;
	int poped = 0;
	for(int i = 0; i <= q.size(); i++){
		if(q[i] <= curTime){
			q.erase(q.begin());
			poped = 1;
			cout<<"Exit at "<<pos<<endl;
		}else{
			break;
		}
	}
	
	if(poped && q.size()){
		q.front() = q.front() + curTime;
	}
	maximum = max(maximum, (int)q.size());
}

void manage(vector<int> &left, vector<int> &right){
	if(abs((int)left.size() - (int)right.size()) <= 1) return;
	if(left.size() > right.size()){
		int k = left.back();
		left.pop_back();
		right.push_back(k);
	}else{
		int k = right.back();
		right.pop_back();
		left.push_back(k);
	}
	manage(left, right);
}

int main(){
	int n = 10;
	int maximum = 0;
	int enter[] = {1,3,4,3, 5, 1, 2, 6,7, 8};
	int time[] = {8, 2, 3, 1, 4, 2, 1, 3, 4,1};
	int numberOfQueues = 4;
	vector<int> q[4];
	vector<pair<int, int>> p;
	for(int i = 0; i < 10; i++){
		p.push_back({enter[i], time[i]});
	}
	
	sort(p.begin(), p.end(), [](pair<int, int> &p1, pair<int, int> &p2){
		return p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second);
	});
	
	int index = 0;
	for(int i = p[0].first; i <= 30 && index < n; i++){
		for(int j = 0; j < numberOfQueues; j++){
			check(q[j], i, maximum,j);
			if(j < numberOfQueues-1) manage(q[j], q[j+1]);
		}
		
		
		if(p[index].first > i) continue;
		
		int minLenQ = 0;
		for(int i = 1; i < numberOfQueues; i++){
			if(q[i].size() < q[minLenQ].size()){
				minLenQ = i;
			}
		}
		
		q[minLenQ].push_back(p[index].second);
		cout<<"At time : "<<i<<endl;
		cout<<1<<"   "<<2<<"   "<<3<<"   "<<4<<endl;
		for(int j = 0; j <= maximum; j++){
			for(int i = 0; i < numberOfQueues; i++){
				if(j >= q[i].size()){
					cout<<"   ";
				}else{
					cout<<"1 "<<"  ";
				}
			}
			cout<<endl;
		}
		int ll;
		cout<<"Press any number to continue : ";
		cin>>ll;
		index++;
	}
}
