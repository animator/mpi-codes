/***************************************
AUTHOR: ANKIT MAHATO
amahato@iitk.ac.in
IIT KANPUR

This code distributes data and search 
for the prime number which occurs first.

The root and other process codes can be 
clubbed together but in this code root
has been treated separately so as for 
better understanding.
***************************************/


#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MASTER 0


int IS_prime(int *num)
{
	int isprime = 0;
	int i; 
	if(*num==2)
		return 0;
	if(*num%2==0)
		return 1;
	for(i = 3; i <= (int)sqrt(*num); i+=2)
	{
		if((*num% i) == 0)
		{
			isprime = 1;
			break;
		}
	}
	return isprime;
}

int main (int argc, char *argv[]) 
{
	int * a;
	int * c;
	// arrays a and c
	int total_proc;	
	// total nuber of processes	
	int rank;
	// rank of each process
	int T;
	// total number of test cases
	long long int n_per_proc;	
	// elements per process		

	long long int i, n;
	MPI_Status status;

	// Initialization of MPI environment
	MPI_Init (&argc, &argv);
	MPI_Comm_size (MPI_COMM_WORLD, &total_proc);
	//Now you know the total number of processes running in parallel
	MPI_Comm_rank (MPI_COMM_WORLD,&rank);
	//Now you know the rank of the current process
    	int * ap;	
	if (rank == MASTER) //you choose process rank 0 to be your root which will be used to perform input output. 
	{
        	scanf ("%d", &T);
        	// you get the total number of test cases
        	MPI_Bcast (&T, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        	// Then you broadcast it to every process out there
        	while (T--)
        	{  	
        		scanf ("%lld", &n);
			a = (int *) malloc(sizeof(int)*n);
			c = (int *) malloc(sizeof(int)*total_proc);
            		MPI_Bcast (&n, 1, MPI_LONG_LONG_INT, MASTER, MPI_COMM_WORLD);
            		n_per_proc = n/total_proc;
			for(i=0;i<n;i++)
				scanf ("%d", &a[i]); 
			if(n%total_proc != 0)
			{
			    	n_per_proc+=1;
			    	for(i=0;i<(n_per_proc*total_proc - n);i++)
			    		a[n+i] = 0;
			} // to divide data evenly by the number of processors 
			ap = (int *) malloc(sizeof(int)*n_per_proc);
			int cp;
			MPI_Bcast (&n_per_proc, 1, MPI_LONG_LONG_INT, MASTER, MPI_COMM_WORLD);
			//Broadcast element per process
			MPI_Scatter(a, n_per_proc, MPI_INT, ap, n_per_proc, MPI_INT, 0, MPI_COMM_WORLD); 
			//scattering array a  
			for(i=0;i<n_per_proc;i++)
			{
				if(IS_prime(&ap[i])==0)
				{
					cp=ap[i];
					break;
				}
				if(i==(n_per_proc-1))
					cp=-1;
			}
			MPI_Gather(&cp, 1, MPI_INT, c, 1, MPI_INT, MASTER, MPI_COMM_WORLD);			//gathering array c
			for(i=0;i<total_proc;i++)
			{
				if(c[i]==-1)
					continue;
				else
				{
					printf ("%d\n", c[i]);
					break;					
				}
			}		
		}
    	} 
	else 
	{ // Non-master tasks
		// Receive T
		MPI_Bcast (&T, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
		//printf("%d from process %d\n",T,rank);
		while (T--) 
		{
			MPI_Bcast (&n, 1, MPI_LONG_LONG_INT, MASTER, MPI_COMM_WORLD);
			MPI_Bcast (&n_per_proc, 1, MPI_LONG_LONG_INT, MASTER, MPI_COMM_WORLD);
			ap = (int *) malloc(sizeof(int)*n_per_proc);
			int cp;
			MPI_Scatter(a, n_per_proc, MPI_INT, ap, n_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
			//Recieving Scattered a  
			for(i=0;i<n_per_proc;i++)
			{
				if(IS_prime(&ap[i])==0)
				{
					cp=ap[i];
					break;
				}
				if(i==(n_per_proc-1))
					cp=-1;		
			}
			MPI_Gather(&cp, 1, MPI_INT, c, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
			//To initiate the gathering of first occurred primes from all processes
			//If no prime number in the process then -1 is returned 
        	}
	}
	MPI_Finalize();
	//Terminate MPI Environment
	return 0;
}
