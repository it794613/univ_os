#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h>
using namespace std;

typedef struct scheduler{
	string process_id;
	int at;         /*at=arrivetime*/
    int cur_bt=0;   //현재 프로세스 bt기억
	int bt;         /*bt=bursttime*/
	int wt = 0;     /*wt=waitingtime*/
	int tat;         /*tt=turnaround time*/
	int priority;
    int rr = 0;
    int response;   //response time=cur_cuptime-at
    }   scheduler;

bool compare(scheduler a, scheduler b) {
    return a.at < b.at;
}

bool compare2(scheduler h,scheduler k) {
    return h.bt < k.bt;
}

int main(){
    int cputime = 0;
    int timecheck = 0;
    int rrtime;
    scheduler process[10];      //job queue
    vector<scheduler> rq(0);    //ready queue
    vector<scheduler> rtq(0);   //result queue
    scheduler temp;
    int process_numb;
    int cur_pro = 0;
    float avg_wt = 0;
    float avg_rp = 0; //average response time 
	cout << "process number : ";
	cin >> process_numb;
    cout << "enter : rrtime : ";
    cin >> rrtime;
	cout << "enter : id, arrivetime, bursttime : ";

    for(int a=0;a<process_numb;a++) {
        cin >> process[a].process_id;
        cin >> process[a].at;
        cin >> process[a].bt;
        process[a].cur_bt=process[a].bt;
    }
    int cur_rr = 0; 
    while(rtq.size() != process_numb){
        for(int b = 0 ; b < process_numb ; b++) {
            if(process[b].at == cputime) {
                rq.push_back(process[b]);
            }
        }
        if(rq[0].cur_bt == 0) {
            rq[0].response=cputime-rq[0].at;
            rtq.push_back(rq[0]);
            rq.erase(rq.begin());
            cur_rr = 0; 
        } else {
            if(cur_rr == rrtime){
                cur_rr = 0;
                temp = rq[0];
                rq.push_back(temp);
                rq.erase(rq.begin());
            }
        }
        rq[0].cur_bt--;
        
        for(int c = 1 ; c < rq.size() ; c++) {
            rq[c].wt++;
        }
        cur_rr++;
        cputime++;
    }
        for(int y=0;y<process_numb;y++){
        rtq[y].tat = rtq[y].bt + rtq[y].wt;
    }
    for(int d=0;d<process_numb;d++) {
        avg_wt += rtq[d].wt;
        avg_rp += rtq[d].response;
        
    }
    avg_rp = avg_rp / float(process_numb);
    avg_wt = avg_wt / float(process_numb);
    cout << "id" << "\t" << "at" << "\t" << "bt" << "\t" << "wt" << "\t" << "response" << "\t" << "tat" << endl;
    for(int e = 0 ; e < process_numb ; e++) {
	    cout << rtq[e].process_id << '\t' \
             << rtq[e].at         << '\t' \
             << rtq[e].bt         << '\t' \
             << rtq[e].wt         << '\t' \
             << rtq[e].response   << '\t' \
             << "\t" << rtq[e].tat<< endl;
    }
    cout << "average wating time : " << avg_wt << endl;
    cout << "average response time : " << avg_rp << endl;
    cout << "cputime : " << cputime - 1 << endl;
}
