#pragma once
#include <algorithm> 
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

template<typename T>
struct Item
{
	const std::string key;
	T value;

	Item(const std::string& n, const T& a) : key(n), value(a) { }
};

template<typename T>
class Hash_Table {
private:
	std::vector<std::list<Item<T>*>*> table;
	std::vector<Item<T>*> doplist;
	int hash(const std::string& key) const;
public:
	Hash_Table();
	Hash_Table(const int capacity);
	~Hash_Table();

	void push(const std::string& key, const T& value);
	void pop(const std::string& key);
	Item<T>* search(std::string key) const;
	void clear();
	bool isEmpty() const;

	class Iterator
	{
	private:
		const Hash_Table<T>& tab;
		typename std::vector<Item<T>*>::const_iterator current;
	public:
		Iterator(const Hash_Table<T>& tab);
		bool finish() const;
		void next();
		void start();
		Item<T>* getValue() const;
	};
};

template class Hash_Table<int>;
template class Hash_Table<double>;