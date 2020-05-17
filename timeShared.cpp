#include<bits/stdc++.h>
using namespace std;

class Job {
    public:
        double arrivalTime;
        double serviceTime;
        int terminal;
        Job() {
            arrivalTime = 0.0;
            serviceTime = 0.0;
            terminal = 0;
        }
        Job(int terminal, double arrivalTime, double serviceTime) {
            this->terminal = terminal;
            this->arrivalTime = arrivalTime;
            this->serviceTime = serviceTime;
        }
};

const int TERMINALS = 80;
const int JOBS = 1000;
const double Q = 3;
const double SWAP_TIME = 0;
double *thinkTimes = new double[TERMINALS];
bool *terminalFree = new bool[TERMINALS];

double findMinThinkTime()
{
    double min = 100000000.0;
    for (int i = 0; i < TERMINALS; i++)
    {
        if (terminalFree[i] && thinkTimes[i] < min)
            min = thinkTimes[i];
    }
    return min;
}
int main()
{
    srand(time(0));
    vector<Job> queue;
    int jobsDone = 0;
    double elapsedTime = 0;
    double utilization = 0.0;
    double lastFree = 0.0;   
    double queueArea = 0.0;  
    bool isCPUidle = true;   
    double responseTime = 0.0;
    double queueTime = 0.0;   
    double lastQueueTime = 0.0;
    for (int i = 0; i < TERMINALS; i++)
    {
        thinkTimes[i] = ((rand() % (10 - 1 + 1)) + 1);
        terminalFree[i] = true;
    }
    cout << "The think times generated are:\n";
    for (int i = 0; i < TERMINALS; i++)
        cout << thinkTimes[i] << " ";
    cout << "\n";
    while (jobsDone < JOBS)
    {
        int minThinkTime = findMinThinkTime();
        if (elapsedTime < minThinkTime) {
        
        } else {
            int queueSizeBefore = queue.size();
            for (int i = 0; i < TERMINALS; i++) {
                if (terminalFree[i] && thinkTimes[i] == minThinkTime) {
                    Job job(i, elapsedTime, (double)(rand() % (30 - 1 + 1) + 1));
                    queue.push_back(job);
                    terminalFree[i] = false;
                }
            }
            int queueSizeAfter = queue.size();
            if (queueSizeAfter == queueSizeBefore) {
            } else {
                queueTime = (elapsedTime - 1) + minThinkTime;
                queueArea += (double)(queueSizeBefore * (queueTime - lastQueueTime));
                lastQueueTime = queueTime;
            }
            if (isCPUidle)
            {
                isCPUidle = false;
                utilization += elapsedTime - lastFree;
            }
        }
        elapsedTime += 1;  
        Job nextJob(-1, -1, -1);
        if (queue.size() > 0) {
            nextJob = queue.at(0);
            queue.erase(queue.begin());
            double cpuTime = min(Q, nextJob.serviceTime);
            nextJob.serviceTime -= cpuTime;

            elapsedTime += (cpuTime + SWAP_TIME);
        } else {
            isCPUidle = true;
            lastFree = elapsedTime;
        }
        if (nextJob.serviceTime > 0) {
            queue.push_back(nextJob);
            elapsedTime += 1;
        } else if (nextJob.serviceTime != -1) {
            terminalFree[nextJob.terminal] = true;
            jobsDone += 1;
            responseTime += (elapsedTime - nextJob.arrivalTime);
            queueArea += ((queue.size() + 1) * (elapsedTime - lastQueueTime));
            lastQueueTime = elapsedTime;
            elapsedTime += 1;
        }
    }
    utilization += elapsedTime - lastFree;
    cout << "The utilization of CPU is: " << (utilization / elapsedTime) * 100 << "%\n";
    cout << "Average response time per job is: " << (responseTime / JOBS) << " units of time.\n";
    cout << "Average queue length: " << (queueArea / queueTime) << " processes.\n";
    return 0;
}
