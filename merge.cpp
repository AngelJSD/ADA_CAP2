#include <iostream>
#include <math.h>

#define MAX 1000000

using namespace std;

void my_merge(int *A,int p ,int q,int r){

    //cout<<"Recibo "<<p<<" "<<q<<" "<<r<<endl;
    int n1=q-p+1;
    int n2=r-q;
    int L[n1+1], R[n2+1];
    //cout<<"L: ";
    for(int i=0; i<n1; ++i)
        L[i]=A[p+i];
    //for(int i=0; i<n1; ++i) cout<<L[i]<<",";
    //cout<<endl;
    //cout<<"R: ";
    for(int j=0; j<=n2; ++j)
        R[j]=A[q+j+1];
    //for(int i=0; i<n2; ++i) cout<<R[i]<<",";
    //cout<<endl;
    L[n1]=MAX;
    R[n2]=MAX;
    int i=0;
    int j=0;
    for(int k=p; k<=r; ++k){

        if(L[i]<=R[j]){

            A[k]=L[i];
            ++i;
        }
        else{

            A[k]=R[j];
            ++j;
        }
    }

}

void merge_sort(int *A,int p,int r){

    if(p<r){

        int q=floor((p+r)/2);
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        my_merge(A,p,q,r);
    }

}

int main(){

    int n;
    cout<<"N de elementos: ";
    cin>>n;
    cout<<"Elementos: ";
    int A[n];
    for(int i=0; i<n; ++i) cin>>A[i];
    for(int i=0; i<n; ++i) cout<<A[i]<<",";
    cout<<endl;
    merge_sort(A,0,n-1);
    cout<<endl;
    for(int i=0; i<n; ++i) cout<<A[i]<<",";
    cout<<endl;

    return 0;

}

