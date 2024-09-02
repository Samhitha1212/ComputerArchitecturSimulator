addi x4, x4, 2048
addi x5, x5, 2047
addi x6, x6, -2048
addi x7, x7, -2049
slli x4, x5, 32
slli x4, x5, 31
slli x4, x5, -32
slli x4, x5, -33
ld x5, 2047(x6)
ld x5, 2048(x6)
ld x5, -2048(x6)
ld x5, -2049(x6)
sd x5, 2047(x6)
sd x6, 2047(x6)
sd x6, -2048(x6)
sd x6, -2049(x6)
beq x6, x7, 4095
beq x3, x4, 4094
beq x3, x4, 4096
beq x3, x4, 23
beq x3, x4, -4096
beq x3, x4, -4097
bne x6, x7, 4095
bne x3, x4, 4094
bne x3, x4, 4096
bne x3, x4, 23
bne x3, x4, -4096
bne x3, x4, -4097
lui x8, 524288
lui x8, 524287
lui x8, -524288
lui x8, -524289
jal x9, 1048576
jal x9, 1048575
jal x9, 1048574
jal x9, -1048576
jal x9, -1048577