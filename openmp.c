#include <omp.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SCALE 10000
#define ARRINIT 2000
#define MAX 100000


/* Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;
    return (diff<0);
}

void timeval_print(struct timeval *tv)
{
    char buffer[300];
    time_t curtime;
    curtime = tv->tv_sec;
}

void pi_digits(int digits)
{
    int carry = 0;
    int arr[digits + 1];
    for (int i = 0; i <= digits; ++i)
        arr[i] = ARRINIT;
    for (int i = digits; i > 0; i-= 14)
        {
            int sum = 0;
            for (int j = i; j > 0; --j)
                {
                    sum = sum * j + SCALE * arr[j];
                    arr[j] = sum % (j * 2 - 1);
                    sum /= j * 2 - 1;
                }
            carry = sum % SCALE;
        }
}

void without_openmp()
{
    long long i,n=MAX;
    long long sum=0;
    for(i=1; i<=n; i++)
        pi_digits(1000);
}

void with_openmp()
{
    long long i,n=MAX;
    long long sum=0;
    #pragma omp parallel for
    for(i=1; i<=n; i++)
        pi_digits(1000);
}


int main()
{
    struct timeval tvBegin, tvEnd, tvDiff;

    //without_openmp
    gettimeofday(&tvBegin, NULL);
    timeval_print(&tvBegin);
    without_openmp();
    gettimeofday(&tvEnd, NULL);
    timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
    printf("without_openmp: %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);

    //with_openmp
    gettimeofday(&tvBegin, NULL);
    timeval_print(&tvBegin);
    with_openmp();
    gettimeofday(&tvEnd, NULL);
    timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
    printf("with_openmp: %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);

    return 0;
}



//extern float average(float,float,float);
//void master_example( float* x, float* xold, int n, float tol )
//{
//    int c, i, toobig;
//    float error, y;
//    c = 0;
//    #pragma omp parallel
//    {
//        do
//            {
//                #pragma omp for private(i)
//                for( i = 1; i < n-1; ++i )
//                    {
//                        xold[i] = x[i];
//                    }
//                #pragma omp single
//                {
//                    toobig = 0;
//                }
//                #pragma omp for private(i,y,error) reduction(+:toobig)
//                for( i = 1; i < n-1; ++i )
//                    {
//                        y = x[i];
//                        x[i] = average( xold[i-1], x[i], xold[i+1] );
//                        error = y - x[i];
//                        if( error > tol || error < -tol ) ++toobig;
//                    }
//                #pragma omp master
//                {
//                    ++c;
//                    printf( "iteration %d, toobig=%d\n", c, toobig );
//                }
//            }
//        while( toobig > 0 );
//    }
//}






//#include <omp.h>
//#include <stdio.h>

//void simple(unsigned n, unsigned *a, unsigned *b)
//{
//    unsigned i;
//#pragma omp parallel for
//    for (i=1;i<n;i++)
//    {
//    b[i]=a[i]+1.0;
//    printf("%lld\n",b[i]);
//    }
//}

//int main()
//{
//    unsigned n=10000;
//    unsigned a=1;
//    unsigned *b;
//    simple(n,&a,b);
//    return 0;
//}






//// #include <omp.h>
//// #include <stdio.h>
//// #include <stdlib.h>
////
//// int main (int argc, char *argv[]) {
////   int th_id, nthreads;
////   #pragma omp parallel private(th_id)
////   {
////     th_id = omp_get_thread_num();
////     printf("Hello World from thread %d\n", th_id);
////     #pragma omp barrier
////     if ( th_id == 0 ) {
////       nthreads = omp_get_num_threads();
////       printf("There are %d threads\n",nthreads);
////     }
////   }
////   return EXIT_SUCCESS;
//// }
