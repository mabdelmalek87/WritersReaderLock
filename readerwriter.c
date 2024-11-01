#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include "readerwriter.h"

void rwlock_init(rwlock_t *sem) {

    sem->readerCounter = 0;                              // set the readers counter to 0
    sem_init(&sem->rd_mutex, 0, 1);                      // Initialize readers mutex semaphore to 1 
    sem_init(&sem->rw_mutex, 0, 1);                      // Initialize resource mutex semaphore to 1 
    sem_init(&sem->resourceQueue, 0, 1);                 // Initialize resource queue mutex semaphore to 1 
}


void readThread(rwlock_t *sem){   
   // A reader created.
    printf("Create reader\n");                
     
    //threades wait here to get queued to access the critical section 
    wait(sem->resourceQueue); 
    // threads wait here to access the critical section
    wait(sem->rd_mutex);                   
    sem->readerCounter++;
    // if there is only one reader it stops the writer from access
    if (sem->readerCounter == 1)            
        wait(sem->rw_mutex);             
    // signal for the next waiting thread in queue to execute
    signal(sem->resourceQueue);  
     // reader can use the critical section now.
    signal(sem->rd_mutex);                 
     // reading is performed ..Only readers allowed
    readAccess();                          
    // wait the reader mutex while updating the reader counter
    wait(sem->rd_mutex);                    
    sem->readerCounter--;
    // for the last reader leaving the critical section
    if(sem->readerCounter == 0)  
     // signal to a writer or another readers to access the critical section 
        signal(sem->rw_mutex);          
    // signal for reader counter again
    signal(sem->rd_mutex);           
}

void writeThread(rwlock_t *sem){
     // A writer created.
    printf("Create writer\n");     
    
    //threades wait here to get queued to access the critical section
    wait(sem->resourceQueue);          
   // threads wait here to access the critical section
    wait(sem->rw_mutex);        
    // signal for the next waiting thread in queue to execute
    signal(sem->resourceQueue);        
    // Writing is performed .. No readers or other writers allowed while excution
    writeAccess(); 
    //signal to a writer or another readers to access the critical section 
    signal(sem->rw_mutex);    
}

// simulating reading
void readAccess(){
    
    printf("Reader's is in... reading\n");
  
    printf("Finished reading\n");
  
}

// simulating writing 

void writeAccess(){

    printf("Writer's in... writing\n");
    
    printf("Finished writing\n");
    
}