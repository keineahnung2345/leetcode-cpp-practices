//deque
//Runtime: 324 ms, faster than 43.49% of C++ online submissions for Shortest Subarray with Sum at Least K.
//Memory Usage: 62.6 MB, less than 67.30% of C++ online submissions for Shortest Subarray with Sum at Least K.
//time: O(N), space: O(N)
class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size();
        //prefix sum: P[0]: 0, P[1]: A[0], P[2]: A[0]+A[1], ...
        vector<int> P(n+1);
        
        for(int i = 0; i < n; ++i){
            P[i+1] = P[i] + A[i];
        }
        
        int ans = n+1; //impossible window size
        deque<int> deq;
        
        for(int y = 0; y < P.size(); ++y){
            /*
            for a specific y, we want to find x s.t.
            P[y] - P[x] >= K
            
            Motivated by that equation, 
            let opt(y) be the largest x 
            such that P[x] <= P[y] - K. 
            We need two key observations:
            
            If x1 < x2 and P[x2] <= P[x1], 
            then opt(y) can never be x1, 
            as if P[x1] <= P[y] - K, 
            then P[x2] <= P[x1] <= P[y] - K 
            but y - x2 is smaller. 
            This implies that our candidates 
            x for opt(y) will have increasing values of P[x].
            
            The text is saying x1 and x2,
            why the code compare x and y??
            */
            //make the deque increasing
            while(!deq.empty() && P[deq.back()] >= P[y]){
                deq.pop_back();
            }
            
            while(!deq.empty() && P[deq.front()] + K <= P[y]){
                ans = min(ans, y - deq.front());
                /*
                If opt(y1) = x, 
                then we do not need to consider this x again. 
                For if we find some y2 > y1 with opt(y2) = x, 
                then it represents an answer of y2 - x 
                which is worse (larger) than y1 - x.
                */
                deq.pop_front();
            }
            
            deq.push_back(y);
        }
        
        return ans == n+1 ? -1 : ans;
        
    }
};
