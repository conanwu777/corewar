# corewar
A reproduction of the Core War game. Including full implementation of assembly compiler, virtual machine and GUI.

This project was done in collaboration with my friends Liam Dehaudt and Charles Gleason at 42.

Corewar in action (quiet mode, 4 players):
![alt text](https://github.com/conanwu777/corewar/blob/master/4.png)

## Background

Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney, inspired by a malicious virus written in the 80’s. To deal with the self-replicating virus, a white hat hacker invented Reaper. It was a virus designed to spread and eliminate the malware. (for more information, see https://en.wikipedia.org/wiki/Core_War)

The idea was simple. You compete by designing viruses to overtake a computer. You win by protecting your own program and overwriting your opponent's programs. This is all happening on a virtual machine.

## Compiling and running

### Assembler
Run `make` in `asm/` folder. An executable will compile.
Run with:
```
./asm Filename.s
```
A collection of sample .s files included in `sfiles/` folder.

### Virtual Machine
Run `make` in `visualizer/` folder. An executable will compile.
Run with:
```
usage: ./corewar [-dump nbr_cycles] [-q]
[[-n number] champion1.cor] [[-n number] champion2.cor]
[[-n number] champion3.cor] [[-n number] champion4.cor]
```
A collection of complied champion(.cor) files included in `cor/` and `chmps/` folder.

## Sample Game

### Warmup
![alt text](https://github.com/conanwu777/corewar/blob/master/1.png)

### Midfight
![alt text](https://github.com/conanwu777/corewar/blob/master/2.png)

### Endgame
![alt text](https://github.com/conanwu777/corewar/blob/master/3.png)

## Worrior command list

-**and:** bitwise AND over the first two arguments and store the result in a registry, which is the third argument. Opcode 0x06. Modifies the carry.

-**or:** bitwise OR, in the same spirit and principle of and, opcode 7.

-**xor:** Acts like and with an exclusive OR. As you will have guessed, its opcode in octal is 10.

-**add:** Opcode 4. Take three registries, add the first two, and place the result in the third, right before modifying the carry.

-**sub:** Same as add, but with the opcode est 0b101, and uses a substraction.

-**ld:** Take an argument and a registry. Load the value of the first argument in the registry. Its opcode is 10 in binary and it will change the carry.

-**lld:** same as ld, but without % IDX_MOD. Modify the carry.

-**ldi:** use 2 indexes and 1 registry, adding the first two, treating that like an address, reading a value of a registry’s size and putting it on the third.

-**lldi:** Opcode 0x0e. Same as ldi, but does not apply any modulo to the addresses. It will however, modify the carry.

-**st:** take a registry and a registry or an indirect and store the value of the registry toward a second argument. Its opcode is 0x03. For example, st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))

-**sti:** Take a registry, and two indexes (potentially registries) add the two indexes, and use this result as an address where the value of the first parameter will be copied.

-**fork:** no coding byte, take an index, opcode 0x0c. Create a new process that will inherit the different states of its father, except its PC, which will be put at (PC + (1st parameter % IDX_MOD)).

-**lfork:** Same as a fork without modulo in the address.

-**zjmp:** there’s never been, isn’t and will never be an argument’s coding byte behind this operation where the opcode is 9. It will take an index and jump to this address if the carry is 1.

-**aff:** The opcode is 10 in the hexadecimal. There is an argument’s coding byte, even if it’s a bit silly because there is only 1 argument that is a registry, which is a registry, and its content is interpreted by the character’s ASCII value to display on the standard output. The code is modulo 256.

-**live:** The instruction that allows a process to stay alive. It can also record that the player whose number is the argument is indeed alive. No argument’s coding byte, opcode 0x01. Oh and its only argument is on 4 bytes.

