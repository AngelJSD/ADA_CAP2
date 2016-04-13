#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > Matrix(vector<vector<int> > A,vector<vector<int> > B){

	int n=A.size();
	vector<vector<int> > C;
	
	for(int i=0; i<n; ++i){
		
		vector<int> aux;
		for(int j=0; j<n; ++j){
			
			int c=0;
			for(int k=0; k<n; ++k){
				
				c=c+A[i][k]*B[k][j];
			}
			aux.push_back(c);
		}
		C.push_back(aux);
	}

	return C;

}


int main(){
	
	int A[4][4]={{4,7,3,4},
				 {9,1,6,9},
				 {5,6,1,1},
				 {3,7,1,4}};
	int B[4][4]={{14,15,19,11},
				 {18,15,13,12},
				 {10,16,14,16},
				 {13,10,13,11}};
	vector<vector<int> > C,va,vb;

	for(int i=0; i<4; ++i){
		vector<int> aux,aux1;
		for(int j=0; j<4; ++j){
			aux.push_back(A[i][j]);
			aux1.push_back(B[i][j]);
		}
		va.push_back(aux);
		vb.push_back(aux1);
	}
	for(int i=0; i<va.size(); ++i){
		for(int j=0; j<va.size(); ++j)
			cout<<va[i][j]<<",";
		cout<<endl;
	}
	cout<<endl;
	for(int i=0; i<vb.size(); ++i){
		for(int j=0; j<vb.size(); ++j)
			cout<<vb[i][j]<<",";
		cout<<endl;
	}
	cout<<endl;

	C=Matrix(va,vb);

	for(int i=0; i<C.size(); ++i){
		for(int j=0; j<C.size(); ++j)
			cout<<C[i][j]<<",";
		cout<<endl;
	}

	return 0;

}
