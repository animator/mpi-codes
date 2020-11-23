# mpi-codes

High Performance Computing using MPI Workshop Slides - [Link](https://www.slideshare.net/ankitmahato/hpc-workshop)

Compile code using:
```
mpicc filename.c
```

Execute it using:
```
mpirun -np NUM_OF_PROCS ./a.out
```

| Code | Description |
|--|--|
| [helloworld](https://github.com/animator/mpi-codes/blob/main/helloworld.c) | The most basic program which prints "Hello world" from all the processes |
| [hello_send_recv](https://github.com/animator/mpi-codes/blob/main/hello_send_recv.c) | Illustrates the use of MPI_Send and MPI_Recv functions. The main process sends a message, “Hello, world”, to the process whose rank is 1, and after receiving the message, the process prints the message along with its rank |
| [vector_addition](https://github.com/animator/mpi-codes/blob/main/vector_addition.c) and [vector_add](https://github.com/animator/mpi-codes/blob/main/vector_add.c) | Brek two vectors in NPROC parts, add the elements in parallel, then rejoin |
| [pi](https://github.com/animator/mpi-codes/blob/main/pi.c) | Pi calculation |
| [mpi_prime](https://github.com/animator/mpi-codes/blob/main/mpi_prime.c) | To check for the occurance of Prime number |
