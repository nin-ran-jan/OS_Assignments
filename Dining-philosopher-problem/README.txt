Q1.

To run the file, use ./prob1 after making.

There will be a deadlock. This is because, there can be a case where each philosopher grabs the fork on their left.
A deadlock is a condition where no work is done in processing and everyone is waiting for everyone to finish.
To avoid this problem, we use semaphores.

We have initialzed a counting semaphore called room. This basically ensures that 
the philosophers entering the room are in a certain critical section of sorts. 
You can only complete work if you are in a critical section. 

Once there are philosophers in a critical section, we can ensure that no deadlock happens.
Even if every philosopher in the section picks up a fork, THERE NEEDS TO BE SOME WORK DONE in the room.

In our case, with 5 forks and 5 philosophers, we need the critical section to accomodate 4 philosophers.
This is because, in the critical section, there are going to be 4 philosophers and 5 forks.
This ensures that at least one philosopher in the critical section has at least 2 forks with them.
Using Pigeonhole principle.

Therefore, in the criticl section, work is always going to be done.

To ensure proper circulation in the critical section, we necessitate that each philosopher will
leave the critical section after their process is complete. THIS PREVENTS HOGGING IN THE PROCESS.

Q2.

There will be no deadlock created in the problem.
This is because there are 5 philosophers, and each philosopher can use only one fork at a time.
This ensures that AT ALL TIMES, there is AT LEAST 1 philosopher with 1 spoon. Hence, work is always taking place.
To increase the processing speed, we could assign a fork to each philosopher and thus, 
they can eat whenever they want.
But even in case there is no such mechanism, A DEADLOCK WILL NEVER HAPPEN.
There can be times, when a philosopher cannot eat (the fork on the left is taken by the philosopher sitting on the right
and vice versa) but, there is always at least 1 philosopher (2 right in front of us) that are processing.

Q3.

Run using ./prob3 after making.

In this case, there will be a deadlock created if the bowls are unevenly distributed.
A deadlock can occur in the following way:
	Phil0 has 2 forks,
	Phil1 to Phil3 has 1 fork and 1 bowl,
	Phil5 has 1 bowl.
Here, we can ask the philosophers to wait in the critical section where there are 4 bowls and 5 forks.
In this critical section, 
    there will be ATLEAST 1 philosopher with 2 forks and 1 bowl.

Hence, this critical section will never deadlock. The rest of the approach is similar to the first question.

