#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

vector<vector<int> > Operacion(vector<vector<int> > A, vector<vector<int> > B,bool f){

	vector<vector<int> > C;
	for(int i=0; i<A.size(); ++i){
		vector<int> aux;
		for(int j=0; j<A.size(); ++j){
			if(f)aux.push_back(A[i][j]-B[i][j]);
			else aux.push_back(A[i][j]+B[i][j]);
		}
		C.push_back(aux);
	}
	//cout<<"S"<<endl;
	return C;
}

vector<vector<int> > Unir(vector<vector<int> > C1, vector<vector<int> > C2,vector<vector<int> > C3, vector<vector<int> > C4){

	vector<vector<int> > D;
	//cout<<"U1"<<endl;
	for(int i=0; i<C1.size()*2;++i){
		vector<int> aux;
		for(int j=0; j<C1.size()*2; ++j){
			if(i<C1.size() && j<C1.size()) aux.push_back(C1[i%C1.size()][j%C1.size()]);
			if(i<C1.size() && j>=C1.size()) aux.push_back(C2[i%C1.size()][j%C1.size()]);
			if(i>=C1.size() && j<C1.size()) aux.push_back(C3[i%C1.size()][j%C1.size()]);
			if(i>=C1.size() && j>=C1.size()) aux.push_back(C4[i%C1.size()][j%C1.size()]);
		}
		D.push_back(aux);
	}
	//cout<<"U"<<endl;
	return D;

}

vector<vector<int> > Strassen(vector<vector<int> > A,vector<vector<int> > B){

	if(A.size()==1){

		vector<vector<int> > D;
		vector<int> aux;
		aux.push_back(A[0][0]*B[0][0]);
		D.push_back(aux);
		//cout<<A[0][0]<<" "<<B[0][0]<<endl;
		return D;
	}
	vector<vector<int> > C1,C2,C3,C4,A11,A12,A21,A22,B11,B12,B21,B22;
	vector<vector<int> > P1,P2,P3,P4,P5,P6,P7;

	for(int i=0; i<A.size(); ++i){
		vector<int> aux,aux1;
		for(int j=0; j<A.size(); ++j){
			if(i<A.size()/2 && j<A.size()/2) {
				aux.push_back(A[i][j]);
				aux1.push_back(B[i][j]);
				if(j==A.size()/2-1){
					A11.push_back(aux);
					B11.push_back(aux1);
					aux.clear();
					aux1.clear();
				}
			}
			if(i<A.size()/2 && j>=A.size()/2){
				aux.push_back(A[i][j]);
				aux1.push_back(B[i][j]);
				if(j==A.size()-1){
					A12.push_back(aux);
					B12.push_back(aux1);
					aux.clear();
					aux1.clear();
				}
			}
			if(i>=A.size()/2 && j<A.size()/2) {
				aux.push_back(A[i][j]);
				aux1.push_back(B[i][j]);
				if(j==A.size()/2-1){
					A21.push_back(aux);
					B21.push_back(aux1);
					aux.clear();
					aux1.clear();
				}
			}
			if(i>=A.size()/2 && j>=A.size()/2) {
				aux.push_back(A[i][j]);
				aux1.push_back(B[i][j]);
				if(j==A.size()-1){
					A22.push_back(aux);
					B22.push_back(aux1);
					aux.clear();
					aux1.clear();
				}
			}
		}
	}
	//cout<<n<<endl;
	//MODIFICAR n
	P1=Strassen(A11,Operacion(B12,B22,1));
	P2=Strassen(Operacion(A11,A12,0),B22);
	P3=Strassen(Operacion(A21,A22,0),B11);
	P4=Strassen(A22,Operacion(B21,B11,1));
	P5=Strassen(Operacion(A11,A22,0),Operacion(B11,B22,0));
	P6=Strassen(Operacion(A12,A22,1),Operacion(B21,B22,0));
	P7=Strassen(Operacion(A11,A21,1),Operacion(B11,B12,0));

	C1=Operacion(Operacion(P5,P4,0),Operacion(P6,P2,1),0);
	C2=Operacion(P1,P2,0);
	C3=Operacion(P3,P4,0);
	C4=Operacion(Operacion(P5,P1,0),Operacion(P3,P7,0),1);

	return Unir(C1,C2,C3,C4);

}

int main(){

	int n;
	cin>>n;
	int A[n][n];
	int B[n][n];
	srand(time(NULL));

	vector<vector<int> > C,va,vb;

	for(int i=0; i<pow(2,ceil(log2(n))); ++i){
		vector<int> aux,aux1;
		for(int j=0; j<pow(2,ceil(log2(n))); ++j){
			if(j>=n or i>=n){
			    aux.push_back(0);
                aux1.push_back(0);
			}
            else{
                aux.push_back(rand() % 100);
                aux1.push_back(rand() % 100);
            }
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
	C=Strassen(va,vb);

	for(int i=0; i<C.size(); ++i){
		for(int j=0; j<C.size(); ++j)
			cout<<C[i][j]<<",";
		cout<<endl;
	}

	return 0;

}
