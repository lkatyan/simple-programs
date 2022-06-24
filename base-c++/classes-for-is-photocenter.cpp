// Проектирование классов для ИС фотоцентра

#include <iostream>
#include <vector>

class Products
{
public:
    std::string name;
    int cost;
};

class Services
{
public:
    std::string name;
    int cost;
};

class Orders
{
public:
    std::vector<Products> products;
    std::vector<Services> services;
    int allCost;
    std::string datas;
    int getAllCost() {
        allCost = products[0].cost + services[0].cost;
        return allCost;
    }
    void setProduct(Products product) {
        products.push_back(product);
    }

    void setService(Services service) {
        services.push_back(service);
    }
};

class Clients
{
public:
    std::string firstName;
    std::string secondName;
    std::vector<Orders> orders;
    void showOrders() {
        std::cout << "Информация о заказе: " << std::endl;
        std::cout << "Дата: " << orders[0].datas << std::endl;
        std::cout << "Стоимость: " << orders[0].allCost << std::endl;
        std::cout << "Товар: " << orders[0].products[0].name << "\t";
        std::cout << orders[0].products[0].cost << std::endl;
        std::cout << "Услуга: " << orders[0].services[0].name << "\t";
        std::cout << orders[0].services[0].cost << std::endl;
    }
    int getCostOrder(std::string datas) {
        return orders[0].getAllCost();
    }
};

int main()
{
    setlocale(0, "");
    Clients clients;
    clients.firstName = "Ivanov";
    clients.secondName = "Ivan";
    std::cout << "Клиент: " << clients.firstName << "\t" << clients.secondName << std::endl;
    Orders order; 
    order.datas = "01.01.2021";
    Products product;
    product.name = "Кружка";
    product.cost = 100;
    order.setProduct(product);
    Services service;
    service.name = "Ксерокопия";
    service.cost = 5;
    order.setService(service);
    order.getAllCost();
    clients.orders.push_back(order);
    clients.showOrders();
    std::cout<<std::endl<<clients.getCostOrder("01.01.2021")<<"\t"<<std::endl;
    
}
