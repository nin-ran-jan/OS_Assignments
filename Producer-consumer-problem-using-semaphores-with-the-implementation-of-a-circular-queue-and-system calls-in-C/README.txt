README

In this question,
use the command ./prod and ./cons to run the producer and consumer respectively.
Please do this after running the makefile.

In this assignment, we have bsaically implemented a circular queue in the linux kernel sys.c file.

We access this queue using the reader and writer functions. In the reader function, we read unsigned long long integers from the queue.
In the writer function, we write unsigned long integers to the queue. We use the /dev/urandom folder to generate a pseudo random number in the kernel.

In the syscall, we basically have 3 semaphores -> producer, consumer and mutexLock.

The producer/consumer is a counting semaphore and ensures that tells us how many instances of the queue are being accessed.
If this number is 5 (as is initially set in case of producer), this implies that 5 files in the queue can be accessed for consumer. 
The opposite logic works for the consumer.
Therefore, any instance where the value of the semaphore goes below 0 (or above length of the circular queue), 
there will be no access provided to the queue for the function (read or write depending on the semaphore).
The mutex lock is a binary semaphore, and ensures that there is no cross access between the reader and writer -> 
files aren't read and written at the same time.

The logic for reading the number from urandom is commented in the code.