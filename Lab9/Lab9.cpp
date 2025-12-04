#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int year;                  
    string event;              
    Node* left;
    Node* right;

    Node(int y, string e) {
        year = y;
        event = e;
        left = right = nullptr;
    }
};


Node* insertEvent(Node* root, int year, string event) {
    if (root == nullptr) {
        cout << "> System: Injecting " << year << "... Timeline stable.\n";
        return new Node(year, event);
    }

    if (year < root->year)
        root->left = insertEvent(root->left, year, event);
    else if (year > root->year)
        root->right = insertEvent(root->right, year, event);
    else {
        cout << "> Alert: Paradox detected at " << year << "!\n";
    }

    return root;
}


Node* search(Node* root, int year) {
    if (root == nullptr)
        return nullptr;

    if (root->year == year)
        return root;

    if (year < root->year)
        return search(root->left, year);
    else
        return search(root->right, year);
}


Node* findMin(Node* root) {
    while (root && root->left != nullptr)
        root = root->left;
    return root;
}


Node* deleteEvent(Node* root, int year) {
    if (root == nullptr)
        return root;

    if (year < root->year)
        root->left = deleteEvent(root->left, year);

    else if (year > root->year)
        root->right = deleteEvent(root->right, year);

    else {
        cout << "> System: Year " << year << " removed. Timeline stabilized.\n";

        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->year = temp->year;
        root->event = temp->event;
        root->right = deleteEvent(root->right, temp->year);
    }

    return root;
}


void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->year << ": " << root->event << endl;
    inorder(root->right);
}

int main() {
    Node* timeline = nullptr;

 
    timeline = insertEvent(timeline, 2050, "Mars Colony Established");
    timeline = insertEvent(timeline, 1969, "Moon Landing");
    timeline = insertEvent(timeline, 2100, "Warp Drive Invented");
    timeline = insertEvent(timeline, 2000, "Y2K Aftermath");

    cout << "\n> Query: Searching for 1969...\n";
    Node* found = search(timeline, 1969);
    if (found)
        cout << "> Result: Event Found! [1969: " << found->event << "]\n";
    else
        cout << "> Result: Event not found.\n";


    timeline = insertEvent(timeline, 1990, "World Wide Web");

    cout << "\n> Alert: Paradox detected at 2000!\n";
    timeline = deleteEvent(timeline, 2000);

    cout << "\n> COMMAND: CHRONOLOGICAL REPORT\n";
    cout << "-------------------------------\n";
    inorder(timeline);
    cout << "-------------------------------\n\n";

    cout << "> Query: Searching for 2000...\n";
    Node* check = search(timeline, 2000);
    if (check)
        cout << "> Result: Event Found!\n";
    else
        cout << "> Result: Year 2000 not found in current timeline.\n";

    return 0;
}
