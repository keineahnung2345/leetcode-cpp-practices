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

//math
//https://leetcode.com/problems/task-scheduler/discuss/104500/Java-O(n)-time-O(1)-space-1-pass-no-sorting-solution-with-detailed-explanation
//using map
//Runtime: 140 ms, faster than 28.22% of C++ online submissions for Task Scheduler.
//Memory Usage: 7.6 MB, less than 100.00% of C++ online submissions for Task Scheduler.
//using unordered_map
//Runtime: 92 ms, faster than 40.84% of C++ online submissions for Task Scheduler.
//Memory Usage: 7.5 MB, less than 100.00% of C++ online submissions for Task Scheduler.
//time: O(n), space: O(1)
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        //map<int, int> counter;
        unordered_map<int, int> counter;
        int most = 0; //AAABBBCC, A is the task with max count, whichi is 3
        int numMost = 0; //the number of tasks whose count is equal to max, 2 in above example
            
        for(char task : tasks){
            counter[task]++;
            if(most < counter[task]){
                most = counter[task];
                numMost = 1;
            }else if(most == counter[task]){
                numMost++;
            }
        }
        
        //the task with count "most" are splitted by "partCount" parts
        int partCount = most - 1;
        //task with count of "most" will take the empty slot
        /*
        when numMost is too large, "partLength" could be 0 or negative
        in this case, we can make the interval wider than "n" and put all
        tasks into the widened interval so that there will be no idle position
        ("idles" will be 0)
        */
        int partLength = n - (numMost - 1);
        //the empty slots formed by the task with count "most"
        int emptySlots = partCount * partLength;
        int availableTasks = tasks.size() - most * numMost;
        int idles = max(0, emptySlots - availableTasks);
        
        return tasks.size() + idles;
    }
};
