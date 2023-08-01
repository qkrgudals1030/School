#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Person 클래스
class Person {
public:
    Person(const string& name, const string& address) : name_(name), address_(address) {}

    string getName() const { return name_; }
    string getAddress() const { return address_; }

    void setName(const string& name) { name_ = name; }
    void setAddress(const string& address) { address_ = address; }

private:
    string name_;
    string address_;
};

// 상품 클래스
class Product {
public:
    Product(const string& name, double price) : name_(name), price_(price) {}

    string getName() const { return name_; }
    double getPrice() const { return price_; }

    void setName(const string& name) { name_ = name; }
    void setPrice(double price) { price_ = price; }

private:
    string name_;
    double price_;
};

// 고객 클래스
class Customer : public Person {
public:
    Customer(const string& name, const string& address) : Person(name, address) {}
};

// 주문 클래스
class Order {
public:
    Order(const Customer& customer, const Product& product, int quantity)
        : quantity_(quantity) {
            customers_.push_back(customer);
            for (int i = 0; i < quantity; ++i) {
                products_.push_back(product);
            }
        }

    const vector<Customer>& getCustomers() const { return customers_; }
    const vector<Product>& getProducts() const { return products_; }
    int getQuantity() const { return quantity_; }

    void addProduct(const Product& product, int quantity) {
        for (int i = 0; i < quantity; ++i) {
            products_.push_back(product);
        }
    }

    void removeProduct(const string& productName) {
        for (int i = 0; i < products_.size(); ++i) {
            if (products_[i].getName() == productName) {
                products_.erase(products_.begin() + i);
                break;
            }
        }
    }

    void addCustomer(const Customer& customer) {
        customers_.push_back(customer);
    }

    void removeCustomer(const string& customerName) {
        for (int i = 0; i < customers_.size(); ++i) {
            if (customers_[i].getName() == customerName) {
                customers_.erase(customers_.begin() + i);
                break;
            }
        }
    }

    void updateCustomer(const string& oldName, const Customer& newCustomer) {
        for (int i = 0; i < customers_.size(); ++i) {
            if (customers_[i].getName() == oldName) {
                customers_[i] = newCustomer;
                break;
            }
        }
    }

    void setCustomer(const Customer& customer) {
        customers_.clear();
        customers_.push_back(customer);
    }

private:
    vector<Customer> customers_;
    vector<Product> products_;
    int quantity_;
};

void printCustomerList(const vector<Customer>& customers) {
    cout << "고객 목록:\n";
    for (const Customer& customer : customers) {
        cout << "고객명: " << customer.getName() << endl;
        cout << "고객 주소: " << customer.getAddress() << endl;
        cout << "=====================\n";
    }
}
int main() {
    // 상품, 고객, 주문 객체 생성 및 관리 예제
    string productName;
    double productPrice;
    string customerName;
    string customerAddress;
    int orderQuantity;
    string action;
    string menu;

    cout << "고객명을 입력하세요: ";
    getline(cin, customerName);
    cout << "주소를 입력하세요: ";
    getline(cin, customerAddress);

    cout << "상품명을 입력하세요: ";
    getline(cin, productName);
    cout << "가격을 입력하세요: ";
    cin >> productPrice;
    cin.ignore(32767, '\n'); // cin 버퍼 비우기

    cout << "주문 수량을 입력하세요: ";
    cin >> orderQuantity;
    cin.ignore(32767, '\n');

    Product product(productName, productPrice);
    Customer customer(customerName, customerAddress);
    Order order(customer, product, orderQuantity);

    cout << "=====================\n";
    cout << "현재 주문 내역: " << endl;
    cout << "상품명: " << product.getName() << endl;
    cout << "가격: " << product.getPrice() << endl;
    cout << "주문 수량: " << order.getQuantity() << endl;
    cout << "고객명: " << customer.getName() << endl;
    cout << "고객 주소: " << customer.getAddress() << endl;
    cout << "=====================\n";

    // 고객 추가 및 삭제 예제
    while (true) {
        cout << "================\n";
        cout << "1. 상품 추가\n";
        cout << "2. 상품 제거\n";
        cout << "3. 고객 정보 변경\n";
        cout << "4. 출력\n";
        cout << "5. 고객 추가\n";
        cout << "6. 고객 삭제\n";
        cout << "7. 고객 목록 출력\n";
        cout << "8. 종료\n";
        cout << "================\n";
        cout << "메뉴를 선택하세요: ";
        getline(cin, menu);

        if (menu == "1") {
            cout << "더 추가하시겠습니까? (y/n) ";
            cin >> action;
            cin.ignore(32767, '\n');
            if (action != "y" && action != "n") {
                cout << "y 또는 n을 입력해 주세요.\n";
                continue;
            }
            while (action == "y") {
                cout << "추가할 상품명을 입력하세요: ";
                getline(cin, productName);
                cout << "가격을 입력하세요: ";
                cin >> productPrice;
                cin.ignore(32767, '\n');
                cout << "추가 수량을 입력하세요: ";
                cin >> orderQuantity;
                cin.ignore(32767, '\n');

                Product newProduct(productName, productPrice);
                order.addProduct(newProduct, orderQuantity);

                cout << "더 추가하시겠습니까? (y/n) ";
                cin >> action;
                cin.ignore(32767, '\n');
                if (action != "y" && action != "n") {
                	  cout << "y 또는 n을 입력해 주세요.\n";
                    continue;
                }
            }
            
        } else if (menu == "2") {
            cout << "제거할 상품명을 입력하세요: ";
            getline(cin, productName);
            order.removeProduct(productName);

        } else if (menu == "3") {
            cout << "변경할 고객명을 입력하세요: ";
            getline(cin, customerName);
            cout << "새로운 고객명을 입력하세요: ";
            getline(cin, productName);
            cout << "새로운 주소를 입력하세요: ";
            getline(cin, customerAddress);

            Customer newCustomer(productName, customerAddress);
            order.updateCustomer(customerName, newCustomer);

        } else if (menu == "4") {
            cout << "현재 주문 내역: " << endl;
            cout << "상품명: " << product.getName() << endl;
            cout << "가격: " << product.getPrice() << endl;
            cout << "주문 수량: " << order.getQuantity() << endl;
            cout << "고객명: " << customer.getName() << endl;
            cout << "고객 주소: " << customer.getAddress() << endl;

        } else if (menu == "5") {
            cout << "추가할 고객명을 입력하세요: ";
            getline(cin, customerName);
            cout << "추가할 주소를 입력하세요: ";
            getline(cin, customerAddress);

            Customer newCustomer(customerName, customerAddress);
            order.addCustomer(newCustomer);

        } else if (menu == "6") {
            cout << "삭제할 고객명을 입력하세요: ";
            getline(cin, customerName);
            order.removeCustomer(customerName);

        } else if (menu == "7") {
            printCustomerList(order.getCustomers());

        } else if (menu == "8") {
            break;

        } else {
            cout << "잘못된 메뉴 선택입니다. 다시 선택해주세요.\n";
        }
    }

    return 0;
}
