.name 		"turtle"
.comment	"TESTING"

loop:
        sti r1, %:live, %1
live:
        live %0
        ld %0, r2
		add	r2, r3, r2
        zjmp %:loop

################################################################################
