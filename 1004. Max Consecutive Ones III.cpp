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

//sliding window
//not understand
//https://leetcode.com/problems/max-consecutive-ones-iii/discuss/247564/JavaC%2B%2BPython-Sliding-Window
//Runtime: 188 ms, faster than 15.66% of C++ online submissions for Max Consecutive Ones III.
//Memory Usage: 55.5 MB, less than 50.08% of C++ online submissions for Max Consecutive Ones III.
class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        int slow, fast;
        
        /*
        slow and fast are not exact index to the array,
        they only specify the size of the window
        in the process, we will continue to find a bigger window,
        if we find one, we will carry this window forward until
        we find a larger one
        */
        for(slow = 0, fast = 0; fast < A.size(); ++fast){
            if(A[fast] == 0) --K;
            // cout << "[" << slow << ", " << fast << "], K: " << K << endl;
            /*
            only when K >= 0,
            it's in a valid state,
            so when K < 0,
            slow will be moved forward, too
            so the window will be carried foward
            
            and if A[slow] is 0, 
            we and increase K back
            */
            if(K < 0 && A[slow++] == 0) ++K;
        }
        
        return fast - slow;
    }
};
