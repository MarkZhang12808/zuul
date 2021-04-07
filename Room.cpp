//Mark Zhang - 4 April 2021 - Zuul: text-based game that allows user to travel between different room\
s and interact with items in the rooms

#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <iterator>
#include <vector>
#include "Item.h"
#include "Room.h"
using namespace std;

//functions that allow the main program to use the Room class

Room::Room(string roomName, string roomDescription) {
  name = roomName;
  description = roomDescription;
  vector<Item> items;
  map<string, Room*> exits;
}

vector<Item> Room::getItems(){
  return items;
}

map<string, Room*> Room::getExits(){
  return exits;
}

string Room::getDescription(){
  return description;
}

string Room::getName(){
  return name;
}

void Room::printItems(){
  vector<Item>::iterator it;
  cout << "ITEMS:" << endl; 
  for(it = items.begin(); it != items.end(); it++){
    cout << " " << it->getName() << endl;
  }
  cout << '\n' << endl;
}

void Room::printExits(){
  cout << "DIRECTION" << '\t' << "DESTINATION" << endl;
  map<string, Room*>::iterator it;
  for(it = exits.begin(); it != exits.end(); it++){
    cout << it->first << '\t' << '\t' << it->second->getName() << endl;
  }
  cout << '\n';
}

void Room::printDescription(){
  cout << "ROOM DESCRIPTION: " << description << '\n'<< endl;
}

void Room::printName(){
  cout << "You are currently in: " << name << '\n' << endl;
}

void Room::addItem(string itemName){
  Item* newItem = new Item(itemName);
  items.push_back(*newItem);
}

void Room::printAllInfo(){
  cout << "------------------------------------------------" << '\n' << endl;
  printName();
  printDescription();
  printItems();
  printExits();
  cout << "------------------------------------------------" << '\n' << endl;
}

void Room::setExits(map<string, Room*> roomExits){
  exits = roomExits;
}

void Room::setItems(vector<Item> newItems){
  items = newItems;
}
