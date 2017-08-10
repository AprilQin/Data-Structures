#include "LinkedList.h"
#include <iostream>
using std::cout;
using std::endl; //this is needed for endl


LinkedList::LinkedList()
{
   //cout<<"create "<<endl;
	//head = NULL; //M5 remember to assign head to NULL, otherwise it is arbitriary
}

LinkedList::LinkedList(const LinkedList & ll)
{
	node* curr = ll.head;
	for (int j = 0; j < ll.length; j++)
	{
		add(curr->entry);
		curr = curr->next;
	}
}

LinkedList::~LinkedList()
{
	node* curr = head;
	for (int i = 0; i < length; i++)
	{
		head = head->next;
		delete curr;
		curr = head;
	}
	length = 0;
}

LinkedList & LinkedList::operator=(const LinkedList & ll)
{
	// TODO: insert return statement here
	if (&ll == this);
	{
        return *this;
	}
	node* curr = head;
	//cout << "beginning length is "<<length << endl;
	for (int i = 0; i < length; i++)
	{
		head = head->next;
		delete curr;
		curr = head;
		//cout << "delete " <<length << endl;
	}
	length = 0;

	curr = ll.head;
	for (int j = 0; j < ll.length; j++)
	{
		add(curr->entry);
		curr = curr->next;
	}
	length = ll.length;
	return *this;
}

bool LinkedList::add(const Val & v)
{
		bool result = search(v);
		if (result)
		{
			return false;
		}
		else
		{
			node* insert = new node();
			insert->entry = v;
			insert->next = head;
			head = insert;
			length++;
			//cout << "the head entry is " << head->entry << endl;
			//cout << "the current length is " << length << endl;
			return true;
		}
}

bool LinkedList::remove(const Val & v)
{
	node* pre = head;
	node* curr = head->next;
	if (pre == NULL)
	{
		return false; //nothing in the list
	}
	else
	{
		if (v == pre->entry)
		{
			delete head; // is the pointer still there?? I think yes
			length--;
			return true;
		}
		else
		{
			int i;
			for (i = 0; i < length; i++)
			{
				if (v == curr->entry) //M3 forgot that equivilent is double =
				{
					//cout << "the input is found" << endl;
					pre->next = curr->next;
					delete curr;
					length--;
					return true;
				}
				else
				{
					pre = curr;
					curr = curr->next;
				}
			}
			//cout << " entry not found " << endl;
			return false;
		}
	}
}

bool LinkedList::search(const Val & v) const
{
	node* curr = head;
	int i;
	for (i = 0; i < length; i++)
	{
		if (v == curr->entry) //M3 forgot that equivilent is double =
		{
			//cout << "the searching input is found" << endl;
			return true; // M4 should use return instead of break coz the it'll still
						  //run the code outside the loop if I just break the loop
		}
		else
			curr = curr->next;
	}
	return false;
}

bool LinkedList::empty() const
{
	if (length == 0)
	{
		return true;
	}
	return false;
}

std::vector<Val> LinkedList::get() const
{
	vector<string>v;
	node* curr = head;
	for (int i = 0; i < length; i++)
	{
		v.push_back(curr->entry); //M1 remember that need to use push back for vector, not index, when adding new elements
		curr = curr->next;
	}
	return v;
}

void LinkedList::printList() const
{
	vector<string> v = get();
    for (int i = 0; i < length; i++)
    {
        cout <<v[i]<<" ";
    }
    cout << endl;
}
