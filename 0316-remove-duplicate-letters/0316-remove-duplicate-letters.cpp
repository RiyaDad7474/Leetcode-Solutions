class Solution {
public:
    string removeDuplicateLetters(string s) {

        vector<int> lastIndex(26);
        string result = "";

        for (int i = 0; i < s.size(); i++) {
            lastIndex[s[i] - 'a'] = i;
        }


        vector<bool> taken(26, false);

        for (int i = 0;i<s.size();i++) {
            char ch = s[i];
            int idx = ch - 'a';

            if(taken[idx] == true)
            continue;

            while(result.length() > 0 && result.back() > ch && lastIndex[result.back() - 'a'] > i){
                taken[result.back() - 'a'] = false;
                result.pop_back();
            }
            result.push_back(ch);
            taken[idx] = true;
        }
        return result;
    }
};