//counter
//Runtime: 36 ms, faster than 75.00% of C++ online submissions for Make Two Arrays Equal by Reversing Sub-arrays.
//Memory Usage: 15.5 MB, less than 100.00% of C++ online submissions for Make Two Arrays Equal by Reversing Sub-arrays.
//time: O(N)
class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        map<int, int> counter;
        
        for(int e : target){
            counter[e]+=1;
        }
        
        for(int e : arr){
            if(counter.find(e) == counter.end()){
                return false;
            }
            counter[e]-=1;
            if(counter[e] == 0){
                counter.erase(e);
            }
        }
        
        return true;
    }
};

//sorting
//Runtime: 28 ms, faster than 75.00% of C++ online submissions for Make Two Arrays Equal by Reversing Sub-arrays.
//Memory Usage: 13.8 MB, less than 100.00% of C++ online submissions for Make Two Arrays Equal by Reversing Sub-arrays.
//time: O(NlogN)
class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        sort(target.begin(), target.end());
        sort(arr.begin(), arr.end());
        return target == arr;
    }
};
