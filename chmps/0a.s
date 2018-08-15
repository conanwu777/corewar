.name "for ldi"
.comment "testing..."

begin:
	st r1,:end
	ldi :end,%0,r2
	sub r1,r2,r3
	st r3,:end
	zjmp %:begin
end:
