# Corewar

![vm](corewar.gif)  
*```The virtual machine visualizer (using ncurses library)```*

## Description  
COREWAR is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer. These battle programs are written in an abstract assembly language called Redcode.  

This project can be broken down into three distinctive parts:  

• **The assembler:** This is the program that will compile champions and translate them from the assembly language into “Bytecode”. Bytecode is a machine code, which will be directly interpreted by the virtual machine.  

• **The virtual machine:** It’s the “arena” where champions will be executed.
It offers various functions, all of which will be useful for the battle of the champions.

• **The champion:** Our task was to write the champion in assembly language which will fight in the arena against other champions.

## Usage
### Assembler:  
```./asm [-h] [-e] [-d DIR] [-x] [-f FILE] [-l] <sourcefile.s> or: ./asm -z [-d DIR] <sourcefile.cor>```  

**Assembler options:**  
**-h** : prints the usage

**-e** : prints all the errors instead of only the first one

**-d** : DIR creates the .cor file to the directory DIR

**-x** : prints the hexdump

**-f** FILE : names the .cor file FILE

**-l** : prints memory leaks

**-z** : disassembles a .cor file to a .s file  

### Corewar:  
```./corewar [-dump N | -d N] [-a] [-l] [-v] [[-n N] file.cor] ```  

**Corewar options:**  
**-n** : This flag assigns an id number to the specified champion. And players who did not receive such a number using the flag, first of the unused id's will be assigned

**-dump** : At the end of nbr_cycles of executions, the program dumps the memory on the standard output and quit the game. The memory is dumped in the hexadecimal format with 32 octets per line.

**-d** : At the end of nbr_cycles of executions, the program dumps the memory on the standard output and quit the game. The memory is dumped in the hexadecimal format with 64 octets per line.

**-a** : Prints output from "aff" (Default is to hide it)

**-l** : For each valid execution of the live instruction, the machine display: A process shows that player X (champion_name) is alive.

**-v** : A graphic interface for the virtual machine using nCurses.  

## Compiling  
You can clone this repository and compile both of the programs by running following command inside of your terminal:  
```git clone https://github.com/kurval/Corewar.git corewar && cd corewar && make```  

## Contributors:  
[@anntuomi](https://github.com/anntuomi) : assembler, test scripts  
[@janettem](https://github.com/janettem) : assembler, vm operations  
[@Konjuhaj](https://github.com/Konjuhaj) : vm parsing, deassembler  
[@kurval](https://github.com/kurval) : vm execution, operations, visualizer  
