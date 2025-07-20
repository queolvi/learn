#include <string>
#include <set>
#include <algorithm>
class TwoToOne
{
public:
    static std::string longest(const std::string &s1, const std::string &s2) 
    {
      std::set<char> uc; // unique_chars
      for(char c : s1) { uc.insert(c); }
      for(char c : s2) { uc.insert(c); }
      std::string res;
      for(char c : uc) { res+=c; }
      
      return res;
    }
};

/*
#include <string>
void testequal(std::string ans, std::string sol) {
    Assert::That(ans, Equals(sol));
}
void dotest(std::string a1, std::string a2, std::string expected)
{
    testequal(TwoToOne::longest(a1, a2), expected);
}
Describe(longest_Tests)
{
    It(Fixed__Tests)
    {
        dotest("aretheyhere", "yestheyarehere", "aehrsty");
        dotest("loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");
    }
};

*/

/* // alt
#include <string>
#include <algorithm>

class TwoToOne {
public:
    static std::string longest(const std::string &s1, const std::string &s2) {
        std::string combined = s1 + s2;
        std::string result;

        // Проходим по всем буквам от 'a' до 'z'
        for (char c = 'a'; c <= 'z'; ++c) {
            // Если буква есть хотя бы в одной из строк, добавляем её
            if (combined.find(c) != std::string::npos) {
                result += c;
            }
        }

        return result;
    }
};
*/
