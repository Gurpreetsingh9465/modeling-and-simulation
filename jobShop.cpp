#include<bits/stdc++.h>
using namespace std;

int cur_clock = 0;

class Job {
    public:
        int id;
        int total_time, time_left, waiting_time, arrival_time, deparcher_time;
        int cur_state;
        vector<pair<int,int>> sequence_machine;
        Job() {}
        bool init_job() {
            if(cur_state >= sequence_machine.size()) 
                return true;
            if(cur_state==0) {
                cur_state++;
                this->arrival_time = cur_clock;
            }
            this->time_left = sequence_machine[cur_state].second;
            return false;
        }
        int getMachineNumber() {
            if(cur_state == 0 || cur_state>=sequence_machine.size())
                return -1;
            return this->sequence_machine[this->cur_state].first;
        }
        void compute_stats(int id) {
            this->total_time += deparcher_time;
            cout<<"job id = "<<id<<" ";
            cout<<"Total time = "<<total_time<<" waiting time = "<<waiting_time<<"\n";
        }
        Job(vector<pair<int,int>> sequence_machine, int id) {
            total_time=0;
            this->sequence_machine = sequence_machine;
            time_left = 0;
            total_time = 0;
            waiting_time = 0;
            arrival_time = 0;
            deparcher_time = 0;
            cur_state = 0;
            this->id = id;
        }


};

class Machine {
    public:
        int cur_job;
        queue<int> job_queue;
        bool isIdle;
        int idle_time;
        int total_time;
        void print_stats(int id) {
            cout<<"MAchine id = "<<id<<" Idle Time = "<<idle_time<<" total_time"<<total_time<<"\n";
        }
        Machine() {
            cur_job = -1;
            isIdle = true;
            idle_time = 0;
            total_time = 0;
        }
        void insertJob(Job &j) {
            if(isIdle) {
                this->cur_job = j.id;
                j.waiting_time = 0;
                this->isIdle = false;
            } else {
                job_queue.push(j.id);
            }
            if(j.cur_state == 0)
                j.arrival_time = cur_clock;
        }

        void departJob(Job j[], int n) {
            j[cur_job].deparcher_time = cur_clock;
            j[cur_job].cur_state++;
            j[cur_job].total_time += (cur_clock-j[cur_job].arrival_time);
            if(job_queue.empty() == true) {
                this->isIdle = true;
                return;
            } else {
                this->cur_job = this->job_queue.front();
                j[cur_job].waiting_time += (cur_clock - j[cur_job].arrival_time);
                job_queue.pop();
            }
        }

        void printCurStats(int id) {
            cout<<"Machine number = "<<id<<" Working on Job = "<<cur_job<<" Current Queue Size = "<<job_queue.size()<<"\n";
        }

        bool run(Job j[], int n, int id) {
            if(this->isIdle){
                this->idle_time++;
                return false;
            } else {
                if(j[this->cur_job].time_left == 0) {
                    this->departJob(j,n);
                    return true;
                } else {
                    j[this->cur_job].time_left-=1;
                }
            }
            printCurStats(id);
            return false;
        }

};

void run(int n, int m, pair<int,int> **seq) {
    Job jobs[n+1];
    int jobs_completed = 0;
    Machine machines[m+1];
    for(int i=1;i<=n;i++) {
        vector<pair<int,int>> sequences(m+1);
        for(int j=1;j<=m;j++) {
            sequences[j] = seq[i][j];
        }
        jobs[i] = Job(sequences,i);
    }
    for(int i=1;i<=n;i++) {
        bool b = jobs[i].init_job();
        machines[jobs[i].getMachineNumber()].insertJob(jobs[i]);
    }
    while (jobs_completed != n) {
        _sleep(1000);
        for(int i=1;i<=m;i++) {
            bool ans = machines[i].run(jobs,n,i);
            if(ans == true) {
                int j = machines[i].cur_job;
                bool a = jobs[j].init_job();
                if(!a) {
                    machines[jobs[j].getMachineNumber()].insertJob(jobs[j]);
                }
                    
                if(a) {
                    jobs_completed++;
                }
            }
        }
        cout<<"======================================================================\n";
        cur_clock++;
    }
    cout<<"simulation completed\n";
    for(int j=1;j<=n;j++) {
        jobs[j].compute_stats(j);
    }
}

/*
6 3
1 2 2 3 3 4
2 3 1 2 3 1
1 2 3 1 2 1
3 1 2 1 1 1
3 5 2 4 1 2
1 2 2 1 3 1
*/

int main() {
    int n; // jobs;
    int m; // machines;

    cout<<"enter number of jobs and number of machines\n";
    cin>>n>>m;
    cout<<"Enter sequence of machine and time taken for each job eg 1 5 means machine 1 and time = 5 \n";
    pair<int,int> **seq = new pair<int,int>*[n+1];
    for(int i=1;i<=n;i++) {
        seq[i] = new pair<int,int>[m+1];
        for(int j=1;j<=m;j++) {
            int mach, time;
            cin>>mach>>time;
            seq[i][j] = {mach, time};
        }
    }
    run(n, m,seq);
    return 0;
}

