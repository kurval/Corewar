.name "Matti"
.comment "Please don't hurt me :("

setup:
sti r1, %:live, %1
live: live %61773
#st	r1, :setup
#st	r2, -6
and	 %61774, r1, r3
#st	r3, :setup
zjmp %:setup
start:	
live %61774
live %61774
live %61774
live %61774
live %61774
live %61774
xor	 %61774, r1, r3
zjmp %:setup
fork %:start
live %61774
live %61774
live %61774
live %61774
live %61774
live %61774
xor	 %61774, r1, r3
zjmp %:setup
fork %:start
live %61774
live %61774
live %61774
live %61774
live %61774
live %61774
xor  %61774, r1, r3
zjmp %:setup
fork %:start
