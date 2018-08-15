.name "The best champion"
.comment "...arguably"

beginning:
	xor r1,r1,r16
	st r1,r15
	sti r15,%:living,%1
	sti r16,:beginning,%0
	sti r16,:beginning,%4
	sti r16,:beginning,%8
	sti r16,:beginning,%12
	ld %16,r10
	ld %197,r9
	ld %43057151,r2
	ld %4290775043,r3
	ld %1879572544,r4
	ld %33554431,r5
	live %1
	fork %:end
	xor r1,r1,r16
living:
	live %0
	sti r2,r9,%0
	sti r3,r9,%-2
	sti r4,r9,%-4
	sti r5,r9,%-6
	add r9,r10,r9
	xor r1,r1,r16
	zjmp %:living
middle:
	ld %-64,r8
	st r8,64
	ld %-64,r8
	st r8,64
	ld %-64,r8
	st r8,64
	ld %-64,r8
	st r8,64
	ld %-64,r8
	st r8,64
	ld %-64,r8
	st r8,64
	ld %-64,r8
	st r8,64
	sti r2,r11,%48
	sti r3,r11,%48
	sti r4,r11,%48
	sti r2,r11,%48
	sti r3,r11,%48
	sti r4,r11,%48
	sti r2,r11,%48
	sti r3,r11,%48
	sti r4,r11,%48
	sti r2,r11,%48
	sti r3,r11,%48
end:
	live %1
	fork %:post_end
	xor r1,r1,r16
	zjmp %:end
post_end:
