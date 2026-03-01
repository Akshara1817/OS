#include <stdio.h>
void bin_search(int arr[],int l,int ele);
void lin_search(int arr[],int l,int ele);
int found;
int main(){
    int arr[]={1,2,3,4,5};
    lin_search(arr,5,2);
    bin_search(arr,5,3);
    return 0;
}

void lin_search(int arr[],int l,int ele){
    for(int i=0;i<l;i++){
            if(arr[i]==ele){
                found =1;
                printf("ele %d",ele);
                break;
            }
    }
    if(found==0){
        printf("not found");
    }
}
void bin_search(int arr[],int l,int ele){
    int mid=l/2;
    int start=0;
    int end=l-1;
    while(start!=end){
        mid=(start+end)/2;

        if(arr[mid]==ele){
            found =2;
            printf("\n found %d",ele);
            break;
        }
        else if(ele<arr[mid]){
            end=mid-1;
        }
        else if(ele>arr[mid]){}
        start=mid+1;
    }
    if(found!=2){
        printf("could not find");
    }

}
