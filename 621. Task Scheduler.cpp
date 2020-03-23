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

//sort by value and then by key
class VKComparison{
public:
    VKComparison(){}
    /*
    sort by count(the larger the earlier to be popped), 
    and then by char(the smaller the earlier to be popped)
    */
    bool operator() (const pair<char, int>& lhs, const pair<char, int>&rhs) const{
        return (lhs.second == rhs.second) ? (lhs.first > rhs.first) : (lhs.second < rhs.second);
    }
};

//Priority queue, greedy
//https://leetcode.com/problems/task-scheduler/discuss/104501/Java-PriorityQueue-solution-Similar-problem-Rearrange-string-K-distance-apart
//Runtime: 236 ms, faster than 5.64% of C++ online submissions for Task Scheduler.
//Memory Usage: 22.2 MB, less than 6.38% of C++ online submissions for Task Scheduler.
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> counter;
        priority_queue<pair<char, int>, vector<pair<char, int>>, VKComparison> pq;
        
        for(char task : tasks){
            counter[task]++;
        }
        
        for(auto it = counter.begin(); it != counter.end(); it++){
            pq.push(make_pair(it->first, it->second));
        }
        
        int ans = 0;
        
        while(!pq.empty()){
            //current part's size
            int part = n+1;
            
            vector<pair<char, int>> tmpRemoved;
            
            //while we still have space or we still have different task
            while(part > 0 && !pq.empty()){
                pair<char, int> cur = pq.top(); pq.pop();
                cur.second--;
                tmpRemoved.push_back(cur);
                part--;
                //we've put a task into this part
                ans++;
                // cout << cur.first;
            }
            
            for(pair<char, int> p : tmpRemoved){
                if(p.second > 0){
                    pq.push(p);
                }
            }
            
            //we've done all tasks
            if(pq.empty()) break;
            //if part > 0, that means there are "part" idle timeslots
            ans += part;
            //note that we only add these idle slots into ans if we still have some tasks to do(pq is not empty)
            // cout << string(part, ' ');
        }
        // cout << endl;
        
        return ans;
    }
};
