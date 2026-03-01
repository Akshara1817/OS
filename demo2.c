#include<stdio.h>
int main(){
    int arr[]={1,2,3,4,5,-1};
    int smallest=arr[0];
    int spos=0;

    for(int i=0;i<6;i++){
        if(arr[i]<smallest){
            spos=i;
            smallest=arr[i];
        }
    }
    printf("%d is smallest at %d",smallest,spos);
    return 0;
}
