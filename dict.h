#pragma once
// Do NOT add any other includes
#include <string> 
#include <iostream>
#include <fstream>
using namespace std;

class StorageNode;
class Trienode{
public:
    char data;
    //Head of the linked list to store frequency
    StorageNode* list=NULL;
    //Tail of the linked list to store data
    StorageNode* curr=list;
    bool is_terminal;
    int count = 0;
    //54 space for each alphabet and number and symbols
    Trienode* children[54];
    //par used for retriving the word once the terminal is reached, as upward traversal in required.
    Trienode* par;

    Trienode(char value){
        data = value;
        is_terminal = false;
        
        for(int i = 0; i<54; i++){
            children[i] = NULL;
        }
    }

};

class Dict {
private:
    //root node
    Trienode* root;
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);
    StorageNode* get_word(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};

class StorageNode{
    public:
        StorageNode* right=NULL;
        int book_code=-1;
        int page=-1;
        int paragraph=-1;
        int freq=0;
        
        StorageNode(int b_code, int pg, int para){
            book_code=b_code;
            page=pg;
            paragraph=para;
            
        }

        StorageNode(){}
};