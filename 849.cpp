#include<vector>
#include<iostream>
#include<stack>

using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int _max = 0;
        for(int i = 0;i < static_cast<int>(seats.size());i++){
            
            if(seats[i] != 1){
                int count = 0;
                for(int index = i-1;index>=0 && index < static_cast<int>(seats.size());index --){
                    count ++;
                    if(1 == seats[index]){
                        seats[i] = -count;
                        break;
                    }
                }

                int _count = 0;
                for(int index = i+1;index>=0 && index < static_cast<int>(seats.size());index ++){
                    _count ++;
                    if(1 == seats[index]){
                        if(_count < count || seats[i] >= 0){
                            seats[i] = -_count;
                            break;
                        }
                    }
                }

                if(_max < - seats[i]){
                    _max = - seats[i];
                }
            }

        }


        return _max;
    }
};

int main(){
    Solution wang;
    vector<int> miao = {0,1};
    cout<< wang.maxDistToClosest(miao);
    return 0;
}