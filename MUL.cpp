#include <pthread.h>
    #include <iostream.h>
    #include <semaphore.h>
    #include <unistd.h>
    #include<math.h>
    
    //Global variables
        double **A;//Matrix A
        double **B;//Matrix B
        double **C;//Output Matrix C
        const int MATRIX_DIMENSION = 10000; //We need a 10000 X 10000 Matrix
        const int NUM_THREADS = 25; // One thread completes 1/25th of the work
        const int THREAD_DIMENSION = MATRIX_DIMENSION / NUM_THREADS; //Array that each thread will operate on
        pthread_t * thread[NUM_THREADS];
        
        /***************************************************************************
        Function that does matrix multiplication of 1/25th of the whole matrix,
        The division is done by dividing the Matrix into row's all 1/25 of the total matrix
        Each row of Matrix A operates on all the columns of Matrix B to get corresponding elements of Matrix C
        Parameter : arg, this is used as and index for which part of the Matrix this particular thread operates on
        Return type: void
        ****************************************************************************/
    void *MatrixMul (void * arg)
    {
        int index;
        index = (int) arg;
        int operation_Lower_Limit = ((index+1) * THREAD_DIMENSION) - THREAD_DIMENSION  ; //Multiplication starting row
        int operation_Upper_Limit = ((index+1) * THREAD_DIMENSION) - 1; //Multiplication ending row
        
        for(int i=operation_Lower_Limit;i<=operation_Upper_Limit;i++) //only 1/25th of Matrix A is used
        {
            for(int j=0 ;j<MATRIX_DIMENSION; j++) // The whole B matrix is used
            {
                for(int k=0;k<MATRIX_DIMENSION;k++)
                {
                    C[i][j]+=A[i][k]*B[k][j];
                }
            }                                                                                                                                                                                                                                                                                                                                           
        }
        return NULL;
    }
    
    int main()
    {
        
        srand(time(0));
        //Assign memory for threads
        for(int i=0;i < NUM_THREADS;i++)
        {
        thread[i] = new pthread_t;
        }
    
        //Assign Matrix A first dimension
        //-----------------------------------------------------------
        A = new double*[MATRIX_DIMENSION];
        //Assign second dimension
        for(int i = 0; i < MATRIX_DIMENSION; i++)
        {
            A[i] = new double[MATRIX_DIMENSION];
        }
        //Assign Matrix B first dimension
        B = new double*[MATRIX_DIMENSION];
        //Assign second dimension
        for(int i = 0; i < MATRIX_DIMENSION; i++)
        {
            B[i] = new double[MATRIX_DIMENSION];
        }
        //Assign Matrix C first dimension
        C = new double*[MATRIX_DIMENSION];
        //Assign second dimension
        for(int i = 0; i < MATRIX_DIMENSION; i++)
        {
            C[i] = new double[MATRIX_DIMENSION];
        }
        //-----------------------------------------------------------
        
        
        
        //Generate random numbers for matrices A and B and assign C to 0
        for(int i=0;i<MATRIX_DIMENSION;i++)
        {
            for(int j=0;j<MATRIX_DIMENSION;j++)
            {
                A[i][j] = rand() % 10000;
                B[i][j] = rand() % 10000;
                C[i][j] = 0; // initialize C to zero
            }
        }
        //-----------------------------------------------------------
        //Do the matrix multiplication
        
        for(int i=0;i<NUM_THREADS;i++)
        {
        pthread_create( thread[ i ], NULL, (MatrixMul), (void *) (i) );
        }
            
        
        //wait for all the threads to complete execution
        for(int i=0;i<NUM_THREADS;i++)
        {
        pthread_join(*thread[i],NULL);
        }
        
        //-----------------------------------------------------------
        //delete the dynamic memory of A
        for (int i = 0; i < MATRIX_DIMENSION; i++)
        {
            delete[] A[i];
        }
        delete[] A;
        //delete the dynamic memory of B
        for (int i = 0; i < MATRIX_DIMENSION; i++)
        {
            delete[] B[i];
        }
        delete[] B;
        //delete the dynamic memory of C
        for (int i = 0; i < MATRIX_DIMENSION; i++)
        {
            delete[] C[i];
        }
        delete[] C;
        //-----------------------------------------------------------
        return(0);
    }