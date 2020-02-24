//Runtime: 284 ms, faster than 47.30% of C++ online submissions for Reduce Array Size to The Half.
//Memory Usage: 42 MB, less than 100.00% of C++ online submissions for Reduce Array Size to The Half.

struct RetrieveValue
{   
    template <typename T>
    typename T::second_type operator()(T keyValuePair) const
    {   
        return keyValuePair.second;
    }
};

class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int n = arr.size();
        map<int, int> count;
        vector<int> values;
        int ans = 0, acc = 0;
        
        for(int e : arr){
            count[e]++;
        }
        
        transform(count.begin(), count.end(), back_inserter(values), RetrieveValue());

        sort(values.begin(), values.end(), greater<int>());
        
        while(acc < n/2){
            acc += values[ans++];
        }
        
        return ans;
    }
};
