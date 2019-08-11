; file ps.as
.entry   LIST
.extern  W
.define  sz = 2
.define size = 8 
MAIN:    mov r3, LIST[sz]
LOOP:    jmp W
         prn #-5
 	 mov STR[5], STR[2]
         sub r1,r4
         cmp K, #sz 
         mov #-1,r6
         mov #size, r5
         add r6,r5
                  lea sz , r4
         bne W
         not r3
L1:	 inc L3
.entry LOOP
         bne LOOP
         clr r0 
         inc r0
END:     stop
.define len = 4
STR:     .string "abcdef"
LIST:    .data 6, -9, len
K:       .data 22
.extern  L3
