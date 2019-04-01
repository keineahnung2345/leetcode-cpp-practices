//Runtime: 116 ms, faster than 99.24% of C++ online submissions for Add to Array-Form of Integer.
//Memory Usage: 12.2 MB, less than 100.00% of C++ online submissions for Add to Array-Form of Integer.

class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        int cur = 0;
        int N = A.size();
        
        //add K to A
        while(K > 0){
            int cursum;
            //current digit
            if(N-1-cur >= 0){
                cursum = A[N-1-cur]+K%10;
                A[N-1-cur] = cursum%10;
            }else{
                cursum = K%10;
                A.insert(A.begin(), cursum);
                //now the size of A changes
                N++;
            }
            //carry over
            if(N-1-(cur+1) >= 0){
                //just update the higher digit
                A[N-1-(cur+1)] += cursum/10;
            }else if(cursum/10 > 0){
                //need one more digit
                A.insert(A.begin(), cursum/10);
                N++;
            }
            K/=10;
            cur++;
        }
        //deal with carry over
        while(N-1-cur >= 0 && A[N-1-cur] >= 10){
            int tmp = A[N-1-cur];
            //current digit
            A[N-1-cur] = tmp%10;
            //deal with carry over
            if(N-1-(cur+1) >= 0){
                A[N-1-(cur+1)] += tmp/10;
            }else{
                A.insert(A.begin(), tmp/10);
            }
            cur++;
        }
        return A;
    }
};

/**
Approach 1: Schoolbook Addition
Intuition

Let's add numbers in a schoolbook way, column by column. For example, to add 123 and 912, we add 3+2, then 2+1, then 1+9. Whenever our addition result is more than 10, we carry the 1 into the next column. The result is 1035.

Algorithm

We can do a variant of the above idea that is easier to implement - we put the entire addend in the first column from the right.

Continuing the example of 123 + 912, we start with [1, 2, 3+912]. Then we perform the addition 3+912, leaving 915. The 5 stays as the digit, while we 'carry' 910 into the next column which becomes 91.

We repeat this process with [1, 2+91, 5]. We have 93, where 3 stays and 90 is carried over as 9. Again, we have [1+9, 3, 5] which transforms into [1, 0, 3, 5].
**/

/**
Complexity Analysis

Time Complexity: O(\max(N, \log K))O(max(N,logK)) where NN is the length of A.

Space Complexity: O(\max(N, \log K))O(max(N,logK)). 
**/

//Runtime: 116 ms, faster than 99.24% of C++ online submissions for Add to Array-Form of Integer.
//Memory Usage: 13.7 MB, less than 52.65% of C++ online submissions for Add to Array-Form of Integer.
/**
class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        int N = A.size();
        vector<int> ans;
        
        int i = N-1;
        //exit when both A and K are visited through
        while(i >= 0 || K > 0){
            if(i >= 0) K += A[i];
            ans.push_back(K%10);
            K/=10;
            i--;
        }
        
        reverse(ans.begin(), ans.end());
        
        return ans;
    }
};
**/
