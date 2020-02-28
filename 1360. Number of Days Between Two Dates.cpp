//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Days Between Two Dates.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Number of Days Between Two Dates.
class Solution {
public:
    std::vector<std::string> string_split(std::string str, std::string delimiter){
        size_t pos = 0;
        std::string token;
        std::vector<std::string> result;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            result.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        result.push_back(str);
        return result;
    }
    
    bool isLeap(int y){
        if(y % 400 == 0){
            return true;
        }else if(y % 100 == 0){
            return false;
        }else if(y % 4 == 0){
            return true;
        }
        return false;
    }
    
    int monthDays(int m, int y){
        if(m <= 7){
            if(m == 2){
                if(isLeap(y)) return 29;
                return 28;
            }else if(m % 2 == 1){
                //1,3,5,7
                return 31;
            }else{
                //4,6
                return 30;
            }
        }else{
            if(m%2 == 0){
                //8,10,12
                return 31;
            }else{
                //9,11
                return 30;
            }
        }
    }
    
    int yearDays(int y){
        return isLeap(y) ? 366 : 365;
    }
    
    int daysBetweenDates(string date1, string date2) {
        vector<string> sdate1 = string_split(date1, "-");
        vector<string> sdate2 = string_split(date2, "-");
        int ans = 0;
        
        if(sdate1 > sdate2){
            vector<string> tmp = sdate1;
            sdate1 = sdate2;
            sdate2 = tmp;
        }
        vector<int> idate1, idate2;
        
        std::transform(sdate1.begin(), sdate1.end(), 
            std::back_inserter(idate1),
            [](const std::string& s) { return std::stoi(s); }
        );
        
        std::transform(sdate2.begin(), sdate2.end(), 
            std::back_inserter(idate2),
            [](const std::string& s) { return std::stoi(s); }
        );
        
        if(idate1[0] < idate2[0]){
            //idate1 to the end of the year
            ans += monthDays(idate1[1], idate1[0]) - idate1[2];
            for(int m = idate1[1]+1; m <= 12; m++){
                ans += monthDays(m, idate1[0]);
            }
            
            //the years btw them
            for(int y = idate1[0]+1; y <= idate2[0]-1; y++){
                ans += yearDays(y);
            }
            
            //the start of next year to idate2
            for(int m = 1; m <= idate2[1]-1; m++){
                ans += monthDays(m, idate2[0]);
            }
            ans += idate2[2];
        }else{
            //same year
            if(idate1[1] < idate2[1]){
                ans += monthDays(idate1[1], idate1[0]) - idate1[2];
                for(int m = idate1[1]+1; m <= idate2[1]-1; m++){
                    ans += monthDays(m, idate1[0]);
                }
                ans += idate2[2];
            }else{
                //same month
                ans += idate2[2] - idate1[2];
            }   
        }
        
        return ans;
    }
};
