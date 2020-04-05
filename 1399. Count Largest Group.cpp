//Runtime: 28 ms, faster than 12.50% of C++ online submissions for Count Largest Group.
//Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for Count Largest Group.
class Solution {
public:
    int digitSum(int n){
        int sum = 0;
        
        while(n){
            sum += n%10;
            n/=10;
        }
        
        return sum;
    };
    
    int countLargestGroup(int n) {
        map<int, int> count;
        int maxCount = 0;
        
        for(int i = 1; i <= n; i++){
            int dsum = digitSum(i);
            count[dsum]++;
            maxCount = max(maxCount, count[dsum]);
        }
        
        int ans = 0;
        
        for(auto it = count.begin(); it != count.end(); it++){
            if(it->second == maxCount){
                ans++;
            }
        }
        
        return ans;
    }
};
