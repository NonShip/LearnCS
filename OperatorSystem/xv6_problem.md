I use riscv64-unknown-elf-gdb  version 10.1  
when debug the xv6, it will show debug information `dwarf2_find_location_expression: Corrupted DWARF expression.` this problem is lack of the DWARF information when complie the problem.  
Solution: add -gdwarf-4 to gcc
