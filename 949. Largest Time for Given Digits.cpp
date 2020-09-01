//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Largest Time for Given Digits.
//Memory Usage: 9.5 MB, less than 80.82% of C++ online submissions for Largest Time for Given Digits.
class Solution {
public:
    string largestTimeFromDigits(vector<int>& A) {
        /*
        ??:??
        first: 0,1,2
        second: 0-9 when first is 0,1; 0-3 when first is 2
        third: 0-5
        fourth: 0-9
        */
        sort(A.begin(), A.end());
        
        int se1_count = 0, se2_count = 0, se3_count = 0, se5_count = 0;
        
        for(int e: A){
            if(e <= 1) ++se1_count;
            if(e <= 2) ++se2_count;
            if(e <= 3) ++se3_count;
            if(e <= 5) ++se5_count;
        }

        if(se2_count < 1 || se5_count < 2){
            return "";
        }

        string ans;
        if(A[se2_count-1] == 2 && se3_count-1 >= 1 && se5_count - 2 >= 1){
            //we can build 2?:??
            ans += A[se2_count-1] + '0';
            A.erase(A.begin()+se2_count-1);
            --se3_count;
            --se5_count;
            // cout << ans << endl;

            ans += A[se3_count-1] + '0';
            A.erase(A.begin()+se3_count-1);
            --se5_count;

            ans += ':';
            // cout << ans << endl;

            ans += A[se5_count-1] + '0';
            A.erase(A.begin()+se5_count-1);
            // cout << ans << endl;

            ans += A[0] + '0';
            // cout << ans << endl;
            return ans;
        }else if(se1_count < 1){
            //cannot build "0?:??" or "1?:??"
            return "";
        }
        
        ans += A[se1_count-1] + '0';
        A.erase(A.begin()+se1_count-1);
        --se2_count;
        --se3_count;
        --se5_count;
        
        // cout << ans << endl;

        ans += A.back() + '0';
        if(A.back() <= 5) --se5_count;
        A.pop_back();
        // cout << ans << endl;

        ans += ':';

        // cout << "se5: " << se5_count << endl;
        ans += A[se5_count-1] + '0';
        A.erase(A.begin()+se5_count-1);
        // cout << ans << endl;

        ans += A[0] + '0';
        // cout << ans << endl;

        return ans;
    }
};
