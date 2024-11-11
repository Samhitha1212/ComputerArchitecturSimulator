#include "globalvars.h"
#include "Execution.h"
#include "operation_map.h"
#include "ErrorHandling.h"
#include "cache.h"
#include "cache_related.h"
#include <iostream>
#include <string>
#include<regex>
#include "cache.h"
#include <fstream>
using namespace std;

int main(){
  string input;
  regex cache_enable("cache_sim\\s+enable\\s+(.*)\\s*");
  smatch match_cacheConfig;
  regex cache_disable("cache_sim\\s+disable\\s*");
  regex cache_status("cache_sim\\s+status\\s*");
  regex cache_invalid("cache_sim\\s+invalidate\\s*");
  regex cache_dump("cache_sim\\s+dump\\s+(.*)\\s*");
  smatch match_cacheDump;
  regex cache_statistics("cache_sim\\s+stats\\s*");
  regex load("load\\s+(.*)");
  smatch match;
  regex breakpoint("break\\s+[0-9]+");
  regex delBreakpoint("del\\s+break\\s+[0-9]+");
  regex memory(R"(mem\s*(0x[0-9A-Fa-f]+|\d+)\s*(\d+))");
  regex run("\\s*run\\s*");
  regex show_stack("\\s*show-stack\\s*");
  regex step("\\s*step\\s*");
  regex regs("\\s*regs\\s*");
  regex show_mem("\\s*show\\s+memory\\s*");
  regex show_break("\\s*show\\s+breakpoints\\s*");
  regex exit("\\s*exit\\s*");
  string out_file;

  do{
    getline(cin, input);
    if(regex_match(input, match_cacheConfig, cache_enable)){
      IsCacheEnabled = configDetails(match_cacheConfig[1]);
      if(!IsCacheEnabled){
        cout<<"ERROR in opening the file "<< match_cacheConfig[1]<<". So cache is not enabled"<<endl;
      }
    }else if(regex_match(input, cache_statistics)){
      
        if(IsCacheEnabled){
          cacheStatastics.Print();
        }
        else{
          cout<<"Cache is not enabled"<<endl;
        }
      
    }

    else if(regex_match(input, cache_status)){
      if(IsCacheEnabled){
        cout<<"D-cache status: Enable"<<endl;
        cache->PrintCacheConfig();
      }else{
        cout<<"D-cache status: Disable"<<endl;
      }
    }

    else if(regex_match(input, cache_invalid)){
      if(IsCacheEnabled){
        if(cache){
          cache->writeDirtyBlocks(Memory);
          cache->InvalidateCacheEntries();
        }
      }
    }

    else if(regex_match(input, match_cacheDump, cache_dump)){
      if(IsCacheEnabled && IsFileloaded){
          cache->dumpFile(match_cacheDump[1]);
      }
    }else if(regex_match(input,cache_disable)){
      if(IsCacheEnabled ){
          cache->InvalidateCacheEntries();
          cache =nullptr;
          IsCacheEnabled=false;
      }
    }else if(regex_match(input, match, load)){
        InitializeTotalData();
        if(loadfile(match[1])){
          cout<<"Error in the file "<<match[1]<<" : File not loaded"<<endl;
          InitializeTotalData();
        }
        else{
          IsFileloaded = true;
          out_file.clear();
          string s = match[1];
          for(int i=0; i<s.length(); i++){
            if(s[i] != '.'){
              out_file += s[i];
            }
            else{
              break;
            }
          }
          out_file += ".output";
          output_file = out_file;
          fstream f(output_file,std::ios::out |std::ios::trunc);
          f.close();
          functionStack.back().line=LineNumber[0]-1;
        }
        cout<<endl;
      }
      else if(regex_match(input, match, breakpoint)){
        if(IsFileloaded){
          string s;
          int i=0;
          for( ; i< input.length(); i++){
            if(input[i] != ' '){
              do{
                i++;
              }while(i<input.length() && input[i] != ' '  );
              i++;
              break;
            }
          }
          for( ; i< input.length(); i++){
            if(input[i]>='0' && input[i]<= '9'){
              do{
                s+=input[i];
                i++;
              }while(i<input.length() && input[i]>='0' && input[i]<= '9' );
              break;
            }
          }
        
          addBreakPoint(stoi(s));
        }else {
          cout<<"ERROR : No file loaded"<<endl;
        }
        cout<<endl;
      }
      else if(regex_match(input, match, delBreakpoint)){
        if(IsFileloaded){
          string s;
          int i=0;
          for( ; i< input.length(); i++){
            if(input[i] != ' '){
              do{
                i++;
              }while(i<input.length() && input[i] != ' '  );
              i++;
              break;
            }
          }
          for( ; i< input.length(); i++){
            if(input[i] != ' '){
              do{
                i++;
              }while(i<input.length() && input[i] != ' '  );
              i++;
              break;
            }
          }
          for( ; i< input.length(); i++){
            if(input[i]>='0' && input[i]<= '9'){
              do{
                s+=input[i];
                i++;
              }while(i<input.length() && input[i]>='0' && input[i]<= '9'  );
              break;
            }
          }
          deleteBreakPoint(stoi(s));
        }else{
          cout<<"ERROR : No file loaded"<<endl;
        }
        cout<<endl;
      }
      else if(regex_match(input, run)){
        if(IsFileloaded){
          if(!IsRuntimeErr){
            if(currentInstruction<instructions && currentInstruction>=0){
            for(; !IsbreakPoint(currentInstruction) && currentInstruction < instructions && !IsRuntimeErr; ){
              ExecuteInstruction(currentInstruction);
            }
            if(currentInstruction >= instructions){
              if(IsCacheEnabled){
                cacheStatastics.Print();
              }
              // cout<<"Execution Completed"<<endl;
              functionStack.clear();
            }else if(!IsRuntimeErr){
              cout<<"Execution stopped at Breakpoint"<<endl;
            }else {
            cout<<"Encountered run time error can not run further"<<endl;
            }
          }else{
            cout<<"Nothing to run"<<endl;
            // cout<<"Execution Completed"<<endl;
          }
          }else{
          cout<<"Encountered run time error can not run further"<<endl;
          }
        
        }
        else{
          cout<<"ERROR : No file loaded"<<endl;
        }
        cout<<endl;
      }
      else if(regex_match(input, step)){
        if(IsFileloaded){
          if(!IsRuntimeErr){
            if(currentInstruction<instructions && currentInstruction>=0){
              ExecuteInstruction(currentInstruction);
              if(currentInstruction>instructions){
                cout<<"Execution Completed"<<endl;
                functionStack.clear();
              }
            }else{
              cout<<"Nothing to step"<<endl;
              // cout<<"Execution Completed"<<endl;
            }
          }else{
          cout<<"Encountered run time error can not run further"<<endl;
          }
      
        }
        else{
          cout<<"ERROR : No file loaded"<<endl;
        }
        cout<<endl;  
      }
      else if(regex_match(input, match, memory)){
        Memory.printMemory(stoi(match[2]), convertToInt(match[1]));
        cout<<endl;
      }else if(regex_match(input, show_mem)){
        Memory.printMemory();
      }
      else if(regex_match(input, regs)){
        RegisterFile.printRegs();
      }else if(regex_match(input, show_stack)){
        if(IsFileloaded){
          showStack();
        }else{
          cout<<"ERROR : No file loaded"<<endl;
        }
        cout<<endl;
      }else if(regex_match(input, show_break)){
        if(IsFileloaded){
          showBreakpoints();
        }else{
          cout<<"ERROR : No file loaded"<<endl;
        }
        cout<<endl;
      }
      // else if(input=="cache"){
      //   cache = new Cache(1024,1,16,ReplacementPolicy::FIFO, WritePolicy::WT,false);
      //   cout<<cache->blocksize<<endl;
      //   cout<<cache->associativity<<endl;
      //   cout<<cache->noOfEntries<<endl;
      // }else if(input=="cache_stats"){
      //   cacheStatastics.Print();
      // }
      else if(!regex_match(input, exit)){
        cout<<"Invalid command"<<endl;
        cout<<endl;
      }
  }while(!regex_match(input, exit));

  cout<<"Exited the simulator"<<endl;
  return 0;
}