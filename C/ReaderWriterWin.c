#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Global variables
int read_count = 0; // Number of readers accessing or waiting for the resource
int shared_resource = 0; // The shared resource

// Mutex
HANDLE mutex; // Protects read_count

// Semaphore
HANDLE wrt; // Signals when it is safe for writers to access shared_resource

// Reader function
DWORD WINAPI reader(LPVOID arg)
{
    int id = *((int *) arg); // Reader id

    while (1)
    {
        // Lock mutex before checking read_count
        WaitForSingleObject(mutex, INFINITE);

        // Increment read_count atomically 
        read_count++;

        // If this is the first reader, wait until there are no writers accessing shared_resource by locking wrt
        if (read_count == 1)
        {
            WaitForSingleObject(wrt, INFINITE);
        }

        // Unlock mutex after updating read count 
        ReleaseMutex(mutex);

        // Read shared_resource 
        printf("Reader %d reads %d\n", id, shared_resource);

		// Lock mutex before checking read count 
		WaitForSingleObject(mutex, INFINITE); 

		// Decrement read count atomically  
		readcount--; 
        
		// If this is the last reader unlock wrt so that writers can access sharedresource 
		if(readcount==0) 
			ReleaseSemaphore(wrt); 

		// Unlock mutex after updating readcount 
		ReleaseMutex(mutex); 

    } 

    return 0; 
} 

// Writer function 
DWORD WINAPI writer(LPVOID arg) 
{ 
    int id = *((int *) arg); // Writer id 

    while (1) 
    { 
    	// Wait until there are no readers or writers accessing sharedresource by locking wrt  
    	sem_wait(&wrt); 
        
    	// Write to sharedresource  
    	printf("Writer %d writes %d\n", id, ++sharedresource); 
        
    	// Unlock wrt after writing to sharedresource  
    	sem_post(&wrt); 
        
    } 

    return 0; 
} 