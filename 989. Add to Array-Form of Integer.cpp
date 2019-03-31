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
