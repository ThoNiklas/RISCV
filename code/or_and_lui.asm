        addi r1, r0, 10 ; setup
        addi r2, r0, 1 ; setup
        or r3, r1, r2 ; should set r3 to 1011
        and r4, r1, r2 ; should set r4 to 0
        addi r2, r0, 2 ; setup
        and r5, r1, r2 ; should set r5 to 10
        lui r6, 8095    ; 

