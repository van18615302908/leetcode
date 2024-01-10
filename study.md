# 动态规划2024/01/09

> 对于一个数组[1,2,3,4,7,56,4,8]求最长的递增序列长度

暴力求解：

对每一个子序列进行计算

```cpp
#include<iostream>
#include<vector>

using namespace std;

int longest_incr_subseq_util(const vector<int>& sequence, int prev_index, int current_index, int current_length) {
    if (current_index == sequence.size()) {
        return current_length;
    }

    int include_current = 0;
    if (sequence[current_index] > sequence[prev_index]) {//下一个数字是递增的
        include_current = longest_incr_subseq_util(sequence, current_index, current_index + 1, current_length + 1);
    }
    //下一个数字不是递增的
    int exclude_current = longest_incr_subseq_util(sequence, prev_index, current_index + 1, current_length);

    return max(include_current, exclude_current);
}

int longest_incr_subseq(const vector<int>& sequence) {
    if (sequence.empty()) {
        return 0;
    }

    int result = 0;
    for (int i = 0; i < sequence.size()-1; ++i) {
        result = max(result, longest_incr_subseq_util(sequence, i, i+1, 0));
    }

    return result;
}
```

暴力求解法在遍历的时候存在多次的重复计算

因此我们使用一个哈希表来储存我们每一个节点计算的结果，计算从i开始的每一个节点的最长子序列长度
```cpp
#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int longest_incr_subseq_util(unordered_map<int,int> &calculated,const vector<int>& sequence, int prev_index, int current_index, int current_length) {
    if (current_index == sequence.size()) {
        return current_length;
    }

    if(calculated.at(current_index) != -1){
        return calculated.at(current_index);
    }
    int include_current = 0;
    if (sequence[current_index] > sequence[prev_index]) {//下一个数字是递增的
       
        include_current = longest_incr_subseq_util(calculated,sequence, current_index, current_index + 1, current_length + 1);
      
        
    }
    //下一个数字不是递增的
    int exclude_current = longest_incr_subseq_util(calculated,sequence, prev_index, current_index + 1, current_length);
    calculated[current_index] = max(include_current, exclude_current);
    return max(include_current, exclude_current);
}

int longest_incr_subseq(const vector<int>& sequence) {
    unordered_map<int,int> calculated;
    for(int i = 0;i < sequence.size();i++){
        calculated[i] = -1;
    }
    if (sequence.empty()) {
        return 0;
    }

    int result = 0;
    for (int i = 0; i < sequence.size(); ++i) {
        result = max(result, longest_incr_subseq_util(calculated,sequence, i, i+1, 0));
    }

    return result;
}
```

上面使用了一个`unordered_map`来储存每一个`index`的所在位置的最大递增数量，如果已经计算过就不再计算

动态规划就是带备忘录的递归
