//Runtime: 240 ms, faster than 24.78% of C++ online submissions for Find K Pairs with Smallest Sums.
//Memory Usage: 84.3 MB, less than 20.00% of C++ online submissions for Find K Pairs with Smallest Sums.
class pairSumGreater{
public:
    pairSumGreater(){};
    bool operator() (const vector<int>& a, const vector<int>& b){
        return a[0] + a[1] > b[0] + b[1];
    };
};

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        priority_queue<vector<int>, vector<vector<int>>, pairSumGreater> pq;
        /*
        or
        auto comp = [&nums1, &nums2](const vector<int>& p1, const vector<int>& p2){
            return p1[0]+p1[1] > p2[0]+p2[1];
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
        */
        for(int i = 0; i < nums1.size(); i++){
            for(int j = 0; j< nums2.size(); j++){
                pq.push({nums1[i], nums2[j]});
            }
        }
        
        vector<vector<int>> ans;
        while(k-- > 0 && !pq.empty()){
            ans.push_back(pq.top());
            pq.pop();
        }
        
        return ans;
    }
};

//Runtime: 860 ms, faster than 5.02% of C++ online submissions for Find K Pairs with Smallest Sums.
//Memory Usage: 43.1 MB, less than 20.00% of C++ online submissions for Find K Pairs with Smallest Sums.
class pairSumLess{
public:
    pairSumLess(){};
    bool operator() (const vector<int>& a, const vector<int>& b){
        return a[0] + a[1] < b[0] + b[1];
    };
};

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        priority_queue<vector<int>, vector<vector<int>>, pairSumLess> pq;
        for(int i = 0; i < nums1.size(); i++){
            for(int j = 0; j< nums2.size(); j++){
                pq.push({nums1[i], nums2[j]});
                if(pq.size() > k){
                    //the greater the earlier be popped
                    pq.pop();
                }
            }
        }
        
        vector<vector<int>> ans;
        while(k-- > 0 && !pq.empty()){
            ans.push_back(pq.top());
            pq.pop();
        }
        
        return ans;
    }
};

//https://leetcode.com/problems/find-k-pairs-with-smallest-sums/discuss/84551/simple-Java-O(KlogK)-solution-with-explanation
//Runtime: 12 ms, faster than 97.80% of C++ online submissions for Find K Pairs with Smallest Sums.
//Memory Usage: 9.2 MB, less than 100.00% of C++ online submissions for Find K Pairs with Smallest Sums.
class PairJ{
public:
    int a; //value from nums1
    int b; //value from nums2
    int j; //index in nums2
    PairJ(int a, int b, int j) : a(a), b(b), j(j) {};
};

class PairJGreater{
public:
    PairJGreater(){};
    bool operator() (const PairJ* p1, const PairJ* p2){
        return p1->a + p1->b > p2->a + p2->b;
    }
};

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> ans;
        
        if(nums1.size() == 0 || nums2.size() == 0 || k == 0) return ans;
        
        priority_queue<PairJ*, vector<PairJ*>, PairJGreater> pq;
        /*
        if nums1.size() > k, 
        then only the former k elements are useful,
        because they are not belong to the first k smallest numbers
        */
        for(int i = 0; i < k && i < nums1.size(); i++){
            pq.push(new PairJ(nums1[i], nums2[0], 0));
        }
        
        while(k-- > 0 && !pq.empty()){
            PairJ* p = pq.top(); pq.pop();
            ans.push_back({p->a, p->b});
            //once we pop (i,j), (i,j+1) is our candidate
            //pq.size() will always <= original k!
            if(p->j+1 >= nums2.size()) continue;
            pq.push(new PairJ(p->a, nums2[p->j+1], p->j+1));
        }
        
        return ans;
    }
};
