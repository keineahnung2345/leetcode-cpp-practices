//heap
//https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/discuss/609678/Python-O(k-*-logk-*-len(mat))-with-detailed-explanations-%2B-4-lines-python.
//Runtime: 280 ms, faster than 71.28% of C++ online submissions for Find the Kth Smallest Sum of a Matrix With Sorted Rows.
//Memory Usage: 22.8 MB, less than 100.00% of C++ online submissions for Find the Kth Smallest Sum of a Matrix With Sorted Rows.
//time: O(k*logk*(m-1)), in which O(k*logk) is a iteration of heap operation
//space: O(k) = O(200)
class Solution {
public:
    vector<int> kSmallestPairs(vector<int>& v1, vector<int>& v2, int k) {
        auto comp = [&v1, &v2](vector<int>& p1, vector<int>& p2){
            return v1[p1[0]] + v2[p1[1]] > v1[p2[0]] + v2[p2[1]];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
        
        for(int i = 0; i < min((int)v1.size(), k); i++){
            pq.push({i, 0});
        }
        
        vector<int> res;
        vector<int> p;
        
        while(k-- && !pq.empty()){
            p = pq.top(); pq.pop();
            res.push_back(v1[p[0]] + v2[p[1]]);
            if(p[1]+1 < v2.size()) pq.push({p[0], p[1]+1});
        }
        
        return res;
    };
    
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        
        vector<int> res = mat[0];
        //merge two rows m-1 times
        for(int i = 1; i < m; i++){
            res = kSmallestPairs(res, mat[i], k);
        }
        
        return res.back();
    }
};

//https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/discuss/609678/Python-O(k-*-logk-*-len(mat))-with-detailed-explanations-%2B-4-lines-python.
//Runtime: 552 ms, faster than 51.37% of C++ online submissions for Find the Kth Smallest Sum of a Matrix With Sorted Rows.
//Memory Usage: 10.3 MB, less than 100.00% of C++ online submissions for Find the Kth Smallest Sum of a Matrix With Sorted Rows.
class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        vector<int> res = mat[0];
        vector<int> tmp;
        
        for(int i = 1; i < mat.size(); i++){
            tmp.clear();
            for(int a : res){
                for(int b : mat[i]){
                    tmp.push_back(a+b);
                }
            }
            sort(tmp.begin(), tmp.end());
            res = vector<int>(tmp.begin(), tmp.begin()+min((int)tmp.size(), k));
        }
        // cout << res.size() << endl;
        return res.back();
    }
};
