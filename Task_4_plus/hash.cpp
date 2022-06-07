#include "hash.h"
/* Элементы такой таблицы по мере их вставки в таблицу должны включаться в дополнительный список
итератор для этого класса, который перебирает элементы в том порядке, в котором они были вставлены */
template<typename T>
Hash_Table<T>::Hash_Table() : table(50)
{
	for (size_t i = 0; i < table.size(); i++)
	{
		table[i] = nullptr;
	}
}

template<typename T>
Hash_Table<T>::Hash_Table(const int capacity) : table(capacity)
{
	for (size_t i = 0; i < table.size(); i++)
	{
		table[i] = nullptr;
	}
}

template<typename T>
Hash_Table<T>::~Hash_Table()
{
	clear();
}

template<typename T>
int Hash_Table<T>::hash(const std::string& key) const
{
	int hashsum = 0;

	for (int i : key) {
		hashsum += i;
	}

	return hashsum % table.size();
}

//добавить элемент
template<typename T>
void Hash_Table<T>::push(const std::string& key, const T& value)
{
	int index = hash(key);
	Item<T>* item = new Item<T>(key, value);
	if (!table[index])
	{
		table[index] = new std::list<Item<T>*>;
		table[index]->push_back(item);
	}
	else
	{
		for (Item<T>* i : *table[index])
		{
			if (i->key == key)
			{
				return;
			}
		}
		table[index]->push_back(item);
	}
	doplist.push_back(item);
}
//удалить элемент
template<typename T>
void Hash_Table<T>::pop(const std::string& key)
{
	int index = hash(key);
	if (!table[index]) {
		return;
	}
	Item<T>* searched_item = search(key);

	if (!searched_item)
	{
		return;
	}
	typename std::vector<Item<T>*>::iterator it = std::find(doplist.begin(), doplist.end(), searched_item);
	if (it == doplist.end()) {
		throw std::exception("Fatal error");
	}

	doplist.erase(it);
	table[index]->remove(searched_item);
}

//найти элемент
template<typename T>
Item<T>* Hash_Table<T>::search(std::string key) const
{
	int index = hash(key);

	if (!table[index])
	{
		return nullptr;
	}

	auto it = table[index]->begin();

	for (Item<T>* item : *table[index])
	{
		if (item->key == key) {
			return item;
		}
	}
	return nullptr;
}

//сделать таблицу пустой
template<typename T>
void Hash_Table<T>::clear()
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i] != nullptr)
		{
			while (!table[i]->empty())
			{
				Item<T>* it = table[i]->back();
				delete it;
				table[i]->pop_back();
			}
		}
	}
	table.clear();
	doplist.clear();
}

//проверка таблицы на пустоту
template<typename T>
bool Hash_Table<T>::isEmpty() const
{
	return doplist.size() == 0;
}
template<typename T>
Hash_Table<T>::Iterator::Iterator(const Hash_Table<T>& tab) : tab(tab)
{

}
template<typename T>
bool Hash_Table<T>::Iterator::finish() const
{
	return current == tab.doplist.end();
}
template<typename T>
void Hash_Table<T>::Iterator::next()
{
	current++;
}
template<typename T>
void Hash_Table<T>::Iterator::start()
{
	current = tab.doplist.begin();
}
template<typename T>
Item<T>* Hash_Table<T>::Iterator::getValue() const
{
	return *current;
}
