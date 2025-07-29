#include <cinttypes>
#include <vector>
#include <algorithm>
#include <string>

uint64_t descendingOrder(uint64_t a) {
    std::string s = std::to_string(a);
    std::sort(s.begin(), s.end(), std::greater<char>());
    return std::stoull(s);
}
/*
<Right>#include <cinttypes>

uint64_t descendingOrder(uint64_t a)
{
  std::vector<int> res_a;
  uint64_t res[a];
  for(uimt64_t i = 0; i < a; ++i) {
    if (i[a] <= 9 ) { res_a.push_back(i) ;}
    else if ( a[i] <= 8 ) { res_a.push_back(i) ;}
    else if ( a[i] <= 7 ) { res_a.push_back(i) ;}
    else if ( a[i] <= 6 ) { res_a.push_back(i) ;}
    else if ( a[i] <= 5 ) { res_a.push_back(i) ;}
    else if ( a[i] <= 4 ) { res_a.push_back(i) ;}
    else if ( a[i] <= 3 ) { res_a.push_back(i) ;}
    else if ( a[i] <= 2 ) { res_a.push_back(i) ;}
    else if ( a[i] <= 1 ) { res_a.push_back(i) ;}
    else if ( a[i] == 0 ) { res_a.push_back(i) ;}
  }
  res_a = res;
  return res_a;
}
*/
