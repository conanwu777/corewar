.name "for lfork"
.comment "testing..."

begin:
	lfork %:end
	live %:end
	lfork %728
	live %:end
	fork %728
end:
