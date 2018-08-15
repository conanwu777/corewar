.name "for or"
.comment "testing..."

begin:
	or r1,r1,r1
	or r1,r2,r2
	st r2,:end
	or :end,:end,r2
	st r2,:end
	or r2,r2,r2
	or r2,:end,r2
	st r2,:end
	or :end,r2,r2
	st r2,:end
	or :begin,:begin,r3
	st r3,:end
	or %:begin,%:begin,r3
	st r3,:end
	or :begin,%:begin,r3
	st r3,:end
end:
