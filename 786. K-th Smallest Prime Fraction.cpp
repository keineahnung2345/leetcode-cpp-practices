//TLE
//53 / 62 test cases passed.
//heap
class Solution {
public:
    priority_queue<double, vector<double>> pq;
    
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        priority_queue<vector<double>, vector<vector<double>>, greater<vector<double>>> pq;
        int n = A.size();
        
        for(int i = 0; i < n; i++){
            pq.push({(double)A[i]/A[n-1], (double)i, n-1.0});    
        }
        
        // cout << endl;
        
        K--;
        while(!pq.empty() && K--){
            vector<double> cur = pq.top(); pq.pop();
            double value = cur[0];
            int nomIdx = cur[1], denomIdx = cur[2];
            // cout << A[nomIdx] << "/" << A[denomIdx] << ":" << value << " ";
            
            if(denomIdx != 0){
                pq.push({(double)A[nomIdx]/A[denomIdx-1], (double)nomIdx, denomIdx-1.0});
            }
        }
        
        return {A[(int)pq.top()[1]], A[(int)pq.top()[2]]};
    }
};
