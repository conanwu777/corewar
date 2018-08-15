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
