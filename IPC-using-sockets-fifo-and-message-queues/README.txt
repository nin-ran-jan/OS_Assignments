Question 2:

Sources - https://man7.org/linux/man-pages/man7/unix.7.html
https://man7.org/linux/man-pages/man7/mq_overview.7.html
https://man7.org/linux/man-pages/man7/fifo.7.html

1. Unix domain sockets
    The first program deals with IPCs using Unix domain sockets.
    There are 2 files - 1receiver.c and 1sender.c; these are analogous to P2 and P1 respectively.

    1sender.c (P1) [run AFTER 1receiver.c with command ./1sender]
    In the sender, 50 random strings are generated and are stored in the characterArray (a 2-D array of characters).
    Then, the socket creation process begins. Using the AF_UNIX family, we create a socket. 
    We also use the SOCK_SEQPACKET type. 
    This guarantees that the packets of data flowing through the socket are sequential in nature.

    After this, we launch the connection of the socket.
    This connects the client to the server (1sender.c to 1receiver.c) through the given socket.
    Now, using basic logic, the client file sends 5 random strings to the server. 
    We use the write system call for the same.
    After sending 5 strings, it sends and "END" signal, indicating that one batch has completed sending its data.

    Now, let us look at the server part of the code.

    1recevier.c (P2) [command ./1receiver]
    Similar to the client, the server also creates a socket with the same family and the same type.
    We bind this socket to the socket name and we listen from the server.
    When listening from the server, we are constantly hearing for connections from the client to be sent to the server.
    Once we have listened to the socket, we accept the connection from the same.
    Now, my program, using basic logic, reads each random string sent from the client and prints it along with the ID.

    EACH RANDOM STRING GENERATED IS MADE UP OF 20 RANDOM CHARACTERS PLUS ONE ENDING INDEX PARAMETER.
    THIS IS THE SAME FOR ALL PROGRAMS.  
    
    Then, writes back to the client the string received with the HIGHEST INDEX.
    After 5 strings have successfully been read, the server recieves and "END" string.
    Now, the control shifts back to the client.

    1sender.c (contd.)
    The client recieves the index of the highest string, and prints out the result.
    Now, it gets back to writing 5 strings to the server.

    The following process repeats and continues till 50 strings are sent.
    Then, the programs end with the closing the connections and unlinking the sockets.

2. FIFO
    This program deals with FIFOs.
    There are 2 files 2receiver.c (P2) and 2sender.c (P1).

    2sender.c (P1) [run BEFORE 2.receiver with command ./2sender]
    The basic flow of the program is similar to the 1st one, with the differences between the two observed below.
    To create a fifo, we use the command mkfifo(). We specify the 0666 protocol, for the read and write functionality.

    Unlike the first program, we do not check for any signals like "END".
    We simply send the strings in a bunch of 5.
    The program needs to send strings one after another. 
    But because of the speed at which the program runs, this is not possible in the program.
    Therefore, we give a sleep() command to prevent misreading of information.
    
    We the open the fifo, write and read in the fifo, and close the fifo based on the flow of the program.
    In the program, I use 2 fifos - one for communicating from client to server, and one for server to client.
    
3. Message Queues
    This program deals with message queues.
    There are 2 files 3receiver.c (P2) and 3sender.c (P1).

    3sender.c (P1) [command ./3sender]
    The basic flow of the program is similar to the 2nd one, with the differences between the two observed below.
    This program also creates 2 message queues, one for sending information and the other for receiving.

    msgget() creates a message queue, for reading and writing, it uses 0666 protocol for reading and writing.
    msgsnd() and msgrcv() are used for reading and writing.
    msgctl() is used for terminating the message queue.

    In case of program hazards, we need to terminate the IPC message queues.
    To do this use the commands ipcs -q to list the running message queues.
    Then, use ipcrm -q <message queue number> to remove the mesaage queue.
    
Question 1:

In this question, we need to modify the vruntime of the Linux scheduler.
Then, we will create a system call to see how the system has impacted it.

In sched.h, we add the time_lag parameter.
In core.c, we initialize time_lag to 0.
In fair.c, (the CFS scheduler for Linux) we add the time_lag parameter to the vruntime. 
    Therefore, when the min_vruntime is calculated, 
    the time lag parameter ensures that the delay reduces the chances of a program being called.
In sys.c, we add the system call. In the system call, we take 2 parameters.
    We add a time_lag parameter to the pid. 
    Therefore, we need the time_lag parameter and the pid as parameters.
    We also convert the time_lag to nanoseconds from milliseconds.
    We also use the pid_task() to find the task corresponding to the pid.
In syscall_64.tbl, we add the system call we added to the kernel.
