//Two pointers, sliding window
//Runtime: 60 ms, faster than 67.45% of C++ online submissions for Max Consecutive Ones III.
//Memory Usage: 13 MB, less than 100.00% of C++ online submissions for Max Consecutive Ones III.
/*
Hints:
One thing's for sure, we will only flip a zero if it extends an existing window of 1s. Otherwise, there's no point in doing it, right? Think Sliding Window!
Since we know this problem can be solved using the sliding window construct, we might as well focus in that direction for hints. Basically, in a given window, we can never have > K zeros, right?
We don't have a fixed size window in this case. The window size can grow and shrink depending upon the number of zeros we have (we don't actually have to flip the zeros here!).
The way to shrink or expand a window would be based on the number of zeros that can still be flipped and so on.
*/
class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        int left = 0, right = 0;
        int N = A.size();
        int ans = 0;
        int used = 0;
        
        while(right < N){
            if(left > 0 && A[left-1] == 0){
                used--;
            }
            //continue to look ahead when the A[right] is 1
            //, or A[right] is 0 but we still have quota to use
            while(right < N && (A[right] == 1 || used < K)){
                if(A[right] == 0 && used < K){
                    used++;
                }
                right++;
            }
            // cout << "[" << left << "," << right-1 << "]" << endl;
            ans = max(ans, right-left);
            left++;
        }
        return ans;
    }
};
