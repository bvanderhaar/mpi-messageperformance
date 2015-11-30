#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

#define MASTER 0
#define TAG 0
#define MSGSIZE 1000
#define MAX 25

int main(int argc, char *argv[]) {
  int my_rank, source, num_nodes;
  char my_host[MAX];
  char message[MSGSIZE];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);

  if (my_rank != MASTER) {
    gethostname(my_host, MAX);
    ////sprintf(message, "Hello from process %d on host %s!", my_rank, my_host);
    ////MPI_Send(message, strlen(message) + 1, MPI_CHAR, MASTER, TAG,
    ////         MPI_COMM_WORLD);
    double message_sent = MPI_Wtime();
    for (long long i = 0; i < MSGSIZE; i++) {
      message[i] = (rand() % 26) + 65;
    }
    MPI_Send(&message, MSGSIZE, MPI_CHAR, MASTER, TAG, MPI_COMM_WORLD);

  } else {
    double program_start = MPI_Wtime();
    printf("Num_nodes: %d\n", num_nodes);
    printf("Hello from Master (process %d)!\n", my_rank);
    char message[MSGSIZE];
    MPI_Status status;
    for (source = 1; source < num_nodes; source++) {
      MPI_Recv(&message, MSGSIZE, MPI_CHAR, source, TAG, MPI_COMM_WORLD,
               &status);
      ////double message_received = MPI_Wtime();
      ////double elapsed = message_received - message_sent;
      ////printf("Host: %d Message Ticks: %f Now: %f Elapsed time: %f\n",
      ////       status.MPI_SOURCE, message_sent, message_received, elapsed);
    }

    double program_end = MPI_Wtime();
    double program_elapsed = program_end - program_start;
    printf("Program Execution Time: %f\n", program_elapsed);
  }

  MPI_Finalize();

  return 0;
}
