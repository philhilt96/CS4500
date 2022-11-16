/*
  list-forming.c: 
  Each thread generates a data node, attaches it to a global list. This is reapeated for K times.
  There are num_threads threads. The value of "num_threads" is input by the student.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sched.h>

// genreate a data node for K times in each thread
//#define K 200
//#define K 400
#define K 800

struct Node
{
    int data;
    struct Node* next;
};

struct list
{
     struct Node * header;
     struct Node * tail;
};

pthread_mutex_t    mutex_lock;

struct list *List;

// added datatype to hold data about thread in list
typedef struct thread_data{
    int CPU;
    struct list threadList;
}thread_data;

/* Function not needed, allowing threads to run on all CPUs will be faster
void bind_thread_to_cpu(int cpuid) {
     cpu_set_t mask;
     CPU_ZERO(&mask);

     CPU_SET(cpuid, &mask);
     if (sched_setaffinity(0, sizeof(cpu_set_t), &mask)) {
         fprintf(stderr, "sched_setaffinity");
         exit(EXIT_FAILURE);
     }
}
*/

struct Node* generate_data_node()
{
    struct Node *ptr;
    ptr = (struct Node *)malloc(sizeof(struct Node));    

    if( NULL != ptr ){
        ptr->next = NULL;
    }
    else {
        printf("Node allocation failed!\n");
    }
    return ptr;
}

void * producer_thread(void  *arg)
{
    // DO NOT BIND THREAD TO SPECIFIC CPU
    //bind_thread_to_cpu(*((int*)arg));//bind this thread to a CPU

    struct Node * ptr, tmp;
    int counter = 0;

    // instantiate modified thread list with thread data to null
    struct list threadList;
    threadList.header = NULL;
    threadList.tail = NULL;

    // use for loop instead of while so that trylock doesn't need to be used
    for(counter; counter < K; counter++)
    {
        ptr = generate_data_node();
        ptr->data  = 1;//generate data
        // attatch node to global list
        if( threadList.header == NULL ){
          threadList.header = threadList.tail = ptr;
        }
        else{
            threadList.tail->next = ptr;
            threadList.tail = ptr;
        }
    }
    // ensure that thread has acess to critical region with mutex_lock
    pthread_mutex_lock(&mutex_lock);
    if( List->header == NULL ){
        List->header = threadList.header;
        List->tail = threadList.tail;
    }
    else{
        List->tail->next = threadList.header;
        List->tail = threadList.tail;
    }
    // exit critical region
    pthread_mutex_unlock(&mutex_lock);
}


int main(int argc, char* argv[])
{
    int i, num_threads;

    int NUM_PROCS;//number of CPU
    int* cpu_array = NULL;

    struct Node  *tmp,*next;
    struct timeval starttime, endtime;

   if(argc == 1){
        printf("ERROR: please provide an input arg (the number of threads)\n");
        exit(1);
    }

    num_threads = atoi(argv[1]); //read num_threads from user
    pthread_t producer[num_threads];
    // create thread data global list
    thread_data threadData[num_threads];
    NUM_PROCS = sysconf(_SC_NPROCESSORS_CONF);//get number of CPU

    if( NUM_PROCS > 0)
    {
        cpu_array = (int *)malloc(NUM_PROCS*sizeof(int));
        if( cpu_array == NULL )
        {
            printf("Allocation failed!\n");
            exit(0);
        }
        else
        {
            for( i = 0; i < NUM_PROCS; i++)
               cpu_array[i] = i;
        }

    }

    pthread_mutex_init(&mutex_lock, NULL);

    List = (struct list *)malloc(sizeof(struct list));
    if( NULL == List )
    {
       printf("End here\n");
       exit(0);	
    }
    List->header = List->tail = NULL;

    gettimeofday(&starttime,NULL); //get program start time
    for( i = 0; i < num_threads; i++ )
    {
        // do not need cpu thread id since desing is not pinning threads to specific CPUs
        pthread_create(&(producer[i]), NULL, (void *) producer_thread, NULL);
    }

    for( i = 0; i < num_threads; i++ )
    {
        if(producer[i] != 0)
        {
            pthread_join(producer[i],NULL); 
        }
    }

    gettimeofday(&endtime,NULL); //get the finish time

    if( List->header != NULL )
    {
        next = tmp = List->header;
        while( tmp != NULL )
        {  
           next = tmp->next;
           free(tmp);
           tmp = next;
        }            
    }
    if( cpu_array!= NULL)
       free(cpu_array);
    /* calculate program runtime */
    printf("Total run time is %ld microseconds.\n", (endtime.tv_sec-starttime.tv_sec) * 1000000+(endtime.tv_usec-starttime.tv_usec));
    return 0;
}
