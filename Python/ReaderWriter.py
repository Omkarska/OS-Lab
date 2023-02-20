import threading as thread
import random

# Global variables
read_count = 0 # Number of readers accessing or waiting for the resource
shared_resource = 0 # The shared resource

# Mutex
mutex = thread.Lock() # Protects read_count

# Reader function
def reader(id):
    global read_count
    global shared_resource

    while True:
        # Lock mutex before checking read_count
        mutex.acquire()

        # Increment read_count atomically 
        read_count += 1

        # Unlock mutex after updating read count 
        mutex.release()

        # Read shared_resource 
        print(f"Reader {id} reads {shared_resource}")
		# Lock mutex before checking read count 
        mutex.acquire() 
        # Decrement read count atomically  
        readcount -= 1 
		# Unlock mutex after updating readcount 
        mutex.release() 