//https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743146/Java-Straightforward-O(N2)-with-optimization
//Runtime: 272 ms, faster than 94.55% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//Memory Usage: 61.7 MB, less than 100.00% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//time: O(N^2), space: O(1)
class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int n = arr.size();
        int res = INT_MAX;
        
        for(int i = 0; i < n; ++i){
            int sum = arr[i];
            for(int j = i; j < n; ++j){
                sum &= arr[j];
                res = min(res, abs(sum-target));
                if(res == 0) return res;
                if(sum < target){
                    /*
                    in inner loop, 
                    the more operations we do,
                    the smaller the "sum",
                    so if sum is already smaller than target,
                    we can just skip further operations
                    */
                    break;
                }
            }
            
            if(sum > target){
                /*
                if sum > target, 
                than sum must be arr[i] & ... & arr[n-1]
                (it completes the inner loop)
                
                in outer loop,
                when we increase i,
                we will get larger "sum",
                so we can just skip further calculation of "sum"
                */
                break;
            }
        }
        
        return res;
    }
};

//https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743381/Python-6-lines-O(nlogm)-solution
//Runtime: 1056 ms, faster than 46.01% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//Memory Usage: 193.9 MB, less than 100.00% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//time: O(nlog(max(arr)))
class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int n = arr.size();
        int ans = INT_MAX;
        /*
        at index j,
        it contains 
        arr[0] & ... & arr[j], 
        arr[1] & ... & arr[j], 
        ..., 
        arr[j-1] & arr[j], 
        arr[j]
        
        for these numbers,
        arr[j] is the largest, and it takes log(arr[j]) bits.
        If we look at bit representations,
        arr[j-1] & arr[j] unset some '1's from arr[j],
        and arr[j-2] & arr[j-1] & arr[j] unset more '1's in arr[j-1] & arr[j],
        ..., and so on, since we have at most log(arr[j]) ones in arr[j],
        so when we are at index j, the size of the set "sum" is O(log(arr[i]))
        
        for all ending index j, the size of "sum" is then O(log(max(arr)))
        */
        set<int> sums;
        
        for(int e : arr){
            set<int> tmp;
            transform(sums.begin(), sums.end(), inserter(tmp, tmp.end()), 
                      [&e](int sum){return (sum & e);});
            tmp.insert(e);
            swap(tmp, sums);
            for(int sum : sums){
                ans = min(ans, abs(sum - target));
            }
        }
        
        return ans;
    }
};

//Binary search
//https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/discuss/743267/C%2B%2B-O(N)-Algorithm-with-detailed-explanation-improved-from-O(N(log(N))
//Runtime: 940 ms, faster than 55.42% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//Memory Usage: 141.9 MB, less than 100.00% of C++ online submissions for Find a Value of a Mysterious Function Closest to Target.
//time: O(NlogN)
class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int n = arr.size();
        int ans = INT_MAX;
        
        const int maxbits = ceil(log2(1e6));
        vector<vector<int>> bit2indices(maxbits);
        
        for(int i = 0; i < n; ++i){
            for(int b = 0; b < maxbits; ++b){
                if(arr[i]>>b & 1){
                    //arr[i]'s bth bit is set
                    bit2indices[b].push_back(i);
                }
            }
        }
        
        /*
        when index is i,
        sums[i]: arr[i]
        sums[i+1]: arr[i]&arr[i+1]
        sums[i+2]: arr[i]&arr[i+1]&arr[i+2]
        ...
        sums[n-1]: arr[i]&...&arr[n-1]
        */
        vector<int> sums(n);
        
        for(int i = n-1; i >= 0; --i){
            //update sums[i+1], sums[i+2], ... sums[n-1]
            for(int b = 0; b < maxbits; ++b){
                if(!((arr[i]>>b)&1)){
                    /*
                    if arr[i]'s jth bit is unset
                    that means we need to 
                    unset all arr[i+1...n-1]'s bth bit
                    */
                    while(!bit2indices[b].empty() && bit2indices[b].back() > i){
                        /*
                        bit2indices[b] is increasing,
                        so bit2indices[b].back() is the largest in bit2indices[b]
                        */
                        
                        /*
                        sums[x]'s meaning changes from arr[i+1]&...&arr[n-1]
                        to arr[i]&arr[i+1]&...&arr[n-1],
                        i.e. sums[x] = sums[x] & arr[i],
                        we unset all sums[x]'s 1s bit by bit
                        */
                        sums[bit2indices[b].back()] -= 1<<b;
                        //After set this element's j'th bit to zero, we need not consider this bit again?
                        bit2indices[b].pop_back();
                    }
                }
            }
            sums[i] = arr[i];
            
            //sums[i...n-1] is decreasing
            //binary search
            int l = i, r = n;
            int mid;
            while(l < r){
                mid = (l+r) >> 1;
                if(sums[mid] == target){
                    return 0;
                }else if(sums[mid] > target){
                    l = mid+1;
                }else{
                    //sums[mid] > target
                    r = mid;
                }
            }
            
            //?
            if(l == n)ans = min(ans, abs(sums[n-1]-target));
            else if(l == i)ans = min(ans, abs(sums[i]-target));
            else ans = min({ans, abs(sums[l]-target), abs(sums[l -1]-target)});
        }
        
        return ans;
    }
};
