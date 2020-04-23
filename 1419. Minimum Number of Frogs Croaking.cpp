//Runtime: 312 ms, faster than 20.09% of C++ online submissions for Minimum Number of Frogs Croaking.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Minimum Number of Frogs Croaking.
class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        int pos = -2;
        int visited = 0;
        int count = 0;
        
        vector<string> croak = {"c", "r", "o", "a", "k"};
        
        while(visited < croakOfFrogs.size()){
            pos = -2;
            bool jump = false;
            while(pos == -2 || (pos >= 0 && pos < croakOfFrogs.size())){
                for(string s : croak){
                    pos = croakOfFrogs.find(s, (pos == -2) ? 0 : pos+1);
                    if(pos != string::npos){
                        croakOfFrogs[pos] = '#';
                        visited++;
                    }else{
                        //not jump at first char, invalid string
                        if(s != "c") return -1;
                        //we need another frog
                        jump = true;
                        break;
                    }
                }
                if(jump) break;
            }
            
            count++;
        }
        
        return count;
    }
};
