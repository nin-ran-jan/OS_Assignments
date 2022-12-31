README

makefile:
    Command to run the file:
        make
    Command to clean the made files:
        make clean
    Command to execute all the made files in one go:
        make run

NOTE:
    Almost all system calls return -1 for an error and 0 for a success.
    There are some exceptions to this, I have mentioned them below.
    All my error cases have been handled based on these errors that are provided in the system calls.

Q1:
    This question mainly deals with opening, reading and closing a file.

    open()
    The parameters of this system call are the file name, and the mode in which we want the file to be opened.
    Here, I have provided the mode as O_RDONLY, which means the file can only be read from.

    read()
    The parameters are the file descriptor of the open file, the pointer location of the character/string to where the data is being stored, and the size of the data being read.
    It returns the size of the data read by it (if not an error).
    In my program, since I am reading the file character by character, the read syscall will return either 1 or 0.
    If it returns 0, it means it has finished reading the file, and 0 bytes are being read.

    close()
    It closes the file, opened by the file descriptor.
    It takes the parameter of the file descriptor.

    CODE LOGIC:
    I take the file, split it into lines (divide them using the "\n") and then seperate it further based on the ",".
    If the section provided corresponds to the function parameter ("A" or "B"), and is on the 2nd column of the line, I store all the next 6 assignments' marks.
    I use an array to calculate the total cumulative marks of a section based on the assignment, and then divide it by the row count to obtain the average.

Q1a:
    The first part basically covers the fork(), waitpid() and getpid() system calls.

    fork()
    When fork() is called, it creates a child process of the process that is currently running (the parent process).
    If the child process is successfully created, it will return 0, and return the process ID of the child process to the parent process.

    waitpid()
    The waitpid() system call basically waits for the execution of the child process first, and then allows the parent process to execute.
    Otherwise, any process could be executed first, the parent or the child.

    getpid()
    The getpid() system call returns the PID of the process being executed.
    This system call is always successful.

Q1b:
    The second part basically covers the pthread_create(), pthread_join() and pthread_exit() system calls.
   
    pthread_create()
    This syscall creates a pthread. A pthread is a process thread and is very effective for parallel processing of the code.
    When a pthread is created, it is more efficient than the fork() system call.
    This is because an entire process is not being created.
    It is only a thread and has lesser memory usage and thus, faster execution.
    The parameters of pthread_create() are thread ID, thread parameters, function to run in the thread, and arguments of the function called in the thread (they need to be (void *)).

    pthread_join()
    This system call joins the thread with the main process of the program.
    It waits for the current thread to terminate its execution.
    The parameters are the thread ID and a return value pointer (void *).

    pthread_exit()
    This syscall terminates the calling thread.
    This function is always successful.
    The parameters are the return values of type (void *).

    P.S.
    Sometimes, upon executing multiple times with small intervals, my program throws a Segmentation Fault.
    This happens if the OS is overloaded with pthread syscalls.
    In case you encounter this, please run my code again.

Q2:
    The second question deals with integrating assembly language with C.

    main()    
    The first call is of main() which in turn calls the function A().


    A()
    Taken a long input (64 bit unsigned integer input) from the user.
    Then, extern the B.asm file and set a long input parameter to it.
    We include C.c in the code as well, to give it a reference in B.
    We then call B() with the long input passed as an argument.


    B()
    Reserved 8 bytes for the string that is going to be printed (in the section .bss).
    Created a set string to print - added this as a custom to show I am in B.asm.
    Created a global B function, to execute and call.
    Then, extern C.c in B.asm to call it from the function B().

    Started the execution of the function B.

    Popped the value of the return address to A from the stack.
    This ensures that the code does not jump back to A() after finishing execution.

    Pushing the C() function into the stack.
    This will cause the next execution to be of the function C (after B() terminates).
   
    The rdi register stores the argument that was provided to B() from A().
    We move this value into the memory location we reserved in .bss.
    When it is printed, it will not print the value of the long.
    Instead, it will print the ASCII value stored inside the memory location.
    This causes the output to be the required string, which we needed as an output.

    Then we call the syscall write() - ID=1, stored in rax
    We choose to print the value in STDOUT - ID=1 - stored in rdi
    We choose the string that we want to print - ID=<name of variable initially declared in .data> - stored in rsi
    We choose the maximum number of bytes as 22 (corresponding to the number of bytes in the string) - ID=22 - stored in rdx
    We call this system call.

    We call the syscall write() again - ID=1, stored in rax
    We choose to print the value in STDOUT - ID=1 - stored in rdi
    We choose the string that we want to print - ID=<string converted from long, declared in .bss> - stored in rsi
    We choose the maximum number of bytes as 8 (corresponding to the number of bytes in the string) - ID=8 - stored in rdx
    We call this system call.

    There is a particular format to calling system calls from a function in ASM.
    The values stored in the registers are placed accordingly, keeping in mind what we need to do and how we need to do it.
    Every system call uses the parameters in the following way:
        ID -> rax
        args[1,2,3,4,5,6] -> {rdi, rsi, rdx, r10, r8, r9}
   
    Finally, we call ret in B.asm.


    C()
    Final print commands in C.
    Exiting from the code.

END