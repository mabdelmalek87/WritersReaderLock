#ifndef _READERWRITER_H__
#define _READERWRITER_H__

#include <semaphore.h>

/*
    This is the definition of the semaphore structure include all locks used to mutex and signal readers and writers process as well queue lock
*/
typedef struct _rwlock_t{    
    sem_t rd_mutex;                           // lock for the reader.
    sem_t rw_mutex;                           // lock for the writer.
    sem_t resourceQueue;                      // lock for the queue of process to be given access to the critical section
    int readerCounter;                        // counter of readers inside the critical section.

} rwlock_t;





void writeAccess();                           //this represent when a writer is reading the resource.

void readAccess();                            //this represent when readerers are reading the resource.
  
void rwlock_init();                           // to initialize the lock semaphore

void readThread();                            //for the reader thread 

void writeThread();                           // for the writer thread 







#endif