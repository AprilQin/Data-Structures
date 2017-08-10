#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "HashTable.h"
#include <iostream>

using std::cout;
using std::endl;
using std::sort;
//using std::string;
//using std::vector;
//using std::endl;
//using std::vector;

bool HashTable::checkalpha(Val v)
{
	int i;
	for (i = 0; i < v.length(); i++)
	{
		if (isalpha(v[i]))
		{
			continue;
		}
		else
			throw std::invalid_argument("invalid input string");
	}
	return false;
}



std::uint32_t HashTable::hash(const Val & key)
{
	int n = key.length();
	uint32_t hashcode = 0;
	int i;

	for (i = 0; i < n; i++)
	{
		int ascii = (int)key[i];
		if (ascii <= 90 && ascii >= 65)
		{
			ascii -= 64;
			//cout << "ascci is " << ascii << endl;
		}
		else
		{
			ascii -= 96;
			//cout << "ascci is " << ascii << endl;
		}
		hashcode = 37 * hashcode + ascii;
	}
	//cout << "the hashcode is " << hashcode << endl;
	return hashcode;
}

std::size_t HashTable::compress(std::uint32_t hash) const
{
	size_t index = 0;
	index = hash % curr_capacity;
	//cout << "index is " << index << endl;
	return index;
}

HashTable::HashTable()
{
	table = make_unique<LinkedList[]>(defaultCapacity); //this already creates the linkedlists for me, so I
	//don't need to manually create linkedlist objects in each index
	curr_capacity = defaultCapacity;
}

bool HashTable::check_prime(int input, int number)
{
	for (int i = 2; i <= input; i++)
	{
		//cout << "prime = " << number << endl;
		if (number % i == 0)
		{
			return false;
		}
	}
	//cout << "found" << endl;
	return true;
}

HashTable::HashTable(int c)
{
	int prime = 2 * c + 1;
	int found = false;
	while (found == false)
	{
		found = check_prime(c, prime);
		if (!found)
		{
			prime = prime + 1;
			found = check_prime(c, prime);
		}
	}
	table = make_unique<LinkedList[]>(prime);
	curr_capacity = prime;
	//cout << "the prime is " << prime << endl;

}

HashTable::HashTable(const HashTable & ht)
{
	curr_capacity = ht.curr_capacity;
	//cout << "curr capacity is " << curr_capacity << endl;
	table = make_unique<LinkedList[]>(curr_capacity);

	for (int i = 0; i < curr_capacity; i++)
	{
		table[i] = ht.table[i];
	}
}

HashTable & HashTable::operator=(const HashTable & ht)
{
	// TODO: insert return statement here
	if (this == &ht)
	{
		return *this; //M11 return this means return the current working address, the requirement is to return a hashtable object which should be the content within the this
	}
	else
	{
		curr_capacity = ht.curr_capacity;
		//unique_ptr<LinkedList[]> copy = make_unique<LinkedList[]>(curr_capacity);
		table = make_unique<LinkedList[]>(curr_capacity);
		for (int i = 0; i < curr_capacity; i++)
		{
			table[i] = ht.table[i];
		}
		return *this;
	}

}

bool HashTable::add(const Val & v)
{
	// check if v is accpetable
	checkalpha(v);
	uint32_t hashcode = hash(v);
	size_t i = compress(hashcode);
	bool result = table[i].add(v);
	if (result)
	{
		curr_size++;
	}
	return result;
}

bool HashTable::remove(const Val & v)
{
	// check if v is accpetable
	checkalpha(v);
	uint32_t hashcode = hash(v);
	size_t i = compress(hashcode);
	bool result = table[i].remove(v);
	if (result)
	{
		curr_size--;
	}
	return result;
}

bool HashTable::search(const Val & v)
{
	checkalpha(v);
	uint32_t hashcode = hash(v);
	size_t i = compress(hashcode);
	bool result = table[i].search(v);
	return result;
}

int HashTable::size() const
{
	//cout << "table size is "<<curr_size << endl;
	return curr_size;
}

int HashTable::capacity() const
{
	// << "capacity is " << curr_capacity<< endl;
	return curr_capacity;
}

std::vector<Val> HashTable::keys() const
{
	vector<Val> all_entries;
	for (int i = 0; i < curr_capacity; i++)
	{
		if (!table[i].empty())
		{
			vector<Val> curr_vector = table[i].get(); //M8 forgot the brackets, again!!
			for (int i = 0; i < curr_vector.size(); i++) //M9 can't call a non-const member function?why
			{
				all_entries.push_back(curr_vector[i]);
			}
		}
	}
	return all_entries;
}

float HashTable::loadFactor() const
{
	//size();
	//capacity();
	float fullness = (float)curr_size / curr_capacity; //M9 I need to change one of the denominator or numerator to float first
	//cout << "the loadFactor is " << fullness << endl;
	return fullness;
}

HashTable HashTable::setunion(const HashTable & ht) const
{
    HashTable uniom(ht);
    vector<string> v; //M12: "v" should not be declared in this scope
    for (int i = 0; i<curr_capacity;i++)
    {
        v = table[i].get();
        for (int j = 0; j<v.size();j++)
        {
            uniom.add(v[j]);
        }
    }

	return uniom;
}

void HashTable::printTable(const std::string & label) const
{
	for (int i = 0; i < curr_capacity; i++)
	{
		if (!table[i].empty())
		{
			table[i].printList(); //M8 forgot the brackets, again!!
		}
	}
}







