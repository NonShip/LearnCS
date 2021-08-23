- ##### Why this lab?
	Unix operator system is a microkernel, so that user operation must trap into kernel to read or write data from disk. The kernel page table of unmodified xv6 is a direct mapping to physical address. If the kernel wants to use the data in user space, it must first translate the user virtual address to attent a physical address. It is not a good design.  
The goal of this lab is to sovle this problem.   
	- add a kernel page table for every process  
		1. modeify the function `procinit` in unmodified xv6, `procinit` will allocate a page of kernel stack for every process. The goal of the process having a kernel stack is to make sure current register status don't be changed by other process when schedul to other process
			that page table is  a bad design to allocate a page for OS. We want to allocate a kernel stack when allocate a process, so the solution is allocate a kernel page table when allocate a process.
```c
	static struct  proc* allocproc(void)  {
	//....
	   p->kernelpagetable = kvmmake();
	   char *pa = (char*)kalloc();
	   if (pa == 0){ 
	       panic("kalloc");
		}
	   uint64 va = TRAMPOLINE - 2*PGSIZE;
	   mappages(p->kernelpagetable, va, PGSIZE, (uint64)pa, PTE_W | PTE_R);
	   p->kstack = va; 
	//....
	}
``` 
xv6 is a timing shared machine, so different process will shared limited CPU. The scheduler of OS will schedule different process. Scheduler will exchange all of process register to save current status, make sure the process will restored. So we need to modified XV6 to satified this goal.		
```c
void scheduler(void) {
//...
w_satp(MAKE_SATP(p->kerenlpagetable); //this is RISC-V instruction of saving data to satp register
sfence_vma(); // flush page table entry
kvminithart(); // no process is running, we use the first process kernel page table
//...
}
```
Now, we run the xv6, we find it's OK! There is a problem, however, we allocate a page, and we don't release this page, this will be a memory leak!
we need release this page when process is free.
```c
void uvmfreeproc_kernelpagetable(pagetable ,uint64 kstack, uint npages) {
	uvmunmap(kernelpagetable, kstack, npages,1);
	freewalk(kernelpagetable);
}
void proc_freekernelpagetable(pagetable_t kernelpagetbale, uint64 kstack, uint64 sz) {
//first unmap all of kernel page table, then unmap and free kernel stack of process,
//at least, free all of kernel page table(include data of user space, next lab)
//pseudocode 
	uvmunmap(UART0);
	uvmunmap(VIRTIO0);
	uvmunmap(PLIC);
	uvmunmap(KERNBASE);
	uvmunmap(extext);
	uvmunmap(TRAMPOLINE);
	uvmunmap(0,PGROUNDUP(sz));
	uvmfreeproc_kernelpagetable(kernelpagetable, kstack);
}	

static void freeproc(struct proc *p) {
	if (p->kernelpagetable) {
		proc_freekernelpagetable(p->kernelpagetable, p->kstack, p->sz);
	}
p->kernelpagetable = 0;
}
```
	
