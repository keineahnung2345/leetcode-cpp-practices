//Runtime: 452 ms, faster than 8.45% of C++ online submissions for Sort Integers by The Power Value.
//Memory Usage: 49.1 MB, less than 100.00% of C++ online submissions for Sort Integers by The Power Value.
class Solution {
public:
    map<int, int> power;
    
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
