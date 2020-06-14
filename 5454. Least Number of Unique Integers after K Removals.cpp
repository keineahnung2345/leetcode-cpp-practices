//Runtime: 1172 ms, faster than 20.00% of C++ online submissions for Least Number of Unique Integers after K Removals.
//Memory Usage: 106.5 MB, less than 20.00% of C++ online submissions for Least Number of Unique Integers after K Removals.
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

//sort
//https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/discuss/686376/Simple-C%2B%2B-O(N-log-N)-VIDEO-SOL
//Runtime: 444 ms, faster than 20.00% of C++ online submissions for Least Number of Unique Integers after K Removals.
//Memory Usage: 61.2 MB, less than 100.00% of C++ online submissions for Least Number of Unique Integers after K Removals.
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> counter;
        
        for(int& num : arr){
            counter[num] += 1;
        }
        
        //the actual number is not important, we only care their counts!
        vector<int> vcounter(counter.size());
        int i = 0;
        for(auto it = counter.begin(); it != counter.end(); it++){
            vcounter[i++] = it->second;
        }
        
        //the smaller count, the earlier be processed
        sort(vcounter.begin(), vcounter.end());
        
        // for(int e : vcounter){
        //     cout << e << " ";
        // }
        // cout << endl;
        
        for(i = 0; i < vcounter.size() && k > 0; ){
            if(k >= vcounter[i]){
                k -= vcounter[i];
                i++;
            }else{
                k = 0;
                /*
                vcounter[i] is not completely used,
                so don't increase i
                */
            }
        }
        
        /*
        [0,i-1] is the removed elements,
        [i, vcounter.size()-1] is the remaining elements,
        remaining elements' count is vcounter.size()-i
        */
        return (vcounter.size() - i);
    }
};
