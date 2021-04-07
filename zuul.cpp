//Mark Zhang - 4 April 2021 - Zuul: text-based game that allows user to travel between different rooms and interact with items in the rooms
//WIN CONDITION: Take the banana from the Feed Storeroom, then travel to the Primate Exhibit and drop the banana, presenting it as an offering to the Great Bonobo

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <iterator>
#include <map>
#include "Item.h"
#include "Room.h"

using namespace std;

//declaring functions
//[move] responsible for setting room when user enters a direction 
//[take] removes item from room, adds item to player inventory
//[drop] same as take, but reversed: removes item from player inventory, adds item to room
Room* move(Room* currentRoom, string direction);
void take(Room* currentRoom, Room* playerInventory, string desiredItem);
void drop(Room* currentRoom, Room* playerInventory, string droppedItem);
bool checkWin(Room* room);

int main() {

  bool gameWon = false;

  //player room is used as the player's inventory since rooms have many functions that can manipulate items
  Room* player = new Room("Player", "room pointer that holds the player's inventory");

  //setting up all visitable rooms
  Room* zvc = new Room("Zoo Visitor Center", "After getting stuck on your C++ project which happens to be due tomorrow, you decide to seek guidance from the wise and all-knowing Great Bonobo. If you can find a suitable offering for him, you may be able to save your grade.");
  Room* nhm = new Room("Natural History Museum", "There are some glass cases with skeletons and stuff"); 
  Room* aad = new Room("Ancient Artifacts Department", "A room filled with old tomes, equipment, and ancient artifacts, along with a very smooth and shiny gold ring. You instinctively mutter, 'my preciousss....'");
  Room* tb = new Room("Ticket Booth", "A place to buy tickets for the zoo");
  Room* aud = new Room("Auditorium", "Watch stuff");
  Room* aqu = new Room("Aquarium", "Why keep fish in a tank when you can just eat them?");
  Room* equ = new Room("Equipment Storeroom", "A bunch of zoo stuff");
  Room* jan = new Room("Janitor's Closet", "Cleaning supplies, presumably for all the smelly ape feces");
  Room* frm = new Room("Feed Storeroom", "A variety of food for all the animals");
  Room* prm = new Room("Primate Exhibit", "The Throne of the One himself, Bonobo the Great, the Allseer, the Allknower, The Magnificent One, He Who Hails from the Congo. The Bonobo goes by many titles and his consulting his Greatness may just be enough to help you finish your C++ project");
  Room* rep = new Room("Reptile Exhibit", "They're like fish: wierd, small-brained; but worse and more useless because you can't even eat them");
  Room* rod = new Room("Rodent Exhibit", "There are some big hairy rats on display");
  Room* ave = new Room("Avian Exhibit", "You see many colorful, skinny chickens flapping about and dropping feathers everywhere");
  Room* sme = new Room("Small Mammals Exhibit", "Many small interesting creatures, albiet mostly quite dumb. If you look closely enough, you might spot some humans");
  Room* bme = new Room("Big Mammals Exhibit", "There are elephants and bison and while you're sure the Great Bonobo would be very pleased with some of these gifts, your project would already be late by the time you somehow got one of these to his Magnificence.");  

  //items are added to the rooms
  aad->addItem("The-One-Ring");
  frm->addItem("banana");
  frm->addItem("watermelon");
  frm->addItem("alfalfa");
  ave->addItem("parrot");

  //each room contains its own map, where the direction string is the key and the room pointer is the value
  //this means that each room contains directions to adjacent rooms
  map<string, Room*> zvcExits;
  zvcExits["east"] = aud;
  zvcExits["north"] = tb;
  zvcExits["west"] = nhm;
  
  map<string, Room*> nhmExits;
  nhmExits["north"] = aad;
  nhmExits["east"] = zvc;

  map<string, Room*> aadExits;
  aadExits["south"] = nhm;

  map<string, Room*> tbExits;
  tbExits["south"] = zvc;
  tbExits["north"] = aqu;
  
  map<string, Room*> audExits;
  audExits["west"] = zvc;

  map<string, Room*> aquExits;
  aquExits["north"] = prm;
  aquExits["south"] = tb;
  aquExits["west"] = equ;
  aquExits["east"] = rep;
  
  map<string, Room*> equExits;
  equExits["north"] = frm;
  equExits["south"] = jan;
  equExits["east"] = aqu;
  
  map<string, Room*> janExits;
  janExits["north"] = equ;
  
  map<string, Room*> frmExits;
  frmExits["south"] = equ;
  
  map<string, Room*> prmExits;
  prmExits["south"] = aqu;
  
  map<string, Room*> repExits;
  repExits["west"] = aqu;
  repExits["east"] = ave;
  
  map<string, Room*> rodExits;
  rodExits["south"] = ave;
  
  map<string, Room*> aveExits;
  aveExits["north"] = rod;
  aveExits["south"] = sme;
  aveExits["west"] = rep;
  aveExits["east"] = bme;
  
  map<string, Room*> smeExits;
  smeExits["north"] = ave;
  
  map<string, Room*> bmeExits;
  bmeExits["west"] = ave;

  //setting all maps
  zvc->setExits(zvcExits);
  nhm->setExits(nhmExits);
  aad->setExits(aadExits);
  tb->setExits(tbExits);
  aud->setExits(audExits);
  aqu->setExits(aquExits);
  equ->setExits(equExits);
  jan->setExits(janExits);
  frm->setExits(frmExits);
  prm->setExits(prmExits);
  rep->setExits(repExits);
  rod->setExits(rodExits);
  ave->setExits(aveExits);
  sme->setExits(smeExits);
  bme->setExits(bmeExits);

  //start in the Zoo Visitor Center
  Room* currentRoom = zvc;
  Room* newRoom;
  cout << "Welcome to Zuul!" << '\n' << endl;
  currentRoom->printAllInfo();
  while(gameWon == false){
     char input[100];
     cout << "enter a command: move, take, drop, quit" << endl;
     cin >> input;
     //prompts user for command
     if(strcmp(input, "move") == 0){     
       cout << "enter a direction: north, south, east, west" << endl;
       cin >> input;
       if(strcmp(input, "north") == 0 || strcmp(input, "south") == 0 || strcmp(input, "east") == 0 || strcmp(input, "west") == 0){ //if the user input matches up with one of the 4 possible directions
	 newRoom = move(currentRoom, input); //uses the move function to determine the room in the direction that the user input
	 if(currentRoom != newRoom){ //if the room is different, print out info
	   currentRoom = newRoom;
	   currentRoom->printAllInfo();
	 }
       }
       else{ //if direction is not valid, tell user
	 cout << "ERROR: please enter a valid direction!" << '\n' << endl;
       }
     }
  
     else if(strcmp(input, "take") == 0){ //if user invokes take command
       cout << "enter item name:" << endl;
       cin >> input;
       take(currentRoom, player, input);
       cout << "Your inventory: ";
       player->printItems();
       //prompts user to enter item name and plugs it into the take function, prints player's inventory
     }

     else if(strcmp(input, "drop") == 0){ //if user invokes drop command
       cout << "enter item name:" << endl;
       cin >> input;
       drop(currentRoom, player, input);
       cout << "Your inventory: ";
       player->printItems();
       currentRoom->printItems();
       //prompts user to enter item name and puts it into drop function, prints room items and player's inventory

       //the win condition is the drop the banana in the Primate Exhibit, so the win must always happen directly after an item has been dropped
       //uses a function to check if the win condition is met
       if(checkWin(prm) == true){
	 cout << "Congratulations, the Great Bonobo has accepted your offering and in return, he has granted you the knowledge to complete your c++ project!" << endl;
         gameWon = true;
	 break;
	 //quits the program upon fulfilling win condition
       }
     }
     else if(strcmp(input, "quit") == 0){ //allows user to quit using the quit command
       cout << "Thanks for playing!" << endl;
       gameWon = true;
       break;
     }
     else{ //in case the user enters something that is not "move", "take", "drop", or "quit'
       cout << "ERROR: please enter valid command!" <<  '\n' << endl;
     }
  }
  return 0;
}

Room* move(Room* currentRoom, string direction){
  //move function returns a room pointer by taking in a room pointer and a string
  //the function looks through the keys in the room's associated map and checks if any match with
  //the string entered by the user. If a match is found, the key's value is returned
  //if no match is found, the room remains the same
  
  map<string, Room*>::iterator it;
  Room* output;
  map<string, Room*> roomExits = currentRoom->getExits();
  for(it = roomExits.begin(); it != roomExits.end(); it++){
    if(it->first.compare(direction) == 0){
      output = it->second;
      return output;
      break;
    }
  }
  cout << "ERROR: can't move in this direction! Please enter valid direction!" << '\n' << endl;
  return currentRoom;
}

void take(Room* currentRoom, Room* playerInventory, string desiredItem){
  //take function takes 2 rooms, one acts as a source and the other, the player inventory,
  //acts as a destination. The function also takes in a string
  //the function searches the source room's item vector for items that match the item name entered by the user
  //if a match is found, the item is removed from the source room's item vector and added to the
  //destination room. If not, prompt the user to enter a valid item name
  
  bool itemErased = false;
  vector<Item> items = currentRoom->getItems();
  for(int i = 0; i < items.size(); i++){
    if(items[i].getName().compare(desiredItem) == 0){
      items.erase(items.begin()+i);
      playerInventory->addItem(desiredItem);
      itemErased = true;
      break;
    }
  }
  if(itemErased == false){
    cout << "ERROR: please enter valid item name!" << '\n' << endl;
  }
  else{
    currentRoom->setItems(items);
  }
}

void drop(Room* currentRoom, Room* playerInventory, string droppedItem){
  //drop is the same as take, but the player's inventory is the source and the other room pointer is
  //the destination
  take(playerInventory, currentRoom, droppedItem);
}

bool checkWin(Room* room){
  //Takes a room which will the be the Primate Exhibit and checks if there is an item
  //with the name "banana"
  //If yes, return true, indicating that the win condition is met
  vector<Item> items = room->getItems();
  vector<Item>::iterator it;
  for(it = items.begin(); it != items.end(); it++){

    if(it->getName().compare("banana") == 0){
      return true;
    }
    
  }
  return false;
}
