//Runtime: 0 ms, faster than 100.00% of C++ online submissions for First Bad Version.
//Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for First Bad Version.
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        //n is 1-based
        if(n == 1) return 1;
        //first -1 to avoid overflow
        int left = 1, right = n;
        int mid = left + (right-left)/2;
        //-1: meaningless, 0: false, 1: true
        unordered_map<int, bool> cache;
        // cout << n+1 << " space allocated." << endl;
        
        do{
            // cout << left << ", " << mid << ", " << right << endl;
            cache[mid] = isBadVersion(mid);
            if(cache[mid]){
                //search left part
                //7->4, 6->3
                right = mid-1;
            }else{
                //search right part
                left = mid+1;

            }
            mid = left + (right-left)/2;
            // if(mid == 1) break; //mid[1-1] is meaningless
        }while((left <= right) && !(cache.find(mid-1)!= cache.end() && cache.find(mid)!= cache.end() && !cache[mid-1] && cache[mid]));
        
        return mid;
    }
};

//binary search
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for First Bad Version.
//Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for First Bad Version.
//time: O(logN), space: O(1)
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        while(left < right){
            int mid = left + (right-left)/2;
            // cout << left << ", " << mid << ", " << right << endl;
            if(isBadVersion(mid)){
                /*
                when right is equal to left+1, 
                mid is also left,
                we should jump out (left < right = mid breaks),  
                because we have found 
                the first bad version which is mid, 
                and mid is equal to left
                */
                right = mid;
            }else{
                left = mid+1;
            }
        }
        return left;
    }
};

//binary seach, different stop condition
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for First Bad Version.
//Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for First Bad Version.
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        while(left <= right){
            int mid = left + (right-left)/2;
            // cout << left << ", " << mid << ", " << right << endl;
            if(isBadVersion(mid)){
                /*
                when right is equal to left+1, 
                mid is also left,
                we should jump out (left = mid <= right = mid-1 breaks), 
                because we have found 
                the first bad version which is mid, 
                and mid is equal to left
                */
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        return left;
    }
};
