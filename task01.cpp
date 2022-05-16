#include<iostream>
#include<fstream>
#include "string.h"
using namespace std;

int total_events=0;

class Event {
    public:
    string event_name;
    int start_time, duration, end_time;
};

void min_duration(Event &e1 , Event &e2){
    if(e1.duration>e2.duration){
        Event temp;
        temp=e2;
        e2=e1;
        e1=temp;
    }
}

void lister(Event*sheet){
    for(int i=0 ; i<total_events-1 ; i++){
        for(int j=0;j<total_events-1;j++){
            if(sheet[j].start_time > sheet[j+1].start_time){
            Event temp;
            temp=sheet[j+1];
            sheet[j+1]=sheet[j];
            sheet[j]=temp;
            }
            else if(sheet[j].start_time == sheet[j+1].start_time){
                min_duration(sheet[j],sheet[j+1]);
            }
        }
    }

}
int scheduler(Event*timetable){
    lister(timetable);
    int events_counter[total_events];
    for(int i=0 ; i<total_events;i++){
        events_counter[i]=1;
    }
    for(int i=0;i<total_events;i++){
        Event new_start;
        new_start=timetable[i];
        for(int j=0;j<total_events;j++){
            bool decider=true;
            if(new_start.end_time==timetable[j].start_time){
                for(int k=0; k<total_events ; k++){
                    if(timetable[j].start_time<timetable[k].start_time && timetable[j].end_time>timetable[k].end_time ){
                        events_counter[i]++;
                        new_start=timetable[k];
                        decider=false;
                        break;
                    }
                }
                if(decider){
                    events_counter[i]++;
                    new_start=timetable[j];
                }
            }
            
            else if(1+new_start.end_time==timetable[j].start_time){
                for(int k=0; k<total_events ; k++){
                    if(timetable[j].start_time<timetable[k].start_time && timetable[j].end_time>timetable[k].end_time ){
                        events_counter[i]++;
                        new_start=timetable[k];
                        decider=false;
                        break;
                    }
                }
                if(decider){
                    events_counter[i]++;
                    new_start=timetable[j];
                }
            }
            
            else if(2+new_start.end_time==timetable[j].start_time){
                for(int k=0; k<total_events ; k++){
                    if(timetable[j].start_time<timetable[k].start_time && timetable[j].end_time>timetable[k].end_time ){
                        events_counter[i]++;
                        new_start=timetable[k];
                        decider=false;
                        break;
                    }
                }
                if(decider){
                    events_counter[i]++;
                    new_start=timetable[j];
                }
            }
        }
    }
    int max=events_counter[0];
    for(int i=1 ; i<total_events; i++){
        if(max<events_counter[i]){
            max=events_counter[i];
        }
    }
    return max;
};
int main(int argc , char**argv){
    Event *sessions;
    ifstream events_list;
    events_list.open(argv[1]);
    string event_name;
    int start_time, duration;
    while(events_list>>event_name>>start_time>>duration){
        total_events++;
    }
    events_list.close();
    events_list.open(argv[1]);
    sessions= new Event[total_events];
    for(int i=0; events_list>>event_name>>start_time>>duration && i<total_events;i++ ){
        sessions[i].event_name = event_name;
        sessions[i].start_time = start_time;
        sessions[i].duration   = duration;
        sessions[i].end_time   = sessions[i].start_time+sessions[i].duration;
        if(sessions[i].end_time>=24){
            sessions[i].end_time-=24;
        }
    }
    events_list.close();
    int at_max;
    at_max=scheduler(sessions);
    cout<<at_max<<endl;
    delete[] sessions;
}