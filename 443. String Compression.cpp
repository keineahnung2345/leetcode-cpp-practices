//Runtime: 8 ms, faster than 86.14% of C++ online submissions for String Compression.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for String Compression.

class Solution {
public:
    int compress(vector<char>& chars) {
        int pos = 0, count = 1;
        char last = chars[pos];
        pos++;
        
        while(pos < chars.size()){
            if(chars[pos] == last){
                count++;
            }
            // cout << "pos: " << pos << ", count: " << count << endl;
            
            //meet different char, or go to the end
            if(chars[pos] != last || pos == chars.size()-1){
                if(count > 1){
                    //remove redundant char
                    //the last char is not inclusive
                    chars.erase(chars.begin()+pos-count+1, chars.begin()+pos);
                    // cout << "last? " << (pos-count+1 == chars.size()-1) << endl;
                    // cout << "[" << pos-count+1 << ", " << pos << "] " << string(chars.begin(), chars.end());
               
                    //always insert at same position
                    //12: insert 2 and then insert 1 before 2
                    int insert_pos = pos-count+1;
                    /*
                    if we are at the end and we are dealing with this char(not previous), 
                    then we need to insert at last
                    */
                    if((pos-count+1 == chars.size()-1) && chars[pos] == last)
                        insert_pos++;
                    // cout << ", insert_pos: " << insert_pos;
                    
                    for(int count_tmp = count; count_tmp > 0; count_tmp /= 10){
                        /*
                        if not last, we are at the char different from last
                        if is last, we are at the char same as last
                        so need to add 1 for last
                        */
                        /*
                        after insert a number, move to next, so add i
                        */
                        chars.insert(chars.begin()+insert_pos, '0'+count_tmp%10);
                        //skip the inserted char
                        pos++;
                    }
                    // cout << ", " << string(chars.begin(), chars.end()) << endl;
                    //skip count-1 char
                    pos -= (count-1);
                    // pos -= (count-1);
                }
                count = 1;
                last = chars[pos];
            }
            pos++;
        }
        return chars.size();
    }
};
