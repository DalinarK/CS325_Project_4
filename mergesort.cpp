#include <iostream>
#include <string>
#include <vector>
using std::cout;
int len;
//adapted from hackerrank.com
//Sorting in non decreasing order
void printArray(int arr[],int i,int j)
{
    for (int start=i; start<=j; start++)
        cout <<arr[start] << " ";
    cout<<"]";
}   


void merge(int arr[], int i, int mid, int j) {
        cout<<"left: [ ";
        printArray(arr,i,mid);
        cout<<" ";
        cout<<"Right: [ ";
        printArray(arr,mid+1,j);
        cout<<"\n";
        
        int temp[len];
        int l=i;
        int r=j;
        int m=mid+1;
        int k=l;
    
        while(l<=mid && m<=r)
        {
            if(arr[l]<=arr[m])
            {
                temp[k++]=arr[l++];
            }
            else
            {
                temp[k++]=arr[m++];
            
            
            }
        
        }
        while(l<=mid)
            temp[k++]=arr[l++];
        while(m<=r){
            temp[k++]=arr[m++];         
        }
        
        for(int i1=i;i1<=j;i1++){
            arr[i1]=temp[i1];
        }
        cout<<"After Merge: [";
        printArray(arr,i,j);
       cout<<"\n";
    
    }
    void mergesort(int arr[], int i, int j) {
        int mid=0;
        if(i<j)
        {
             mid=(i+j)/2;
             mergesort(arr,i,mid);
             mergesort(arr,mid+1,j);
             
             merge(arr,i,mid,j);    
             
        
        }
    
    }
int main()
{
    int arr[]={9,4,8,3,1,2,5};
    len=sizeof(arr)/sizeof(int);
    cout<<"Initial Array"<<" [ ";
    printArray(arr,0,len-1);
    cout<<"\n";
    
    mergesort(arr,0,len-1);
    return 0;
    
}