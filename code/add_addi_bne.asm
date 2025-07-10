        addi    r1, r1, 5       ; loop counter
        add     r2, r0 ,r0      ; reset result register
loop:   add     r2, r2, r1      
        addi    r1, r1, -1       
        bne     r1, r0, loop

