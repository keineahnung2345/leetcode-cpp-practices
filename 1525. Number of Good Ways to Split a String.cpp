//TLE
//49 / 61 test cases passed.
class Solution {
public:
    int uniqCount(string& s, int start, int end){
        set<char> myset(s.begin()+start, s.begin()+end+1);
        return myset.size();
    };
    
    int uniqCountInterval(string& s, int l, int r){
        int count = 0;
        int n = s.size();
        
        if(l > r) return 0;
        
        int mid = (l+r) >> 1;
        
        if(uniqCount(s, 0, mid) < uniqCount(s, mid+1, n-1)){
            return uniqCountInterval(s, mid+1, r);
        }else if(uniqCount(s, 0, mid) > uniqCount(s, mid+1, n-1)){
            return uniqCountInterval(s, l, mid-1);
        }else{
            //uniqCount(s, 0, mid) == uniqCount(s, mid+1, n-1)
            ++count;
            count += uniqCountInterval(s, l, mid-1);
            count += uniqCountInterval(s, mid+1, r);
        }
        
        return count;
    }
    
    int numSplits(string s) {
        int n = s.size();
        
        return uniqCountInterval(s, 0, n-1);
    }
};

//Two hashmaps
//Runtime: 36 ms, faster than 94.96% of C++ online submissions for Number of Good Ways to Split a String.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Number of Good Ways to Split a String.
//time: O(N)
class Solution {
public:
    int numSplits(string s) {
        vector<int> leftCounter(26), rightCounter(26);
        int leftUniqCount = 0, rightUniqCount = 0;

        for(char c : s){
            if(rightCounter[c-'a'] == 0) ++rightUniqCount;
            ++rightCounter[c-'a'];
        }
        
        int n = s.size();
        int ans = 0;
        
        //stop at n-2: right substring cannot be empty
        for(int i = 0; i < n-1; ++i){
            if(leftCounter[s[i]-'a'] == 0) ++leftUniqCount;
            if(rightCounter[s[i]-'a'] == 1) --rightUniqCount;
            if(leftUniqCount == rightUniqCount) ++ans;
            ++leftCounter[s[i]-'a'];
            --rightCounter[s[i]-'a'];
            // cout << leftUniqCount << ", " << rightUniqCount << endl;
        }
        
        return ans;
    }
};
