//Runtime: 4 ms, faster than 60.28% of C++ online submissions for Last Stone Weight.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Last Stone Weight.

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        while(stones.size() > 1){
            sort(stones.begin(), stones.end(), greater<int>());
            int x = stones[0], y = stones[1];
            
            stones.erase(stones.begin()+1);
            stones.erase(stones.begin()+0);
            
            if(x != y){
                stones.push_back(abs(x-y));
            }
            
        }
        return stones.size() > 0 ? stones[0] : 0;
    }
};
