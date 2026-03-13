#include <stdio.h>
struct Process{
    int id, at, bt, pri, ct, wt, tat,rt;
};
int main(){
    int n;
    printf("\nenter no of process: ");
    scanf("%d",&n);
    struct Process p[n];
    for(int i=0;i<n;i++){
            p[i].id=i+1;
            printf("enter at bt and priority of P%d ",p[i].id);
            scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].pri);
            p[i].rt=p[i].bt;

    }
    int currt=0;
    int completed=0;
    int pri_max;
    int idx;
    while(completed<n){
        pri_max=1000;
        idx=-1;
        for(int i=0;i<n;i++){
            if((p[i].at<=currt)&&(p[i].rt>0)){
                if(p[i].pri<pri_max){
                    pri_max=p[i].pri;
                    idx=i;
                }

            }
        }
        if(idx==-1){
            currt++;
        }else{
            p[idx].rt=p[idx].rt-1;
            currt++;
            if(p[idx].rt==0){
                p[idx].ct=currt;
                p[idx].tat=p[idx].ct-p[idx].at;
                p[idx].wt=p[idx].tat-p[idx].bt;
                completed++;
            }
        }
    }
    printf("\nPID\tAT\tBT\tPri\tCT\tWT\tTAT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].wt, p[i].tat);
    }
    int sumtat=0;
    int sumwt=0;
    for(int i=0;i<n;i++){
        sumtat+=p[i].tat;
        sumwt+=p[i].wt;
    }
    printf("\n avg tat %.2f",(float)sumtat/(float)n);
    printf("\n avg tat %.2f",(float)sumwt/(float)n);
    printf("\n1BM24CS028");
    return 0;

}
