//Mark Zhang - 4 April 2021 - Zuul: text-based game that allows user to travel between different room\
s and interact with items in the rooms

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>

//HEADER FILE for Item class

using namespace std;

class Item {
 public:
  Item(string newName);
  string getName();

  //items contain only a name which cannot be changed after the item is created

 private:
  string name;

};

#endif
