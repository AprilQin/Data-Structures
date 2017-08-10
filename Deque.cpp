#include <iostream>
#include <string> //need to include this header file because of the label thing
#include "Deque.h" // don't forget to use double quotation marks instead of <>
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::endl;
using std::string;
using std::runtime_error;


Deque::Deque(const Deque & que) //this pass the address of que, now we can use que like we are on the stack since the function knows the address of it
//que is not a pointer to some other object. It is the address of that obeject I passed it.
{
	Node* curr = que.head.get();
	while (curr != NULL)
	{
		insert_back(curr->val);
		curr = curr->next.get();
	}
}

Deque::~Deque()
{
	tail = NULL; //since everything else is a unique pointer (head, next, etc), I don't need to call delete. when the program terminates, the deque will be destroyed 
	//tail still has the memory address, but the stuff in the address is destroyed already, I can't call delete tail. I only need to set tail to NULL
}

Deque & Deque::operator=(const Deque & que)
{
	// TODO: insert return statement here
	if (this == &que)
	{
		return *this;
	}
	Deque copy(que);

	head = move(copy.head);
	tail = copy.tail; 
	length = que.length;
	return *this;
}

void Deque::insert_front(int value)
{
	if (head == NULL)
	{
		head = make_unique <Node>(value);
		tail = head.get();
	}

	else
	{
		unique_ptr <Node> newNode(make_unique<Node>(value, move(head))); //since head is an unique pointer,
		// it can't be passed by value. 
		head = move(newNode);
	}

	length++;

	
}

void Deque::insert_back(int value)
{
	if (head == NULL)
	{
		head = make_unique <Node>(value);
		tail = head.get();
	}

	else
	{
		unique_ptr <Node> newNode(make_unique<Node>(value));
		tail->next = move(newNode);
		tail = tail->next.get();
	}

	length++;
}

int Deque::remove_front()
{
	int removed;
	if (head == NULL)
	{
		throw runtime_error("empty deque"); //have to write runtime error messege!
	}
	
	else
	{
		removed = head->val; // can't create the removed here since removed needs to be returned.
		//therefore, if I put it in else, it'll be a local varible to else
		head = move(head->next);
		length--;
	}
	return removed;
}

int Deque::remove_back()
{
	int removed;
	if (head == NULL)
	{
		throw runtime_error("empty deque"); //have to write runtime error messege!
	}
	else
	{
		removed = tail->val;
		Node* curr = head.get();

		if (length == 1)
		{
			removed = head->val;
			head = NULL;
			tail = NULL;
			length--;
			return removed;
		}

		while (curr->next.get() != tail) //get return the stored pointer. since curr->next is a unique pointer, tail is 
			//an observer, they are considered different types. We need to use .get() to get the pointer value in order to
			//compare them. btw, I can compare unique ptr to unique ptr
		{
			curr = curr->next.get();
		}
		curr->next = NULL; // this frees the memory of the last node
		tail = curr;
		length--;
	}
	return removed;
}

int Deque::peek_front() const
{
	if (head == NULL)
	{
		throw runtime_error("empty deque");

	}
	return head->val;
}

int Deque::peek_back() const
{
	if (head == NULL)
	{
		throw runtime_error("empty deque");
	}
	return tail->val;
}

bool Deque::empty() const
{
	return length == 0;
}

int Deque::size() const
{
	return length;
}

void Deque::print_queue(const std::string & label) const
{
	cout << label << endl;
	Node* curr = head.get();
	while (curr != 0)
	{
		cout << *curr << endl; 
		curr = curr->next.get();
	}
}


//int main()
//{
//	Deque dq1;
//	cout << dq1.empty() << " - 1" << endl;
//
//	dq1.insert_front(42);
//	dq1.insert_back(216);
//
//	cout << dq1.peek_front() << " - 42" << endl;
//	cout << dq1.peek_back() << " - 216" << endl;
//	cout << dq1.size() << " - 2" << endl;
//
//	dq1.print_queue("dq1 before copy constructor and copy assignment");
//
//	Deque dq2(dq1);
//	dq2.print_queue("dq2 after copy constructor");
//	Deque dq3;
//	dq3 = dq1;
//
//	dq3.print_queue("dq3 after copy assignment");
//
//	cout << dq1.remove_front() << " - 42" << endl;
//	cout << dq1.remove_back() << " - 216" << endl;
//	dq1.print_queue("dq1 should be empty");
//
//	cout << dq2.peek_front() << " - 42" << endl;
//	cout << dq2.peek_back() << " - 216" << endl;
//
//	dq3.print_queue("After two removes from dq1");
//
//	cout << dq3.peek_front() << " - 42" << endl;
//	cout << dq3.peek_back() << " - 216" << endl;
//
//	system("pause");
//}