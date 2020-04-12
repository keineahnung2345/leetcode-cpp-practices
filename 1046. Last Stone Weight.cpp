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

//https://leetcode.com/problems/last-stone-weight/discuss/294956/JavaC%2B%2BPython-Priority-Queue
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Last Stone Weight.
//Memory Usage: 8.4 MB, less than 100.00% of C++ online submissions for Last Stone Weight.
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        std::priority_queue<int> pq(stones.begin(), stones.end());
        while(pq.size() >= 2){
            //y is always >= x
            int y = pq.top(); pq.pop();
            int x = pq.top(); pq.pop();
            
            if(x != y) pq.push(y-x);
        }
        
        //note its pq.top() not pq[0]!
        return pq.size() > 0 ? pq.top() : 0;
    }
};

