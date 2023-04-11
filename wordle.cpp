    #ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include <string.h>

#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(std::string input,  std::string floating, const std::set<std::string>& dict, std::set<std::string>& retset, vector<int> loc, int depth, int nonFloats);
bool valid(std::string input, const std::string& floating, const std::set<std::string>& dict, std::string word );


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<string>& dict)
{
  std::set<string> retset;
  vector<int> loc;
    // Add your code here
    //Essentially take the input word and try every combination with the floating characters and compare them to the dictonairy to see if they are actually words
    
  string ins = in;

  int dashes = 0;
  for(unsigned int i =0; i< ins.size(); i++){
      if(ins[i] == '-'){
        loc.push_back(i);
        dashes++;
      }
  }
  if(ins.size() == 0) return retset;
  if(dashes == 0){
    retset.insert(ins);
    return retset;
  }
  int nonFloats = dashes - floating.size();
  int depth = 0;
  string floatingcpy = floating;
  wordleHelper(ins, floatingcpy, dict, retset, loc, depth, nonFloats);
  return retset;

}


// Define any helper functions here
void wordleHelper(std::string input,  std::string floating, const std::set<std::string>& dict, std::set<std::string>& retset, vector<int> loc, int depth, int nonFloats){
  if(depth == loc.size()){
    return;
  }
  if(nonFloats > 0){
    for(int i =0; i< 26; i++){
      input[loc[depth]] = ('a' +i);
      if(depth == loc.size()-1){
        if(valid(input, floating, dict, input)){
          retset.insert(input);
        }
      }
      
      wordleHelper(input, floating, dict, retset, loc, depth+1, nonFloats-1);
      
    }
  }
  for(int i=0; i< floating.size(); i++){
    input[loc[depth]] = floating[i];
    string floatcpy = floating;
    if(depth == loc.size()-1){
        if(valid(input, floating, dict, input)){
          retset.insert(input);
        }
      }
      floatcpy.erase(i,1);
      wordleHelper(input, floatcpy, dict, retset, loc, depth+1, nonFloats);
  }
  
  
  
  
}
bool valid(std::string input, const std::string& floating, const std::set<std::string>& dict, std::string word ){
    
  for(int i =0; i < floating.size(); i++){
    if(input.find(floating[i]) == string::npos){
      return false;
    }
    input.erase(input.find(floating[i]));
  }
  if(dict.find(word) != dict.end())return true;
  return false;
}

