/*
Question Name:Readers Writer Problem
Submitted By:Zerk Shaban
Roll Number:P14-6012
Section:CS-A
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
	//Declaring the objects of type semaphore
	sem_t writer,reader,mutex;
	//declared the readercount varible to manage multiple users to read from same file
	// will be more cleared when I will explain its use while using below
	int readercount=0;
	//buffer where we are going to wrtie the data and from where the data will be read
	char buf[30];
	//function through which we will write in buffer it is invoked by thread1 object 
	//below
	void *Write(){
	//as per the rules of the probles only one writer can write into a file at one time
	//so we will put the lock on the critical section of writing 
		sem_wait(&writer);
	//writing into the file
		sprintf(buf,"%s","My name is zerk shaban");
	//after we havee written the data into the file we will exit the file or other words
	//we will unlock the lock
		sem_post(&writer);
	}
	//function that will be used to read from the buffer 
	void *Read(){
	//as we face the proble which letting multiple threads to use from the same file so first
	//we will lock the whole critical section 
		sem_wait(&mutex);
	//we have to keep the record of the first user and the other users so the first user can read
	//only when the value of readercount equals to one for that we will increment the value from 
	//zero to one
		readercount++;
	//to seprate the first reader from the others we will pu the first one into lock 
		sem_wait(&reader);
		if(readercount==1){
			printf("First reader reading %s\n",buf);
		}
	//after first read have read from the file as we know for reading of first user the value
	//of the reader count should be 1 so we will decrement the value to zero because the
	//first user is done with the reading
		readercount--;
	//after reading the data we will unlock the critical section 
		sem_post(&reader);
	//as the value would have deacred from one to zero now other users will be allowed to read from
	// the same file at the same time
		if(readercount==0){
			printf("Other reader reading the same file %s\n",buf);
		}
		sem_post(&mutex);
	}

	int main(){
	//initlizing the values to the objects
		sem_init(&mutex,0,1);
		sem_init(&writer,0,1);
		sem_init(&reader,0,1);
	//Declaring the variables for threads
		pthread_t thread1,thread2;
	//creating the threads for invoking the write and read function
		pthread_create(&thread1,NULL,Write,NULL);
		pthread_create(&thread2,NULL,Read,NULL);
	//putting the join for threads
		pthread_join(thread1,NULL);
		pthread_join(thread2,NULL);
	//after using we will reallocate the momory that was given to it	
		sem_destroy(&mutex);
		sem_destroy(&reader);
		sem_destroy(&writer);
		
	}