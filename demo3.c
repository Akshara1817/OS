#include <stdio.h>
int main(){
    int arr[]={1,2,3,4,4,5,6,7};
    int len=8;
    int flag=0;
    for(int i=0;i<len;i++){
        for(int j=i;j<len;j++){
                    if(arr[i]==arr[j]){}
                        flag=1;
                        break;
        }
    }
    if(flag==0){
        printf("no duplicates");
    }else{
        printf("duplicates found");
    }
    return 0;
}
