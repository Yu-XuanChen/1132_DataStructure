class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size(); //將nums陣列的大小存到n
        vector<int> result(n); //大小為n的陣列，用來存放結果

        result[0] = nums[0]; 
        for (int i = 1; i < n; i++){ //從i = 1開始遍歷nums陣列
            result[i] = result[i-1]+nums[i]; //result[i]存為result[i]前一個數的累積和加上當前的數
        }
        return result; 
    }
};
