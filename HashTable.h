#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "LinkedList.h"

using std::unique_ptr;
using std::make_unique;



class HashTable {
public:
	//Create a hash table of capacity defaultCapacity.
	HashTable();

	//The capacity of the table should be the smallest prime ≥2n.If n<1n<1, throw a std::invalid_argument
	HashTable(int c);

	//Construct a deep copy of ht
	HashTable(const HashTable& ht);

	//The default destructor should be sufficient.
	~HashTable() = default;

	//... complicated
	HashTable& operator=(const HashTable& ht);

	//Verify the single string parameter. 
	//If the parameter is acceptable and it is not already in the table, add it to the HashTable; return true if the parameter was added (it was not already in the table), return false otherwise (the parameter was already in the table).
	bool add(const Val& v);

	//If the parameter is acceptable and it is in the HashTable, remove it; return true
	//return false if the parameter value was not found in the table.
	bool remove(const Val& v);

	//If the parameter is acceptable, return true if it is contained in the HashTable, return false otherwise.
	bool search(const Val& v);

	
	int size() const;
	int capacity() const;

	//Return a vector<string> containing all the entries in this table.Their order can be arbitrary but each element must occur exactly once.
	std::vector<Val> keys() const;

	//Return the(float) load factor of the HashTable.
	float loadFactor() const;

	//Return a HashTable containing the set union of this table and its single HashTable reference parameter. The entries in the result table are deep copies of the entries in the original two tables.
	HashTable setunion(const HashTable& ht) const;

	//Compute the hash code for its string parameter.
	static std::uint32_t hash(const Val& key); //Q1: why set the return value static??

	//Given a hash code of type std::uint32_t, compress to the appropriate index for the capacity of this table.
	std::size_t compress(std::uint32_t hash) const;

	constexpr static int defaultCapacity{ 101 }; 

	//Print the table contents on cout. Use any format you wish.
	void printTable(const std::string& label) const;

private:
	// Add your member variables and any private member functions here
	unique_ptr<LinkedList[]> table = nullptr; //an array of linked list?
	int curr_capacity = 0;
	int curr_size = 0;
	bool checkalpha(Val v);
	bool check_prime(int input, int number);

};

#endif