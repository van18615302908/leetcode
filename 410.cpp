// 410. 分割数组的最大值
// 已解答
// 困难

// 相关标签
// 相关企业
// 给定一个非负整数数组 nums 和一个整数 k ，你需要将这个数组分成 k 个非空的连续子数组。
//Given a nonnegative integer array nums and an integer k, you need to divide the array into k nonempty contiguous subarrays.
// Design an algorithm to minimize the maximum value of the respective sum of these k subarrays.
// 设计一个算法使得这 k 个子数组各自和的最大值最小。

 

// 示例 1：

// 输入：nums = [7,2,5,10,8], k = 2
// 输出：18
// 解释：
// 一共有四种方法将 nums 分割为 2 个子数组。 
// 其中最好的方式是将其分为 [7,2,5] 和 [10,8] 。
// 因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。
// 示例 2：

// 输入：nums = [1,2,3,4,5], k = 2
// 输出：9
// 示例 3：

// 输入：nums = [1,4,4], k = 3
// 输出：4

// 动态规划
// f（n,m） response that the mimum sum of an array of n nums which is divided into m parts
// f（n,m） = mimum(n，k = 1) max{f(n-k,m-1),f(k,1)}
// f(0,0) = 0
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<vector<long long>> f(n + 1, vector<long long>(m + 1, LLONG_MAX));
        vector<long long> sub(n + 1, 0);
        for (int i = 0; i < n; i++) {
            sub[i + 1] = sub[i] + nums[i];
        }
        f[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, m); j++) {
                for (int k = 0; k < i; k++) {
                    f[i][j] = min(f[i][j], max(f[k][j - 1], sub[i] - sub[k]));
                }
            }
        }
        return (int)f[n][m];
    }
};



int main(){
    vector<int> miao = {7,2,5,10,8};
    Solution A;
    A.splitArray(miao,2);
    return 0;
}