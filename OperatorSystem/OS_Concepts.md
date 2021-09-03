##### 1.2 Computer-System Organization
###### 1.2.1 Interrupt
Interrupt is a key part of how OS and hardware interact. CPU hardware has a wire which can sense the signals from controler.  
1. **nonmaskable interrupt** which is reserved for events such as unrecoverable memory errors.  
2. **maskable interrupt** it can be truned off by CPU to execute some instruction that must not be interrupted.  
interrupt chaining is used so heavily for time-sensitive processing, efficient interrupt handling.  
###### 1.2.2 Storage Structure
##### 1.3 Computer system architecture
###### 1.3.1 Single-Processor Systems
The one main CPU with its core is capable of executing a general-purpose instruction set. They may come in the form of device-specific processors.  
###### 1.3.2 Multiprocessor Systems
The processors share the computer bus and sometimes the clock, memory and devices.  
**symmetric multiprocessing(SMP)**  each peer CPU processor performs all tasks.  
**multicore system** in which multiple computing cores reside on a single chip. On-chip communication is faster than between-chip communication and is less power than muliple single-core chips.  
###### 1.3.3 Clustered Systems
which gathers together multiple CPUs. Clustered computers share storage and are closely linked via a local-area network LAN or others. it provides **high-availability service**(procedure runs on the cluster nodes, each node can monitor one or more of the others. if one monitored machine fails, the monitoring machine can take ownship its storage and restart the application.  
**asymetric clustering** one machine do nothing but monitor the active server. if activer server fails, the machine become active.  
**symmetric clustering** two or more machine run app and monitoring each other.  
**high-performance computing** it needs Parallelization, which divides a program into separate components that run in parallel on individual cores in a cluster.
##### 1.4 OS operation
##### 1.4.2 Dual-Mode and Multimode operation
In order to ensure the proper execution of the system, we must to distinguish user mode and kernel mode which need hardware support that set mode bit.  
##### 1.4.3 Timer  
To make sure that the OS maintains control over the CPU, if a user program get stuck in an infinite loop and never return control to OS. A timer can be set to interrupt the computer after a specified period.  

----
#### 2.1 OS services
1. **User interface** which interaction with OS
2. **Program execution** system must be able to load a program into memory and to run that program. 
3. **I/O operations** for efficiency and protection, users usually cannot control I/O devices directly.
4. **File-system manipulation**
5. **Communications** different processes need to exchange information with other process. **shared memory** and **message passing**
6. **Error detection**
7. **Resource allocation**
8. **Logging**
9. **Protection and security**

##### 2.3.3 Types of System calls
###### 2.3.3.1 Process Control
running program needs to halt its execution either normally(end()) or abnormally(abort()). If the program runs into a problem and causes an error trap, a **dump** memory is taken and error message generated, the dump will be written to a special log file on disk and may be examined by a debugger.
##### 2.8 OS Structure
###### 2.8.1 Monolithic Structure
**Monolithic structure** run entirely in kernel mode in a single address space. it is difficult to implement and extend. Monolithic kernel do have a distinct performance advantage.  
**Microkernels** remove all noessential components from the kernel and implementing them as user-level programs that reside in separate address spaces. It makes extending the OS easier. Different app communicate indirectly by exchangeing messages with the microkernel. Microkernel provides more security and reliability.  
**LKMs(loadable kernel modules** the kernel has a set of core components and can link in additional services via modules, either at boot time or during run time.  
##### 3.1 Process
###### 3.1.3 
PCB(process control block):
1. **Process state**
2. **Program counter**
3. **CPU registers** 
4. **CPU-scheduling information**
5. **Memory-management information** 
6. **Accounting information** 
7. **I/O satus information**
##### 3.2 Process Scheduling
Each CPU can run one process at a time. Sometimes a process needs to request I/O, since devices run significantly slower than processors, CPU will entry into a loop to wait the I/O finished. This problem call **I/O-bound process** spends more of its time doing I/O than doing computations. In contrast, **CPU-bound process** .
###### 3.2.1 Scheduline Queue
To solved the wasted rescourse of CPU, when processes entry the system, they are put into a **read queue** where they are ready and waiting to execute on a CPU's core. **wait queue** for these waiting processes.
###### 3.2.2 CPU Scheduling
**CPU scheduler** is to select from among the processes that are in ready queue and allocate a CPU core to one of them. CPU scheduler executes at least every 100 milliseconds.
###### 3.2.3 Context Switch
Switching CPU core to another process requires save currently process and restore a different process. In xv6, CPU struct and proc struct both have the context struct to save registers. Context-switch times are highly dependent on hardware support.
###### 3.3.2 Process Termination
**zombie process** child process termination but whose parent process has not yet called wait().
##### 3.5 Shared-Memory Systems
Buffers can solved the shared-memory probolem. **unbounded buffer** place no limit on the size of the buffer, producer can always produce new items. **bounded buffer** a fixed buffer size.
##### 3.6 Message-Passing Systems
###### 3.6.1 Naming
***direct communication***  
If differents processes want to communicate, they must send messages to and receive messages from each other by **communication link**.
```C
send(P, message);
receive(Q,message);
```
1. A link is established betweent every process that want to communicate. The processes need to know each other identity to communicate.
2. Between each pair of processes, there exists exactly one link.
Disadvantage: communication need to know each other ID, and is limited modularity 

 
***indirect communication***  
**messages** are sent to and received from mailboxes or ports. Each mailbox has a unique ID, two processes can communicate only if they have a shared mailbox.
```C
send(A, message); send a message to mailbox A
receive(A, message); receive a message from mailbox A  
```
1. A link is established between a pair of processes only if both members of the pair have a shared mailbox
2. A link may be associated with more than two processes.

