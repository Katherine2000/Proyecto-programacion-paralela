/*
 ============================================================================
 Name        : calc_pi.c
 Author      : Juan José Hoyos
 Version     :
 Copyright   : 
 Description : Calculate Pi using numerical integration and MPI
 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int rank,size;
	int n = 1000000;//numero de intervalos deseados
	int root = 0;

	double pi = 0.0;//para el calculo global de pi
	double mypi,w,t1,t2,tf;
	double PI25DT = 3.141592653589793238462643;//valor de referencia para pi



	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	MPI_Barrier (MPI_COMM_WORLD);
	t1 = MPI_Wtime();

	//comunircarle a todos la cantidad de intervalos que quiero
	MPI_Bcast(&n,1,MPI_INT,root,MPI_COMM_WORLD);

	w = (1.0)/(double)n;
	mypi = 0.0;//calculo local de pi

	int i;
	for (i=rank+1;i<=n;i+=size){
		mypi += w * sqrt(1 - (((double) i / n) * ((double) i / n)));
		/*printf("Soy el procesador %d, estoy en el intervalo %d y este es mi aporte al calculo de pi %f\n",
				rank,i,mypi);*/
	}

	MPI_Barrier (MPI_COMM_WORLD);
	t2 = MPI_Wtime();
	tf = t2-t1;

	MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,root,MPI_COMM_WORLD);



	if (rank==0){
		printf("Pi es aproximadamente %.16f, con un error de  %.16f\n", 4 * pi,
				fabs((4 * pi) - PI25DT));
		printf("El tiempo que se demoraron los procesadores en calcular pi fue:  %f \n",tf);
	}

	MPI_Finalize();


}
