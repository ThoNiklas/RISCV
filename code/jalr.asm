first:  addi r1, r0, 1 ; setup
        addi r2, r0, 32 ; setup
        jalr r3, r2, 6 ; should set pc to 40 and write back 12
