//Counting sort
//https://leetcode.com/problems/h-index/discuss/70768/Java-bucket-sort-O(n)-solution-with-detail-explanation
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for H-Index.
//Memory Usage: 6.7 MB, less than 100.00% of C++ online submissions for H-Index.
//time: O(N)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int N = citations.size();
        vector<int> bucket(N+1, 0);
        
        for(int citation : citations){
            bucket[min(N, citation)]++;
        }
        
        int count = 0;
        for(int i = N; i >= 0; i--){
            count += bucket[i];
            // cout << i << " " << count << endl;
            if(count >= i){
                /*
                there are count papers having at least i citation,
                and the other N-i papers having citation <= i
                */
                return i;
            }
        }
        
        return 0;
    }
};
