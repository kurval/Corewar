.comment "Pleased to meet you"
.name "Besnik"

l1:		live %1
		sti r1, %:live, %1
		fork %:fork

live:	live %1
		zjmp %:l1
		fork %:l1

fork:	live %1
		fork %:live
		live %1
