        addi r1, r0, 10 ; setup
        addi r2, r0, 13 ; setup
        sll  r3, r1, r2 ; should shift 13 ti the left
        slt r4, r1, r2  ; should set
        slt r5, r2, r1  ; should not set
        sltu r8, r1, r2 ; should set
        sltu r9, r2, r1 ; should not set
        addi r1, r0, -5 ; setup
        slt r6, r1, r2  ; should set
        slt r7, r2, r1   ; should not set
        sltu r10, r2, r1 ; should set
        sltu r11, r1, r2 ; should not set
