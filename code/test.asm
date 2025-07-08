first:  addi    r1, r1,  5 ; comment
        addi    r2, r2, 10
        add     r3, r1, r2
        lb      r4, 48(r5) ; comment
        auipc   r6, 13
        sb      r7, 0(r8)
second: lui     r9, 234
        beq     r10, r11, first
        jalr    r12, r13, 234

        jal     r14, second
