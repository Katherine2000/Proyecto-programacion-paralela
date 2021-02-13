/*
 ============================================================================
 Name        : ejercicio.c
 Author      : Juan José Hoyos
 Version     :
 Copyright   : Your copyright notice
 Description : Passing messages between two cores
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include "mpi.h"
#define tag 0

/*
 * Ejectutado por consola en linux con los siguientes comandos:
 * mpicc ejercicio.c -o ejercicio
 * mpiexec -n 2 ./ejercicio
 */

int main(int argc, char* argv[]){

	MPI_Init(&argc, &argv);

	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	int comm_size;
	MPI_Comm_size(MPI_COMM_WORLD,&comm_size);


	int ans;
	char buffer[100];
	if (my_rank==0){
		MPI_Request request;
		MPI_Status  status;
		sprintf(buffer,"%d",1);
		MPI_Isend(buffer,strlen(buffer)+1,MPI_INT,1,tag,MPI_COMM_WORLD,&request);
		MPI_Wait(&request,&status);
		MPI_Irecv(buffer,100,MPI_INT,1,tag,MPI_COMM_WORLD,&request);
		MPI_Wait(&request,&status);
		printf("Soy el procesador cero y recibo el rank del  %s.\n", buffer);

	}

	else {
		MPI_Request request;
		MPI_Status  status;
		MPI_Irecv(buffer,100,MPI_INT,0,tag,MPI_COMM_WORLD,&request);
		MPI_Wait(&request,&status);
		printf("Soy el procesador uno y recibo el rank del  %s.\n", buffer);
		sprintf(buffer,"%d",0);
		MPI_Isend(buffer,strlen(buffer)+1,MPI_INT,0,tag,MPI_COMM_WORLD,&request);
		MPI_Wait(&request,&status);
	}

	MPI_Finalize();
	return 0;
}
