//Runtime: 4 ms, faster than 23.97% of C++ online submissions for Compare Version Numbers.
//Memory Usage: 6.4 MB, less than 20.14% of C++ online submissions for Compare Version Numbers.
class Solution {
public:
    std::vector<std::string> string_split(std::string str, std::string delimiter){
        size_t pos = 0;
        std::string token;
        std::vector<std::string> result;
        
        while(true){
            pos = str.find(delimiter);
            //works even if pos is string::npos
            token = str.substr(0, pos);
            result.push_back(token);
            if(pos == string::npos) break;
            //pos+1 equals to 0, so the line below can't handle this situation
            str.erase(0, pos+delimiter.length());
        }
        return result;
    };

    int compareVersion(string version1, string version2) {
        vector<string> vsv1 = string_split(version1, ".");
        vector<string> vsv2 = string_split(version2, ".");

        // for(string& s : vsv1){
        //     cout << s << " ";
        // }
        // cout << endl;
        
        // for(string& s : vsv2){
        //     cout << s << " ";
        // }
        // cout << endl;

        vector<int> viv1, viv2;
        transform(vsv1.begin(), vsv1.end(), back_inserter(viv1), [](string& s){return stoi(s);});
        transform(vsv2.begin(), vsv2.end(), back_inserter(viv2), [](string& s){return stoi(s);});

        int swapped = 1;
        //viv1 is always longer
        if(viv1.size() < viv2.size()) {
            swapped = -1;
            swap(viv1, viv2);
        }
        
        int i;

        for(i = 0; i < viv2.size() && viv1[i] == viv2[i]; ++i){}

        if(i == viv2.size()){
            //viv1[0... viv2.size()) == viv2[0... viv2.size())
            //assume viv2[ viv2.size()...viv1.size()) is all 0
            for(i =  viv2.size(); i < viv1.size() && viv1[i] == 0; ++i){}
            return (i == viv1.size()) ? 0 : (viv1[i] > 0) ? 1*swapped : -1*swapped;
        }else{
            return (viv1[i] > viv2[i]) ? 1*swapped : -1*swapped;
        }
        
    }
};
