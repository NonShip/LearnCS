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
