#include <iostream>
#include <memory>

class NodeSafe {
public:
    std::string name;
    std::weak_ptr<NodeSafe> partner; // Слабая ссылка - разрывает цикл!
    
    NodeSafe(const std::string& n) : name(n) {
        std::cout << "Node " << name << " created\n";
    }
    
    ~NodeSafe() {
        std::cout << "Node " << name << " destroyed\n";
    }
    
    void setPartner(std::shared_ptr<NodeSafe> p) {
        partner = p; // weak_ptr не увеличивает счетчик ссылок
    }
    
    void printPartner() {
        if (auto shared_partner = partner.lock()) {
            std::cout << name << "'s partner: " << shared_partner->name << std::endl;
        } else {
            std::cout << name << "'s partner no longer exists\n";
        }
    }
};

// Класс для демонстрации циклической ссылки (утечки памяти)
class NodeUnsafe {
public:
    std::string name;
    std::shared_ptr<NodeUnsafe> partner; // Опасная циклическая ссылка!
    
    NodeUnsafe(const std::string& n) : name(n) {
        std::cout << "Unsafe Node " << name << " created\n";
    }
    
    ~NodeUnsafe() {
        std::cout << "Unsafe Node " << name << " destroyed\n";
    }
    
    void setPartner(std::shared_ptr<NodeUnsafe> p) {
        partner = p; // shared_ptr увеличивает счетчик ссылок - циклическая ссылка!
    }
};

#ifdef CIRCULAR_REF
void createCircularReference() {
    std::cout << "\n=== Creating circular reference (memory leak) ===\n";
    
    auto node1 = std::make_shared<NodeUnsafe>("Alice");
    auto node2 = std::make_shared<NodeUnsafe>("Bob");
    
    // Создаем циклическую ссылку - ПЛОХО!
    node1->setPartner(node2);
    node2->setPartner(node1);
    
    std::cout << "Alice use_count: " << node1.use_count() << std::endl; // 2
    std::cout << "Bob use_count: " << node2.use_count() << std::endl;   // 2
    
    // При выходе из функции память НЕ освободится из-за циклической ссылки!
}
#endif

#ifdef BREAK_CIRCULAR
void breakCircularReference() {
    std::cout << "\n=== Breaking circular reference with weak_ptr ===\n";
    
    auto node1 = std::make_shared<NodeSafe>("Alice");
    auto node2 = std::make_shared<NodeSafe>("Bob");
    
    // Создаем ссылки, но теперь с weak_ptr - ХОРОШО!
    node1->setPartner(node2);
    node2->setPartner(node1);
    
    std::cout << "Alice use_count: " << node1.use_count() << std::endl; // 1
    std::cout << "Bob use_count: " << node2.use_count() << std::endl;   // 1
    
    // Проверяем работу weak_ptr
    node1->printPartner();
    node2->printPartner();
    
    // При выходе из функции память КОРРЕКТНО освободится!
}
#endif

int main() {
#ifdef CIRCULAR_REF
    createCircularReference(); // Вызовет утечку памяти
#endif

#ifdef BREAK_CIRCULAR  
    breakCircularReference();  // Корректно очистит память
#endif
    
    return 0;
}
