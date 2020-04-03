//Runtime: 376 ms, faster than 5.28% of C++ online submissions for My Calendar I.
//Memory Usage: 33.4 MB, less than 100.00% of C++ online submissions for My Calendar I.
class MyCalendar {
public:
    map<int, int> events;
    
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        for(auto it = events.begin(); it != events.end(); it++){
            if((start >= it->first && start < it->second) || 
              (end > it->first && end <= it->second) || 
              (start <= it->first && end >= it->second)){
                //intersection is not empty
                return false;
            }else if(it->first >= end){
                //no intersection
                break;
            }
        }
        events[start] = end;
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
 
//Approach #2: Balanced Tree, c++ map::upper_bound, map::lower_bound
//time: O(NlogN), N operations, each search for O(logN), insert for O(1)
//space: O(N)
class MyCalendar {
public:
    map<int, int> calendar;
    
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        //floorKey
        auto it = calendar.upper_bound(start);
        int prev = (it != calendar.begin()) ? (--it)->first : -1;
        //ceilingKey
        it = calendar.lower_bound(start);
        int next = (it != calendar.end()) ? it->first : -1;
        
        if((prev == -1 || calendar[prev] <= start) &&
          (next == -1 || end <= next)){
            //it's valid iff calendar[prev] <= start <= end <= next
            calendar[start] = end;
            return true;
        }
        return false;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
