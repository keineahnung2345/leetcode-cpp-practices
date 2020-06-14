//TLE
//43 / 43 test cases passed, but took too long.
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> counter;
        
        for(int& num : arr){
            counter[num] += 1;
        }
        
        vector<vector<int>> vcounter;
        for(auto it = counter.begin(); it != counter.end(); it++){
            vcounter.push_back({it->first, it->second});
        }
        
        //the smaller count, the earlier be popped
        auto comp = [](const vector<int>& p, const vector<int>& q){
            return p[1] > q[1];
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(vcounter.begin(), vcounter.end(), comp);
        
        while(!pq.empty() && k > 0){
            vector<int> p = pq.top(); pq.pop();
            if(k < p[1]){
                pq.push({p[0], p[1]-k});
            }
            k -= p[1];
        }
        
        return pq.size();
    }
};
