first:  addi r1, r0, 20 ; setup
        addi r2, r0, 10 ; setup
        blt r1, r2, first ; should not reset pc
        addi r1, r0, 5  ; setup
        blt r1, r2, first ; should reset pc
