.name "for sub"
.comment "testing..."

begin:
	add r1,r1,r2
	sub r1,r2,r1
	st r1,:end
	sub r1,r1,r3
	zjmp %:begin
end:
