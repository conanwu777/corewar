.name "for lldi"
.comment "testing..."

begin:
	lldi :begin,%0,r2
	lldi %:begin,%0,r3
	st r2,:end
	st r3,:end
	ldi r2,r1,r4
	lldi r2,r1,r5
	ldi r3,r1,r6
	lldi r3,r1,r7
	st r4,:end
	st r5,:end
	xor r1,r1,r8
	st r8,:end
	st r6,:end
	st r7,:end
end:
