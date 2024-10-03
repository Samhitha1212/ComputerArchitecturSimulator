addi x4, x0, 255
addi x5, x0, 256
addi x6, x0, -256
addi x7, x0, -255
lui x3, 0x10
sb x4, -3(x3)
sb x5, -2(x3)
sb x6, -1(x3)
sb x7, 0(x3)
sh x4, 2(x3)
sh x5, 4(x3)
sh x6, 6(x3)
sh x7, 8(x3)