#include<iostream>
#include<iomanip>
using namespace std;

/*
* Node Class:
*	This class is used to create a node that stores integer data, 
*	and two pointers (next and prev) for double linking.
*/
class Node {

public:

	int data;
	Node* next;
	Node* prev;

	Node(int value)
	{
		this->data = value;
		this->next = nullptr;
		this->prev = nullptr;
	}
};


/*
* DLL Class:
*	This class represents a Doubly Linked List.
*	It manages insertion, deletion, traversal, and search operations.
*/
class DLL
{

public:

	Node* head;
	Node* tail;

	DLL()
	{
		head = nullptr;
		tail = nullptr;
	}

	// 🧱 Task 1: Create a Destructor
	/*
	* Destructor:
	*	This function deletes all nodes in the list and releases memory properly.
	*	It should print the nodes being deleted and confirm when all nodes are deleted.
	*/
	~DLL()
	{
		Node* current = head;

		while (current != nullptr)
		{
			cout << "Deleting Node: " << current->data << endl;
			Node* temp = current;
			current = current->next;
			delete temp;
		}

		cout << "All nodes deleted successfully!" << endl;
		head = nullptr;
		tail = nullptr;
	}



	/*
	* display(): 
	*	This function is used to display only the linked list elements (data).
	*	It will also check if the list is empty.
	*/
	void display()
	{
		Node* current = head;

		if (current == nullptr)
		{
			cout << "List is Empty" << endl;
			return;
		}

		while (current != nullptr)
		{
			cout << current->data << endl;
			current = current->next;
		}
	}


	/* Display():
	*	This function is used to display the nodes with detailed memory information.
	*	Prev Address: Contains the address of the Previous Node
	*	Data: Contains the Node value
	*	Next Address: Contains the address of the Next Node
	*	Node Address: Address of the Current Node
	*/
	void Display() {
		Node* temp = head;
		cout << "\n------------------------------------------------------\n";
		cout << "     Prev Address        |   Data   |     Next Address |   Node Address\n";
		cout << "------------------------------------------------------\n";

		while (temp != nullptr) {
			cout << setw(20) << temp->prev
				<< " | " << setw(7) << temp->data
				<< " | " << setw(18) << temp->next
				<< " | " << setw(20) << temp
				<< endl;
			temp = temp->next;
		}
		cout << endl << "Tail: " << tail << endl;
		cout << "------------------------------------------------------\n";
	}



	/*
	* insertAtBegin():
	*	This function is used to insert the Node at the beginning of the list.
	*/
	void insertAtBegin(int value)
	{
		Node* newNode = new Node(value);

		newNode->next = head;

		if (head != nullptr)
		{
			head->prev = newNode;
		}
		head = newNode;

		if (tail == nullptr)
		{
			tail = newNode;
		}
	}



	/* insertAtPos()
	*	This function is used to insert values at a specific position.
	*
	* 📍 Task 2:
	*	Currently, the previous version failed when inserting the fifth or last element.
	*	Update the logic so that elements can be correctly inserted at any valid position.
	*/
	void insertAtPos(int position, int value)
	{
		if (position <= 0)
		{
			cout << "Invalid position!" << endl;
			return;
		}

		// If position is 1 or list is empty → Insert at beginning
		if (position == 1)
		{
			insertAtBegin(value);
			return;
		}

		Node* current = head;

		// Move current to one node before the desired location
		for (int i = 1; i < position - 1 && current->next != nullptr; i++)
		{
			current = current->next;
		}

		Node* newNode = new Node(value);

		newNode->next = current->next;
		newNode->prev = current;
		current->next = newNode;

		// If inserting in between
		if (newNode->next != nullptr)
			newNode->next->prev = newNode;
		else
			tail = newNode; // If inserted at the end, update tail
	}



	/*
	* deleteFB():
	*	This function is used to delete the node from the front (beginning).
	*
	* 🗑️ Task 3:
	*	Ensure the head pointer correctly points to the next node after deletion.
	*	Also make sure prev pointer of new head becomes NULL.
	*/
	void deleteFB()
	{
		if (head == nullptr)
		{
			cout << "List is Empty" << endl;
			return;
		}

		cout << "Deleting Node: " << head->data << endl;

		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			Node* temp = head;
			head = head->next;
			head->prev = nullptr; // ✅ Fix: New head’s prev must be NULL
			delete temp;
		}
	}



	/* DisplayNode():
	*	The purpose of this function is to display the content of a single node.
	*
	* 🔍 Task 4:
	*	The previous version displayed more than one node.
	*	This version displays only the given node.
	*/
	void DisplayNode(Node* node)
	{
		if (node == nullptr)
		{
			cout << "Node not found!" << endl;
			return;
		}

		cout << "\n------------------------------------------------------\n";
		cout << "     Prev Address        |   Data   |     Next Address |   Node Address\n";
		cout << "------------------------------------------------------\n";

		cout << setw(20) << node->prev
			<< " | " << setw(7) << node->data
			<< " | " << setw(18) << node->next
			<< " | " << setw(20) << node
			<< endl;

		cout << "------------------------------------------------------\n";
	}



	/*
	* search():
	*	This function searches a node by value.
	*	If found, it calls DisplayNode() to show that specific node.
	*/
	void search(int value)
	{
		Node* current = head;

		while (current != nullptr)
		{
			if (current->data == value)
			{
				cout << "Node found..." << endl;
				DisplayNode(current);
				return;
			}
			current = current->next;
		}
		cout << "Node not found!" << endl;
	}



	/*
	* insertAtEnd():
	*	This function inserts a new node at the end of the list.
	*/
	void insertAtEnd(int value)
	{
		if (tail == nullptr)
		{
			insertAtBegin(value);
		}
		else
		{
			Node* newNode = new Node(value);
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

};




/*
* main():
*	Test Plan for all four tasks.
*
* 1. Insert elements in list
* 2. Insert at specific position
* 3. Delete first node
* 4. Search and display a node
*/
int main()
{
	DLL list;


	list.insertAtBegin(89);
	list.insertAtEnd(48);
	list.insertAtEnd(59);
	list.insertAtEnd(36);


	list.insertAtPos(5, 19);
	list.Display();

	
	list.deleteFB();
	list.Display();

	
	list.search(48);

	return 0;
}
