#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

int main() {
    std::unordered_map<int, std::string> hash_category;
    std::map<std::string, int> category_counts;
    std::vector<std::string> categories_list;
    int key = 1;

    std::cout << "Enter names of categories (type 'done' to finish):\n";
    
    // Ввод категорий
    while (true) {
        std::cout << "Category " << key << ": ";
        std::string input;
        std::getline(std::cin, input);
        
        if (input == "done") {
            break;
        }
        
        if (!input.empty()) {
            hash_category.insert({key, input});
            categories_list.push_back(input);
            key++;
            
            if (key > 50) {
                std::cout << "Maximum categories reached (50).\n";
                break;
            }
        }
    }

    // Подсчет количества каждой категории
    for (const auto& category : categories_list) {
        category_counts[category]++;
    }

    // Вывод всех категорий с ключами
    std::cout << "\nAll categories with keys:\n";
    for (const auto& pair : hash_category) {
        std::cout << "Key: " << pair.first << " | Category: " << pair.second << "\n";
    }

    // Вывод статистики по категориям
    std::cout << "\nCategory statistics:\n";
    for (const auto& count_pair : category_counts) {
        std::cout << "Category: " << count_pair.first 
                  << " | Count: " << count_pair.second << "\n";
    }

    // Выборка по конкретной категории
    std::cout << "\nEnter category to search: ";
    std::string search_category;
    std::getline(std::cin, search_category);

    std::cout << "\nSearch results for '" << search_category << "':\n";
    int found = 0;
    for (const auto& pair : hash_category) {
        if (pair.second == search_category) {
            std::cout << "Found at key: " << pair.first << "\n";
            found++;
        }
    }
    
    if (found == 0) {
        std::cout << "No entries found for this category.\n";
    } else {
        std::cout << "Total found: " << found << "\n";
    }

    return 0;}
