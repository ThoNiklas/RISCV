first:  addi r1, r0, 1 ; setup
        addi r2, r0, 32 ; setup
        jal r3, first ; should pc to 0 and write back 12
