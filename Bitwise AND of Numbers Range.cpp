//bit operation
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        if(m == 0) return 0;
        //log(0) is not defined
        int mb = log2(m), nb = log2(n);
        
        if(mb != nb) return 0;
        
        int ans = 0;
        
        //examine one bit at a time
        while(mb == nb){
            //remove that bit once examined
            ans += (1 << mb);
            m -= (1 << mb);
            n -= (1 << mb);
            if(m == 0) break;
            mb = log2(m);
            nb = log2(n);
        };
        
        return ans;
    }
};
