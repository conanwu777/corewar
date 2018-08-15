.name "for add"
.comment "testing..."

begin:
	xor r1,r1,r2
	add r1,r2,r2
	add r1,r1,r1
	st r1,:end
	xor r1,r1,r2
	zjmp %:begin
end:
