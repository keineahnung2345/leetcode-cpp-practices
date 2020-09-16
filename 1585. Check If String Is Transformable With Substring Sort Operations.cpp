//https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/discuss/843917/C%2B%2BJavaPython-O(n)
//Runtime: 140 ms, faster than 67.24% of C++ online submissions for Check If String Is Transformable With Substring Sort Operations.
//Memory Usage: 22.8 MB, less than 29.02% of C++ online submissions for Check If String Is Transformable With Substring Sort Operations.
class Solution {
public:
    bool isTransformable(string s, string t) {
        vector<vector<int>> pos(10);
        
        for(int i = 0; i < s.size(); ++i){
            pos[s[i]-'0'].push_back(i);
        }
        
        //count of processed digit
        vector<int> cnt(10);
        for(int i = 0; i < t.size(); ++i){
            /*
            in each iteration, 
            we check if we can find an unprocessed d in s,
            and "swap" it to t[i]
            */
            int d = t[i]-'0';
            
            if(cnt[d]+1 > pos[d].size()){
                //cnt[d]+1: this is the (cnt[d]+1)th d  in t we meet
                //pos[d].size(): we have pos[d].size() d in s
                //this means we have more d in t than in s
                //so we cannot find the unprocessed d in s
                return false;
            }
            
            for(int sd = 0; sd < d; ++sd){
                //sd: any number smaller than d
                if(cnt[sd] < pos[sd].size() && pos[sd][cnt[sd]] < pos[d][cnt[d]]){
                    //cnt[sd] < pos[sd].size(): sd is not fully processed
                    /*
                    pos[sd][cnt[sd]] < pos[d][cnt[d]]: 
                    some unprocessed digit is former than this unprocessed d (in s),
                    that means we cannot swap sd and d,
                    so we cannot put d into its right position
                    */
                    return false;
                }
            }
            
            //mark it as processed
            ++cnt[d];
        }
        
        return true;
    }
};
