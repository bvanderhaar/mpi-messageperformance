#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

#define MASTER 0
#define TAG 0
#define MSGSIZE 10
#define MAX 25

int main(int argc, char *argv[]) {
  int my_rank, source, num_nodes;
  char my_host[MAX];
  char message[MSGSIZE];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);

  double program_start = MPI_Wtime();
  if (my_rank != MASTER) {
    gethostname(my_host, MAX);
    ////sprintf(message, "Hello from process %d on host %s!", my_rank, my_host);
    ////MPI_Send(message, strlen(message) + 1, MPI_CHAR, MASTER, TAG,
    ////         MPI_COMM_WORLD);
    double message_sent = MPI_Wtime();
    MPI_Send(&message_sent, MSGSIZE, MPI_DOUBLE, MASTER, TAG, MPI_COMM_WORLD);

  } else {
    printf("Num_nodes: %d\n", num_nodes);
    printf("Hello from Master (process %d)!\n", my_rank);
    double message_sent = 0;
    MPI_Status status;
    for (source = 1; source < num_nodes; source++) {
      MPI_Recv(&message_sent, MSGSIZE, MPI_LONG_INT, source, TAG,
               MPI_COMM_WORLD, &status);
      double message_received = MPI_Wtime();
      double elapsed = message_received - message_sent;
      printf("Host: %d Message Ticks: %f Now: %f Elapsed time: %f\n",
             status.MPI_SOURCE, message_sent, message_received, elapsed);
    }
  }

  MPI_Finalize();
  /*double program_end = MPI_Wtime();
  double program_elapsed = program_end - program_start;
  printf("Program Execution Time: %f", program_elapsed);*/
  return 0;
}
