        addi r1, r0, 10 ; setup
        addi r2, r0, 15 ; setup
        xor r3, r1, r2  ; should set r3 to 101
        addi r4, r0, 2  ; setup
        srl r5, r3, r4  ; should set r5 to 1
        addi r6, r0, -34 ; setup
        sra r7, r6, r4  ; arithemtic right shift

