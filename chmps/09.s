.name "for zjmp"
.comment "test8hgl"

begin:
	zjmp %:two
one:
	xor r1,r1,r2
	zjmp %:four
two:
	and r1,r1,r1
	zjmp %:five
three:
	xor r1,r1,r2
	zjmp %:three
four:
	and r1,r2,r3
	zjmp %:five
five:
six:
seven:
eight:
nine:
ten:
end:
