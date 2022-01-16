README

For question 1:

    General Overview:
    In this question, we basically need to handle signals communicating from one file to another.
    In Linux operating systems, there is a way to communicate between multiple processes. We do this using signals.

    Parent Process:
    We start with creating 4 processes (3 children and 1 parent). Each process has an infinite loop associated with it.
    We need this infinite loop to keep the processes communicating as long as we interrupt them using 'Ctrl+C'.

    S1 Process:
    In the first child (S1), we create a signal termination handler.
    Basically, whenever a process is killed using the SIGTERM signal, we start this signal terminating function.
    We do this using the sigaction struct and the sigaction() function.
    This tells the processes that whenever it is terminated with the SIGTERM signal, execute S1's signal termination handler function.
   
    SR Process:
    We then continue and go on to the SR process.
    To go to SR child program 'S1.c', we use the execl function and as arguments, we provide it with the PID of the S1 process.
    The PID is provided to call the S1 signal termination handler function.
    Once we are in SR, there is no way for this child process to go back to the parent process.
    We set a timer using struct itimerval and function setitimer() to call a SIGALRM after every second.
    In every one of these cycles, we send a SIGALRM signal to the signal alarm handler function in SR.
    This then uses the random number generator function (that uses rdrand and inline assembly) to create a random number.
    The alarm handler then enqueues the random number to the signal queue, and calls the SIGTERM signal, leading back to S1.
   
    ST Process:
    We then continue to the ST process.
    <I am avoiding repeating what I have said before in the SR process. There are a lot of similarities in SR and ST.>
    We use 2 sigactions, 1 to call the alarm handler and the other to call the termination handler.
    The alarm handler uses inline assembly and rdtsc to generate the CPU clock cycles.
    This enqueues the cycles to the sigqueue and sends it back to the S1 child, using the SIGTERM signal.
    It also uses SIGTERM to go to its own signal termination handler.
    In this signal termination handler, the human-readable version of the CPU Cycle count is printed.

    How to calculate CPU run time from CPU cycles:
    The CPU basically constantly runs at a very high speed (2.4 GHz for my laptop).
    2.4 GHz implies that in 1 second, my CPU completes 2.4*10^9 cycles.
    To obtain the number of seconds my CPU has been running, I basically need to divide the CPU cycles by the frequency.
    Hence, I obtain the hours, minutes and seconds that state how long my machine has been running.
    The signal termination handler then prints the result for the user.

    This concludes the first question.

For question 2:

    Overview:
    In this question, we basically go into the Linux system directories and write a C function for our system call.
    We need to define system calls in a particular way in C. This is done using SYSCALL_DEFINE<no. of parameters>.
    The first parameter contains the name of the system call; for our program it is kernel_2d_memcpy.
    The following parameters defined are the types of the parameters, followed by the variable names of the parameters.
    There are 4 parameters in the system call defined by me.
    Therefore, the SYSCALL_DEFINE4 will contain 9 parameters: 1 + (2*4).

    Then, we 'make' the kernel and run a set of commands to add the syscall to the Linux kernel.

    System Call Code Logic:
    To code, the system call, firstly declare a 2-d float type array. This is our temporary matrix.
    We use the number of rows and columns to allocate memory for the temp matrix from the parameters provided to us.
    Now, we use the copy_from_user() function to copy the data of the second matrix parameter into the temporary matrix.
    Then, we copy the data from the temp matrix into the first matrix parameter using the copy_to_user() function.

    In case of an error, we return -EFAULT. This is a negative error number for the failure of our code.
    If the function successfully copies the data of the matrices, we return 0 for success.

    Program Logic:
    We initialize a matrix with certain initial values. We print this matrix.
    Then, we declare another matrix with different values and call our system call with appropriate parameters.
    We print the matrix once again and observe.
    We see that the matrix printed has successfully changed its values.

    This concludes the second question.

ENDOFREADME
