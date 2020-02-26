//Runtime: 40 ms, faster than 27.67% of C++ online submissions for Duplicate Zeros.
//Memory Usage: 9.5 MB, less than 100.00% of C++ online submissions for Duplicate Zeros.

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        
        for(int i = n-1; i >= 0; i--){
            if(arr[i] == 0){
                arr.insert(arr.begin() + i, 0);
            }
        }
        
        arr.resize(n);
    }
};

//official sol
//time: O(N), space: O(1)
//Runtime: 16 ms, faster than 98.61% of C++ online submissions for Duplicate Zeros.
//Memory Usage: 9.3 MB, less than 100.00% of C++ online submissions for Duplicate Zeros.

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int possibleDups = 0;
        int n = arr.size();
        
        for(int left = 0; left + possibleDups < n; left++){
            if(arr[left] == 0){
                if(left + possibleDups == n - 1){
                    //set the last element to 0
                    //and decrease the effective length by 1
                    arr[n-1] = 0;
                    n -= 1;
                    break;
                }
                //zero's count
                possibleDups++;
            }
        }
        
        int last = n - 1 - possibleDups;
        //fill from the end
        for(int i = last; i >= 0; i--){
            if(arr[i] == 0){
                //0 take 2 places
                arr[i + possibleDups] = 0;
                arr[i + possibleDups - 1] = 0;
                possibleDups--;
            }else{
                arr[i + possibleDups] = arr[i];
            }
        }
    }
};
