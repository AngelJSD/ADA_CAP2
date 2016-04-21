#include<iostream>

using namespace std;

void Heapify(int *A, int i,int n){

    int l=2*i;
    int r=2*i+1;
    int largest=i;
    if(l<n && A[l]>A[i])
        largest=l;
    if(r<n && A[r]>A[largest])
        largest=r;
    if(largest!=i){
        int aux=A[i];
        A[i]=A[largest];
        A[largest]=aux;
        Heapify(A,largest,n);
    }
}

void Build_Max_Heap(int *A, int n){

    for(int i=n/2; i>=0; --i)
        Heapify(A,i,n);
}

void Heapsort(int *A, int n){

    Build_Max_Heap(A, n);
    for(int i=n-1; i>=1; --i){

        int aux=A[0];
        A[0]=A[i];
        A[i]=aux;
        n-=1;
        Heapify(A,0,n);
    }

}

int main(){

    int A[10]={4,1,3,2,0,9,10,14,8,7};
    Heapsort(A,10);
    for(int i=0; i<10; ++i) cout<<A[i]<<",";
    return 0;
}
