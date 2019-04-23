//Runtime: 20 ms, faster than 91.05% of C++ online submissions for Can Place Flowers.
//Memory Usage: 10.9 MB, less than 86.42% of C++ online submissions for Can Place Flowers.
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        vector<int> planted;
        for(int i = 0; i < flowerbed.size(); i++){
            if(flowerbed[i] == 1) planted.push_back(i);
        }
        
        //when the first flower locates at x >= 2, we can plant flower(s) at left
        planted.insert(planted.begin(), -2);
        //when the last flower locates at x <= n-3, we can plant flower(s) at right
        planted.push_back(flowerbed.size()+1);
        
        int count = 0;
        // if(planted[0] >= 2) count += planted[i]/2;
        // if(flowerbed.size()-1-planted.back() >= 2) count += (flowerbed.size()-1-planted.back())/2;
         
        for(int i = 1; i < planted.size(); i++){
            if(planted[i] - planted[i-1] >= 4){
                count += ((planted[i] - planted[i-1])/2-1);
            }
            if(count >= n) return true;
        }
        
        return false;
    }
};
