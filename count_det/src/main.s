.text
.global count_det

count_det:
        mov r3, r0

        ldr r0, [r3]
        ldr r1, [r3, #16]
        mul r1, r0
        ldr r0, [r3, #32]
        mul r1, r0

        mov r2, r1
//1

        ldr r0, [r3, #4]
        ldr r1, [r3, #20]
        mul r1, r0
        ldr r0, [r3, #24]
        mul r1, r0

        add r2, r1
//2

        ldr r0, [r3, #8]
        ldr r1, [r3, #12]
        mul r1, r0
        ldr r0, [r3, #28]
        mul r1, r0

        add r2, r1
//3

        ldr r0, [r3]
        ldr r1, [r3, #20]
        mul r1, r0
        ldr r0, [r3, #28]
        mul r1, r0

        sub r2, r1
//4

        ldr r0, [r3, #4]
        ldr r1, [r3, #12]
        mul r1, r0
        ldr r0, [r3, #32]
        mul r1, r0

        sub r2, r1
//5

        ldr r0, [r3, #8]
        ldr r1, [r3, #16]
        mul r1, r0
        ldr r0, [r3, #24]
        mul r1, r0

        sub r2, r1
//6

        mov r0, r2

        bx lr