##### Why this lab?
xv6 is a microkernel operator system, so user needs kernel to do some operation(syscall, interrupt, faults).   
How the user tells kernel to do something?   
Answer is trap!  
What needs to happen when user wants kernel to do something(such as write syscall)? 
1. save user status ==> uservec
2. switch to supervisor mode
3. switch to kernel page table
4. switch to kernel stack
5. jump to kernel C code
6. execute kernel code and finish
7. save kernel status to trampframe 
8. restore user status from trampframe

RISC-V ecall will do: 
1. change user mode to supervisor mode
2. save pc tp sepc
3. jump to sepc

lab backtrace
design a backtrace function return stack frame when invoke a function 
```c
static inline uint64
r_fp()
{
  uint64 x;
  asm volatile("mv %0, s0" : "=r" (x) );
  return x;
}
```    
will return stack frame pointer of the currently executing function  
xv6 stack struct:  
	`	return address`     
	`	previous fp `   
	`	saved registers `   
	`	local variables `   
		`...`   


lab alarm
The goal of this lab is to finish a syscall `sigalarm(int ticks, void(*handler)())`  every tick, the hardware clock forces an interrupt, invoking the alarm function handler().  
usertrap will handle this problem, `which_dev == 2` is the timer interrupt. we need to add a interval and spend in struct proc. Every timer interrupt will increase spend, if spend is equal to interval, invoking the handler()
```C
kernel/proc.h
struct proc {
...
int interval;
int spend;
void (*handler)();
}
```  
```C 
kernel/trap.c
void usertrap(){ 
else if((which_dev == devintr()) != 0) {
	if (which_dev == 2) {
		p->spend++;
		p->traframe->epc = (uint64)p->handler; //when usertrap is finish, it will invoke usertrapret, the PC will set to function handler()
	}
	}
}
```
```C
kernel/sysproc.c
uint64
sys_sigalarm(void) {
	struct proc *p = myproc();
	int interval;
	if (argint(0, &interval) < 0) {
		return -1;
	}
	p->interval = interval;
	uint64 func;
	if (argaddr(1, &func) < 0) {
		return -1;
	}
	p->handler = (void(*)())func;
}
```

when run alarmtest, the screen will print ....alarm! in loop. The problem is we invoking the function handler(), but the function don't return to original function. which means we loose the original process.  
So the solution is to save the status of process before call function handler. We save the status in a new trapframe of proc.    
```C
kernel/proc.h
struct proc {
...
struct trapframe *savetrapframe;
}
```  
```C
kernel/trap.c
void switch_proc_trapframe(struct trapframe *trapframe_source, struct trapframe *trapframe_dest) {
	int N = sizeof(struct trapframe)/sizeof(uint64);
	for (int i = 0; i < N; i++) {
		*((uint64*)trapframe_dest) = *((uint64*)trapframe_source);
	}
}
void usertrap() {
else if ((which_dev == devintr()) != 0) {
	if (which_dev == 2) {
		p->spend++;
		switch_proc_trapframe(p->trapframe, p->savetrapframe);
		p->trapframe->epc = (uint64)p->handler;
	}
	}
}
```


the goal of test2 is avoiding realarm. We need a flag to solve this problem.
```C
kernel/proc.h
struct proc {
...
int waiting;
}

void usertrap() {
else if ((which_dev == devintr()) != 0) {
	if (which_dev == 2 && p->waiting == 0) {
		p->spend++;
		switch_proc_trapframe(p->trapframe, p->savetrapframe);
		p->trapframe->epc = (uint64)p->handler;
		p->waiting = 1;
	}
}
}	

kernel/syscall.c
uint64
sys_sigreturn() {
	struct proc *p = myproc();
	switch_proc_trapframe(p->savetrapframe, p->trapframe);
	p->waiting = 0;
	return 0;
}

```
