//Runtime: 4 ms, faster than 54.05% of C++ online submissions for Defanging an IP Address.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Defanging an IP Address.

class Solution {
public:
    string defangIPaddr(string address) {
        int start = 0;
        size_t pos;
        while((pos = address.find(".", start)) != -1){
	        address.replace(pos, 1, "[.]");
            start = pos + 3;
        }
        return address;
    }
};
