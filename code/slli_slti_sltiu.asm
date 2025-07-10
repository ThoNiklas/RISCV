        addi r1, r0, 10 ; setup
        slli r2, r1, 5  ; should shift r1 in r2 by 5 to the left
        slti r3, r1, 20 ; should set r3
        slti r3, r1, 4095  ; should not set r3
        sltiu r4, r1, 4095 ; should set r4
        sltiu r4, r1, 5 ; should not set r4

