.name "for fork"
.comment "testing..."

begin:
	fork %:middle
	live %:begin
	fork %:middle
	live %:end
	fork %:end
	aff r1
middle:
	aff r1
	aff r2
	aff r1
end:
