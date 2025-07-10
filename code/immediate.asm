        addi r1, r0, 10 ; setup
        xori r2, r1, 5  ; should set r2 to 1111
        xori r3, r1, 15 ; should set r3 to 0101
        srli r4, r1, 2  ; should set r4 to 10, logical right shift
        addi r5, r0, -10 ; setup
        srai r6, r5, 2  ; should right shift with sign extension
        ori  r7, r0, 10 ; should r7 to 1010
        ori  r8, r1, 5  ; should set r8 to 1111
        andi r9, r1, 10 ; should set r9 to 1010
        andi r10, r1, 5 ; should set r10 to 0

