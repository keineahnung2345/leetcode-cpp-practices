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
