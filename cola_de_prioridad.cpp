#include<iostream>
#include<vector>

using namespace std;

void Heapify(vector<int> &A, int i,int n){

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

void Build_Max_Heap(vector<int> A, int n){

    for(int i=n/2; i>=0; --i)
        Heapify(A,i,n);
}



int Heap_Maximum(vector<int> A) {return A[0];}

int Heap_Extract_Max(vector<int> &A, int n){

    if(A[n]<0) cout<<"error";
    int maximo=A[0];
    A[0]=A[n-1];
    A.erase(A.begin());
    --n;
    Heapify(A,0,n);
    return maximo;
}

void Heap_Increase_Key(vector<int> &A, int i, int key){

    if(key<A[i]) cout<<"new key is smaller than current key"<<endl;
    A[i]=key;for(int i=0; i<A.size(); ++i) cout<<A[i]<<",";
    cout<<endl;
    while (i>0 && A[i/2]<A[i]){

        int aux = A[i];
        A[i]=A[i/2];
        A[i/2]=aux;
        i=i/2;
    }
}

void Max_heap_insert(vector<int> &A, int key, int n){

    n++;
    A.push_back(-1);
    Heap_Increase_Key(A,n-1,key);

}

int main(){

    vector<int> A;
    Max_heap_insert(A,30,A.size());
    for(int i=0; i<A.size(); ++i) cout<<A[i]<<",";
    cout<<endl;
    Max_heap_insert(A,15,A.size());
    for(int i=0; i<A.size(); ++i) cout<<A[i]<<",";
    cout<<endl;
    Max_heap_insert(A,3,A.size());
    for(int i=0; i<A.size(); ++i) cout<<A[i]<<",";
    cout<<endl;
    Max_heap_insert(A,12,A.size());
    for(int i=0; i<A.size(); ++i) cout<<A[i]<<",";
    cout<<endl;
    Heap_Extract_Max(A, A.size());
    for(int i=0; i<A.size(); ++i) cout<<A[i]<<",";
    cout<<endl;
    return 0;
}
