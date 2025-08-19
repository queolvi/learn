#include <iostream>
#include <vector>
class Solution {
public:
    long long zeroFilledSubarray(std::vector<int>& nums) {
        long long res = 0;
        long long dop_res = 0;    
    for(int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {dop_res++; res+= dop_res;}
        }
        return res;
    }
};

int main () {

std::vector<int> vec = {1,3,0,0,2,0,0,4};
Solution sol;
  std::cout << sol.zeroFilledSubarray(vec);


            return 0;
            }
