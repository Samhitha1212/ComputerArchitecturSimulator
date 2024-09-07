
lui x3 0x10000
addi x3 x3 0x200
lui x4 0x10000
ld x20 0(x4) 
; n
addi x4 x4 8


add x21 x0 x0 
;i

Loop: 
    bge x21 x20 LoopExit
    ld x5 0(x4)
    ld x6 8(x4)
    addi x4 x4 16
    
    jal x1 GCD
    sd x7 0(x3)
    addi x3 x3 8
    
    addi x21 x21 1 ;i++
    beq x0 x0 Loop

LoopExit:
    beq x0 x0 ProgramExit


; calculates GCD of x5 , x6 and keeps the result in x7
; uses x9,x10 (min,max) , x11
GCD:
    blt x5 x6 L1
    add x9 x6 x0
    add x10 x5 x0
    beq x0 x0 L2
    
L1: 
    add x9 x5 x0
    add x10 x6 x0
L2:
    beq x9 x0 F
L3: sub x10 x10 x9
    bge x10 x9 L3
    
    beq x10 x0 F
    ; swaping x9 and x10
    add x11 x9 x0
    add x9 x10 x0
    add x10 x11 x0
    beq x0 x0 L3
    
 F:  
     add x7 x9 x0
GCDExit:
    jalr x0 0(x1)

ProgramExit: add x0 x0 x0
