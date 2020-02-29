#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int n, i;
    double PI25DT = 3.141592653589793238462643;
    double pi, h, sum, x;

    int numprocs, myid;
    double startTime, endTime;

    if (argc != 2)
        return 1;

    /* Initialize MPI and get number of processes and my number or rank*/
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* Processor zero sets the number of intervals and starts its clock*/
    if (myid == 0)
    {
        n = atoi(argv[1]);
        startTime = MPI_Wtime();

        for (i = 1; i < numprocs; i++)
        {
            MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    /* Calculate the width of intervals */
    h = 1.0 / (double)n;

    /* Initialize sum */
    sum = 0.0;
    /* Step over each inteval I own */
    for (i = myid + 1; i <= n; i += numprocs)
    {
        /* Calculate midpoint of interval */
        x = h * ((double)i - 0.5);
        /* Add rectangle's area = height*width = f(x)*h */
        sum += (4.0 / (1.0 + x * x)) * h;
    }

    if (myid != 0)
    {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
    }
    else
    {
        pi = sum;

        for (i = 1; i < numprocs; i++)
        {
            MPI_Recv(&sum, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            pi += sum;
        }

        /* Print approximate value of pi and runtime*/
        printf("pi is approximately %.16f, Error is %e\n",
               pi, fabs(pi - PI25DT));
        endTime = MPI_Wtime();
        printf("runtime is=%.16f", endTime - startTime);
    }

    MPI_Finalize();
    return 0;
}
