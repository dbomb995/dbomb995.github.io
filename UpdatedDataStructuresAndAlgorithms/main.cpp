#include <iostream>
#include <time.h>
#include <algorithm>
#include <climits>
#include "CSVparser.hpp"
#include <vector>

using namespace std;

//forward Declaration
double strToDouble(string str, char ch);
const unsigned int DEFAULT_SIZE = 180;
string csvPath;
string bidKey = "98109";

struct Bid {
    string bidId;
    string title;
    string fund;
    double amount;
    Bid() { amount = 0.0; } }; 

vector <Bid> savedBids(0);
vector <Bid> savedBidsForSort(0);

struct BSTNode {
    Bid dataVal;
    BSTNode* right;
    BSTNode* left;
};

float Timer(clock_t start){
    start = clock() - start; // current clock ticks minus starting clock ticks
    //std::cout << "time: " << start << " clock ticks" << endl;
    //std::cout << "time: " << start * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
    return (start * 1.0 / CLOCKS_PER_SEC) * 1000;
}

void displayBid(Bid bid);

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {
    struct node{
    Bid dataVal;
    node* nextNodePtr;
  };
private: 
    int size = 0;
    node *head, *tail;
    public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    head = NULL;
    tail = NULL;
    return;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
  node *temp= new node;
  temp ->dataVal = bid;
  temp->nextNodePtr=NULL;
  if(head==NULL){
    head=temp;
    tail=temp;
    temp=NULL;
  }
  else{
    tail->nextNodePtr = temp;
    tail = temp;
  }
  size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
  node *temp= new node;
  temp->dataVal = bid;
  temp->nextNodePtr=NULL;
  if(head==NULL){
    head = temp;
    tail = temp;
    temp = NULL;
  }
  else{
    head->nextNodePtr = head;
    head=temp;
  }
  size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    node *temp = new node;
    temp = head;
    while(temp != NULL){
      std::cout << temp->dataVal.bidId << ": " << temp->dataVal.title << " | " << temp->dataVal.amount << 
        " | " << temp->dataVal.fund << endl;
      temp=temp->nextNodePtr;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    node *temp = new node;
    node *prev = new node;
    temp = head;
    while(temp != NULL){
      if(temp->dataVal.bidId == bidId){
        temp->dataVal = temp->nextNodePtr->dataVal;
        temp->nextNodePtr = temp->nextNodePtr->nextNodePtr;
        std::cout<<"Bid ID: " << bidId << " removed." << endl; 
        size--;
        break;
      }

      prev = temp;
      temp=temp->nextNodePtr;
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    node *temp = new node;
    temp = head;
    int i;
    bool found = false;
    for(i = 0; i<size; i++){
        if(temp->dataVal.bidId == bidId){
          found = true;
          return temp->dataVal;
      }
      temp=temp->nextNodePtr;
    }
    Bid empty;
    return empty;
}     

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

Bid getBid() {
    Bid bid;

    std::cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    std::cout << "Enter title: ";
    getline(cin, bid.title);

    std::cout << "Enter fund: ";
    cin >> bid.fund;

    std::cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

void loadBidsForLinkedList(string csvPath, LinkedList *list) {
    std::cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}


//============================================================================
// End of Linked-List class definition
//============================================================================

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {
/*
  struct node{
    Bid dataVal;
    node* nextNodePtr;
  };
 */

LinkedList bids[DEFAULT_SIZE]; 
 
private:
    // FIXME (1): Define structures to hold bids
   unsigned int hash(int key);
public:
  HashTable();
   // FIXME (2): Initialize the structures used to hold bids
   virtual ~HashTable();
   void Insert(Bid bid);
   void PrintAll();
   void Remove(string bidId);
   Bid Search(string bidId);
};

/**
 * Default constructor
 */
HashTable::HashTable(){
}

/**
 * Destructor
 */

HashTable::~HashTable() {
  // FIXME (3): Implement logic to free storage when class is destroye
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */

unsigned int HashTable::hash(int key) {
    // FIXME (4): Implement logic to calculate a hash value
    unsigned int hashVal;
    hashVal = key % 20;
    return hashVal;
}

/**I
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (5): Implement logic to insert a bid
    int hashVal = hash(stoi(bid.bidId));
    bids[hashVal].Append(bid);
    return;
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (6): Implement logic to print all bids
  std::cout << "-------------------------------------------------" << endl;
  for(int i = 0; i < DEFAULT_SIZE; i++){
    bids[i].PrintList();
  }
  std::cout << "-----------------------------------------------" << endl; 
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // FIXME (7): Implement logic to remove a bid
    for (int i = 0; i < DEFAULT_SIZE; i++){
      if(bids[i].Search(bidId).bidId.compare("") == 0){
        continue;
      }
      else{
        bids[i].Remove(bidId);
      }
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

    // FIXME (8): Implement logic to search for and return a bid
    for (int i = 0; i < DEFAULT_SIZE; i++){
      if(bids[i].Search(bidId).bidId.compare("") == 0){
        continue;
      }
      else{
        bid = bids[i].Search(bidId);
      }
    }
    return bid;
}

void loadBidsForHashTable(string csvPath, HashTable* hashTable) {
    std::cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        std::cout << c << " | ";
    }
    std::cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //std::cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

//============================================================================
// End of Hash Table class definition
//============================================================================

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

  private:
    bool hasRoot;
    BSTNode* root;
    void addBSTNode(BSTNode* BSTnode, Bid bid);
    BSTNode* removeBSTNode(BSTNode* BSTnode, string bidId);
    void RecurseBinTree(BSTNode* BSTnode, int mode);
    public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    BSTNode* Search(string bidId);
    Bid bidSearch(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
  hasRoot = false;
  root = NULL;
  return;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every BSTnode
    RecurseBinTree(root, 1);
}

/**
 * recursively Traverse the tree in order
 */
void BinarySearchTree::RecurseBinTree(BSTNode* BSTnode, int mode = 0){
  if(BSTnode !=NULL){
    if(BSTnode->left){
      RecurseBinTree(BSTnode->left); 
    }
    if(mode == 0 ){
      displayBid(BSTnode->dataVal);
    }
    else{
      delete BSTnode;
    }
    if(BSTnode->right){
      RecurseBinTree(BSTnode->right);
    }
   }
   else{
    return;
   }
}

void BinarySearchTree::InOrder() {
    RecurseBinTree(root);
}
/**
 * Insert a bid into binary search tree
 */
void BinarySearchTree::Insert(Bid bid) {
  BSTNode *curr = new BSTNode;
  BSTNode *tempL = new BSTNode;
  BSTNode *tempR = new BSTNode;
  if(!hasRoot){ //adds root BSTNode if none exists
    root = curr;
    root->dataVal = bid;
    root->left = NULL;
    root->right = NULL;
    hasRoot = true;
  }
  else{
    curr = root;
    while(true){ //finds the proper place to put the BSTnode
      if(strToDouble(bid.bidId, 'm') < strToDouble(curr->dataVal.bidId, 'M')){
        if(curr->left == 0){
          curr->left = tempL;
          addBSTNode(tempL, bid);
          break;
        }
        else{
          curr = curr->left;
        }
      }
     else{
       if(curr->right == 0){
        curr->right = tempR;
        addBSTNode(tempR, bid);
        break;
       }
       else{
        curr = curr->right;
       }
     }
      }
    }
   return;
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
  BSTNode* BSTnode = new BSTNode;
  BSTNode* temp = new BSTNode;
  BSTnode = Search(bidId);
  if(BSTnode == 0){//Could not find the BSTnode to be deleted
    std::cout << "Bid ID: " << bidId << " not found could not remove." << endl;
    return;
  }
  if(BSTnode->left == 0 && BSTnode->right == 0){ //deletes a leaf
    delete BSTnode;
  }
  else if(BSTnode->left != 0 && BSTnode->right != 0){ //deletes a 2 child parent BSTnode
    temp = BSTnode->right;
    while(temp->left!=0){
      temp=temp->left;
    }
    delete BSTnode;
    BSTnode = temp;
    temp = NULL;
  }
  else if(BSTnode->right == 0 && BSTnode->left != 0){ //deletes a single child parent
    temp = BSTnode->left;
    delete BSTnode;
    BSTnode = temp;
    temp = NULL;
  }
  else if(BSTnode->left == 0 && BSTnode->right != 0){ //deletes a single child parent
    temp = BSTnode->right;
    delete BSTnode;
    BSTnode = temp;
    BSTnode = NULL;
  }
  else{
    std::cout << "Bid ID: " << bidId << " not found could not remove." << endl;
    return;
  }
  std::cout << "Bid ID: " << bidId << " removed" << endl;
}

/**
 * Search for a BSTnode
 */
BSTNode* BinarySearchTree::Search(string bidId) {
  BSTNode* crr = new BSTNode;
  crr = root;
  int i = 0;
  while(true){
      if(crr == NULL){
        break;
      }
      else{
        if(crr->dataVal.bidId.compare(bidId) == 0){
          break;
        }
        else if(strToDouble(bidId, 'M') > strToDouble(crr->dataVal.bidId, 'M')){
          crr = crr->right;
        }
        else if(strToDouble(bidId, 'M') < strToDouble(crr->dataVal.bidId, 'M')){
          crr = crr->left;
        }
      }
      i++;
    }
    
    return crr;
}
/**
 *returns bid from a searched for BSTnode
 */

Bid BinarySearchTree::bidSearch(string bidId){
  Bid bid;
  BSTNode* temp = Search(bidId);
  if(temp != 0){
     bid = Search(bidId)->dataVal;
  }
  return bid;
}
/**
 * Add a bid to some BSTnode (recursive)
 *
 * @param BSTnode Current BSTnode in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addBSTNode(BSTNode* BSTnode, Bid bid) {
    BSTnode->dataVal = bid;
    BSTnode->left = NULL;
    BSTnode->right = NULL;
    return;
}

void loadBidsForBST(string csvPath, BinarySearchTree* bst) {
    std::cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        std::cout << c << " | ";
    }
    std::cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //std::cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;
            // push this bid to the end
             bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}


//============================================================================
// end of Binary Search Tree class definition
//============================================================================

//============================================================================
//  Quick and Selection sort definition
//============================================================================

int partition(vector<Bid>& bids, int begin, int end) {
  int l, h, midpoint;
  Bid temp;
  string pivot;
  bool done = false;

  midpoint = begin + (end - begin)/2;
  pivot = bids[midpoint].title;
  l = begin;
  h = end;

  while(!done){
    while(bids[l].title < pivot){
      ++l;
    }
    while(pivot < bids[h].title){
      --h;
    }

    if(l>=h){
      done =true;
    }
    else{
      temp = bids[l];
      bids[l] = bids[h];
      bids[h] = temp;

      ++l;
      --h;
    }
  }
  return h;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
  int j = 0;

  if(begin >= end){
    return;
  }

  j = partition(bids, begin, end);
  
  quickSort(bids, begin, j);
  quickSort(bids, j+1, end);
  return;
}


/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
  int indexSmallest = 0;
  Bid temp;
  for(int i = 0; i<bids.size();i++){
    for(int j = i + 1; j<bids.size(); j++){
      if(bids.at(j).title<bids.at(indexSmallest).title){
        indexSmallest = j;
      }
    }
    temp = bids.at(i);
    bids.at(i) = bids.at(indexSmallest);
    bids.at(indexSmallest) = temp;
  }
}

//============================================================================
// end of Quick and Selection sort definition
//============================================================================


//Saves bids in Vector Format
vector<Bid> loadBidsIntoVector(string csvPath) {	    
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

void searchAnArray(vector <Bid> Input){
    Bid bid;
    for(int i = 0; i < Input.size()-1; ++i){
        if(Input.at(i).bidId == bidKey){
            displayBid(Input.at(i));
            return;
        }
    }
    cout << "Bid Not Found" << endl;
}

vector <Bid> DeleteFromAnArray(vector <Bid> Input){
    Bid bid;
    for(int i = 0; i < Input.size()-1; ++i){
        if(Input.at(i).bidId == bidKey){
            cout << i;
            Input.erase(Input.begin() + i);
            return Input;
        }
    }
    cout << "Bid Not Found" << endl;
}

//Prints Bid in a human readable format
void displayBid(Bid bid) {
    std::cout << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

//Displays Menu Options
int displayMenuForVector(){
        int choice = 0;
        std::cout << "***********************************"<< endl;
        std::cout << "Vector Menu:" << endl;
        std::cout << "  1. Enter a Bid" << endl;
        std::cout << "  2. Load Bids into Vector" << endl;
        std::cout << "  3. Display All Bids" << endl;
        std::cout << "  4. Search for a Bid" << endl;
        std::cout << "  5. Delete a Bid" << endl;
        std::cout << "  9. Exit Vectors" << endl;
        std::cout << "Enter choice: ";
        cin >> choice;
        return choice;
}

//Takes input from user to perform selected option
int menuOptionsForVector(int choice){
    clock_t begin_time;
    switch (choice)
    {
        case 2:
            savedBids = loadBidsIntoVector(csvPath);
            return 0;
        case 3:
            for (int i = 0; i < savedBids.size(); ++i) {
              displayBid(savedBids.at(i));
           }
            std::cout << endl;
            return 0;
        case 4:
            searchAnArray(savedBids);
            return 0;
        case 5:
            savedBids = DeleteFromAnArray(savedBids);
            return 0;
        case 9: //Breaks the loop and exits program
            return -1;
        default:
            return 0;
    }
}

int displayMenuForBST(){
        int choice;
        std::cout << "***********************************"<< endl;
        std::cout << "BST Menu:" << endl;
        std::cout << "  1. Load Bids" << endl;
        std::cout << "  2. Display All Bids" << endl;
        std::cout << "  3. Find Bid" << endl;
        std::cout << "  4. Remove Bid" << endl;
        std::cout << "  9. Exit" << endl;
        std::cout << "Enter choice: ";
        cin >> choice;
        return choice;
}

int menuOptionsForBST(int choice, BinarySearchTree* bst){
    clock_t begin_time;
    Bid bid;
    switch (choice){
        case 1:
            loadBidsForBST(csvPath, bst);
            return 0;
        case 2:
            bst->InOrder();
            return 0;
        case 3:
            bid = bst->bidSearch(bidKey);
            if (!bid.bidId.empty()){
                displayBid(bid);
            }
            else {
                std::cout << "Bid Id " << bidKey << " not Found" << endl;
            }
            return 0;
        case 4:
            bst->Remove(bidKey);
            return 0;
        case 9:
            return -1;
        default:
            return 0;
    }
}

int displayMenuForHashTable(){
    int choice;
    std::cout << "Hash Table Menu:" << endl;
    std::cout << "  1. Load Bids" << endl;
    std::cout << "  2. Display All Bids" << endl;
    std::cout << "  3. Find Bid" << endl;
    std::cout << "  4. Remove Bid" << endl;
    std::cout << "  9. Exit" << endl;
    std::cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

HashTable* permanentHashTable = new HashTable();
int menuOptionsForHashTable(int choice, HashTable* bidTable){
    clock_t ticks;
    Bid bid;
    switch (choice) {
        case 1:
            bidTable = new HashTable();
            ticks = clock();
            loadBidsForHashTable(csvPath, bidTable);
            permanentHashTable = bidTable;
            return 0;
        case 2:
            permanentHashTable->PrintAll();
            return 0;
        case 3:
            bid = permanentHashTable->Search(bidKey);
            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                std::cout << "Bid Id " << bidKey << " not found." << endl;
            }
            return 0;
        case 4:
            permanentHashTable->Remove(bidKey);
            return 0;
        case 9:
            return -1;
        default:
            return 0;
        }
}

LinkedList permanentList;

int displayMenuForLinkedList(){
        int choice;
        std::cout << "Linked List Menu:" << endl;
        std::cout << "  1. Enter a Bid" << endl;
        std::cout << "  2. Load Bids" << endl;
        std::cout << "  3. Display All Bids" << endl;
        std::cout << "  4. Find Bid" << endl;
        std::cout << "  5. Remove Bid" << endl;
        std::cout << "  9. Exit" << endl;
        std::cout << "Enter choice: ";
        cin >> choice;
        return choice;
}

int menuOptionsForLinkedList(int choice, LinkedList bidList){
    Bid bid;
    switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);
            return 0;
        case 2:
            loadBidsForLinkedList(csvPath, &bidList);
            std::cout << bidList.Size() << " bids read" << endl;
            permanentList = bidList;
            return 0;
        case 3:
            permanentList.PrintList();
            return 0;
        case 4:
            bid =permanentList.Search(bidKey);
            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	std::cout << "Bid Id " << bidKey << " not found." << endl;
            }
            return 0;
        case 5:
            permanentList.Remove(bidKey);
            return 0;
        case 9:
            return -1;
        default:
            return 0;
        }
}

int displayMenuForVectorSorting(){
    int choice;
    std::cout << "Vector Sorting Menu:" << endl;
    std::cout << "  1. Load Bids" << endl;
    std::cout << "  2. Display All Bids" << endl;
    std::cout << "  3. Selection Sort All Bids" << endl;
    std::cout << "  4. Quick Sort All Bids" << endl;
    std::cout << "  5. Search for Bid" << endl;
    std::cout << "  6. Delete a Bid" << endl;
    std::cout << "  9. Exit" << endl;
    std::cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

int menuOptionsForVectorSorting(int choice){
    switch (choice)
    {
        case 1:
            savedBidsForSort = loadBidsIntoVector(csvPath);
            return 0;
        case 2:
            for (int i = 0; i < savedBidsForSort.size(); ++i) {
              displayBid(savedBidsForSort.at(i));
           }
            std::cout << endl;
            return 0;
        case 3:
            selectionSort(savedBidsForSort);
            return 0;
        case 4:
            quickSort(savedBidsForSort, 0, savedBidsForSort.size()-1);
            return 0;
        case 5:
            searchAnArray(savedBidsForSort);
            return 0;
        case 6:
            savedBidsForSort = DeleteFromAnArray(savedBidsForSort);
            return 0;
        case 9: //Breaks the loop and exits program
            return -1;
        default:
            return 0;
    }
}

int displayMenuForComparison(){
    int choice;
    std::cout << "Comparison Menu:" << endl;
    std::cout << "  1. Compare speed of loading Bids" << endl;
    std::cout << "  2. Compare speed of Displaying All Bids" << endl;
    std::cout << "  3. Compare speed of searching for a Bid" << endl;
    std::cout << "  4. Compare speed of deleting a Bid" << endl;
    std::cout << "  9. Exit" << endl;
    std::cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

int menuOptionsForComparison(int choice){
    LinkedList* bidList = new LinkedList();
    BinarySearchTree* bst = new BinarySearchTree();
    HashTable* bidTable = new HashTable();
    clock_t start;
    float VectorTimeUnsorted, VectorTimeQuickSort, VectorTimeSelectionSort, LinkedListTime, BSTTime, HashTableTime;
    switch(choice){
        case 1:
            //Time to load into a vector
            start = clock();
            menuOptionsForVectorSorting(1);
            VectorTimeUnsorted = Timer(start);
            //Time for Linked List
            start = clock();
            menuOptionsForLinkedList(2, *bidList);
            LinkedListTime = Timer(start);
            //Time for BST
            start = clock();
            menuOptionsForBST(1, bst);
            BSTTime = Timer(start);
            //Time for Hash Table
            start = clock();
            menuOptionsForHashTable(1, bidTable);
            HashTableTime = Timer(start);

            std::cout << endl;
            std::cout << "************************************" << endl;
            std::cout << "Vector took " << VectorTimeUnsorted << " MilliSeconds to load the data" << endl;
            std::cout << "Linked List took " << LinkedListTime << " MilliSeconds to load the data" << endl;
            std::cout << "Binary Search Tree took " << BSTTime << " MilliSeconds to load the data" << endl;
            std::cout << "Hash Table took " << HashTableTime << " MilliSeconds to load the data" << endl;
            std::cout << "************************************" << endl;
            std::cout << endl;
            return 0;
            break;

        case 2:
            //Time to for an unsorted vector
            start = clock();
            menuOptionsForVectorSorting(2);
            VectorTimeUnsorted = Timer(start);
            //Time for Linked List
            start = clock();
            menuOptionsForLinkedList(3, *bidList);
            LinkedListTime = Timer(start);
            //Time for BST
            start = clock();
            menuOptionsForBST(2, bst);
            BSTTime = Timer(start);
            //Time for Hash Table
            start = clock();
            menuOptionsForHashTable(2, bidTable);
            HashTableTime = Timer(start);
            //Time to for an sorted vector
            menuOptionsForVectorSorting(3);
            start = clock();
            menuOptionsForVectorSorting(2);
            VectorTimeQuickSort = Timer(start);
            menuOptionsForVectorSorting(1);

            std::cout << endl;
            std::cout << "************************************" << endl;
            std::cout << "Unsorted Vector took " << VectorTimeUnsorted << " MilliSeconds to Display the data" << endl;
            std::cout << "Linked List took " << LinkedListTime << " MilliSeconds to Display the data" << endl;
            std::cout << "Binary Search Tree took " << BSTTime << " MilliSeconds to Display the data" << endl;
            std::cout << "Hash Table took " << HashTableTime << " MilliSeconds to Display the data" << endl;
            std::cout << "Sorted Vector took " << HashTableTime << " MilliSeconds to Display the data" << endl;
            std::cout << "************************************" << endl;
            std::cout << endl;

            return 0;
            break;
        case 3:
            //Time to for an unsorted vector
            start = clock();
            menuOptionsForVectorSorting(5);
            VectorTimeUnsorted = Timer(start);
            //Time for Linked List
            start = clock();
            menuOptionsForLinkedList(4, *bidList);
            LinkedListTime = Timer(start);
            //Time for BST
            start = clock();
            menuOptionsForBST(3, bst);
            BSTTime = Timer(start);
            //Time for Hash Table
            start = clock();
            menuOptionsForHashTable(3, bidTable);
            HashTableTime = Timer(start);
            menuOptionsForVectorSorting(1);
            menuOptionsForVectorSorting(4);
            start = clock();
            menuOptionsForVectorSorting(5);
            VectorTimeQuickSort = Timer(start);
            menuOptionsForVectorSorting(1);

            std::cout << endl;
            std::cout << "************************************" << endl;
            std::cout << "Unsorted Vector took " << VectorTimeUnsorted << " MilliSeconds to find the bid" << endl;
            std::cout << "Linked List took " << LinkedListTime << " MilliSeconds to find the bid" << endl;
            std::cout << "Binary Search Tree took " << BSTTime << " MilliSeconds to find the bid" << endl;
            std::cout << "Hash Table took " << HashTableTime << " MilliSeconds to find the bid" << endl;
            std::cout << "Sorted Vector took " << VectorTimeQuickSort << " MilliSeconds to find the bid" << endl;
            std::cout << "************************************" << endl;
            std::cout << endl;

            return 0;
            break;
        case 4:
            //Time to for an unsorted vector
            start = clock();
            menuOptionsForVectorSorting(6);
            VectorTimeUnsorted = Timer(start);
            //Time for Linked List
            start = clock();
            menuOptionsForLinkedList(5, *bidList);
            LinkedListTime = Timer(start);
            //Time for BST
            start = clock();
            menuOptionsForBST(4, bst);
            BSTTime = Timer(start);
            //Time for Hash Table
            start = clock();
            menuOptionsForHashTable(4, bidTable);
            HashTableTime = Timer(start);
            menuOptionsForVectorSorting(1);
            menuOptionsForVectorSorting(4);
            start = clock();
            menuOptionsForVectorSorting(6);
            VectorTimeQuickSort = Timer(start);
            menuOptionsForVectorSorting(1);
            
            std::cout << endl;
            std::cout << "************************************" << endl;
            std::cout << "Unsorted Vector took " << VectorTimeUnsorted << " MilliSeconds to delete the bid" << endl;
            std::cout << "Linked List took " << LinkedListTime << " MilliSeconds to Display find the bid" << endl;
            std::cout << "Binary Search Tree took " << BSTTime << " MilliSeconds to Display find the bid" << endl;
            std::cout << "Hash Table took " << HashTableTime << " MilliSeconds to Display find the bid" << endl;
            std::cout << "sorted Vector took " << VectorTimeUnsorted << " MilliSeconds to delete the bid" << endl;
            std::cout << "************************************" << endl;
            std::cout << endl;
            return 0;
        case 9:
            return -1;
    }
}

int mainMenu(){
        int choice = 0;
        std::cout << "***********************************"<< endl;
        std::cout << "Main Menu:" << endl;
        std::cout << "  1. Vector Menu" << endl;
        std::cout << "  2. Binary Search Tree Menu" << endl;
        std::cout << "  3. HashTable Menu" << endl;
        std::cout << "  4. LinkedList Menu" << endl;
        std::cout << "  5. Vector Sorting" << endl;
        std::cout << "  6. Comparison" << endl;
        std::cout << "  9. Exit" << endl;
        std::cout << "Enter choice: ";
        cin >> choice;
        return choice;
}



int mainMenuLoop(){
    LinkedList* bidList = new LinkedList();
    int choice;
    BinarySearchTree* bst = new BinarySearchTree();
    HashTable* bidTable = new HashTable();
    while(true){
        choice = mainMenu();
        switch (choice)
        {
            //Enters loop for vector options
            case 1:
                while(true){
                    choice = displayMenuForVector();
                    if(menuOptionsForVector(choice) == -1){
                        break;
                    }
                }
                choice = 0;
                break;
            //Enters loop for BST
            case 2:
                
                while(true){
                    choice = displayMenuForBST();
                    if(menuOptionsForBST(choice, bst) == -1){
                        break;
                    }
                }
                choice = 0;
                break;
            //Enters loop for Hash Table
            case 3:
                while(true){
                    choice = displayMenuForHashTable();
                if(menuOptionsForHashTable(choice, bidTable) == -1){
                        break;
                    }
                }
                choice = 0;
                break;
            //Enters loop for linked list
            case 4:
                while(true){
                    choice = displayMenuForLinkedList();
                    if(menuOptionsForLinkedList(choice, *bidList) == -1){
                        break;
                    }
                }
                choice = 0;
                break;
            //enters loop for vector sorting
            case 5:
                while(true){
                    choice = displayMenuForVectorSorting();
                    if(menuOptionsForVectorSorting(choice) == -1){
                        break;
                    }
                }
                choice = 0;
                break;
            case 6:
                while(true){
                    choice = displayMenuForComparison();
                    if(menuOptionsForComparison(choice) == -1){
                        break;
                    }
                }
                choice = 0;
                break;
            case 9:
                return -1;
            default:
                break;
        }
    }
}

//Sets CSVpath based on command line input
string csvPathSet(int argc, char* CSVpath[]){
    switch (argc)
    {
    case 2:
        csvPath = CSVpath[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv"; //Default If user does not input path to CSV 
    }
    return csvPath;
}

//Converts String to Double after stripping unwanted charachters
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

int main(int argc, char* argv[]){
    string csvPath = csvPathSet(argc, argv);
    std::cout << "Your CSV path is set to " << csvPath << endl;
    mainMenuLoop();
}