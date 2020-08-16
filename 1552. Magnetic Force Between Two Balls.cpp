//Binary search
//Runtime: 440 ms, faster than 100.00% of C++ online submissions for Magnetic Force Between Two Balls.
//Memory Usage: 57.9 MB, less than 33.33% of C++ online submissions for Magnetic Force Between Two Balls.
class Solution {
public:
    int check(vector<int>& pos, int& m, int interval){
        int count = 1;
        int last = pos[0];
        
        for(int& e : pos){
            if(e - last >= interval){
                ++count;
                last = e;
                if(count >= m) return true;
            }
        }
        
        return false;
    };
    
    int maxDistance(vector<int>& pos, int m) {
        sort(pos.begin(), pos.end());
        
        int interval = (pos.back() - pos.front()) / (m-1);
        
        int l = 1, r = interval;
        
        //find right boundary
        while(l <= r){
            int mid = (l+r) >> 1;
            // cout << l << ", " << mid << ", " << r << endl;
            if(check(pos, m, mid)){
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
        
        return r;
    }
};
