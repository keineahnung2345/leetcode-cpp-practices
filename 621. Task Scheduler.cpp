//WA
//51 / 69 test cases passed.
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        map<char, int> counter;
        map<char, int>::iterator it;
        
        for(char task : tasks){
            counter[task]++;
        }
        
//         it = counter.begin();
//         while(!counter.empty()){
//             it->second--;
//             if(it->second == 0){
//                 char key = it->first;
//                 it++;
//                 counter.erase(key);
//             }
            
//         }
        
        //sort by key, descending
        multimap<int, char, greater<int>> counterR;
        
        for(it = counter.begin(); it != counter.end(); it++){
            counterR.insert(make_pair(it->second, it->first));
        }
        
        int ans = 0;
        //the empty spaces in between
        int empty = 0;
        bool first = true;
        for(multimap<int, char>::iterator itM = counterR.begin(); itM != counterR.end(); itM++){
            if(first){
                ans += (itM->first-1) * (n+1) + 1;
                empty = n * (itM->first-1);
                first = false;
            }else if(itM->first == counterR.begin()->first && empty != 0){
                empty= max(empty - itM->first, 0);
                ans++;
                first = true;
            }else if(empty >= itM->first){
                empty-= itM->first;
            }else{
                ans += (itM->first-1) * (n+1) + 1;
                empty = n * (itM->first-1);
            }
            cout << ans << " " << empty << endl;
        }
        
        return ans;
    }
};
