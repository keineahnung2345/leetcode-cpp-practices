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
 
