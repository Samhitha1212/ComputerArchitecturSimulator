riscv_asm: main.o Evaluate.o operation_map.o
	g++ main.o Evaluate.o operation_map.o -o riscv_asm

main.o: main.cpp FMT.h operation_map.h
	g++ -c main.cpp

Evaluate.o: Evaluate.cpp FMT.h operation_map.h
	g++ -c Evaluate.cpp

operation_map.o: operation_map.cpp operation_map.h
	g++ -c operation_map.cpp

clean:
	rm -f *.o riscv_asm
