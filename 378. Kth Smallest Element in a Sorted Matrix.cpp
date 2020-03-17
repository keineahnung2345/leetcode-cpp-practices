//Runtime: 84 ms, faster than 14.51% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
//Memory Usage: 12.4 MB, less than 59.09% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int, vector<int>, less<int>> pq;
        
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size(); j++){
                pq.push(matrix[i][j]);
                if(pq.size() > k){
                    cout << "pop: " << pq.top() << endl;
                    pq.pop();
                }
            }
        }
        
        //the answer is the k-th smallest element,
        //which is the smallest element in the heap of size k
        return pq.top();
    }
};
