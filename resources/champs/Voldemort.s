.name "Lord Voldemort"
.comment "I'm here to destroy"
		
loop:
        sti r1, %:live, %1
live:
        live %0
		ld %1, r2
        and	r1, %0, r3
		sti r1, 5, r2
        zjmp %:loop
