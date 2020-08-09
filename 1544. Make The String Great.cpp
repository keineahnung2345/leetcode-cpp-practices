//Runtime: 4 ms, faster than 83.33% of C++ online submissions for Make The String Great.
//Memory Usage: 6.2 MB, less than 83.33% of C++ online submissions for Make The String Great.
class Solution {
public:
    string makeGood(string s) {
        int i = 0;
        
        while(i+1 < s.size()){
            //'A': 65, 'a': 97
            if(abs(s[i] - s[i+1]) == 32){
                s.erase(i, 2);
                if(i > 0) --i;
            }else{
                ++i;
            }
        }
        
        return s;
    }
};
