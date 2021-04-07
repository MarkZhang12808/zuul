//Mark Zhang - 4 April 2021 - Zuul: text-based game that allows user to travel between different room\
s and interact with items in the rooms

#ifndef ROOM_H
#define ITEM_H

#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include "Item.h"

using namespace std;

//HEADER FILE for the Room class

class Room{
 private:
  string name;
  string description;
  vector<Item> items; //vector to store items associated with a room, allows player to drop many items into a room
  map<string, Room*> exits; //stores directions and the adjacent room associated with each direction

 public:
  //room constructor takes parameters for the room's name and description
  //exits are added via a map with strings as keys and room pointers as values
  //Items are added to individually to the room via the "addItem()" function
  Room(string roomName, string roomDescription);
  
  string getDescription();
  void printDescription();

  string getName();
  void printName();

  vector<Item> getItems();
  void printItems();
  void addItem(string itemName);
  void setItems(vector<Item> newItems);
  
  map<string, Room*> getExits();
  void setExits(map<string, Room*> roomExits);
  void printExits();

  void printAllInfo();
  
};

#endif
