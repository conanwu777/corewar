.name "for sti"
.comment "testing..."

begin:
	sti r1,:end,%0
	sti r1,%:end,%4
	sti r1,%0,r2
	sti r1,r2,%0
	st r1,r2
	sti r1,r2,%0
end:
