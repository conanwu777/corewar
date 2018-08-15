.name "for xor"
.comment "Testing..."

begin:
	xor r1,r1,r1
	xor r1,r2,r2
	st r2,:end
	xor :end,:end,r2
	st r2,:end
	xor r2,r2,r2
	xor r2,:end,r2
	st r2,:end
	xor :end,r2,r2
	st r2,:end
	xor :begin,:begin,r3
	st r3,:end
	xor %:begin,%:begin,r3
	st r3,:end
	xor :begin,%:begin,r3
	st r3,:end
end:
