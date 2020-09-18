#champion by jmetelin (jmetelin@student.hive.fi)

.name "Zorkbuster"
.comment "Who you gonna call? Zorkbuster!"

#fills the empty positions by lives




#store the player id (from the registry 1) to the live

#cycles before execution: 5, accumulation of cycles: 5
#03 70 01 00 1E
st r1, 30




#load the values



#load the first 4 bytes from the live to the registry 2

#cycles before execution: 5, accumulation of cycles: 10
#02 D0 00 18 02
ld :live, r2



#load the last byte from the live to the registry 3

#cycles before execution: 5, accumulation of cycles: 15
#02 D0 00 17 03
ld 23, r3



#load the relative address from the first sti to the first empty position (20)
#to the registry 4

#cycles before execution: 5, accumulation of cycles: 20
#02 90 00 00 00 14 04
ld %20, r4



#load the size of the live (5) to the registry 5

#cycles before execution: 5, accumulation of cycles: 25
#02 90 00 00 00 05 05
ld %5, r5




#loop



#live

#cycles before execution: 10, accumulation of cycles: 35
#01 00 00 00 00 ->
#01 FF FF FF FF | 01 FF FF FF FE | 01 FF FF FF FD | 01 FF FF FF FC
live: live %0



#print the live to the first empty position


#print the first 4 bytes of the live (from the registry 2) to the first empty
#position (the relative address from the registry 4)

#cycles before execution: 25, accumulation of cycles: 60
#0B 58 02 04 00 00
sti r2, r4, %0


#print the last byte of the live (from the registry 3) to the end of the first 4
#bytes of the live (the relative address from the registry 4 - 2)

#cycles before execution: 25, accumulation of cycles: 85
#0B 58 03 04 FF FE
sti r3, r4, %-2



#update the relative address from the first sti to the first empty position
#(from the registry 4) by adding the size of the live (from the registry 5) to
#the relative address (from the registry 4)

#cycles before execution: 10, accumulation of cycles: 95
#04 54 04 05 04
add r4, r5, r4



#make a copy of the carriage to the beginning of the loop

#cycles before execution: 800, accumulation of cycles: 895
#0C FF EA
fork %:live
