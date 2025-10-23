🧩 Doubly Linked List (DLL) in C++

This project implements a Doubly Linked List (DLL) data structure in C++ with complete memory management, insertion, deletion, traversal, and search functionality.

Each node in the list stores:

An integer data value

A pointer to the next node

A pointer to the previous node

🚀 Features

✅ Create and manage a doubly linked list
✅ Insert nodes at:

Beginning

End

Any specific position

✅ Delete nodes from the front
✅ Search for nodes by value
✅ Display:

List data

Detailed memory layout (addresses of previous, next, and current node)
✅ Destructor that safely deletes all nodes and prevents memory leaks

🧱 Class Overview
1. Node Class

Represents a single node of the doubly linked list.

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) {
        this->data = value;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

2. DLL Class

Manages the list and provides all core operations.

🔧 Main Functions:
Function	Description
insertAtBegin(int value)	Inserts a new node at the beginning
insertAtEnd(int value)	Inserts a new node at the end
insertAtPos(int position, int value)	Inserts a node at a specific position
deleteFB()	Deletes the first node
search(int value)	Searches for a node and displays its details
display()	Displays node data only
Display()	Displays all nodes with pointer information
DisplayNode(Node* node)	Displays a single node’s details
~DLL()	Destructor — deletes all nodes safely
📄 Program Flow (main.cpp)
int main() {
    DLL list;

    // Insert elements
    list.insertAtBegin(89);
    list.insertAtEnd(48);
    list.insertAtEnd(59);
    list.insertAtEnd(36);

    // Insert at specific position (5th)
    list.insertAtPos(5, 19);

    // Display complete list with memory details
    list.Display();

    // Delete first node
    list.deleteFB();

    // Display updated list
    list.Display();

    // Search for a node
    list.search(48);

    return 0;
}

🧠 Example Output
------------------------------------------------------
     Prev Address        |   Data   |     Next Address |   Node Address
------------------------------------------------------
                 0 |      89 |     0x123456 |        0x111111
         0x111111 |      48 |     0x222222 |        0x123456
         0x123456 |      59 |     0x333333 |        0x222222
         0x222222 |      36 |     0x444444 |        0x333333
         0x333333 |      19 |              0 |        0x444444
Tail: 0x444444
------------------------------------------------------

Deleting Node: 89
------------------------------------------------------
     Prev Address        |   Data   |     Next Address |   Node Address
------------------------------------------------------
                 0 |      48 |     0x222222 |        0x123456
         0x123456 |      59 |     0x333333 |        0x222222
         0x222222 |      36 |     0x444444 |        0x333333
         0x333333 |      19 |              0 |        0x444444
------------------------------------------------------
Tail: 0x444444
------------------------------------------------------

Node found...

------------------------------------------------------
     Prev Address        |   Data   |     Next Address |   Node Address
------------------------------------------------------
                 0 |      48 |     0x222222 |        0x123456
------------------------------------------------------

All nodes deleted successfully!

🧹 Memory Management

The destructor automatically deletes all nodes when the list object goes out of scope:

~DLL() {
    Node* current = head;
    while (current != nullptr) {
        cout << "Deleting Node: " << current->data << endl;
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    cout << "All nodes deleted successfully!" << endl;
}


✅ No memory leaks
✅ Head and tail pointers reset to nullptr

🛠️ How to Run

Clone or download this repository.

Open the folder in any C++ IDE (e.g., Visual Studio Code, Code::Blocks, Dev-C++).

Compile and run using a C++17-compatible compiler.

Example (using terminal):
g++ -o dll main.cpp
./dll

🧾 Future Enhancements

Add delete by value or delete by position

Add reverse traversal (from tail to head)

Add count and isEmpty() helper functions

Implement file-based persistence for the list

👨‍💻 Author

Your Name
📧 mughiraijaz07@gmail.com
💼 https://github.com/MughiraIjaz

📜 License

This project is open-source and available under the MIT License.
Feel free to use, modify, and distribute.
