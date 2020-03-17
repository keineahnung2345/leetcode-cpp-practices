//Runtime: 104 ms, faster than 94.88% of C++ online submissions for Boats to Save People.
//Memory Usage: 13.3 MB, less than 100.00% of C++ online submissions for Boats to Save People.

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int N = people.size();
        // for(int i = 0; i < N; i++){
        //     cout << people[i] << " ";
        // }
        // cout << endl;
        //the boundaries, exclusive
        int left = -1, right = N;
        int boats = 0;
        
        //the range to be explored is (left, right) = (left+1, right-1)
        //, and there should be at least one empty position in the range so we need right - left > 1
        while(left+1 < N && right-1 >= 0 && right - left > 1){
            int cur = 0;
            cur += people[--right];
            if(right-1 >= 0 && right - left > 1 && cur + people[right-1] <= limit){
                cur += people[--right];
            }else if(left+1 < N && right - left > 1 && cur + people[left+1] <= limit){
                cur += people[++left];
            }
            boats++;
            // cout << "(" << left << ", " << right << ") " << cur << " " << boats << endl;
        }
        
        return boats;
    }
};

//Approach 1: Greedy (Two Pointer)
//Runtime: 108 ms, faster than 92.83% of C++ online submissions for Boats to Save People.
//Memory Usage: 13 MB, less than 100.00% of C++ online submissions for Boats to Save People.
//time: O(nlogn), space: O(n)
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int N = people.size();
        int i = 0, j = N-1;
        int ans = 0;
        
        sort(people.begin(), people.end());
        // for(int k = 0; k < N; k++){
        //     cout << people[k] << " ";
        // }
        // cout << endl;
        
        while(i <= j){
            ans++;
            //when i equals to j, people[i] may be added twice
            //, but that doesn't affect the ans
            
            if(people[i] + people[j] <= limit){
                i++;
            }
            j--;
            // cout << "[" << i << ", " << j << "]" << endl;
        }
        
        return ans;
    }
};
