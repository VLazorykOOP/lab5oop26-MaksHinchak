#include <iostream>
#include <cstring>
#include <queue>
#include <cctype>

using namespace std;

// ======================================================
//                   ЗАДАЧА 1.5
// ======================================================

class Quadrilateral {
protected:
    double a, b, c, d;

public:
    Quadrilateral() : a(0), b(0), c(0), d(0) {
        cout << "Quadrilateral: constructor without parameters\n";
    }

    Quadrilateral(double a, double b, double c, double d)
        : a(a), b(b), c(c), d(d) {
        cout << "Quadrilateral: constructor with parameters\n";
    }

    Quadrilateral(const Quadrilateral& other)
        : a(other.a), b(other.b), c(other.c), d(other.d) {
        cout << "Quadrilateral: copy constructor\n";
    }

    Quadrilateral& operator=(const Quadrilateral& other) {
        if (this != &other) {
            a = other.a;
            b = other.b;
            c = other.c;
            d = other.d;
        }
        cout << "Quadrilateral: assignment operator\n";
        return *this;
    }

    virtual ~Quadrilateral() {
        cout << "Quadrilateral: destructor\n";
    }

    virtual double area() const = 0;

    virtual double perimeter() const {
        return a + b + c + d;
    }

    virtual void print() const {
        cout << "Quadrilateral sides: "
             << a << ", " << b << ", " << c << ", " << d << endl;
    }
};

class Rectangle : public Quadrilateral {
protected:
    double width, height;

public:
    Rectangle() : Quadrilateral(0, 0, 0, 0), width(0), height(0) {
        cout << "Rectangle: constructor without parameters\n";
    }

    Rectangle(double width, double height)
        : Quadrilateral(width, height, width, height),
          width(width), height(height) {
        cout << "Rectangle: constructor with parameters\n";
    }

    Rectangle(const Rectangle& other)
        : Quadrilateral(other), width(other.width), height(other.height) {
        cout << "Rectangle: copy constructor\n";
    }

    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            Quadrilateral::operator=(other);
            width = other.width;
            height = other.height;
        }
        cout << "Rectangle: assignment operator\n";
        return *this;
    }

    ~Rectangle() override {
        cout << "Rectangle: destructor\n";
    }

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    void print() const override {
        cout << "Rectangle: width = " << width
             << ", height = " << height << endl;
        cout << "Area = " << area()
             << ", Perimeter = " << perimeter() << endl;
    }
};

class Square : public Rectangle {
public:
    Square() : Rectangle(0, 0) {
        cout << "Square: constructor without parameters\n";
    }

    Square(double side) : Rectangle(side, side) {
        cout << "Square: constructor with parameter\n";
    }

    Square(const Square& other) : Rectangle(other) {
        cout << "Square: copy constructor\n";
    }

    Square& operator=(const Square& other) {
        if (this != &other) {
            Rectangle::operator=(other);
        }
        cout << "Square: assignment operator\n";
        return *this;
    }

    ~Square() override {
        cout << "Square: destructor\n";
    }

    void print() const override {
        cout << "Square: side = " << width << endl;
        cout << "Area = " << area()
             << ", Perimeter = " << perimeter() << endl;
    }
};

// ======================================================
//                   ЗАДАЧА 2.5
// ======================================================

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {
        cout << "TreeNode created: " << data << endl;
    }

    ~TreeNode() {
        cout << "TreeNode destroyed: " << data << endl;
    }
};

class BinarySearchTree {
private:
    TreeNode* root;

    void destroyTree(TreeNode* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    void reverseInorder(TreeNode* node) const {
        if (!node) return;
        reverseInorder(node->right);
        cout << node->data << " ";
        reverseInorder(node->left);
    }

public:
    BinarySearchTree() : root(nullptr) {
        cout << "BinarySearchTree: constructor\n";
    }

    ~BinarySearchTree() {
        destroyTree(root);
        cout << "BinarySearchTree: destructor\n";
    }

    void insert(int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
            cout << "Inserted root: " << value << endl;
            return;
        }

        TreeNode* current = root;
        TreeNode* parent = nullptr;

        while (current != nullptr) {
            parent = current;

            if (value < current->data) {
                current = current->left;
            } else if (value > current->data) {
                current = current->right;
            } else {
                cout << "Value " << value << " already exists. Duplicate not inserted.\n";
                return;
            }
        }

        if (value < parent->data) {
            parent->left = new TreeNode(value);
            cout << "Inserted " << value << " to the left of " << parent->data << endl;
        } else {
            parent->right = new TreeNode(value);
            cout << "Inserted " << value << " to the right of " << parent->data << endl;
        }
    }

    void breadthTraversal() const {
        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return;
        }

        queue<TreeNode*> q;
        q.push(root);

        cout << "Breadth-first traversal: ";
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << endl;
    }

    void reverseTraversal() const {
        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "Reverse traversal (descending): ";
        reverseInorder(root);
        cout << endl;
    }
};

// ======================================================
//                   ЗАДАЧА 3.5
// ======================================================

class MyString {
protected:
    char* str;

    void setString(const char* s) {
        delete[] str;
        if (s == nullptr) {
            str = new char[1];
            str[0] = '\0';
            return;
        }

        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

public:
    MyString() {
        str = new char[1];
        str[0] = '\0';
        cout << "MyString: constructor without parameters\n";
    }

    MyString(const char* s) {
        str = nullptr;
        setString(s);
        cout << "MyString: constructor with parameter\n";
    }

    MyString(const MyString& other) {
        str = nullptr;
        setString(other.str);
        cout << "MyString: copy constructor\n";
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            setString(other.str);
        }
        cout << "MyString: assignment operator\n";
        return *this;
    }

    virtual ~MyString() {
        delete[] str;
        cout << "MyString: destructor\n";
    }

    virtual void print(ostream& os) const {
        os << str;
    }

    virtual void input(istream& is) {
        char buffer[1000];
        is.getline(buffer, 1000);
        setString(buffer);
    }

    friend ostream& operator<<(ostream& os, const MyString& obj) {
        obj.print(os);
        return os;
    }

    friend istream& operator>>(istream& is, MyString& obj) {
        char buffer[1000];
        is.getline(buffer, 1000);
        obj.setString(buffer);
        return is;
    }
};

class DigitString : public MyString {
private:
    bool isDigitsOnly(const char* s) const {
        for (int i = 0; s[i] != '\0'; i++) {
            if (!isdigit(static_cast<unsigned char>(s[i]))) {
                return false;
            }
        }
        return true;
    }

public:
    DigitString() : MyString() {
        cout << "DigitString: constructor without parameters\n";
    }

    DigitString(const char* s) : MyString() {
        if (s && isDigitsOnly(s)) {
            setString(s);
        } else {
            setString("");
            cout << "DigitString: invalid string, only digits allowed. Set to empty string.\n";
        }
        cout << "DigitString: constructor with parameter\n";
    }

    DigitString(const DigitString& other) : MyString(other) {
        cout << "DigitString: copy constructor\n";
    }

    DigitString& operator=(const DigitString& other) {
        if (this != &other) {
            MyString::operator=(other);
        }
        cout << "DigitString: assignment operator\n";
        return *this;
    }

    ~DigitString() override {
        cout << "DigitString: destructor\n";
    }

    void print(ostream& os) const override {
        os << str;
    }

    void input(istream& is) override {
        char buffer[1000];
        is.getline(buffer, 1000);

        if (isDigitsOnly(buffer)) {
            setString(buffer);
        } else {
            setString("");
            cout << "Only digits are allowed. String set to empty.\n";
        }
    }

    friend istream& operator>>(istream& is, DigitString& obj) {
        char buffer[1000];
        is.getline(buffer, 1000);

        if (obj.isDigitsOnly(buffer)) {
            obj.setString(buffer);
        } else {
            obj.setString("");
            cout << "Only digits are allowed. String set to empty.\n";
        }
        return is;
    }
};

// ======================================================
//                   ТЕСТУВАННЯ
// ======================================================

void testTask1() {
    cout << "\n========== TASK 1 ==========\n";

    Rectangle r1(5, 3);
    r1.print();

    cout << endl;

    Square s1(4);
    s1.print();

    cout << endl;

    Rectangle r2 = r1;
    r2.print();

    cout << endl;

    Square s2;
    s2 = s1;
    s2.print();

    cout << endl;

    Quadrilateral* figures[2];
    figures[0] = new Rectangle(10, 2);
    figures[1] = new Square(6);

    for (int i = 0; i < 2; i++) {
        figures[i]->print();
        cout << endl;
    }

    for (int i = 0; i < 2; i++) {
        delete figures[i];
    }
}

void testTask2() {
    cout << "\n========== TASK 2 ==========\n";

    BinarySearchTree tree;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 70};
    for (int v : values) {
        tree.insert(v);
    }

    cout << endl;
    tree.breadthTraversal();
    tree.reverseTraversal();
}

void testTask3() {
    cout << "\n========== TASK 3 ==========\n";

    MyString s1("Hello world");
    cout << "s1 = " << s1 << endl;

    MyString s2 = s1;
    cout << "s2 (copy of s1) = " << s2 << endl;

    MyString s3;
    s3 = s1;
    cout << "s3 (assigned from s1) = " << s3 << endl;

    cout << endl;

    DigitString d1("123456");
    cout << "d1 = " << d1 << endl;

    DigitString d2("12ab45");
    cout << "d2 = " << d2 << endl;

    DigitString d3 = d1;
    cout << "d3 (copy of d1) = " << d3 << endl;

    DigitString d4;
    d4 = d1;
    cout << "d4 (assigned from d1) = " << d4 << endl;

    cout << "\nEnter MyString: ";
    cin.ignore();
    MyString userStr;
    cin >> userStr;
    cout << "You entered MyString: " << userStr << endl;

    cout << "Enter DigitString: ";
    DigitString userDigitStr;
    cin >> userDigitStr;
    cout << "You entered DigitString: " << userDigitStr << endl;
}

int main() {
    int choice;

    do {
        cout << "\n=========== MENU ===========\n";
        cout << "1 - Test task 1 (Quadrilateral, Rectangle, Square)\n";
        cout << "2 - Test task 2 (Binary Search Tree)\n";
        cout << "3 - Test task 3 (MyString, DigitString)\n";
        cout << "4 - Test all tasks\n";
        cout << "0 - Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                testTask1();
                break;
            case 2:
                testTask2();
                break;
            case 3:
                testTask3();
                break;
            case 4:
                testTask1();
                testTask2();
                testTask3();
                break;
            case 0:
                cout << "Program finished.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}