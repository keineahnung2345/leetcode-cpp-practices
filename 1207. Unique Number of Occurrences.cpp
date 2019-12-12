//Runtime: 4 ms, faster than 74.54% of C++ online submissions for Unique Number of Occurrences.
//Memory Usage: 9 MB, less than 100.00% of C++ online submissions for Unique Number of Occurrences.

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        map<int, int> mcount;
        set<int> scount;
        for(int e : arr){
            if(mcount.find(e) == mcount.end()){
                mcount[e] = 1;
            }else{
                mcount[e]++;
            }
        }
        
        for(map<int, int>::iterator it = mcount.begin(); it != mcount.end(); it++){
            if(scount.find(it->second) == scount.end()){
                scount.insert(it->second);
            }else{
                return false;
            }
        }
        return true;
    }
};
