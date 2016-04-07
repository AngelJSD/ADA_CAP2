#include <iostream>

using namespace std;

int* FMCS(int *A, int low, int mid, int high){

    int rpta[3];
    int left_sum=-1000000000;
    int right_sum=-1000000000;
    int sum=0;
    int max_left,max_rigth;
    for(int i=mid; i>=low; --i){

        sum+=A[i];
        if(sum>left_sum){

            //cout<<"h1"<<endl;
            left_sum=sum;
            max_left=i;
        }
    }
    sum=0;
    for(int i=mid+1; i<=high; ++i){

        sum+=A[i];
        if(sum>right_sum){
            //cout<<"h1"<<endl;
            right_sum=sum;
            max_rigth=i;
        }
    }
    rpta[0]=max_left;
    rpta[1]=max_rigth;
    rpta[2]=left_sum+right_sum;

    return rpta;

}

int* FMS(int A[],int low,int high){

    int rpta[3],mid;
    int *r;
    if(high==low){

        rpta[0]=low;
        rpta[1]=high;
        rpta[2]=A[low];
        return rpta;
    }
    mid=(low+high)/2;
    r=FMS(A, low, mid);
    int left_low=r[0], left_high=r[1], left_sum=r[2];
    r=FMS(A, mid+1, high);
    int right_low=r[0], right_high=r[1], right_sum=r[2];
    r=FMCS(A, low, mid, high);
    int cross_low=r[0], cross_high=r[1], cross_sum=r[2];
    if(left_sum>=right_sum && left_sum>=cross_sum){
        rpta[0]=left_low;
        rpta[1]=left_high;
        rpta[2]=left_sum;

        return rpta;
    }
    else if(right_sum>=left_sum && right_sum>=cross_sum){
        rpta[0]=right_low;
        rpta[1]=right_high;
        rpta[2]=right_sum;

        return rpta;
    }
    else{
        rpta[0]=cross_low;
        rpta[1]=cross_high;
        rpta[2]=cross_sum;
        return rpta;
    }

}

int main(){

    int A[16]{13,-3,-25,20,-3,-16,-23,8,20,-57,12,-5,-22,15,-4,136};
    int* rpta;
    int a,b,c;

    rpta=FMS(A,0,15);
    a=rpta[0];
    b=rpta[1];
    c=rpta[2];
    cout<<"MAIN"<<endl;
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;


    return 0;
}
