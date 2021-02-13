#include <bits/stdc++.h>
using namespace std;
void *ecuacion_lineal_2var(void *args){
	int n = *(int*)args;
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
	pthread_exit(0);
	return 0;
}

void *ecuacion_lineal_3var(void *args){
	int n = *(int*)args;
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
	pthread_exit(0);
	return 0;
}

void *ecuacion_lineal_4var(void *args){
	int n = *(int*)args;
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
	pthread_exit(0);
	return 0;
}

int main(){

    auto start = std::chrono::system_clock::now();
	pthread_t hilo1;
	pthread_t hilo2;
	pthread_t hilo3;
	
	int n1 = 100000,n2 = 2000,n3 = 300;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_create(&hilo1,NULL,ecuacion_lineal_2var,(void*)&n1);
	pthread_create(&hilo2,NULL,ecuacion_lineal_3var,(void*)&n2);
	pthread_create(&hilo3,NULL,ecuacion_lineal_4var,(void*)&n3);


	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);
	pthread_join(hilo3,NULL);

	auto end = std::chrono::system_clock::now();
	chrono::duration<double> elapsed = end - start;
	printf("Ejecutar los tres algoritmos de manera paralela toma un tiempo de: %.2lf segundos\n", elapsed.count());

}
