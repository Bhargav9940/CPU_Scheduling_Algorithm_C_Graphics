#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
struct process {
    int id, at, bt, pr, ft, tat, wt, rt, flag;
};
    int fix = 18;//24; //distance on axis
    int y1 = 300, y2 = 340; //for Gantt chart
    char p; //for priority
void swap(struct process *x, struct process *y) {
    struct process temp = *x;
    *x = *y;
    *y = temp;
}
void sort_by_at(struct process ar1[], int n) {
        for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-1-i; j++) {
            if(ar1[j].at > ar1[j+1].at) {
                swap(&ar1[j+1], &ar1[j]);
            }
            else if(ar1[j].at == ar1[j+1].at) {
                if(ar1[j].id > ar1[j+1].id) {
                    swap(&ar1[j], &ar1[j+1]);
                }
            }
        }
    }
}
void sort_by_id(struct process ar1[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-1-i; j++) {
            if(ar1[j].id > ar1[j+1].id) {
                swap(&ar1[j+1], &ar1[j]);
            }
        }
    }
}
void tat_wt(struct process ar1[], int n) {
    for(int i=0; i<n; i++) {
        ar1[i].tat = ar1[i].ft - ar1[i].at;
        ar1[i].wt = ar1[i].tat - ar1[i].bt;
    }
}
void avg_print(struct process ar[], int n) {
    float totaltat = 0, totalwt = 0;
    for(int i=0; i<n; i++) {
        totaltat = totaltat + ar[i].tat;
        totalwt = totalwt + ar[i].wt;
    }
    float avgtat = totaltat/n;
    float avgwt = totalwt/n;
    printf("P\tAT\tBT\tFT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", ar[i].id, ar[i].at, ar[i].bt, ar[i].ft, ar[i].tat, ar[i].wt);
    }
    printf("\n");
    printf("Average TAT: %.2fms\n", avgtat);
    printf("Average WT: %.2fms\n", avgwt);
    char print_str[100];
    int xx1 = 46, yy1 = 34, xx2 = 330, yy2 = 34;
    if(p == 'y')
        xx2 += 50;
    line(xx1, yy1, xx2, yy2);         //table line
    line(xx1, yy1+28, xx2, yy2+28);    //table line
    strcpy(print_str, "P");
    outtextxy(50, 40, print_str);
    strcpy(print_str, "AT");
    outtextxy(100, 40, print_str);
    strcpy(print_str, "BT");
    outtextxy(150, 40, print_str);
    strcpy(print_str, "FT");
    outtextxy(200, 40, print_str);
    strcpy(print_str, "TAT");
    outtextxy(250, 40, print_str);
    strcpy(print_str, "WT");
    outtextxy(300, 40, print_str);
    if(p == 'y') {
        strcpy(print_str, "PR");
        outtextxy(350, 40, print_str);
    }
    int a = 50, b = 70;    //  x & y axis
    for(int i=0; i<n; i++) {
        sprintf(print_str, "P%d", ar[i].id);
        outtextxy(a, b, print_str);
        b += 25;
    }
    b = 70;
    a += 50;
    for(int i=0; i<n; i++) {
        sprintf(print_str, "%d", ar[i].at);
        outtextxy(a, b, print_str);
        b += 25;
    }
    b = 70;
    a += 50;
    for(int i=0; i<n; i++) {
        sprintf(print_str, "%d", ar[i].bt);
        outtextxy(a, b, print_str);
        b += 25;
    }
    b = 70;
    a += 50;
    for(int i=0; i<n; i++) {
        sprintf(print_str, "%d", ar[i].ft);
        outtextxy(a, b, print_str);
        b += 25;
    }
    b = 70;
    a += 50;
    for(int i=0; i<n; i++) {
        sprintf(print_str, "%d", ar[i].tat);
        outtextxy(a, b, print_str);
        b += 25;
    }
    b = 70;
    a += 50;
    for(int i=0; i<n; i++) {
        sprintf(print_str, "%d", ar[i].wt);
        outtextxy(a, b, print_str);
        b += 25;
    }
    int temp = 6;
    if(p == 'y') {
        b = 70;
        a += 50;
        temp = 7;
        for(int i=0; i<n; i++) {
            sprintf(print_str, "%d", ar[i].pr);
            outtextxy(a, b, print_str);
            b += 25;
        }
    }
    line(xx1, b+6, xx2, b+6);   //table line
    float x = (float)xx1;
    for(int i=0; i<temp; i++) {
        line(x, yy1, x, b+6);   //table parallel line
        x += 47.2;
    }
    x = x - 16;
    line(xx2, yy1, xx2, b+6);      //table parallel line
    b += 25;
    a = 50;
    sprintf(print_str, "Average Turn Around Time: %.2fms", avgtat);
    outtextxy(a, b, print_str);
    b += 20;
    sprintf(print_str, "Average Waiting Time: %.2fms", avgwt);
    outtextxy(a, b, print_str);
}
int time_overhead() {
    char q;
    int to = 0;
    getchar();
    printf("Time overhead require? (y/n): ");
    q = getchar();
    if(q == 'y') {
        getchar();
        printf("Enter Time Overhead: ");
        scanf("%d", &to);
    }
    return to;
}
void npz(int totalft, int non_time, int y1, int y2) {
    char strin[100];
    line((totalft*fix)+100, y1, (totalft*fix)+100, y2);
                sprintf(strin, "%d", totalft);
                outtextxy((totalft*fix)+100, y2+1, strin);
                strcpy(strin, "NP");
                outtextxy(((totalft-non_time)*fix)+100+2, (y1+y2)/2, strin); 
}
void pz_nonpreemptive(int totalft, int y1, int y2, struct process ar[], int i) {
    char strin[100];
    line((totalft*fix)+100, y1, (totalft*fix)+100, y2);
    sprintf(strin, "%d", totalft);
    outtextxy((totalft*fix)+100, y2+1, strin);  //time
    sprintf(strin, "P%d", ar[i].id);
    outtextxy(((totalft-ar[i].bt)*fix)+100+2, (y1+y2)/2, strin);  //((totalft*fix)+100)-((ar[i].bt*fix)-2)
}
void to_zone(int totalft, int to, int y1, int y2) {
    char strin[100];
    line((totalft*fix)+100, y1, (totalft*fix)+100, y2);
    sprintf(strin, "%d", totalft);
    outtextxy((totalft*fix)+100, y2+1, strin);
    strcpy(strin, "TO");
    outtextxy(((totalft-to)*fix)+100+2, (y1+y2)/2, strin);
}
void gantt_start_line(int totalft, int y1, int y2) {
    char strin[100];
    strcpy(strin, "Gantt Chart: ");
    outtextxy(100, y1-20, strin);
    line(100, y1, 100, y2);
    sprintf(strin, "%d", totalft);
    outtextxy(100, y2+2, strin);
}
void gantt_upper_line(int totalft, int y1, int y2) {
    line(100, y1, (totalft*fix)+100, y1);
    line(100, y2, (totalft*fix)+100, y2);
}
void fcfs(struct process ar[], int n) {
    char strin[]= "FCFS";   
    int to = time_overhead();
    int gd = DETECT, gm;
    char str[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, str);
    outtextxy(50, 10, strin);
    sort_by_at(ar, n);
    int totalft = 0;    //Calculation of ft
    gantt_start_line(totalft, y1, y2);
    for(int i=0; i<n; i++) { 
        if(ar[i].at > totalft) {
            int non_time = ar[i].at-totalft;
            totalft = totalft + non_time;  //Non-process Zone
            npz(totalft, non_time, y1, y2);
        }
        totalft = totalft + ar[i].bt;
        ar[i].ft = totalft;
            pz_nonpreemptive(totalft, y1, y2, ar, i);
        if(to != 0 && i != n-1) {
            totalft = totalft + to;
            to_zone(totalft, to, y1, y2);
        }
    }
    gantt_upper_line(totalft, y1, y2);
    sort_by_id(ar, n);
    tat_wt(ar, n);
    avg_print(ar, n);
    getch();
    closegraph();
}
void sjf(struct process ar[], int n) {
    char strin[]= "SJF";
    int to = time_overhead();
    int gd = DETECT, gm;
    char str[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, str);
    outtextxy(50, 10, strin);
    sort_by_at(ar, n);  
    int totalft = 0;
    gantt_start_line(totalft, y1, y2);
    int front = 0;
    for(int i=0; i<n; i++) {
        int min = front;
        for(int j=front; j<n; j++) {    //to find minimum
            if(ar[j].bt < ar[min].bt && ar[j].at <= totalft) {
                swap(&ar[min], &ar[j]);
            }
            else if(ar[j].bt == ar[min].bt && ar[j].at <= totalft) {   //if bt same
                if(ar[j].at < ar[min].at) {
                    swap(&ar[min], &ar[j]);
                }
                else if(ar[j].at == ar[min].at) {   //if at is also same
                    if(ar[j].id < ar[min].id) {
                        swap(&ar[min], &ar[j]);
                    }
                }
            }
        }
        if(ar[min].at > totalft) { 
            int non_time = ar[min].at-totalft;                    
            totalft = totalft + non_time;  //Non-process Zone
            npz(totalft, non_time, y1, y2);
        }
        totalft = totalft + ar[min].bt;  
        ar[min].ft = totalft;
            pz_nonpreemptive(totalft, y1, y2, ar, min);
        if(to != 0 && i != n-1) {
            totalft = totalft + to;        //time overhead
            to_zone(totalft, to, y1, y2);
        } 
        front++;
    }
    gantt_upper_line(totalft, y1, y2);
    sort_by_id(ar, n);   
    tat_wt(ar, n);
    avg_print(ar, n);
    getch();
    closegraph();
}
void pz_preemptive(int totalft, int lasttotalft, int y1, int y2, struct process ar[], int i) {
    char strinn[100];
    line((totalft*fix)+100, y1, (totalft*fix)+100, y2);
    sprintf(strinn, "%d", totalft);
    outtextxy((totalft*fix)+100, y2+1, strinn);  //time
    sprintf(strinn, "P%d", ar[i].id);  //i=min
    outtextxy((lasttotalft*fix)+100+2, (y1+y2)/2, strinn); 
}
void srtn(struct process ar[], int n) {
    char strin[]= "SRTN";
    int to = time_overhead();
    int gd = DETECT, gm;
    char str[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, str);
    outtextxy(50, 10, strin);
    sort_by_at(ar, n);
    int totalft = 0;
    gantt_start_line(totalft, y1, y2);
    int totalbt = 0;
    for(int i=0; i<n; i++) {
        totalbt = totalbt + ar[i].bt;
    }
    for(int i=0; i<n; i++) {    //copying bt to rt
        ar[i].rt = ar[i].bt;
    }
    int front = 0;        //ft
    int min = front;
    int prior_id = ar[min].id;
    int lasttotalft = totalft;
    for(int i=0; i<totalbt; i++) {
        min = front;
        for(int j=front; j<n; j++) {    //to find minimum
            if(ar[j].rt < ar[min].rt && ar[j].at <= totalft) {
                swap(&ar[j], &ar[min]);
            }
            else if(ar[j].rt == ar[min].rt && ar[j].at <= totalft) {   //if bt same
                if(ar[j].at < ar[min].at) {
                    swap(&ar[j], &ar[min]);
                }
                else if(ar[j].at == ar[min].at) {   //if at is also same
                    if(ar[j].id < ar[min].id) {
                        swap(&ar[j], &ar[min]);
                    }
                }
            }
        }
        if(ar[min].id != prior_id) {  //process switches
            int w, flag = 0;
                for(w=front; w<n; w++) {
                    if(prior_id == ar[w].id && ar[w].rt != 0) {
                        flag = 1;
                        break;
                    }
                }
            if (flag == 1) {
                pz_preemptive(totalft, lasttotalft, y1, y2, ar, w);
            }
            if(to != 0) {
                totalft = totalft + to;     //time overhead
                to_zone(totalft, to, y1, y2);
            }
            lasttotalft = totalft;
        }
        if(ar[min].at > totalft) {                            //perfact 
            int non_time = ar[min].at-totalft;
            totalft = totalft + non_time;  //Non-process Zone
            npz(totalft, non_time, y1, y2);
            lasttotalft = totalft;
        }
        totalft = totalft + 1;  
        ar[min].rt -= 1;
        prior_id = ar[min].id;  //--
        if(ar[min].rt == 0) {
            ar[min].ft = totalft;
            pz_preemptive(totalft, lasttotalft, y1, y2, ar, min);
            front++;
        }
    }
    gantt_upper_line(totalft, y1, y2);
    sort_by_id(ar, n);
    tat_wt(ar, n);
    avg_print(ar, n);
    getch();
    closegraph();
}
void priority_nonpreemptive(struct process ar[], int n) {
    //considering 1 (minimum) as the highest priority
    char strin[]= "Priority Nonpreemptive: ";
    int to = time_overhead();
    int gd = DETECT, gm;
    char str[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, str);
    outtextxy(50, 10, strin);
    sort_by_at(ar, n);     
    int totalft = 0;   //ft
    gantt_start_line(totalft, y1, y2);
    int front = 0;
    for(int i=0; i<n; i++) {
        int min = front;
        for(int j=front; j<n; j++) {    //to find minimum
            if(ar[j].pr < ar[min].pr && ar[j].at <= totalft) {
                swap(&ar[j], &ar[min]);
            }
            else if(ar[j].pr == ar[min].pr && ar[j].at <= totalft) {   //if bt same
                if(ar[j].at < ar[min].at) {
                    swap(&ar[j], &ar[min]);
                }
                else if(ar[j].at == ar[min].at) {   //if at is also same
                    if(ar[j].id < ar[min].id) {
                        swap(&ar[j], &ar[min]);
                    }
                }
            }
        }
        if(ar[min].at > totalft) {                            //perfact 
            int non_time = ar[i].at-totalft;
            totalft = totalft + non_time;  //Non-process Zone
            npz(totalft, non_time, y1, y2);
        }
        totalft = totalft + ar[min].bt;  
            pz_nonpreemptive(totalft, y1, y2, ar, min);
        ar[min].ft = totalft;
        if(to != 0 && i != n-1) {
            totalft = totalft + to;        //time overhead
            to_zone(totalft, to, y1, y2);
        }
        front++;
    }
    gantt_upper_line(totalft, y1, y2);
    sort_by_id(ar, n);
    tat_wt(ar, n);
    avg_print(ar, n);
    getch();
    closegraph();
}
void priority_preemptive(struct process ar[], int n) {
    //Considering 1 (minimum) as the highest priority
    char strin[]= "Priority Preemptive: ";
    int to = time_overhead();
    int gd = DETECT, gm;
    char str[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, str);
    outtextxy(50, 10, strin);
    sort_by_at(ar, n); 
    int totalft = 0;
    int totalbt = 0;
    gantt_start_line(totalft, y1, y2);
    for(int i=0; i<n; i++) {
        totalbt = totalbt + ar[i].bt;
    }
    //copying bt to rt
    for(int i=0; i<n; i++) {
        ar[i].rt = ar[i].bt;
    }
    //ft
    int front = 0;
    int min = front;
    int prior_id = ar[min].id;
    int lasttotalft = totalft;
    for(int i=0; i<totalbt; i++) {
        min = front;
        for(int j=front; j<n; j++) {    //to find minimum
            if(ar[j].pr < ar[min].pr && ar[j].at <= totalft) {
                swap(&ar[j], &ar[min]);
            }
            else if(ar[j].pr == ar[min].pr && ar[j].at <= totalft) {   //if bt same
                if(ar[j].at < ar[min].at) {
                    swap(&ar[j], &ar[min]);
                }
                else if(ar[j].at == ar[min].at) {   //if at is also same
                    if(ar[j].id < ar[min].id) {
                        swap(&ar[j], &ar[min]);
                    }
                }
            }
        }
        if(ar[min].id != prior_id) {  //process switches
            int w, flag = 0;
                for(w=front; w<n; w++) {
                    if(prior_id == ar[w].id && ar[w].rt != 0) {
                        flag = 1;
                        break;
                    }
                }
            if (flag == 1) {
                pz_preemptive(totalft, lasttotalft, y1, y2, ar, w);
            }
            if(to != 0) {
                totalft = totalft + to;     //time overhead
                to_zone(totalft, to, y1, y2);
            }
            lasttotalft = totalft;
        } 
        if(ar[min].at > totalft) {     
            int non_time = ar[i].at-totalft;
            totalft = totalft + (ar[min].at - totalft);  //Non-process Zone
            npz(totalft, non_time, y1, y2);
            lasttotalft = totalft;     //changed
        }
        totalft = totalft + 1;  
        ar[min].rt -= 1;
        prior_id = ar[min].id;  //--
        if(ar[min].rt == 0) {
            ar[min].ft = totalft;
            pz_preemptive(totalft, lasttotalft, y1, y2, ar, min);
            front++;
        }
    }
    gantt_upper_line(totalft, y1, y2);
    sort_by_id(ar, n);
    tat_wt(ar, n);
    avg_print(ar, n);
    getch();
    closegraph();
}
void round_robin(struct process ar[], int n) {
    char strin[]= "Round Robin: ";
    int tq = 0;
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    int to = time_overhead();
    int gd = DETECT, gm;
    char str[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, str);
    outtextxy(50, 10, strin);
    sort_by_at(ar, n);     
    int totalft = 0, totalbt = 0, totalrt = 0;
    for(int i=0; i<n; i++) {
        totalbt = totalbt + ar[i].bt;
    }
    totalrt = totalbt;
    gantt_start_line(totalft, y1, y2);
    //copying bt to rt
    for(int i=0; i<n; i++) {
        ar[i].rt = ar[i].bt;
    }
    int k = 0;  
    int totalflag = n;
    int flag;
    int lasttotalft = totalft;
    while(totalflag != 0) {
        if(ar[k].at > totalft) {
            int non_time = ar[k].at-totalft;
            totalft = totalft + non_time; //no process zone
            npz(totalft, non_time, y1, y2);
        }
        if(totalflag == 1) {    //for last remaining process
            lasttotalft = totalft;
            totalft = totalft + ar[k].rt;
            ar[k].ft = totalft;
            ar[k].rt = 0;
            pz_preemptive(totalft, lasttotalft, y1, y2, ar, k);
            flag = 1;
        }
        else if(ar[k].rt <= tq && ar[k].rt > 0) {
            lasttotalft = totalft;
            totalft = totalft + ar[k].rt;
            ar[k].ft = totalft;
            ar[k].rt = 0;
            pz_preemptive(totalft, lasttotalft, y1, y2, ar, k);
            flag = 1;
            if(to != 0) {
                totalft = totalft + to;     //time overhead
                to_zone(totalft, to, y1, y2);
            }
        }
        else if(ar[k].rt > 0) {
            lasttotalft = totalft;
            totalft = totalft + tq;
            ar[k].ft = totalft;
            ar[k].rt = ar[k].rt - tq;
            pz_preemptive(totalft, lasttotalft, y1, y2, ar, k);
            if(to != 0) {
                totalft = totalft + to;     //time overhead
                to_zone(totalft, to, y1, y2);
            }
        }
        if(ar[k].rt == 0 && flag == 1) {
            totalflag--;
            flag = 0;
        }
        if(k == n-1)
            k = 0;
        else if(ar[k+1].at <= totalft) {
            k++;
        }
        else 
            k = 0;
    }
    gantt_upper_line(totalft, y1, y2);
    sort_by_id(ar, n);
    tat_wt(ar, n);
    avg_print(ar, n);
    getch();
    closegraph();
}
int main() {
    int n;
    printf("Enter no. of process: ");
    scanf("%d", &n);
    struct process pr[n];
    int countid = 1;
    for(int i=0; i<n; i++) {
        printf("Enter Arrival Time for P%d: ", i+1);
        scanf("%d", &pr[i].at);
        pr[i].id = countid++;
    }
    for(int i=0; i<n; i++) {
        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &pr[i].bt);
    }
    getchar();
    printf("Priority require? (y/n): ");
    scanf("%c", &p);
    if(p == 'y') {
        for(int i=0; i<n; i++) {
            printf("Enter priority for P%d: ", pr[i].id);
            scanf("%d", &pr[i].pr);
        }
    }
    printf("\nSelect Algorithm to apply: \n");
    int option;
    while(1) {
        printf("Enter 1 for FCFS.\n");
        printf("Enter 2 for SJF.\n");
        printf("Enter 3 for SRTN.\n");
        printf("Enter 4 for Priority(Non-preemptive).\n");
        printf("Enter 5 for Priority(Preemptive).\n");
        printf("Enter 6 for Round Robin.\n");
        printf("Enter 7 for exit.\n");
        printf("Enter option: ");
        scanf("%d", &option);
        switch(option) {
            case 1: fcfs(pr, n);
            break;
            case 2: sjf(pr, n);
            break;
            case 3: srtn(pr, n);
            break;
            case 4: priority_nonpreemptive(pr, n);
            break;
            case 5: priority_preemptive(pr, n);
            break;
            case 6: round_robin(pr, n);
            break;
            case 7: exit(0);
            break;
        }
    }
}