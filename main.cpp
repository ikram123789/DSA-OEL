#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Product {
    int productID;
    string productName;
    string category;
    double price;
    int stock;
};

struct CartNode {
    int productID;
    string productName;
    float price;
    int quantity;

    CartNode* next;
};

struct Order {
    int orderID;
    float totalAmount;

    Order* next;
};

Order* front = NULL;
Order* rear = NULL;

int orderCount = 0;

CartNode* cartHead = NULL;
const int MAX = 100;

Product products[MAX];
int productCount = 0;

void addProduct() {

    if (productCount == MAX) {
        cout << "Product storage is full!";
        return;
    }

    // Take product ID
    cout<<"Enter Product ID: ";
    cin>>products[productCount].productID;

    // Check for duplicate ID
    for(int i=0; i<productCount; i++){
        if (products[i].productID == products[productCount].productID){
            cout<<"Duplicate Product ID!"<<endl;
            return;
        }
    }

    // Take remaining product information
    cout<<"Enter Product Name: ";
    cin.ignore();
    getline(cin,products[productCount].productName);
    cout<<"Enter Category: ";
    getline(cin,products[productCount].category);
    cout<<"Enter Price: ";
    cin>>products[productCount].price;
    cout<<"Enter Available Stock: ";
    cin>>products[productCount].stock;

    // Increase productCount
    productCount++;

    cout << "Product Added Successfully!" << endl;

}

void displayProducts() {

    // 1. Check if productCount == 0
    if(productCount == 0){
        cout<<"Catalog is empty. Add products first."<<endl;
        return;
    }

    // 2. Use a for loop to traverse products
    cout<<"Product ID"<<"   "<<"Product Name"<<"   "<<"Category"<<"   "<<"Price"<<"   "<<"Stock"<<"   "<<endl;
    for (int i=0; i<productCount; i++){
        cout<<products[i].productID<<"           "<<products[i].productName<<"            "<<products[i].category<<"        "<<products[i].price<<"     "<<products[i].stock<<endl;
    }
}

void searchProduct() {

    int id;
    // Ask user for product ID
    cout<<"Enter Product ID to search: ";
    cin>>id;

    // Traverse products using a for loop
    for (int i=0; i<productCount; i++){
        if(products[i].productID == id){
            cout<<"Product with Product ID "<<id<<" found!"<<endl;
            cout<<products[i].productID<<"   "<<products[i].productName<<"   "<<products[i].category<<"   "<<products[i].price<<"   "<<products[i].stock<<endl;
            return;
        }
    }

    cout<<"No Product found!"<<endl;
}

void updateProduct() {

    int id;

    // Ask user for product ID
    cout<<"Enter Product ID to update: ";
    cin>>id;

    // Search for that ID
    for (int i=0; i<productCount; i++){
        if(products[i].productID == id){
            cout<<"Product with Product ID "<<id<<" found!"<<endl;

            int newID;

            cout << "Enter Product ID: ";
            cin >> newID;

            // Check for duplicate ID
            for(int j = 0; j < productCount; j++) {

                if(products[j].productID == newID && j != i) {

                    cout << "Duplicate Product ID!" << endl;
                    return;
                }
            }

            products[i].productID = newID;

            // Take remaining product information
            cout<<"Enter Product Name: ";
            cin.ignore();
            getline(cin,products[i].productName);
            cout<<"Enter Category: ";
            getline(cin,products[i].category);
            cout<<"Enter Price: ";
            cin>>products[i].price;
            cout<<"Enter Available Stock: ";
            cin>>products[i].stock;

            cout << "Product Updated Successfully!" << endl;
            return;
        }
    }

            cout<<"No Product found with this ID !"<<endl;
}

void deleteProduct() {

    int id;
    // Ask user for Product ID
    cout << "Enter Product ID to delete: ";
    cin >> id;

    // Search for the Product ID
    for (int i = 0; i < productCount; i++) {

        if (products[i].productID == id) {

            cout << "Product found!" << endl;

            // Shift remaining products to the left
            for (int j = i; j < productCount-1; j++) {
                products[j] = products[j+1];
            }

            // Decrease productCount
            productCount --;
            cout << "Product Deleted Successfully!" << endl;

            return;
        }
    }

    // If product is not found
    cout << "No Product found with this ID!" << endl;
}

void sortProductsByPrice() {

    Product temp;

    // Bubble Sort
    for (int i = 0; i < productCount - 1; i++) {

        for (int j = 0; j < productCount - i - 1; j++) {

            // Compare adjacent product prices
            if (products[j].price > products[j + 1].price) {

                // Swap complete product structures
                temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;

            }
        }
    }

    cout << "\nProducts sorted by price successfully!" << endl;

    displayProducts();
}

void addToCart() {

    int id, quantity;
    bool found = false;

    cout << "Enter Product ID: ";
    cin >> id;

    // Search product in products array
    for (int i = 0; i < productCount; i++) {

        if (products[i].productID == id) {

            found = true;

            cout << "Product found!" << endl;

            cout << "Enter quantity: ";
            cin >> quantity;

            // Check available stock
            if (quantity <= 0) {
                cout << "Invalid quantity!" << endl;
                return;
            }

            if (quantity > products[i].stock) {
                cout << "Insufficient stock!" << endl;
                return;
            }

            // Create a new node
            CartNode* newNode = new CartNode;

            newNode->productID = products[i].productID;
            newNode->productName = products[i].productName;
            newNode->price = products[i].price;
            newNode->quantity = quantity;
            newNode->next = NULL;

            // Insert node into linked list
            if (cartHead == NULL) {

                cartHead = newNode;

            }
            else {

                CartNode* temp = cartHead;

                while (temp->next != NULL) {
                    temp = temp->next;
                }

                temp->next = newNode;
            }

            cout << "Product added to cart!" << endl;

            return;
        }
    }

    if (!found) {
        cout << "Product not found!" << endl;
    }
}

void displayCart() {

    if (cartHead == NULL) {
        cout << "Shopping Cart is Empty!" << endl;
        return;
    }

    CartNode* temp = cartHead;
    float total = 0;

    cout << "\n========== SHOPPING CART ==========" << endl;

    while (temp != NULL) {

        float subtotal = temp->price * temp->quantity;

        cout << "\nProduct ID: " << temp->productID;
        cout << "\nProduct Name: " << temp->productName;
        cout << "\nPrice: " << temp->price;
        cout << "\nQuantity: " << temp->quantity;
        cout << "\nSubtotal: " << subtotal << endl;

        total += subtotal;

        temp = temp->next;
    }

    cout << "\nGrand Total: " << total << endl;
}

void removeFromCart() {

    int id;

    if (cartHead == NULL) {
        cout << "Shopping Cart is Empty!" << endl;
        return;
    }

    cout << "Enter Product ID to remove: ";
    cin >> id;

    CartNode* temp = cartHead;
    CartNode* prev = NULL;

    while (temp != NULL) {

        if (temp->productID == id) {

            // If deleting the first node
            if (prev == NULL) {
                cartHead = temp->next;
            }
            else {
                prev->next = temp->next;
            }

            delete temp;

            cout << "Product Removed Successfully!" << endl;
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Product not found in Cart!" << endl;
}

void calculateTotal() {

    CartNode* temp = cartHead;
    float total = 0;

    while (temp != NULL) {

        total += temp->price * temp->quantity;

        temp = temp->next;
    }

    cout << "Total Shopping Cart Price: " << total << endl;
}

void placeOrder() {

    if (cartHead == NULL) {
        cout << "Cart is Empty! Add Products First." << endl;
        return;
    }

    float total = 0;

    CartNode* temp = cartHead;

    while (temp != NULL) {

        total += temp->price * temp->quantity;

        temp = temp->next;
    }

    Order* newOrder = new Order;

    newOrder->orderID = ++orderCount;
    newOrder->totalAmount = total;
    newOrder->next = NULL;

    if (front == NULL) {

        front = newOrder;
        rear = newOrder;

    }
    else {

        rear->next = newOrder;
        rear = newOrder;
    }

    cout << "Order Placed Successfully!" << endl;
    cout << "Order ID: " << newOrder->orderID << endl;
    cout << "Total Amount: " << total << endl;

    // Clear shopping cart after placing order
    while (cartHead != NULL) {

        CartNode* temp = cartHead;

        cartHead = cartHead->next;

        delete temp;
    }
}

void processOrder() {

    if (front == NULL) {
        cout << "No Pending Orders!" << endl;
        return;
    }

    Order* temp = front;

    cout << "\nProcessing Order..." << endl;
    cout << "Order ID: " << temp->orderID << endl;
    cout << "Total Amount: " << temp->totalAmount << endl;

    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }

    delete temp;

    cout << "Order Processed Successfully!" << endl;
}

void displayOrders() {

    if (front == NULL) {
        cout << "No Pending Orders!" << endl;
        return;
    }

    Order* temp = front;

    cout << "\n========== PENDING ORDERS ==========" << endl;

    while (temp != NULL) {

        cout << "\nOrder ID: " << temp->orderID;
        cout << "\nTotal Amount: " << temp->totalAmount << endl;

        temp = temp->next;
    }
}

void saveProducts() {

    ofstream file("products.txt");

    if (!file) {
        cout << "File could not be opened!" << endl;
        return;
    }

    for (int i = 0; i < productCount; i++) {

        file << products[i].productID << endl;
        file << products[i].productName << endl;
        file << products[i].category << endl;
        file << products[i].price << endl;
        file << products[i].stock << endl;
    }

    file.close();

    cout << "Products Saved Successfully!" << endl;
}

void loadProducts() {

    ifstream file("products.txt");

    if (!file) {
        cout << "No Previous Product Records Found!" << endl;
        return;
    }

    productCount = 0;

    while (productCount < MAX &&
           file >> products[productCount].productID) {

        file.ignore();

        getline(file, products[productCount].productName);
        getline(file, products[productCount].category);

        file >> products[productCount].price;
        file >> products[productCount].stock;

        file.ignore();

        productCount++;
    }

    file.close();

    cout << "Products Loaded Successfully!" << endl;
}

void saveOrders() {

    ofstream file("orders.txt");

    if (!file) {
        cout << "File could not be opened!" << endl;
        return;
    }

    Order* temp = front;

    while (temp != NULL) {

        file << temp->orderID << endl;
        file << temp->totalAmount << endl;

        temp = temp->next;
    }

    file.close();

    cout << "Orders Saved Successfully!" << endl;
}

void loadOrders() {

    ifstream file("orders.txt");

    if (!file) {
        return;
    }

    while (true) {

        int id;
        float amount;

        if (!(file >> id >> amount)) {
            break;
        }

        Order* newOrder = new Order;

        newOrder->orderID = id;
        newOrder->totalAmount = amount;
        newOrder->next = NULL;

        if (front == NULL) {

            front = newOrder;
            rear = newOrder;

        }
        else {

            rear->next = newOrder;
            rear = newOrder;
        }

        if (id > orderCount) {
            orderCount = id;
        }
    }

    file.close();
}

int main() {

    loadProducts();
    loadOrders();

    int choice;

    do {

        cout << "\n===== ONLINE SHOPPING SYSTEM =====" << endl;

        cout << "1. Add Product" << endl;
        cout << "2. Search Product" << endl;
        cout << "3. Display Products" << endl;
        cout << "4. Update Product" << endl;
        cout << "5. Delete Product" << endl;
        cout << "6. Sort Products By Price" << endl;
        cout << "7. Add To Cart" << endl;
        cout << "8. Display Cart" << endl;
        cout << "9. Remove From Cart" << endl;
        cout << "10. Calculate Cart Total" << endl;
        cout << "11. Place Order" << endl;
        cout << "12. Process Order" << endl;
        cout << "13. Display Pending Orders" << endl;
        cout << "14. Save Products and Orders" << endl;
        cout << "15. Exit" << endl;

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {

            case 1: addProduct(); break;
            case 2: searchProduct(); break;
            case 3: displayProducts(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: sortProductsByPrice(); break;
            case 7: addToCart(); break;
            case 8: displayCart(); break;
            case 9: removeFromCart(); break;
            case 10: calculateTotal(); break;
            case 11: placeOrder(); break;
            case 12: processOrder(); break;
            case 13: displayOrders(); break;
            case 14:
                saveProducts();
                saveOrders();
                break;

            case 15:
                saveProducts();
                saveOrders();
                cout << "Thank You!" << endl;
                break;

            default:
                cout << "Invalid Choice!" << endl;
        }

    } while (choice != 15);

    return 0;
}