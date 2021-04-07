//Mark Zhang - 4 April 2021 - Zuul: text-based game that allows user to travel between different room\
s and interact with items in the rooms

#include <iostream>
#include <map>
#include <string>
#include "Item.h"
using namespace std;

//only contains a function that returns the item's name

Item::Item(string setName) {
  name = setName;
  
}

string Item::getName() {
  return name;
}
