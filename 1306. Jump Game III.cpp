//Runtime: 44 ms, faster than 97.42% of C++ online submissions for Jump Game III.
//Memory Usage: 12.7 MB, less than 100.00% of C++ online submissions for Jump Game III.

class Solution {
public:
    enum Index{
        GOOD, BAD, UNKNOWN
    };
    
    vector<Index> reach;
    vector<bool> visited;
    
    bool canReachRecursive(vector<int>& arr, int start) {
        //avoid fall into a loop in the graph
        if(visited[start]){
            reach[start] = Index::BAD;
            return reach[start];
        }
        visited[start] = true;
        
        // cout << start << ": ";
        // switch(reach[start]){
        //     case Index::GOOD:
        //         cout << "G ";
        //         break;
        //     case Index::BAD:
        //         cout << "B ";
        //         break;
        //     case Index::UNKNOWN:
        //         cout << "U ";
        // }
        // cout << endl;
        
        if(reach[start] == Index::GOOD || reach[start] == Index::BAD){
            return reach[start];
        }
        
        //jump right
        if(start + arr[start] < arr.size()){
            if(canReachRecursive(arr, start + arr[start]) == Index::GOOD){
                reach[start] = Index::GOOD;
                return reach[start];
            }
        }
        
        //jump left
        if(start - arr[start] >= 0){    
            if(canReachRecursive(arr, start - arr[start]) == Index::GOOD){
                reach[start] = Index::GOOD;
                return reach[start];
            }
        }
        
        //cannot reach 0
        reach[start] = Index::BAD;
        
        // for(int i = 0; i < reach.size(); i++){
        //     cout << i << ": ";
        //     switch(reach[i]){
        //         case Index::GOOD:
        //             cout << "G ";
        //             break;
        //         case Index::BAD:
        //             cout << "B ";
        //             break;
        //         case Index::UNKNOWN:
        //             cout << "U ";
        //     }
        // }
        // cout << endl;
        
        return reach[start];
    }
    
    bool canReach(vector<int>& arr, int start) {
        int N = arr.size();
        
        reach = vector<Index>(N, Index::UNKNOWN);
        visited = vector<bool>(N, false);
        
        for(int i = 0; i < N; i++){
            if(arr[i] == 0)
                reach[i] = Index::GOOD;
        }
        
        return canReachRecursive(arr, start) == Index::GOOD;
    }
};

//Recursion
//https://leetcode.com/problems/jump-game-iii/discuss/464083/C%2B%2BJava-Recursion
//Runtime: 52 ms, faster than 77.17% of C++ online submissions for Jump Game III.
//Memory Usage: 11.9 MB, less than 100.00% of C++ online submissions for Jump Game III.
//time: O(n), space: O(n)
class Solution {
public:
    set<int> visited;
    
    bool canReach(vector<int>& arr, int start) {
        if((start >= 0) && (start < arr.size()) && visited.insert(start).second){
            return arr[start] == 0 || canReach(arr, start+arr[start]) || canReach(arr, start-arr[start]);
        }
        //not valid "start" or already visited
        return false;
    }
};
