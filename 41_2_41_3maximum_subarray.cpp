#include <iostream>

using namespace std;

int* FMS_brute(int A[],int low,int high){

    int rpta[3];
    int *r;
    int max_sum=0;
    int sum;

    for(int i=low; i<=high; ++i){

        sum=0;
        for(int j=i; j<=high; ++j){

            sum+=A[j];
            if(sum>max_sum){

                rpta[0]=i;
                rpta[1]=j;
                rpta[2]=sum;
                max_sum=sum;
            }
        }
    }

    return rpta;
}

int main(){

    int A[16]{13,-3,-25,20,-3,-16,-23,8,20,-57,12,-5,-22,15,-4,136};
    int* rpta;
    int a,b,c;

    rpta=FMS_brute(A,0,15);
    a=rpta[0];
    b=rpta[1];
    c=rpta[2];
    cout<<"MAIN"<<endl;
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;


    return 0;
}
