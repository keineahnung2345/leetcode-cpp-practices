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

//heap, mapped to "Kth Smallest Element in a Sorted Matrix"
//https://leetcode.com/problems/k-th-smallest-prime-fraction/discuss/115819/Summary-of-solutions-for-problems-%22reducible%22-to-LeetCode-378
//TLE
//53 / 62 test cases passed.
//time: O((n + K) * logn), with n = A.length
//space: O(n)
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        auto comp = [&A](vector<int>& a, vector<int>& b){
            //first coord represents for nominator, accessing A
            //second coord represents for denominator, accessing reversed A
            
            // return A[a[0]]/A[A.size()-1-a[1]] > A[b[0]]/A[A.size()-1-b[1]];
            return A[a[0]]*A[A.size()-1-b[1]] > A[b[0]]*A[A.size()-1-a[1]];
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
        int n = A.size();
        
        for(int i = 0; i < n; i++){
            /*
            For A = {1,2,3,5}, we build a matrix:
               5   3   2   1
            1 1/5 1/3 1/2 1/1
            2 2/5 2/3 2/2 2/1
            3 3/5 3/3 3/2 3/1
            5 5/5 5/3 5/2 5/1
            
            Which uses rows to represent nominator,
            cols(in reverse order) to represent denominator,
            so that every row is sorted, ascending
            also every col is sorted, ascending
            
            (coord for nominator, coord for denominator)
            */
            pq.push({i, 0});
        }
        
        vector<int> cur;
        while(K-- > 0){
            cur = pq.top(); pq.pop();
            // cout << "pop: " << cur[0] << ", " << cur[1] << endl;
            if(cur[1]+1 < n){
                // cout << "push: " << cur[0] << ", " << cur[1]+1 << endl;
                pq.push({cur[0], cur[1]+1});
            }
        }
        
        //second coord is the index of reversed A!
        return {A[cur[0]], A[A.size()-1-cur[1]]};
    }
};

//binary search, can only be used when there is no duplicate elements
//https://leetcode.com/problems/k-th-smallest-prime-fraction/discuss/115819/Summary-of-solutions-for-problems-%22reducible%22-to-LeetCode-378
//Runtime: 16 ms, faster than 77.92% of C++ online submissions for K-th Smallest Prime Fraction.
//Memory Usage: 9.9 MB, less than 100.00% of C++ online submissions for K-th Smallest Prime Fraction.
//time: O(n * log(MAX^2)), where MAX is the maximum element in A //?
//space: O(1)
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        //the range of prime fraction
        double left = 0, right = 1;
        double mid;
        //numerator and denominator of candidate answer
        int numerator = 0, denominator = 1;
        int n = A.size();
        
        while(left < right){
            mid = (left + right)/2.0;
            
            //count of fractions <= mid
            int count = 0;
            numerator = 0; //make sure "A[n-1-j] * numerator" will be smaller than any number initially!
            for(int i = 0, j = n -1; j >= 0 && i< n; i++){
                // cout << i << ", " << j << ", " << (double)A[i]/A[n-1-j] << endl;
                // while(j >= 0 && (double)A[i]/A[n-1-j] > mid) j--;
                while(j >= 0 && A[i] > mid*A[n-1-j]) j--;
                //now A[i]/A[j] <= mid
                count += (j+1);
                //if((double)A[i]/A[j] > (double)numerator/denominator){
                if(j >= 0 && A[i]*denominator > A[n-1-j] * numerator){
                    numerator = A[i];
                    denominator = A[n-1-j];
                }
                // cout << numerator << "/" << denominator << endl;
            }
            
            // cout << "count: " << count << endl;
            
            if(count == K){
                return {numerator, denominator};
            }else if(count < K){
                left = mid;
            }else if(count > K){
                right = mid;
            }
        }
        
        return {0, 0};
    }
};
