#include "hash.h"

int main()
{

        Hash_Table<int> table;
        table.push("aaa", 1);
        table.push("aab", 2);
        table.push("aav", 3);
        table.push("aac", 4);
        table.push("aax", 5);
        table.push("aaz", 6);
        table.push("aas", 7);
        table.push("aad", 8);

        Hash_Table<int>::Iterator it(table);

       it.start();
      while (!it.finish())
        {
            std::cout << it.getValue()->value << " ";
            it.next();
        }
        std::cout << std::endl;
        std::cout << table.search("aaa")->value << std::endl;
        Item<int>* item = table.search("aav");

        std::cout << item->value << std::endl;
        table.pop("aav");
        std::cout << table.search("aav") << std::endl;

        Hash_Table<int>::Iterator it1(table);
        it1.start();

        while (!it1.finish())
        {
            std::cout << it1.getValue()->value << " ";
            it1.next();
        }

        table.clear();

        it1.start();

        while (!it1.finish())
        {
            std::cout << it1.getValue()->value << " ";
            it1.next();
        }

}
