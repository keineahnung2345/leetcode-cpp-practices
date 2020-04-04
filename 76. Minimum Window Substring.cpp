//TLE
//267 / 268 test cases passed.
class Solution {
public:
    bool isValid(map<char, int>& m1, map<char, int>& m2){
        //m1 is base, return true if m2 >= m1
        for(auto it = m1.begin(); it != m1.end(); it++){
            if(m2.find(it->first) == m2.end() || 
                    m1[it->first] > m2[it->first]){
                return false;
            }
        }
        return true;
    }
    
    string minWindow(string s, string t) {
        int l = 0, r = 0;
        int minLen = INT_MAX;
        string minStr;
        map<char, int> tCount, curCount;
        
        for(int i = 0; i < t.size(); i++){
            tCount[t[i]]++;
        }
        
        //window is initially [0...0]
        curCount[s[l]]++;
        while(r < s.size()){
            // cout << s.substr(l, r-l+1) << endl;
            //move forward r until curCount >= tCount
            if(!isValid(tCount, curCount)){
                r++;
                //update curCount
                curCount[s[r]]++;
            }else{
                // cout << "found" << endl;
                if(r-l+1 < minLen){
                    minLen = r-l+1;
                    minStr = s.substr(l, r-l+1);
                }
                
                //s[l] is discarded
                curCount[s[l]]--;
                //move forward l
                l++;
            }
            
        }
        
        return minStr;
    }
};

//Approach 1: Sliding Window, improve efficiency to determine if a window is valid
//Runtime: 116 ms, faster than 11.76% of C++ online submissions for Minimum Window Substring.
//Memory Usage: 16.7 MB, less than 32.00% of C++ online submissions for Minimum Window Substring.
//time: O(|S|+|T|), space: O(|S|+|T|)
class Solution {
public:
    string minWindow(string s, string t) {
        if(s.size() == 0 || t.size() == 0) return "";
        
        int l = 0, r = 0;
        int minLen = INT_MAX;
        string minStr;
        map<char, int> tCount, curCount;
        
        for(int i = 0; i < t.size(); i++){
            tCount[t[i]]++;
        }
        
        //#unique char in t
        int required = tCount.size();
        //#unique char required in s
        int possessed = 0;
        
        //window is initially [0...0]
        while(r < s.size()){
            //meet new char, update our data structure
            curCount[s[r]]++;
            
            // cout << s.substr(l, r-l+1) << endl;
            if((tCount.find(s[r]) != tCount.end()) && 
              curCount[s[r]] == tCount[s[r]]){
                //we have just collected enough char of s[r]
                possessed++;
            }
            
            //try contract windows size
            while((possessed == required) && (l <= r)){
                // cout << "found" << endl;
                if(r-l+1 < minLen){
                    minLen = r-l+1;
                    minStr = s.substr(l, r-l+1);
                }
                
                //s[l] is discarded
                curCount[s[l]]--;
                if(tCount.find(s[l]) != tCount.end()
                  && curCount[s[l]] == tCount[s[l]]-1){
                    /*
                    the char count of s[l] is just deduced,
                    and not enough to form t
                    */
                    possessed--;
                }
                //move forward l
                l++;
            }
            
            r++;            
        }
        
        return minStr;
    }
};
