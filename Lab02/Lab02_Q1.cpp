class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        int count[101] = {0};
        int n = nums.size();
        int operationcount = 0;
        vector<int> result(n);

        for (int num:nums) {
            count[num]++;
            operationcount ++;
        }
        
        for (int i = 1; i < 101; i++){
            operationcount ++;
            count[i] += count[i-1];
            operationcount ++;
        }
        for (int i = 0; i < n; i++){
            operationcount ++;
            result[i] = (nums[i] == 0) ?0 : count[nums[i]-1];
            operationcount ++;
        }
        cout << operationcount;
        return result;
    }
};
