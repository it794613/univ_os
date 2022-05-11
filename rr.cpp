#include <iostream>
#include <algorithm>
using namespace std;

typedef struct scheduler{
	string process_id;
	int at; /*at=arrivetime*/
	int bt; /*bt=bursttime*/
	int wt = 0; /*wt=waitingtime*/
	int tt; /*tt=turnaround time*/
	int priority;
}scheduler;



bool compare(scheduler a, scheduler b){
    return a.at<b.at;
}

int main(){
    int cputime=0;
    int timecheck=0;
    scheduler process[10];
    int process_numb;
    int cur_pro=0;
    int timeslice = 0;
	cout<<"process number : ";
	cin>>process_numb;
	cout<<"enter : id, arrivetime, bursttime : "<<endl;
    for(int a=0;a<process_numb;a++){
            cin>>process[a].process_id;
            cin>>process[a].at;
            cin>>process[a].bt;
            }
    cout<<"enter : timeslice : ";
    cin>>timeslice;
    sort(process, process+process_numb,compare);
    while(1){
        if(cur_pro!=process_numb){
            if(timecheck==timeslice){
                cur_pro++;
                timecheck=0;
            }
            else{
                for(int z=cur_pro+1;z<process_numb;z++){
                    process[z].wt++;
                }
            timecheck++;
            cputime++;
            }
        }
        else{break;}
    }
    for(int a=0;a<process_numb;a++){
        process[a].wt-=process[a].at;
    }
    for(int v=0;v<process_numb;v++){
	cout<<process[v].process_id<<"\t"<<process[v].at<<"\t"<<process[v].bt<<"\t"<<process[v].wt<<endl;
	}
    cout<<cputime<<endl;
}