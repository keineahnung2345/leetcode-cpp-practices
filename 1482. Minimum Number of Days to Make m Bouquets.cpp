//sliding window + binary search
//Runtime: 1744 ms, faster than 10.00% of C++ online submissions for Minimum Number of Days to Make m Bouquets.
//Memory Usage: 165.3 MB, less than 10.00% of C++ online submissions for Minimum Number of Days to Make m Bouquets.
class Solution {
public:
    bool check(vector<int>& bloomDay, int m, int k, int day){
        int start = 0, end = 0;
        
        for(int i = 0; i < bloomDay.size(); i++){
            if(bloomDay[i] <= day){
                if(start == -1 || end+1 != i){
                    //new window
                    start = end = i;
                }else if(end+1 == i){
                    //extend existing window
                    end++;
                }
                
                if(end-start+1 == k){
                    m--;
                    start = end = -1;
                }
                
                if(m == 0) return true;
            }
        }
        
        return false;
    };
    
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if(m*k > n) return -1;
        
        unordered_map<int, int> mcounter;
        for(int& day : bloomDay){
            mcounter[day] += 1;
        }
        
        vector<vector<int>> counter;
        for(auto it = mcounter.begin(); it != mcounter.end(); it++){
            counter.push_back({it->first, it->second});
        }
        
        //smaller day, larger count
        sort(counter.begin(), counter.end(), [](const vector<int>& v1, const vector<int>& v2){
            return (v1[0] == v2[0]) ? (v1[1] > v2[1]) : (v1[0] < v2[0]);
        });
        
        int left = -1, right = counter.size()-1, mid;
        int totalCount = 0;
        for(int i = 0; i < counter.size(); i++){
            totalCount += counter[i][1];
            if(totalCount >= m*k){
                left = i;
                break;
                // if(check(bloomDay, m, k, counter[i][0])){
                //     return counter[i][0];
                // }
            }
        }
        
        if(left == -1) return -1;
        
        //find left boundary
        while(left <= right){
            mid = left + (right-left)/2;
            if(check(bloomDay, m, k, counter[mid][0])){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        
        return counter[left][0];
    }
};

//just binary search
//https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/discuss/686316/JavaC%2B%2BPython-Binary-Search
//Runtime: 364 ms, faster than 88.50% of C++ online submissions for Minimum Number of Days to Make m Bouquets.
//Memory Usage: 63.3 MB, less than 10.00% of C++ online submissions for Minimum Number of Days to Make m Bouquets.
//time: O(log(max(bloomDay))), space: O(1)
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if(m*k > n) return -1;
        
        int left = 1, right = 1e9;
        
        while(left <= right){
            int mid = left + (right - left)/2;
            //window size and window count
            int wsize = 0, wcount = 0;
            for(int i = 0; i < bloomDay.size(); i++){
                if(mid < bloomDay[i]){
                    //the old window is broken
                    wsize = 0;
                }else if(++wsize >= k){
                    //the window is large enough
                    wcount++;
                    //prepare for next iteration
                    wsize = 0;
                }
            }
            
            if(wcount >= m){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        /*
        we can definitely find a day s.t. we can hold m bouquets,
        because n >= m*k, we just wait until all flowers blossom
        */
        return left;
    }
};
