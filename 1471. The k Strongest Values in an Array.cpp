//Runtime: 968 ms, faster than 52.07% of C++ online submissions for The k Strongest Values in an Array.
//Memory Usage: 80.6 MB, less than 100.00% of C++ online submissions for The k Strongest Values in an Array.
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int median = arr[(n-1)/2];
        
        sort(arr.begin(), arr.end(),
            [&median](const int& x, const int& y){
                return (abs(x-median) == abs(y-median)) ? (x > y) : (abs(x-median) > abs(y-median));
            });
        
        return vector<int>(arr.begin(), arr.begin()+k);
    }
};

//two pointer
//https://leetcode.com/problems/the-k-strongest-values-in-an-array/discuss/674384/C%2B%2BJavaPython-Two-Pointers-%2B-3-Bonuses
//Runtime: 708 ms, faster than 74.91% of C++ online submissions for The k Strongest Values in an Array.
//Memory Usage: 80.5 MB, less than 100.00% of C++ online submissions for The k Strongest Values in an Array.
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int median = arr[(n-1)/2];
        int i = 0, j = n-1;
        
        //remove k weakest values
        while(k-- > 0){
            if(median - arr[i] > arr[j] - median){
                ++i;
            }else/* if(median - arr[i] <= arr[j] - median)*/{
                /*
                when median - arr[i] == arr[j] - median,
                we choose to move j forward,
                i.e. to maintain the original arr[j],
                because arr[j] is larger than arr[i],
                so arr[j] is also stronger than arr[i]
                */
                --j;
            }
        }
        
        //[i, j] are to be removed
        arr.erase(arr.begin()+i, arr.begin()+j+1);
        return arr;
    }
};

//partial_sort
//https://leetcode.com/problems/the-k-strongest-values-in-an-array/discuss/674384/C%2B%2BJavaPython-Two-Pointers-%2B-3-Bonuses
//Runtime: 1508 ms, faster than 23.09% of C++ online submissions for The k Strongest Values in an Array.
//Memory Usage: 80.4 MB, less than 100.00% of C++ online submissions for The k Strongest Values in an Array.
//time: O(nlogk)
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        if(n == 0) return arr;
        //quick select, O(n)
        nth_element(arr.begin(), arr.begin() + (n-1)/2, arr.end());
        int median = arr[(n-1)/2];
        //O(nlogk)
        partial_sort(arr.begin(), arr.begin()+k, arr.end(),
            [&median](const int& a, const int& b){
                return abs(a-median) == abs(b-median) ? a > b : abs(a-median) > abs(b-median);
            });
        arr.resize(k);
        return arr;
    }
};

//heap
//https://leetcode.com/problems/the-k-strongest-values-in-an-array/discuss/674384/C%2B%2BJavaPython-Two-Pointers-%2B-3-Bonuses
//Runtime: 992 ms, faster than 47.27% of C++ online submissions for The k Strongest Values in an Array.
//Memory Usage: 85.8 MB, less than 100.00% of C++ online submissions for The k Strongest Values in an Array.
//time: O(n+klogn)
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        if(n == 0) return arr;
        //O(n)
        nth_element(arr.begin(), arr.begin() + (n-1)/2, arr.end());
        int median = arr[(n-1)/2];
        
        //the comp function is the opposite from previous method!
        //since we want the larger to be popped earlier
        auto comp = [&median](const int& a, const int& b){
            return abs(a-median) == abs(b-median) ? a < b : abs(a-median) < abs(b-median);
        };
        
        //build heap: O(n)
        //https://www.geeksforgeeks.org/time-complexity-of-building-a-heap/
        priority_queue<int, vector<int>, decltype(comp)> pq(arr.begin(), arr.end(), comp);
        
        //O(klogn)
        vector<int> ans;
        while(k-- > 0){
            ans.push_back(pq.top()); pq.pop();
        }
        
        return ans;
    }
};
