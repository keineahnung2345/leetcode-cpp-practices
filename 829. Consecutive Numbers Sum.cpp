//Two pointer + binary search
//TLE
//120 / 170 test cases passed.
class Solution {
public:
    long long cumsum(int i, int j){
        long long a = i+j;
        long long b = j-i+1;
        
        if(a & 1) b >>= 1;
        else if(b & 1) a >>= 1;
        
        return a*b;
    }
    
    int consecutiveNumbersSum(int N) {
        int count = 0;
        
        //find two number i and j s.t. i+(i+1)+...+j = N
        for(int i = 1; i < N; ++i){
            /*
            binary search to find a j s.t.
            i+(i+1)+...+j = N
            
            j's range is [i+1, N-1]
            */
            
            int l = i+1, r = N-1;
            int j;
            
            while(l <= r){
                j = (l+r) >> 1;
                
                // int windowSum = ((i+j)*(j-i+1))>>1;
                long long windowSum = cumsum(i, j);
                // cout << "[" << i << ", " << j << "]: " << windowSum << endl;
                
                if(windowSum < N){
                    l = j+1;
                }else if(windowSum > N){
                    r = j-1;
                }else{
                    ++count;
                    break;
                }
            }
        }
        
        return count+1;
    }
};

//Math
//https://leetcode.com/problems/consecutive-numbers-sum/discuss/129015/5-lines-C%2B%2B-solution-with-detailed-mathematical-explanation.
//Runtime: 8 ms, faster than 33.16% of C++ online submissions for Consecutive Numbers Sum.
//Memory Usage: 5.9 MB, less than 71.57% of C++ online submissions for Consecutive Numbers Sum.
class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int count = 0;
        
        /*
        k terms:
        x + (x+1) + (x+2) + ... + (x+k-1) = N
        kx + k*(k-1)/2 = N
        (N - k*(k-1)/2) % k == 0 means
        there is a window starting from x with size k sum to N

        upper bound for k:
        (N - k*(k-1)/2) should be greater than 0,
        so N > k*(k-1)/2,
        k*k-k < 2*N,
        (k-1)*(k-1) < k*k-k < 2*N,
        k-1 < sqrt(2*N),
        k < sqrt(2*N)+1
        */
        for(int k = 2; k < sqrt(2*N)+1; ++k){
            /*
            https://leetcode.com/problems/consecutive-numbers-sum/discuss/129015/5-lines-C++-solution-with-detailed-mathematical-explanation./369550
            N=15 and k=6,
            the approximate condition: k < sqrt(2*N)+1 -> (k-1)*(k-1) < 2*N
            -> 5*5 < 2*15, this allows k=6.
            but the actual condition: 
            N - k*(k-1)/2 > 0 -> k*(k-1) < 2*N -> 6*5 < 2*15,
            this doesn't allow.
            So our condition "k < sqrt(2*N)+1" is not tight enough. 
            For N=15 it allows k=6 numbers starting from 0 (0,1,2,3,4,5) to be considered.
            so we still need to check "k*(k-1) < 2*N"
            */
            if((k*(k-1) < 2*N) && ((N - k*(k-1)/2) % k == 0)) ++count;
        }
        
        return count+1;
    }
};
