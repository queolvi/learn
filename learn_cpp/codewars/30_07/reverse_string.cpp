#include <string>
#include <algorithm> // For std::reverse

std::string reverse_words(std::string str) {
    size_t start = 0;
    size_t end = 0;
    
    while (start < str.length()) {
        
        start = str.find_first_not_of(' ', end);
        if (start == std::string::npos) break;
        
       
        end = str.find(' ', start);
        if (end == std::string::npos) end = str.length();
        
       
        std::reverse(str.begin() + start, str.begin() + end);
    }
    
    return str;
}
