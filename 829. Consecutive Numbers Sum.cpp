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
