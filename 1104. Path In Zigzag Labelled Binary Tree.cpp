//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Path In Zigzag Labelled Binary Tree.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Path In Zigzag Labelled Binary Tree.

class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        int level = int(log2(label)); //index starts from 0
        vector<int> path;
        int node;
        int index; //the index in a level, starts from 0, from left to right
        path.push_back(label);
        
        node = label;
        while(node != 1){
            if(level % 2 == 0){
                //label from left to right
                index = node - pow(2, level);
                //get the index of its parent
                index /= 2;
                //pow(2, level) - 1: the 0th element of last level
                // - index: because in the last level, label is from right to left
                node = (pow(2, level) - 1) - index;
            }else{
                //label from right to left
                //(pow(2, level)-1) - xxx: to change the direction of the index in a level
                index = (pow(2, level)-1) - (node - pow(2, level));
                //get the index of its parent
                index /= 2;
                node = pow(2, level-1) + index;
            }
            path.insert(path.begin(), node);
            level--;
            // cout << node << " ";
        };
        
        return path;
    }
};
