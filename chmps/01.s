.name "For live"
.comment "Sure is"

begin:
	sti	r1,%:loop,%1
	or	%0,%0,r2
loop:
	live	%12
	zjmp	%:loop
