//Runtime: 72 ms, faster than 99.56% of C++ online submissions for Find K Closest Elements.
//Memory Usage: 31 MB, less than 16.67% of C++ online submissions for Find K Closest Elements.
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        auto it = lower_bound(arr.begin(), arr.end(), x);
        
        if(it == arr.begin()){
            return vector<int>(arr.begin(), arr.begin()+k);
        }else if(it == arr.end()){
            return vector<int>(arr.end() - k, arr.end());
        }
        
        int n = arr.size();
        int idx = it - arr.begin();
        int left, right;
        left = idx - k/2;
        right = left + k;
        
        // cout << left << ", " << right << " -> ";
        
        if(left < 0){
            left = 0;
            right = left +k;
        }
        
        if(right > n){
            right = n;
            left = right - k;
        }
        
        // cout << left << ", " << right << " -> ";
        
        /*
        since arr[idx] is just a surrogate of x, 
        we need to examine the diff of elements with "x" again
        */
        
        /*
        while the diff of the element to the leftmost element "<=" that of the rightmost element,
        move the subarray left
        
        here the "<=" means we prefer smaller element
        */
        while(left > 0 && x - arr[left-1] <= arr[right-1] - x){
            right--;
            left--;
        }
        
        /*
        while the diff of rightmost element "<" that of the element to the leftmost element,
        move the subarray right
        */
        while(right < n && arr[(right-1)+1] - x < x - arr[left]){
            right++;
            left++;
        }
        
        // cout << left << ", " << right << endl;
        
        return vector<int>(arr.begin()+left , arr.begin()+right);
    }
};

//Approach 2: Binary Search and Two Pointers
//similar as above, cleaner
//Runtime: 116 ms, faster than 38.21% of C++ online submissions for Find K Closest Elements.
//Memory Usage: 31.2 MB, less than 16.67% of C++ online submissions for Find K Closest Elements.
//time: O(logN+K), space: O(K)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        //find element >= x
        auto it = lower_bound(arr.begin(), arr.end(), x);
        
        if(it == arr.begin()){
            return vector<int>(arr.begin(), arr.begin()+k);
        }else if(it == arr.end()){
            return vector<int>(arr.end() - k, arr.end());
        }
        
        int n = arr.size();
        int idx = it - arr.begin();
        int left, right;
        /*
        search range suggested by solution is [idx-(k-1), idx+(k-1)],
        but idx will not necessary be included in final subarray, 
        so here expand the search range
        */
        left = max(0, idx - k); //max(0, idx - (k-1));
        right = min(n-1, idx + k); //min(n-1, idx + (k-1));
        //[left, right]: both inclusive
        
        // cout << left << ", " << right << " ";
        
        while(right - left + 1 > k){
            if(x - arr[left] <= arr[right] - x){
                right--;
            }else if(arr[right] - x < x - arr[left]){
                left++;
            }
            // cout << left << ", " << right << " ";
        }
        
        return vector<int>(arr.begin()+left , arr.begin()+right+1);
    }
};


//Approach 1: sort
//Runtime: 284 ms, faster than 7.52% of C++ online submissions for Find K Closest Elements.
//Memory Usage: 31.2 MB, less than 16.67% of C++ online submissions for Find K Closest Elements.
//time: O(NlogN), space: O(k)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        sort(arr.begin(), arr.end(), [x](const int& a, const int& b){
            return (abs(a-x) == abs(b-x)) ? a < b : (abs(a-x) < abs(b-x));
        });
        
        vector<int> ans(arr.begin(), arr.begin()+k);
        //now ans is not ascending, need to sort it again
        
        sort(ans.begin(), ans.end());
        
        return ans;
    }
};
