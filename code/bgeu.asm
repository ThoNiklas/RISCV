first:  addi r1, r0, 1 ; setup
        addi r2, r0, 10 ; setup
        bgeu r1, r2, first ; should not reset pc
        addi r1, r0, -1 ; setup
        bgeu r1, r2, first ; should reset pc
