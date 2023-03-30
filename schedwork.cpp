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
bool isValid(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, int day, Worker_T worker, vector<int>& shifts
)
{
    int numDupes = 0; 
    for (int i = 0; i < dailyNeed; i++)
    {
        if (sched[day][i] == worker) numDupes++;
        if (numDupes > 1) return false;
    }

    if (!avail[day][worker] || shifts[worker] > maxShifts) return false;
    else return true;
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, int day, int workerCol,
    vector<int>& shifts
)
{
    size_t workers = avail[0].size();
    if (day >= avail.size())
    {
        return true;
    }
    else
    {
        for (int i = 0; i < workers; i++) // NUMBER OF DAYS
        {
					vector<Worker_T> daySched = sched[day];
					if (find(daySched.begin(), daySched.end(), i) == daySched.end()){
            sched[day][workerCol] = i;
            shifts[i]++;
            int tempWorkerCol = workerCol;
            int tempDay = day;
            
            if (isValid(avail, dailyNeed, maxShifts, sched, day, i, shifts))
            {
                tempWorkerCol++;
                if (tempWorkerCol >= dailyNeed)
                {
                    tempDay++;
                    tempWorkerCol = 0;
                }
                bool status = scheduleHelper(avail, dailyNeed, maxShifts, sched, 
                    tempDay, tempWorkerCol, shifts);
                
                if (status) return true;
            }
            sched[day][workerCol] = INVALID_ID;
            shifts[i]--;
					}
        }
        return false;
    }

}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    
    // Add your code below
    vector<int> shifts(avail[0].size());
    std::fill(shifts.begin(), shifts.end(), 0);
    for (int i = 0; i < avail.size(); i++)
    {
        // vector<Worker_T> daySched;
        // for (int j = 0; j < dailyNeed; j++)
        // {
        //     daySched.push_back(INVALID_ID);
        // }
        vector<Worker_T> daySched(dailyNeed);
        std::fill(daySched.begin(), daySched.end(), INVALID_ID);
        sched.push_back(daySched);
        
    }
    
    // for (int i = 0; i < avail[0].size(); i++)
    // {
    //     shifts.push_back(0);
    // }

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, shifts);
    


}
