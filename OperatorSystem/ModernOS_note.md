##### 1.3 computer hardware
###### 1. Process CPU
1. fetch instruction from memory
2. decode instruction to determine its types and operands
3. execute instruction  
  
Each CPU has a specific set of instructions that it can execute, so inter CPU can't execute ARM programs.  
To improve performance, mordern CPU will fetch, decode and execute instruction at the same time. This called pipeline.  
A better design is that puts fetch and decoded instruction into a buf, then execute as like a query.  
User space and kernel space make OS secuity. This designs makes all instruction involving I/O and memory protection are disallowed in user mode. Syscall will solved this problem.   

###### 2. Memory  
1. register: internal to CPU, as fast as CPU  
2. cache: as a buf between CPU and main memory. cache hit and cache miss. L1 cache is always inside the CPU and feeds decode instruction into CPU's execution engine(16KB). L2 cache holds several megabytes of recently used memory words.
3. main memory: RAM(Random Access Memory) if volatile miss, the data miss too. ROM(Read Only Memory) nonvolatile memory (e.g. boot code). CMOS memory is volatile, holds the current time, date and configuration parameters(which disk to boot from). It draws little power.

###### 3. I/O devices  
I/O devices consist of two parts: a controller and device.OS will sees interface to the controller. Controler has a small number of registers to communicate with OS and devices. Interrupt is very important in OS.  
Three different ways to finished I/O  
1. a tight loop continuously polling the device to see if it is done.  
2. If I/O is finished, then the controller will signals interrput controller. Interrput is just a pin on the CPU chip. It puts number of the device on the bus so CPU can read it and know device has finished.   
Once CPU take the interrupt, CPU will switched into kernel mode.
