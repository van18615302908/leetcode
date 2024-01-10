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