#ifndef Deque_header
#define Deque_header

#include "Node.h"
#include <memory>
using std::unique_ptr;
using std::make_unique;

class Deque
{
	public:
		//Request a default constructor that will construct an empty queue.
		Deque() = default;      //don't need to write default

		//Construct a deep copy of its constant Deque reference parameter.
		Deque(const Deque& que);

		//must use constant space
		~Deque(); 

		//If the target is the same as the parameter (the source) the assignment operator should have no effect:
		Deque& operator=(const Deque& que);

		//must run in constant O(1) time.
		void insert_front(int value);

		//must run in constant O(1) time.
		void insert_back(int value);

		//Remove and return the value at the front of the deque; if the deque is empty throw a runtime_error (this error class is defined in the stdexcept library file); 
		//must run in constant O(1) time.
		int remove_front();

		//Remove and return the value at the back of the deque; if the deque is empty throw a runtime_error;
		//must run in constant O(n) time.
		int remove_back();

		//Return the value at the front of the deque
		//if the deque is empty throw a runtime_error; 
		//must run in constant O(1) time.
		int peek_front() const;


		int peek_back() const;

		//Return true if the deque is empty, false otherwise.
		bool empty() const;

		//Return the number of items stored in the deque; 
		//must run in constant O(1) time.
		int size() const;

		//prints all the Nodes in the queue, together with the pointers to the head and tail and the size of the queue
		//calls the Node output function
		void print_queue(const std::string& label) const;

	private:
		int length {0}; //can't name it size since we already have a member function called size

		unique_ptr<Node> head ; 

		Node* tail;
};

#endif

//make_unique is like new. It allocate a
//space on heap of type Node, the difference is that the pointer pointing to this object
//returned to stack is a unique pointer. 