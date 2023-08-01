#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Person Ŭ����
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

// ��ǰ Ŭ����
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

// �� Ŭ����
class Customer : public Person {
public:
    Customer(const string& name, const string& address) : Person(name, address) {}
};

// �ֹ� Ŭ����
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
    cout << "�� ���:\n";
    for (const Customer& customer : customers) {
        cout << "����: " << customer.getName() << endl;
        cout << "�� �ּ�: " << customer.getAddress() << endl;
        cout << "=====================\n";
    }
}
int main() {
    // ��ǰ, ��, �ֹ� ��ü ���� �� ���� ����
    string productName;
    double productPrice;
    string customerName;
    string customerAddress;
    int orderQuantity;
    string action;
    string menu;

    cout << "������ �Է��ϼ���: ";
    getline(cin, customerName);
    cout << "�ּҸ� �Է��ϼ���: ";
    getline(cin, customerAddress);

    cout << "��ǰ���� �Է��ϼ���: ";
    getline(cin, productName);
    cout << "������ �Է��ϼ���: ";
    cin >> productPrice;
    cin.ignore(32767, '\n'); // cin ���� ����

    cout << "�ֹ� ������ �Է��ϼ���: ";
    cin >> orderQuantity;
    cin.ignore(32767, '\n');

    Product product(productName, productPrice);
    Customer customer(customerName, customerAddress);
    Order order(customer, product, orderQuantity);

    cout << "=====================\n";
    cout << "���� �ֹ� ����: " << endl;
    cout << "��ǰ��: " << product.getName() << endl;
    cout << "����: " << product.getPrice() << endl;
    cout << "�ֹ� ����: " << order.getQuantity() << endl;
    cout << "����: " << customer.getName() << endl;
    cout << "�� �ּ�: " << customer.getAddress() << endl;
    cout << "=====================\n";

    // �� �߰� �� ���� ����
    while (true) {
        cout << "================\n";
        cout << "1. ��ǰ �߰�\n";
        cout << "2. ��ǰ ����\n";
        cout << "3. �� ���� ����\n";
        cout << "4. ���\n";
        cout << "5. �� �߰�\n";
        cout << "6. �� ����\n";
        cout << "7. �� ��� ���\n";
        cout << "8. ����\n";
        cout << "================\n";
        cout << "�޴��� �����ϼ���: ";
        getline(cin, menu);

        if (menu == "1") {
            cout << "�� �߰��Ͻðڽ��ϱ�? (y/n) ";
            cin >> action;
            cin.ignore(32767, '\n');
            if (action != "y" && action != "n") {
                cout << "y �Ǵ� n�� �Է��� �ּ���.\n";
                continue;
            }
            while (action == "y") {
                cout << "�߰��� ��ǰ���� �Է��ϼ���: ";
                getline(cin, productName);
                cout << "������ �Է��ϼ���: ";
                cin >> productPrice;
                cin.ignore(32767, '\n');
                cout << "�߰� ������ �Է��ϼ���: ";
                cin >> orderQuantity;
                cin.ignore(32767, '\n');

                Product newProduct(productName, productPrice);
                order.addProduct(newProduct, orderQuantity);

                cout << "�� �߰��Ͻðڽ��ϱ�? (y/n) ";
                cin >> action;
                cin.ignore(32767, '\n');
                if (action != "y" && action != "n") {
                	  cout << "y �Ǵ� n�� �Է��� �ּ���.\n";
                    continue;
                }
            }
            
        } else if (menu == "2") {
            cout << "������ ��ǰ���� �Է��ϼ���: ";
            getline(cin, productName);
            order.removeProduct(productName);

        } else if (menu == "3") {
            cout << "������ ������ �Է��ϼ���: ";
            getline(cin, customerName);
            cout << "���ο� ������ �Է��ϼ���: ";
            getline(cin, productName);
            cout << "���ο� �ּҸ� �Է��ϼ���: ";
            getline(cin, customerAddress);

            Customer newCustomer(productName, customerAddress);
            order.updateCustomer(customerName, newCustomer);

        } else if (menu == "4") {
            cout << "���� �ֹ� ����: " << endl;
            cout << "��ǰ��: " << product.getName() << endl;
            cout << "����: " << product.getPrice() << endl;
            cout << "�ֹ� ����: " << order.getQuantity() << endl;
            cout << "����: " << customer.getName() << endl;
            cout << "�� �ּ�: " << customer.getAddress() << endl;

        } else if (menu == "5") {
            cout << "�߰��� ������ �Է��ϼ���: ";
            getline(cin, customerName);
            cout << "�߰��� �ּҸ� �Է��ϼ���: ";
            getline(cin, customerAddress);

            Customer newCustomer(customerName, customerAddress);
            order.addCustomer(newCustomer);

        } else if (menu == "6") {
            cout << "������ ������ �Է��ϼ���: ";
            getline(cin, customerName);
            order.removeCustomer(customerName);

        } else if (menu == "7") {
            printCustomerList(order.getCustomers());

        } else if (menu == "8") {
            break;

        } else {
            cout << "�߸��� �޴� �����Դϴ�. �ٽ� �������ּ���.\n";
        }
    }

    return 0;
}
