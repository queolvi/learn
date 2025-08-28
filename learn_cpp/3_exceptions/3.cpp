#include <iostream>
#include <vector>
#include <stdexcept>
#include <climits>
class DataProcessor {
private:
  std::vector<int> data;
public:
    void addData(int value) {
        // Добавьте проверки:
        // - value не отрицательный
        if (value <= 0) {throw std::invalid_argument("Value must be greater than 0!");}
        // - data не превышает максимальный размер
        if (value > INT_MAX) {throw std::length_error("Value cannot be greater tham max int value size!");}
        // - value не равен специальному "ошибочному" числу (например, 999)
        if (value == 1023) {throw std::out_of_range("Value must be another. Try again.");}
      return;
    }
    
    int getDataAt(size_t index) {
        // Реализуйте с проверкой границ
    addData(index);
    int new_data = index;  
    return data.push_back(new_data);
    }
};

int main() {
    DataProcessor processor;
    
    try {
        processor.addData(10);
        processor.addData(-5);  // Должно бросить invalid_argument
        processor.addData(1023); // Должно бросить runtime_error
        
        for(int i = 0; i < 1000; i++) {
            processor.addData(i); // Должно бросить length_error
        }
        
        std::cout << processor.getDataAt(1000) << std::endl; // Должно бросить out_of_range
        
    } catch (const std::invalid_argument& e) {
      std::cout << "Неверный аргумент: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Выход за границы: " << e.what() << std::endl;
    } catch (const std::length_error& e) {
      std::cout << "Ошибка длины: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
      std::cout << "Ошибка выполнения: " << e.what() << std::endl;
    } catch (...) {
      std::cout << "Неизвестная ошибка" << std::endl;
    }
    
    return 0;
}
