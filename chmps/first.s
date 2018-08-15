.name "first"
.comment "it stays alive"

lbl:
	sti	r1,%:lbl2,%1
	or	%0,%0,r2
	sti	r1,%:lbl,%0
lbl2:
	live	%12
	zjmp	%:lbl2
