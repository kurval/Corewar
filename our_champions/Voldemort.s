.name "Lord Voldemort"
.comment "I'm here to destroy"
		
loop:
        sti r1, %:live, %1
        fork %:live
        fork %:destroy

live:
        live %0
        st r1, r2
        and	r1, %0, r3
		sti r1, r3, r1
        zjmp %:loop

destroy:
        sti r1, r3, %42
