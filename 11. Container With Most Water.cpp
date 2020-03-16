//WA
class Solution {
public:
    int maxArea(vector<int>& height) {
        int N = height.size();
        int left = 0, right = N-1;
        int ans = 0;
        bool leftTurn = true;
        
        while(left < right){
            int lh = height[left], rh = height[right];
            // cout << left << " " << right << endl;
            ans = max(ans, min(lh, rh) * (right-left));
            
            if(leftTurn){
                //move left so heigh[left] is larger than old lh
                do{
                    left++;
                    // cout << "left: " << left << endl;
                }while(left < N && height[left] <= lh);
            }else{
                //move right so height[right] is larger than old rh
                do{
                    right--;
                    // cout << "right: " << right << endl;
                }while(right >= 0 && height[right] <= rh);
            }
            
            leftTurn = !leftTurn;
            
        }
        
        return ans;
    }
};
