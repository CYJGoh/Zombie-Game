// This is COS30008 Programming Project 2 by Clement Goh Yung Jing (101218668)
// Project Title: Zombie Text-Based Game
#include "ZombieIterator.h"
#include "ZombieIndexer.h"
#include "ZombieFactory.h"
#include "LevelManager.h"
#include "LevelTree.h"
#include "Arsenal.h"
#include "Queue.h"
#include "AttackVisitor.h"
#include "ReportVisitor.h"
#include <fstream>

using namespace std;

void mainMenu(string aLoc) {
    cout << "------------------------------------------------------------------" << endl;
    cout << "\nYou're at " << aLoc << " now.\n" << endl;
    cout << "Choose an action [travel/rest/arsenal/collection/info/return/help/quit]" << endl;
}

void help() {
    ifstream  fileInput;
    string line;

    //open input file
    fileInput.open("instruction.txt", ifstream::in);

    //while not end of file
    while (fileInput)
    {
        //read each line in file
        getline(fileInput, line);

        //display output in console
        cout << line << endl;
    }

    //close file
    fileInput.close();
}

int main()
{
    //Initialisation
    string lUserInput1;
    string lUserInput2;
    string lUserInput3;
    bool isWin= false;
    bool isPlaying = false;
    bool isEnd = false;

    //Arsenal creation
    Arsenal* arsenal = new Arsenal();

    //Inventory creation
    Inventory* inventory = new Inventory();

    inventory->StoreTop("Shield Potion"); //Startup item stored in inventory

    //Player creation
    Player* player1 = new Player("Player 1", "1001", 100, arsenal, inventory);

    //Zombie factory creation
    ZombieFactory factory;

    //Zombie array creation
    Zombie zombieArr[3];
    zombieArr[0] = factory.createLurker();
    zombieArr[1] = factory.createGasbag();
    zombieArr[2] = factory.createBull();

    //Zombie Iterator creation
    ZombieIterator zomIter(zombieArr, 3);

    //Array of keys for zombie array
    string zomKey[3];
    zomKey[0] = "lurker";
    zomKey[1] = "gasbag";
    zomKey[2] = "bull";

    //Zombie Indexer (Assoc array/Adapter for zombie array object) creation
    ZombieIndexer zomIndexer(zombieArr, zomKey, 3);

    //Weapon creation stored in array
    Weapon weaponList[5];
    weaponList[0] = Weapon("Machete", 20, Melee);
    weaponList[1] = Weapon("Crossbow", 35, Range);
    weaponList[2] = Weapon("Sawed Shotgun", 50, Firearm);
    weaponList[3] = Weapon("MP5 SMG", 75, Firearm);
    weaponList[4] = Weapon("MGL Grenade Launcher", 100, Explosive);

    //Collectibles creation
    string items[10];
    items[0] = string("Sarawak Kek Lapis");
    items[1] = string("Batik Cloth");
    items[2] = string("Agong's Keris");
    items[3] = string("Shield Potion");
    items[4] = string("Rattan baskets"); 
    items[5] = string("Unicorn Soft Toy");
    items[6] = string("Gundam model");
    items[7] = string("Hotwheels model");
    items[8] = string("Kaws Figurine");
    items[9] = string("Gold ring");

    //Queue creation
    Queue<string> collectibleLevel1 = Queue<string>();
    collectibleLevel1.Enqueue(items[0]);
    collectibleLevel1.Enqueue(items[1]);
    collectibleLevel1.Enqueue(items[3]);

    Queue<string> collectibleLevel2 = Queue<string>();
    collectibleLevel2.Enqueue(items[4]);
    collectibleLevel2.Enqueue(items[5]);
    collectibleLevel2.Enqueue(items[3]);

    Queue<string> collectibleLevel3 = Queue<string>();
    collectibleLevel3.Enqueue(items[2]);
    collectibleLevel3.Enqueue(items[6]);
    collectibleLevel3.Enqueue(items[3]);

    Queue<string> collectibleLevel4 = Queue<string>();
    collectibleLevel4.Enqueue(items[7]);
    collectibleLevel4.Enqueue(items[8]);
    collectibleLevel4.Enqueue(items[9]);

    Queue<string> collectibleLevel5 = Queue<string>();
    collectibleLevel5.Enqueue(items[3]);
    
    //Level creation
    Level level1 = Level("Padang Merdeka", weaponList[0], zomIndexer["lurker"], player1, collectibleLevel1);
    Level level2 = Level("Old Courthouse", weaponList[1], zomIndexer["lurker"], player1, collectibleLevel2);
    Level level3 = Level("Cafeteria", weaponList[2], zomIndexer["gasbag"], player1, collectibleLevel3);
    Level level4 = Level("Golden Bridge", weaponList[4], zomIndexer["bull"], player1, collectibleLevel4);
    Level level5 = Level("Carpenter Street", weaponList[3], zomIndexer["bull"], player1, collectibleLevel5);

    //LevelTree creation
    LevelTree lvlTree = LevelTree();
    lvlTree.InsertLeft(level1);
    MapNode<Level>& temp = lvlTree.getCurrent();
    lvlTree.InsertRight(level2);
    lvlTree.InsertLeft(level3);
    lvlTree.InsertRight(level5);
    lvlTree.Parent();
    lvlTree.InsertLeft(level4);
    lvlTree.InsertLeft(&temp);

    lvlTree.Reset();

    //Level manager (Stack feature)
    LevelManager* lvlmanager = new LevelManager();

    //Visitor object creation
    ReportVisitor reportVisitor = ReportVisitor();

    //Inheritance demonstration
    /*cout << "Stats of Player 1" << endl;
    cout << "Name: " << player1->getName() << endl;
    cout << "HP: " << player1->getCurrentHP() << "/" << player1->getMaxHP() << endl;
    cout << "Shield: " << player1->getCurrentShield() << "/" << player1->getMaxShield() << endl;
    cout << "Weapon Equipped: " << player1->getWeapon().getName() << endl;
    cout << "Damage: " << player1->getDamageDealt() << endl;

    cout << "\nStats of Bull Zombie" << endl;
    cout << "Name: " << zomIndexer["bull"].getName() << endl;
    cout << "HP: " << zomIndexer["bull"].getCurrentHP() << "/" << zomIndexer["bull"].getMaxHP() << endl;
    cout << "Damage: " << zomIndexer["bull"].getDamage() << endl;*/

    //Demo the fighting between player and multiple zombies
    /*player1->Attack(zombieArr[0]);
    cout << "Health of Lurker after attacked:" << zombieArr[0].getCurrentHP() << endl;
    zombieArr[2].Attack(*player1);
    zombieArr[2].Attack(*player1);
    cout << "Health of Player after attacked:" << player1->getCurrentHP() << endl;
    cout << "\nPlayer 1 resting" << endl;
    player1->Rest();
    cout << "Health of Player after rested:" << player1->getCurrentHP() << endl;*/

    //Demonstration of application of array
    /*cout << "Accessing the zombie in the level stored using array" << endl;
    cout << "Zombie in Padang Merdeka: " << level1.getEnemy().getName() << endl;
    cout << "Zombie in Old Courthouse: " << level2.getEnemy().getName() << endl;
    cout << "Zombie in Cafeteria: " << level3.getEnemy().getName() << endl;
    cout << "Zombie in Golden Bridge: " << level4.getEnemy().getName() << endl;
    cout << "Zombie in Carpenter Street: " << level5.getEnemy().getName() << endl;

    cout << "\nAccessing the weapon dropped in the level stored using array" << endl;
    cout << "Weapon in Padang Merdeka: " << level1.getWeapon().getName() << endl;
    cout << "Weapon in Old Courthouse: " << level2.getWeapon().getName() << endl;
    cout << "Weapon in Cafeteria: " << level3.getWeapon().getName() << endl;
    cout << "Weapon in Golden Bridge: " << level4.getWeapon().getName() << endl;
    cout << "Weapon in Carpenter Street: " << level5.getWeapon().getName() << endl;

    cout << "\nAccessing the first item dropped in the level stored using array" << endl;
    cout << "First item in Padang Merdeka: " << level1.getCollect() << endl;
    cout << "First item in Old Courthouse: " << level2.getCollect() << endl;
    cout << "First item in Cafeteria: " << level3.getCollect() << endl;
    cout << "First item in Golden Bridge: " << level4.getCollect() << endl;
    cout << "First item in Carpenter Street: " << level5.getCollect() << endl;*/

    //Demonstration of application of DLL
    /*inventory->StoreTop("Shield Potion");
    inventory->StoreLast("Bottle of Dwayne Johnson's Sweat");
    inventory->StoreLast("Holy Bible");
    inventory->StoreBefore("Agong's Keris", inventory->getTopNode());
    cout << "Demonstration of application of DLL" << endl;
    cout << "Before removing Agong's Keris" << endl;
    inventory->accept(reportVisitor);
    inventory->RemoveSelectedItem("Agong's Keris");
    cout << "After removing Agong's Keris" << endl;
    inventory->accept(reportVisitor);*/

    //Stack demonstration
    /*lvlmanager->push(level1);
    cout << "Pushed " << lvlmanager->get()->item.getName() << " into the stack" << endl;
    lvlmanager->push(level2);
    cout << "Pushed " << lvlmanager->get()->item.getName() << " into the stack" << endl;
    lvlmanager->push(level3);
    cout << "Pushed " << lvlmanager->get()->item.getName() << " into the stack" << endl;
    
    cout << "\nPopped " << lvlmanager->get()->item.getName() << " out of the stack" << endl;
    lvlmanager->pop();
    cout << "Popped " << lvlmanager->get()->item.getName() << " out of the stack" << endl;
    lvlmanager->pop();
    cout << "Popped " << lvlmanager->get()->item.getName() << " out of the stack" << endl;
    lvlmanager->pop();*/

    //Queue demonstration
    /*Queue<string> collectibleQueue = Queue<string>();
    collectibleQueue.Enqueue(items[0]);
    cout << "Enqueuing " << items[0] << " into queue" << endl;
    cout << "Front item: " << collectibleQueue.GetFront()->item << endl;
    cout << "Rear item: " << collectibleQueue.GetRear()->item << endl;
    cout << "Size of queue: " << collectibleQueue.Size() << endl;

    collectibleQueue.Enqueue(items[1]);
    cout << "\mEnqueuing " << items[0] << " into queue" << endl;
    cout << "Front item: " << collectibleQueue.GetFront()->item << endl;
    cout << "Rear item: " << collectibleQueue.GetRear()->item << endl;
    cout << "Size of queue: " << collectibleQueue.Size() << endl;

    collectibleQueue.Enqueue(items[2]);
    cout << "\nEnqueuing " << items[0] << " into queue" << endl;
    cout << "Front item: " << collectibleQueue.GetFront()->item << endl;
    cout << "Rear item: " << collectibleQueue.GetRear()->item << endl;
    cout << "Size of queue: " << collectibleQueue.Size() << endl;

    collectibleQueue.Dequeue();
    cout << "\nDequeuing " << items[0] << " out of queue" << endl;
    cout << "Front item" << collectibleQueue.GetFront()->item << endl;
    cout << "Rear item: " << collectibleQueue.GetRear()->item << endl;
    cout << "Size of queue: " << collectibleQueue.Size() << endl;

    collectibleQueue.Dequeue();
    cout << "\nDequeuing " << items[1] << " out of queue" << endl;
    cout << "Front item" << collectibleQueue.GetFront()->item << endl;
    cout << "Rear item: " << collectibleQueue.GetRear()->item << endl;
    cout << "Size of queue: " << collectibleQueue.Size() << endl;

    collectibleQueue.Dequeue();
    cout << "\nDequeuing " << items[2] << " out of queue" << endl;
    cout << "Size of queue: " << collectibleQueue.Size() << endl;*/

    //Tree demonstration
    /*cout << "First Level: " << lvlTree.getCurrent().getData().getName() << endl;
    cout << "Second level: " << lvlTree.Right().getData().getName() << endl;
    cout << "Third level: " << lvlTree.Left().getData().getName() << endl;
    cout << "Fourth level: " << lvlTree.Left().getData().getName() << endl;
    cout << "Third level: " << lvlTree.Parent().getData().getName() << endl;
    cout << "Fifth level: " << lvlTree.Right().getData().getName() << endl;
    cout << "Third level: " << lvlTree.Parent().getData().getName() << endl;
    cout << "First level: " << lvlTree.Left().getData().getName() << endl;*/

    //Arsenal demonstration
    /*arsenal->insertTop(weaponList[0]); //Machete is originally stored in arsenal
    arsenal->insertEnd(weaponList[1]);
    arsenal->next(); //Shift to the next node
    arsenal->insertWeapon(weaponList[2], arsenal->getSelectedNode()); //Insert in between first and second node
    cout << *arsenal << endl;*/

    //ZombieIndexer demonstration
    /*cout << "First zombie" << endl;
    zomIndexer["lurker"].accept(reportVisitor);
    cout << "\nSecond zombie" << endl;
    zomIndexer["gasbag"].accept(reportVisitor);
    cout << "\Third zombie" << endl;
    zomIndexer["bull"].accept(reportVisitor);*/

    //Visitor demonstration
    /*AttackVisitor attackByZombie = AttackVisitor(zomIndexer["lurker"].getDamage());
    AttackVisitor attackByPlayer = AttackVisitor(player1->getDamageDealt());
    player1->accept(attackByZombie);
    player1->accept(reportVisitor);
    zomIndexer["lurker"].accept(attackByPlayer);
    zomIndexer["lurker"].accept(reportVisitor);
    */

    //Demonstration of zombie factory
    /*cout << factory.createLurker().getName() << " can deal " << factory.createLurker().getDamage() << " damage" << endl;
    cout << factory.createGasbag().getName() << " can deal " << factory.createGasbag().getDamage() << " damage" << endl;
    cout << factory.createBull().getName() << " can deal " << factory.createBull().getDamage() << " damage" << endl;*/

    while (true) {
        isWin = false;
        isPlaying = true;
        level1.fCompleted = level2.fCompleted = level3.fCompleted = level4.fCompleted = level5.fCompleted = false;
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        cout << "Welcome to my Zombie Text-Based Game!" << endl;
        cout << "Please enter an option [play/exit]" << endl;
        cin >> lUserInput1;
        if (lUserInput1 == "play") {
            cout << "--------------------------------------------------------------------------------------------------" << endl;
            cout << "The disease has infected more than 3 billions of people worldwide. You are now stranded in middle of Plaza Merdeka Mall. You will need to make your way to the survival camp set up at the State Assembly Building. At each location, you will face different level of zombies and each level you will find yourself a weapon that will enable you to make it through the next location." << endl;

            //Game starts
            while (isPlaying) {
                //Player in Plaza Merdeka
                while (!level1.fCompleted && !isWin) {
                    mainMenu("Plaza Merdeka");
                    cin >> lUserInput2;
                    if (lUserInput2 == "travel") {
                        lvlTree.Reset();
                        lvlmanager->push(level1);
                        level1.Display();
                        level1.Battle(&lvlTree);
                    }
                    else if (lUserInput2 == "rest") {
                        player1->Rest();
                    }
                    else if (lUserInput2 == "arsenal") {
                        cout << *arsenal;
                        cout << "Do you want to equip new weapon? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the weapon that you want to equip" << endl;
                            int index;
                            cin >> index;
                            player1->EquipWeapon(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, make sure you don't regeret" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "collection") {
                        cout << *inventory;
                        cout << "Do you want to use the item to refill your shield? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the item that you want to use" << endl;
                            int index;
                            cin >> index;
                            player1->UseCollectibles(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, make sure you don't regeret" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "info") {
                        player1->accept(reportVisitor);
                    }
                    else if (lUserInput2 == "return") {
                        if (!isEnd)
                            cout << "You're still in the first level lah. Where do you think you can return too?" << endl;
                        else {
                            lvlmanager->pop();
                            lvlTree.Parent();
                            level1.fCompleted = level2.fCompleted = level3.fCompleted = level4.fCompleted = true;
                        }
                    }
                    else if (lUserInput2 == "help") {
                        help();
                    }
                    else if (lUserInput2 == "quit") {
                        cout << "Hmm okay, Hope to see you soon" << endl;
                        isWin = true;
                        break;
                    }
                    else {
                        cout << "Aiyo type properly lah!" << endl;
                    }
                }

                //Player in Padang Merdeka
                while (!level2.fCompleted && level1.fCompleted && !isWin) {
                    mainMenu("Padang Merdeka");
                    cin >> lUserInput2;
                    if (lUserInput2 == "travel") {
                        lvlTree.Right();
                        lvlmanager->push(level2);
                        level2.Display();
                        level2.Battle(&lvlTree);
                    }
                    else if (lUserInput2 == "rest") {
                        player1->Rest();
                    }
                    else if (lUserInput2 == "arsenal") {
                        cout << *arsenal;
                        cout << "Do you want to equip new weapon? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the weapon that you want to equip" << endl;
                            int index;
                            cin >> index;
                            player1->EquipWeapon(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, make sure you don't regeret" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "collection") {
                        cout << *inventory;
                        cout << "Do you want to use the item to refill your shield? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the item that you want to use" << endl;
                            int index;
                            cin >> index;
                            player1->UseCollectibles(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, make sure you don't regeret" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "info") {
                        player1->accept(reportVisitor);
                    }
                    else if (lUserInput2 == "return") {
                        lvlmanager->pop();
                        lvlTree.Parent();
                        level1.fCompleted = false;
                    }
                    else if (lUserInput2 == "help") {
                        help();
                    }
                    else if (lUserInput2 == "quit") {
                        cout << "Hmm okay, Hope to see you soon" << endl;
                        isWin = true;
                        break;
                    }
                    else
                    {
                        cout << "Aiyo type properly lah!" << endl;
                    }
                }

                //Player in Old Courthouse
                while (!level3.fCompleted && level2.fCompleted && !isWin) {
                    mainMenu("Old Courthouse");
                    cin >> lUserInput2;
                    if (lUserInput2 == "travel") {
                        lvlTree.Left();
                        lvlmanager->push(level3);
                        level3.Display();
                        level3.Battle(&lvlTree);
                    }
                    else if (lUserInput2 == "rest") {
                        player1->Rest();
                    }
                    else if (lUserInput2 == "arsenal") {
                        cout << *arsenal;
                        cout << "Do you want to equip new weapon? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the weapon that you want to equip" << endl;
                            int index;
                            cin >> index;
                            player1->EquipWeapon(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, make sure you don't regeret" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "collection") {
                        cout << *inventory;
                        cout << "Do you want to use the item to refill your shield? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the item that you want to use:" << endl;
                            int index;
                            cin >> index;
                            player1->UseCollectibles(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, no problem!" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "info") {
                        player1->accept(reportVisitor);
                    }
                    else if (lUserInput2 == "return") {
                        lvlmanager->pop();
                        lvlTree.Parent();
                        level2.fCompleted = false;
                    }
                    else if (lUserInput2 == "quit") {
                        cout << "Hmm okay, Hope to see you soon" << endl;
                        isWin = true;
                        break;
                    }
                    else
                    {
                        cout << "Aiyo type properly lah!" << endl;
                    }
                }

                //Player in Cafeteria
                while (!level4.fCompleted && !level5.fCompleted && level3.fCompleted && !isWin) {
                    mainMenu("Cafeteria");
                    cin >> lUserInput2;
                    if (lUserInput2 == "travel") {
                        cout << "Which direction do you wish to go? [left/right]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "left") {
                            lvlTree.Left();
                            lvlmanager->push(level4);
                            level4.Display();
                            level4.Battle(&lvlTree);
                        }
                        else if (lUserInput3 == "right") {
                            lvlTree.Right();
                            lvlmanager->push(level5);
                            level5.Display();
                            level5.Battle(&lvlTree);
                        }
                        else {
                            cout << "Aiyo type properly again!" << endl;
                        }
                    }
                    else if (lUserInput2 == "rest") {
                        player1->Rest();
                    }
                    else if (lUserInput2 == "arsenal") {
                        cout << *arsenal;
                        cout << "Do you want to equip new weapon? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the weapon that you want to equip" << endl;
                            int index;
                            cin >> index;
                            player1->EquipWeapon(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, make sure you don't regeret" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "collection") {
                        cout << *inventory;
                        cout << "Do you want to use the item to refill your shield? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the item that you want to use:" << endl;
                            int index;
                            cin >> index;
                            player1->UseCollectibles(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, no problem!" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "info") {
                        player1->accept(reportVisitor);
                    }
                    else if (lUserInput2 == "return") {
                        lvlmanager->pop();
                        lvlTree.Parent();
                        level3.fCompleted = false;
                    }
                    else if (lUserInput2 == "help") {
                        help();
                    }
                    else if (lUserInput2 == "quit") {
                        cout << "Hmm okay, Hope to see you soon" << endl;
                        isWin = true;
                        break;
                    }
                    else
                    {
                        cout << "Aiyo type properly lah!" << endl;
                    }
                }

                //Player in Carpenter Street
                while (level5.fCompleted && !isWin) {
                    mainMenu("Carpenter Street");
                    cin >> lUserInput2;
                    if (lUserInput2 == "travel") {
                        cout << "This is a dead end. Return to the previous round!" << endl;
                    }
                    else if (lUserInput2 == "rest") {
                        player1->Rest();
                    }
                    else if (lUserInput2 == "arsenal") {
                        cout << *arsenal;
                        cout << "Do you want to equip new weapon? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the weapon that you want to equip" << endl;
                            int index;
                            cin >> index;
                            player1->EquipWeapon(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, make sure you don't regeret" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "collection") {
                        cout << *inventory;
                        cout << "Do you want to use the item to refill your shield? [yes/no]" << endl;
                        cin >> lUserInput3;
                        if (lUserInput3 == "yes") {
                            cout << "Enter index of the item that you want to use:" << endl;
                            int index;
                            cin >> index;
                            player1->UseCollectibles(index);
                        }
                        else if (lUserInput3 == "no") {
                            cout << "Okay, no problem!" << endl;
                        }
                        else {
                            cout << "Type properly lah aiya" << endl;
                        }
                    }
                    else if (lUserInput2 == "info") {
                        player1->accept(reportVisitor);
                    }
                    else if (lUserInput2 == "return") {
                        lvlmanager->pop();
                        lvlTree.Parent();
                        level5.fCompleted = false;
                    }
                    else if (lUserInput2 == "help") {
                        help();
                    }
                    else if (lUserInput2 == "quit") {
                        cout << "Hmm okay, Hope to see you soon" << endl;
                        isWin = true;
                        break;
                    }
                    else
                    {
                        cout << "Aiyo type properly lah!" << endl;
                    }
                }

                //Player reached Golden Bridge
                if (level4.fCompleted)
                {
                    isEnd = true;
                    cout << "--------------------------------------------------------------------------------------------------" << endl;
                    cout << "\nYou made it through the Golden Bridge! As you make your way to the State Assembly Building, a troop of the Malaysian Army welcomed your arrival and congratulated you for making it through the waves of zombies.\n" << endl;
                    cout << "You now can return back to any location to fight the zombies again.\n" << endl;
                    while (level4.fCompleted)
                    {
                        mainMenu("Golden Bridge");
                        cin >> lUserInput2;
                        if (lUserInput2 == "travel") {
                            level1.fCompleted = level2.fCompleted = level3.fCompleted = level4.fCompleted = level5.fCompleted = false;
                            lvlTree.Reset();
                            lvlmanager->push(level1);
                        }
                        else if (lUserInput2 == "rest") {
                            player1->Rest();
                        }
                        else if (lUserInput2 == "arsenal") {
                            cout << *arsenal;
                            cout << "Do you want to equip new weapon? [yes/no]" << endl;
                            cin >> lUserInput3;
                            if (lUserInput3 == "yes") {
                                cout << "Enter index of the weapon that you want to equip" << endl;
                                int index;
                                cin >> index;
                                player1->EquipWeapon(index);
                            }
                            else if (lUserInput3 == "no") {
                                cout << "Okay, make sure you don't regeret" << endl;
                            }
                            else {
                                cout << "Type properly lah aiya" << endl;
                            }
                        }
                        else if (lUserInput2 == "collection") {
                            cout << *inventory;
                            cout << "Do you want to use the item to refill your shield? [yes/no]" << endl;
                            cin >> lUserInput3;
                            if (lUserInput3 == "yes") {
                                cout << "Enter index of the item that you want to use:" << endl;
                                int index;
                                cin >> index;
                                player1->UseCollectibles(index);
                            }
                            else if (lUserInput3 == "no") {
                                cout << "Okay, no problem!" << endl;
                            }
                            else {
                                cout << "Type properly lah aiya" << endl;
                            }
                        }
                        else if (lUserInput2 == "info") {
                            player1->accept(reportVisitor);
                        } 
                        else if (lUserInput2 == "return") {
                            lvlmanager->pop();
                            lvlTree.Parent();
                            level4.fCompleted = false;
                        }
                        else if (lUserInput2 == "help") {
                            help();
                        }
                        else if (lUserInput2 == "quit") {
                            cout << "Hmm okay, Hope to see you soon" << endl;
                            isWin = true;
                            break;
                        }
                        else
                        {
                            cout << "Aiyo type properly lah!" << endl;
                        }
                    }
                }

                //Credit Scene
                if (isWin) {
                    cout << "This short Zombie Text-Based game is created by Clement Goh - 101218668 for COS30008 Data Structures and Patterns Programming Project 2" << endl;
                    cout << "Last updated on: 11/12/2020" << endl;
                    isPlaying = false;
                }
            }
        }
        else if (lUserInput1 == "exit") {
            cout << "Okay! Bye Bye~" << endl;

            ofstream fileOutput;

            //open output file
            fileOutput.open("playerStats.txt", ifstream::out);

            //print player stats into file
            fileOutput << *player1 << endl;

            //print list of weapons in arsenal into file
            fileOutput << *arsenal << endl;

            //print all collectibles into file
            DLLNode<string> temp = inventory->getSelectedNode();
            fileOutput << "Items in inventory: " << endl;
            for (int i = 0; i < inventory->Size(); i++) {
                fileOutput << "[" << i + 1 << "] " << temp.getValue() << endl;
                temp = temp.getNext();
            }

            // Close the File 
            fileOutput.close();

            break;
        }
        else {
            cout << "Aiyo type properly lah!" << endl;
        }
    }
    return 0;
}
