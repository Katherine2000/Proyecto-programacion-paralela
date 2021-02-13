#include <bits/stdc++.h>
using namespace std;
int ecuacion_lineal_2var(int n){
	vector< tuple<int,int> > ans;
	/*
	Encontrar todas las soluciones para i,j entre 0 y n donde
	3i +5j = 100
	*/
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if((3*i+5*j)==100){
				tuple<int,int> t1;
				t1 = make_tuple(i,j);
				ans.push_back(t1);
			}	
		}
	}

	return 0;
}

int ecuacion_lineal_3var(int n){
	vector< tuple<int,int,int> > ans;
	/*
	Encontrar todas las soluciones para i,j,k entre 0 y n donde
	3i +5j +6k = 100
	*/
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				if((3*i+5*j+6*k)==100){
					tuple<int,int,int> t1;
					t1 = make_tuple(i,j,k);
					ans.push_back(t1);
				}
			}
		}
	}

	return 0;
}

int ecuacion_lineal_4var(int n){
	vector< tuple<int,int,int,int> > ans;
	/*
	Encontrar todas las soluciones para i,j,k,l entre 0 y n donde
	3i +5j +6k +7l = 120
	*/
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				for (int l=0;l<n;l++){
					if((3*i+5*j+6*k+7*l)==120){
						tuple<int,int,int,int> t1;
						t1 = make_tuple(i,j,k,l);
						ans.push_back(t1);
				}

				}

			}
		}
	}

	return 0;
}



int main(){
	auto start = std::chrono::system_clock::now();
	ecuacion_lineal_2var(100000);
	ecuacion_lineal_3var(2000);
	ecuacion_lineal_4var(300);
	
	auto end = std::chrono::system_clock::now();
	chrono::duration<double> elapsed = end - start;
	printf("Ejecutar los tres algoritmos de manera secuencial toma un tiempo de: %.2lf segundos\n", elapsed.count());
	return 0;
}