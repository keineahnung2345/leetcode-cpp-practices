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

//Speed up with count_if
//https://leetcode.com/problems/count-largest-group/discuss/563295/C%2B%2BJava-Count
//Runtime: 4 ms, faster than 87.50% of C++ online submissions for Count Largest Group.
//Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for Count Largest Group.
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
        //n's range: [1...10000], 9999's digit sum is 36, which is largest
        vector<int> count(37);
        int maxCount = 0;
        
        for(int i = 1; i <= n; i++){
            int dsum = digitSum(i);
            count[dsum]++;
            maxCount = max(maxCount, count[dsum]);
        }
        
        return count_if(count.begin(), count.end(), 
            [&maxCount](int n){return n == maxCount;});
    }
};
