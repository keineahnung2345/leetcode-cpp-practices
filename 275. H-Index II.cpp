//binary search
//https://leetcode.com/problems/h-index-ii/discuss/71063/Standard-binary-search
//Runtime: 32 ms, faster than 88.51% of C++ online submissions for H-Index II.
//Memory Usage: 18.7 MB, less than 47.45% of C++ online submissions for H-Index II.
//time: O(logN), space: O(1)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        int l = 0, r = n-1;
        int mid;
        
        /*
        c:      3, 3, 5, 8, 25　
        index0: 0, 1, 2, 3, 4  (original index)
        index1: 5, 4, 3, 2, 1  (how many papers having citation >= c[index0])
        
        we want to find the first(largest) index1 s.t.
        c[index0] >= index1,
        i.e. to find the first(smallest) index0 s.t.
        c[index0] >= n-index0
        */
        while(l <= r){
            mid = l + (r-l)/2;
            //convert from index0 to index1, serves as 'h'
            int count = n-mid;
            if(citations[mid] == count){
                return count;
            }else if(citations[mid] > count){
                //r will be an invalid value
                r = mid-1;
            }else if(citations[mid] < count){
                l = mid+1;
            }
        }
        
        //r+1: convert it to a valid value
        /*
        n-(r+1): convert from index0 to index1, 
        i.e. get its count
        */
        
        return n - (r+1);
    }
};
