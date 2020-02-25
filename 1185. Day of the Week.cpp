//Runtime: 4 ms, faster than 55.47% of C++ online submissions for Day of the Week.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Day of the Week.
class Solution {
public:
    vector<string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    
    //1971/1/1 is Friday
    
    int yearDays(int year){
        if(year % 400 == 0){
            return 366;
        }else if(year % 100 == 0){
            return 365;
        }else if(year % 4 == 0){
            return 366;
        }
        return 365;
    }
    
    int monthDays(int month, int year){
        if(month == 2){
            if(year % 400 == 0){
                return 29;
            }else if(year % 100 == 0){
                return 28;
            }else if(year % 4 == 0){
                return 29;
            }
            return 28;
        }else if((month <= 7 && month % 2 == 1) || 
                (month >= 8 && month % 2 == 0)){
            //1,3,5,7,8,10,12
            return 31;
        }
        //4,6,9,11
        return 30;
    }
    
    string dayOfTheWeek(int day, int month, int year) {
        int ans = 0;
        
        for(int y = 1971; y < year; y++){
            ans += yearDays(y);
        }
        
        for(int m = 1; m < month; m++){
            ans += monthDays(m, year);
        }
        
        ans += day;
        //the difference with 1971/1/1
        return days[(ans + 5 - 1) % 7];
    }
};
