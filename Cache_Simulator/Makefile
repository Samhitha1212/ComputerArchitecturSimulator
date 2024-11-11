CXX :=g++

srcfiles:=$(wildcard ./*.cpp)
objfiles:=$(patsubst ./%.cpp,./%.o, $(srcfiles))


riscv_sim: $(objfiles) 
	$(CXX) $^ -o $@

./%.o:./%.cpp FMT.h operation_map.h ErrorHandling.h Execution.h globalvars.h memory.h register.h cache.h cache_related.h
	$(CXX) -c $^ -o $@ 

clean:
	rm $(objfiles) riscv_sim