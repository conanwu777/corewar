.name "conan"
.comment "I kinda suck"

start:	sti r1, %:live1, %1
		sti r1, %:live2, %1
		sti r1, %:live3, %1
		sti r1, %:live4, %1
		ld %16843009, r3
		ld %500, r2
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
live1:	live %0
fork:	fork	%:out
		and r2, %0, r2
live2:	live %0
fork2:	fork 	%:out
		and r2, %0, r2
live3:	live %0
fork3:	fork 	%:out
		and r2, %0, r2
live4:	live %0
fork4:	fork 	%:out
		and r2, %0, r2
out:	ld %67, r3
		aff r3
		ld %111, r3
		aff r3
		aff r3
		ld %108, r3
		aff r3
		ld %0, r3
		st r1, r3
		st r1, r4
		st r1, r5
		st r1, r6
		st r1, r7
		st r1, r8
		st r1, r9
		st r1, r10
		st r1, r11
		st r1, r12
		st r1, r13
		st r1, r14
		st r1, r15
		st r1, r16
		sti r15, %:live5, %1
live5:	live %0
		ld %16843009, r3
		ld %500, r2
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
		ld %16843009, r3
		ld %500, r2
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
		sti r3, r2, %3
		aff r3
		sti r1, r2, %0
		sti r15, %:live6, %1
live6:	live %0
