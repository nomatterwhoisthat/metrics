#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Класс Product
class Product {
public:
    std::string name;
    double price;

    // Конструктор
    Product(const std::string& name, double price)
        : name(name), price(price) {}

    // Геттер для цены
    double getPrice() const {
        return price;
    }

    // Метод для применения скидки к цене
    void applyDiscount(double discountPercentage) {
        price -= price * (discountPercentage / 100);
        std::cout << "Скидка применена! Новая цена для " << name << ": " << price << std::endl;
    }
};

// Базовый класс Customer
class Customer {
protected:
    std::string name;
    std::string customerId;

public:
    // Конструктор
    Customer(const std::string& name, const std::string& customerId)
        : name(name), customerId(customerId) {}

    // Метод для размещения заказа
    virtual void placeOrder(const Product& product) {
        std::cout << name << " разместил заказ на продукт с ценой: " << product.getPrice() << std::endl;
    }
};

// Класс Admin
class Admin : public Customer {
protected:
    std::vector<Product> products; // Список продуктов

public:
    // Конструктор
    Admin(const std::string& name, const std::string& customerId)
        : Customer(name, customerId) {}

    // Метод для добавления продукта
    virtual void addProduct(const Product& product) {
        products.push_back(product);
        std::cout << "Продукт добавлен администратором: " << product.name << ", Цена: " << product.getPrice() << std::endl;
    }

    // Переопределенный метод размещения заказа
    void placeOrder(const Product& product) override {
        std::cout << "Администратор " << name << " разместил заказ на продукт с ценой: " << product.getPrice() << std::endl;
    }
};

// Класс SuperAdmin
class SuperAdmin : public Admin {
public:
    // Конструктор
    SuperAdmin(const std::string& name, const std::string& customerId)
        : Admin(name, customerId) {}

    // Метод для применения скидки к продукту
    void applyDiscountToProduct(Product& product, double discountPercentage) {
        product.applyDiscount(discountPercentage);
    }

    // Переопределенный метод добавления продукта
    void addProduct(const Product& product) override {
        products.push_back(product);
        std::cout << "Продукт добавлен суперадминистратором: " << product.name << ", Цена: " << product.getPrice() << std::endl;
    }

    // Переопределенный метод размещения заказа
    void placeOrder(const Product& product) override {
        std::cout << "Суперадминистратор " << name << " разместил заказ на продукт с ценой: " << product.getPrice() << std::endl;
    }
};

int main() {
    // Создаем объекты Admin и SuperAdmin
    Admin admin("Алиса", "A123");
    SuperAdmin superAdmin("Боб", "S456");

    // Создаем продукты
    Product laptop("Ноутбук", 1000.0);
    Product smartphone("Смартфон", 500.0);

    // Admin добавляет продукты
    admin.addProduct(laptop);
    admin.addProduct(smartphone);

    // SuperAdmin добавляет продукты
    superAdmin.addProduct(laptop);

    // SuperAdmin применяет скидку
    superAdmin.applyDiscountToProduct(laptop, 10.0);

    return 0;
}
