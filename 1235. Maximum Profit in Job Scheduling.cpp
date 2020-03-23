//Runtime: 196 ms, faster than 45.83% of C++ online submissions for Maximum Profit in Job Scheduling.
//Memory Usage: 14.9 MB, less than 100.00% of C++ online submissions for Maximum Profit in Job Scheduling.
class Solution {
public:
    template <typename T>
    vector<size_t> sort_indexes(const vector<T> &v) {

      // initialize original index locations
      vector<size_t> idx(v.size());
      iota(idx.begin(), idx.end(), 0);

      // sort indexes based on comparing values in v
      sort(idx.begin(), idx.end(),
           [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

      return idx;
    };
    
    template< typename order_iterator, typename value_iterator >
    void reorder( order_iterator order_begin, order_iterator order_end, value_iterator v )  {   
        typedef typename std::iterator_traits< value_iterator >::value_type value_t;
        typedef typename std::iterator_traits< order_iterator >::value_type index_t;
        typedef typename std::iterator_traits< order_iterator >::difference_type diff_t;

        diff_t remaining = order_end - 1 - order_begin;
        for ( index_t s = index_t(), d; remaining > 0; ++ s ) {
            for ( d = order_begin[s]; d > s; d = order_begin[d] ) ;
            if ( d == s ) {
                -- remaining;
                value_t temp = v[s];
                while ( d = order_begin[d], d != s ) {
                    std::swap( temp, v[d] );
                    -- remaining;
                }
                v[s] = temp;
            }
        }
    };
    
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int N = startTime.size();
        
        vector<size_t> ixs = sort_indexes(startTime);
        vector<size_t> tmp(N);
        for(int i = 0; i < N; i++){
            int ix = ixs[i];
            tmp[ix] = i;
        }
        ixs = tmp;
        
        reorder(ixs.begin(), ixs.end(), startTime.begin());
        reorder(ixs.begin(), ixs.end(), endTime.begin());
        reorder(ixs.begin(), ixs.end(), profit.begin());
        
        vector<int> dp(N, 0);
        
        for(int i = N-1; i >= 0; i--){
            int curEnd = endTime[i];
            //lower_bound: find the smallest number >= x
            auto afterIt = lower_bound(startTime.begin(), startTime.end(), curEnd);
            int afterIdx = -1;
            if(afterIt != startTime.end()){
                afterIdx = afterIt - startTime.begin();
            }
            dp[i] = max((i+1 < N ? dp[i+1] : 0), 
                        profit[i] + (afterIdx >= 0 ? dp[afterIdx] : 0));
        }
        
//         copy(ixs.begin(), ixs.end(), ostream_iterator<int>(cout, " "));
//         cout << endl;
        
//         copy(startTime.begin(), startTime.end(), ostream_iterator<int>(cout, " "));
//         cout << endl;
        
//         copy(endTime.begin(), endTime.end(), ostream_iterator<int>(cout, " "));
//         cout << endl;
        
//         copy(profit.begin(), profit.end(), ostream_iterator<int>(cout, " "));
//         cout << endl;
        
//         copy(dp.begin(), dp.end(), ostream_iterator<int>(cout, " "));
//         cout << endl;
        
        return dp[0];
    }
};
