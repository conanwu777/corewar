.name "for ld"
.comment "testing..."

begin:
	ld :middle,r2
	ld 60,r3
middle:
	sti r1,r2,r3
	ld %0,r4
	zjmp %:middle
