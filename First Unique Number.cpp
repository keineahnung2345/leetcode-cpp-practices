//TLE
//15 / 17 test cases passed.
class FirstUnique {
public:
    map<int, int> counter;
    vector<int> uniqs;
    
    FirstUnique(vector<int>& nums) {
        for(int num : nums){
            counter[num] += 1;
            if(counter[num] == 1){
                uniqs.push_back(num);
            }else{
                vector<int>::iterator position = find(uniqs.begin(), uniqs.end(), num);
                if (position != uniqs.end())
                    uniqs.erase(position);
            }
        }
    }
    
    int showFirstUnique() {
        return uniqs.size() > 0 ? uniqs[0] : -1;
    }
    
    void add(int value) {
        if(counter.find(value) == counter.end()){
            counter[value] = 1;
            uniqs.push_back(value);
        }else{
            counter[value]++;
            vector<int>::iterator position = find(uniqs.begin(), uniqs.end(), value);
            if (position != uniqs.end())
                uniqs.erase(position);
        }
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
 
//double linked list
//Runtime: 1204 ms
//Memory Usage: 91.3 MB
class DLinkedNode{
public:
    DLinkedNode *prev, *next;
    int value;
    DLinkedNode(int v) : value(v){
        prev = nullptr;
        next = nullptr;
    };
};

class FirstUnique {
public:
    map<int, int> counter;
    DLinkedNode *head, *tail;
    vector<int> uniqs;
    
    FirstUnique(vector<int>& nums) {
        head = new DLinkedNode(-1);
        tail = new DLinkedNode(-1);
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
        for(int num : nums){
            counter[num] += 1;
            if(counter[num] == 1){
                DLinkedNode* node = new DLinkedNode(num);
                node->prev = tail->prev;
                node->next = tail;
                
                tail->prev->next = node;
                tail->prev = node;
            }else{
                DLinkedNode *cur = head;
                while(cur != nullptr){
                    if(cur->value == num){
                        //remove this node
                        cur->prev->next = cur->next;
                        cur->next->prev = cur->prev;
                        delete cur;
                        cur = nullptr;
                        break;
                    }
                    cur = cur->next;
                }
            }
        }
    }
    
    int showFirstUnique() {
        return head->next != tail ? head->next->value : -1;
    }
    
    void add(int value) {
        if(counter.find(value) == counter.end()){
            counter[value] = 1;
                
            DLinkedNode* node = new DLinkedNode(value);
            node->prev = tail->prev;
            node->next = tail;

            tail->prev->next = node;
            tail->prev = node;
        }else{
            if(counter[value] == 1){
                DLinkedNode *cur = head;
                while(cur != nullptr){
                    if(cur->value == value){
                        //remove this node
                        cur->prev->next = cur->next;
                        cur->next->prev = cur->prev;
                        delete cur;
                        cur = nullptr;
                        break;
                    }
                    cur = cur->next;
                }
            }
            counter[value]++;
        }
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
 
