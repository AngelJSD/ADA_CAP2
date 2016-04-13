#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > Suma(vector<vector<int> > A, vector<vector<int> > B){

	vector<vector<int> > C;
	for(int i=0; i<A.size(); ++i){
		vector<int> aux;
		for(int j=0; j<A.size(); ++j){
			aux.push_back(A[i][j]+B[i][j]);
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

vector<vector<int> > Matrix_DC(vector<vector<int> > A,vector<vector<int> > B){
	
	if(A.size()==1){
		
		vector<vector<int> > D;
		vector<int> aux;
		aux.push_back(A[0][0]*B[0][0]);
		D.push_back(aux);
		//cout<<A[0][0]<<" "<<B[0][0]<<endl;
		return D;
	}
	vector<vector<int> > C1,C2,C3,C4,A11,A12,A21,A22,B11,B12,B21,B22;
	
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
	C1=Suma(Matrix_DC(A11,B11),Matrix_DC(A12,B21));
	C2=Suma(Matrix_DC(A11,B12),Matrix_DC(A12,B22));
	C3=Suma(Matrix_DC(A21,B11),Matrix_DC(A22,B21));
	C4=Suma(Matrix_DC(A21,B12),Matrix_DC(A22,B22));
	
	return Unir(C1,C2,C3,C4);

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

	C=Matrix_DC(va,vb);

	for(int i=0; i<C.size(); ++i){
		for(int j=0; j<C.size(); ++j)
			cout<<C[i][j]<<",";
		cout<<endl;
	}

	return 0;

}
