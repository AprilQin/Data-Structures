#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>
#include <string>
#include <vector>

using std::string;
using Val = std::string; //I should see Val as string
using std::make_unique;
using std::unique_ptr;
using std::vector;

// Define class Node here
struct node
{
	Val entry;
	node* next = NULL;
};



class LinkedList {
public:
	LinkedList();

	LinkedList(const LinkedList& ll);
	~LinkedList();

	LinkedList& operator=(const LinkedList& ll);

	bool add(const Val& v);
	bool remove(const Val& v);

	bool search(const Val& v) const;
	bool empty() const;

	std::vector<Val> get() const;

	void printList() const;

private:
	// Add your member variables and any private member functions here
	node* head = NULL;
	int length = 0;
};

#endif

