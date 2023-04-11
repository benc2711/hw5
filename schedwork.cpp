#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool possible(size_t row, size_t worker, const AvailabilityMatrix& avail,
    const size_t maxShifts,
    DailySchedule& sched, const size_t dailyNeed);
bool solve(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    DailySchedule& sched, 
    const size_t maxShifts, 
    size_t row, 
    size_t col);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

  // 
   vector<Worker_T> workers(dailyNeed, INVALID_ID); 
  sched.insert(sched.begin(), avail.size(), workers);
  return solve(avail, dailyNeed, sched, maxShifts, 0, 0);


}


bool solve(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    DailySchedule& sched,
    const size_t maxShifts, 
    size_t row, 
    size_t col
)
{
  //This is our base case so that if we reach the last index we are done
  if((col == dailyNeed) && (row == avail.size())){
    return true;
  }
  if(col == dailyNeed){
    row++;
    col = 0;
  }
  if(row == avail.size()) return true;
  if(sched[row][col] != INVALID_ID){
    return solve(avail, dailyNeed, sched, maxShifts,  row, col+1);
  }
  //Go through the workers
  for(size_t i =0; i < avail.size(); i++){
    //where row is the day and i is the workerID effectivly 

    if(possible(row, i, avail, maxShifts, sched, dailyNeed)){
      sched[row][col] = i;

      if(solve(avail, dailyNeed, sched, maxShifts, row, col+1)){
        return true;
      }
    }
    sched[row][col] = INVALID_ID;
  }
  return false;
}

bool possible(size_t row, size_t worker, const AvailabilityMatrix& avail,
    const size_t maxShifts,
    DailySchedule& sched, const size_t dailyNeed){
  //Search the schedule to see if the worker would be over max shifts 
  size_t shiftcounter = 0;
  //ensure that the worker is avaliable 
    if(avail[row][worker] == 0){
      return false;
    }
    //Need to check if the worker has already been asigned for the given day
    
    for(size_t i =0; i< sched.size(); i++){
      for(size_t j =0; j< sched[i].size(); j++){
        if(row == i){
          if(sched[row][j] == worker) return false;
        }
        if(sched[i][j] == worker){
          shiftcounter++;
        }
      }
    }
    if(shiftcounter < maxShifts) return true;
    return false;
  
}

