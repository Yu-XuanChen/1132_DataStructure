class Solution {
public:
    int findLucky(vector<int>& arr) {
        int luckynum = -1;
        int count[501] = {0};
        
        for (int num : arr) {
            count[num]++;
        }

        for (int i = 1; i <= 500; i++){
            if (count[i] == i ){
                luckynum = i;
            }
        }
        return luckynum;
    }
};
