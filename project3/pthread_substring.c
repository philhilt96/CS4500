#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>


#define MAX 1024

int total = 0;
int n1,n2;
char *s1,*s2;
FILE *fp;

int readf(FILE *fp)
{
	if((fp=fopen("strings.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2=(char *)malloc(sizeof(char)*MAX);
	if(s2==NULL){
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1=fgets(s1, MAX, fp);
	s2=fgets(s2, MAX, fp);
	n1=strlen(s1)-1;  /*length of s1*/
	n2=strlen(s2)-1; /*length of s2*/
	
	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;
}

void  *num_substring(int i)
{
	int j,k;
	int count = 0;

	//Deleted first loop from sequential_substring. i is now the input from the thread
	for(j = i,k = 0; k < n2; j++,k++){  /*search for the next string of size of n2*/  
		if (*(s1+j)!=*(s2+k)){
			break;
		}else{
			count++;
		}

		if(count==n2){
			total++;
		}    
		}
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	int count;
 	int ret;

	//Read File and set number of threads	
	readf(fp);
	int NUM_THREADS = n1-n2;
	pthread_t threads[NUM_THREADS];
	
	//Create Threads
	int t;
	for(t = 0; t <= NUM_THREADS; t++){
		//num_substring as process and t as input
		ret = pthread_create(&threads[t], NULL, num_substring, t);
		if(ret != 0){
			printf("ERROR, return code: %d\n", ret);
		}
		//Join Threads		
		pthread_join(threads[t],NULL);
		
	}
	//Print Total
	printf("Total substrings: %d", total);	
	pthread_exit(0);
	return 1;
}











