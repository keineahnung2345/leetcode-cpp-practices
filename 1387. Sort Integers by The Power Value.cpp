//map
//Runtime: 452 ms, faster than 8.45% of C++ online submissions for Sort Integers by The Power Value.
//Memory Usage: 49.1 MB, less than 100.00% of C++ online submissions for Sort Integers by The Power Value.
//unordered_map
//Runtime: 284 ms, faster than 20.76% of C++ online submissions for Sort Integers by The Power Value.
//Memory Usage: 47.1 MB, less than 100.00% of C++ online submissions for Sort Integers by The Power Value.
class Solution {
public:
    //map<int, int> power;
    unordered_map<int, int> power;
    
    int getPower(int x){
        if(x == 1) return 0;
        
        if(power.find(x) != power.end()) return power[x];
        
        int ans;
        
        if(x % 2 == 0){
            ans = 1 + getPower(x/2);
        }else{
            ans = 1 + getPower(3*x+1);
        }
        
        power[x] = ans;
        
        return ans;
    };
    
    int getKth(int lo, int hi, int k) {
        //the larger the earlier to be popped
        priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int,int>>> pq;
        
        for(int i = lo; i <= hi; i++){
            pq.push(make_pair(getPower(i), i));
            if(pq.size() > k){
                pq.pop();
            }
            // cout << i << " " << power[i] << endl;
        }
        
        //the answer is the largest in k pairs
        int ans = pq.top().second;
        
        return ans;
    }
};

//Precompute, partial sort
//https://leetcode.com/problems/sort-integers-by-the-power-value/discuss/547055/C%2B%2B-8-ms-precompute-and-partial-sort
//Runtime: 28 ms, faster than 96.47% of C++ online submissions for Sort Integers by The Power Value.
//Memory Usage: 7.5 MB, less than 100.00% of C++ online submissions for Sort Integers by The Power Value.
class Solution {
public:
    int getPower(int x){
        if(x == 1) return 0;
        
        int ans;
        
        if(x % 2 == 0){
            ans = 1 + getPower(x/2);
        }else{
            ans = 1 + getPower(3*x+1);
        }
        
        return ans;
    };
    
    int getKth(int lo, int hi, int k) {
        vector<int> computed = vector<int>(hi-lo+1, 0);
        
        for(int i = lo; i <= hi; i++){
            computed[i-lo] = getPower(i);
        }
        
        vector<int> ids(hi-lo+1);
        iota(ids.begin(), ids.end(), lo);
        
        nth_element(ids.begin(), ids.begin()+k-1, ids.end(), 
            [&computed, lo](const int i, const int j){
                return (computed[i-lo] == computed[j-lo]) ? (i < j) : (computed[i-lo] < computed[j-lo]);
            });
        
        return ids[k-1];
    }
};
