# Cache Simulator

## Overview
This Simulator is designed to run riscv Instructions and also supports cache simulation to identify which accesses would cause a cache hit and which accesses would cause a cache miss when an riscv assembly program is executing.

## Commands Available
- **cache_sim enable config_file** :- Enables the cache with config details inside the file "config_file"
- **cache_sim disable** :- Disables the cache.
- **cache_sim status**  :- prints the status of Cache and its configuration details if cache is enabled.
- **cache_sim invalidate** :- invalidates all entries of the D-cache.
- **cache_sim dump myFile.out** :- writes all the current D-cache valid entries to the file “myFile.out” 
- **cache_sim stats** :- prints the cache statistics for the executing code at the current instance.



### Folder Structure
1. Inside the folder Cache_Simulator , It will have all source files , header files , MakeFile , reprt.pdf anfd readme.md

### How to run the code 
1. Navigate to directoy Cache_Simulator and enter make command to compile code and generate executable file riscv_sim
   ```bash
   make 
   ```
     **or** 

    ```bash
   make riscv_sim
   ```
2. Now run the executable file riscv_sim
   ```bash
   ./riscv_sim
   ```
3. To clean object files and executable files enter make clean command 
   ```bash
   make clean
   ```