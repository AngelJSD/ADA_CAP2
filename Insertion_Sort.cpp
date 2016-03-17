#include <iostream>

using namespace std;

void insertion_sort(int n, int* a){

    int key;
    for(int i=1; i<n; ++i){

        key=a[i];
        int j=i-1;
        while(j>-1 && a[j]>key){
            a[j+1]=a[j];
            --j;
        }
        a[j+1]=key;
    }

    return;
}


int main(){

    int n;
    cout<<"Ingrese el numero de elementos: ";
    cin>>n;
    int a[n];
    cout<<"Ingrese los "<<n<<" elementos: "<<endl;
    for(int i=0; i<n; ++i) cin>>a[i];

    cout<<endl;
    cout<<endl;
    insertion_sort(n,a);
    for(int i=0; i<n; ++i) cout<<a[i]<<",";
    cout<<endl;
    return 0;
}
