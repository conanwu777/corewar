.name "for and"
.comment "testing..."

begin:
	and r1,r1,r1
	and r1,r2,r2
	st r2,:end
	and :end,:end,r2
	st r2,:end
	add r2,r2,r2
	and r2,:end,r2
	st r2,:end
	and :end,r2,r2
	st r2,:end
	and :begin,:begin,r3
	st r3,:end
	and %:begin,%:begin,r3
	st r3,:end
	and :begin,%:begin,r3
	st r3,:end
end:
