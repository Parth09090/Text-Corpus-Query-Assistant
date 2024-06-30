// Do NOT add any other includes
#include "dict.h"
#include<iostream>
using namespace std;

Dict::Dict(){
    root = new Trienode('!');
    root->par = NULL;
}


Dict::~Dict(){
    // Implement your function here  
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    //ignored symbols . , - : ! " ' ( ) ? [ ] ; @
    string breaker = " .,-:!\"\'()?[];@";
    int i = 0;
    Trienode* temp = root;
    while(i < sentence.size()){
        bool wrdbrk = false;
        for(char c : breaker){
            if(sentence[i] == c){
                wrdbrk = true;
                break;
            }
        }

        //Alphabet Case, index(0-25)
        if((sentence[i]>64 && sentence[i]<91) || (sentence[i]>96 && sentence[i]<123)){ 
            int index = (sentence[i]>90) ? sentence[i]-'a' : sentence[i]-'A';

            //converting index to character based on ascci value(0-a;25-z)
            char value = char(index+97);
            
            if(temp->children[index] == NULL){
                //if letter not in current word string, add new node and shift to that node
                temp->children[index] = new Trienode(value);
                temp->children[index]->par = temp;
                temp = temp->children[index];
            }else{
                temp = temp->children[index];
            }
        }
        //number case, index(26-35)
        else if((sentence[i]>47 && sentence[i]<58)){
            int index = sentence[i]-'0'+26;
            char value = char(index+48-26);
            if(temp->children[index] == NULL){
                //if number not in current word string, add new node and shift to that node
                temp->children[index] = new Trienode(value);
                temp->children[index]->par = temp;
                temp = temp->children[index];
            }else{
                temp = temp->children[index];
            }
        }
        
        else if(wrdbrk){
            if(temp->curr==NULL){
                temp->curr=new StorageNode(book_code,page,paragraph);
                temp->list=temp->curr;
            }
            else{
                if(temp->curr->paragraph!=paragraph || temp->curr->book_code!=book_code or temp->curr->page!=page){
                    temp->curr->right=new StorageNode(book_code,page,paragraph);
                    temp->curr=temp->curr->right;
                }
                
            }
            temp->curr->freq++;
            temp->is_terminal = true;
            temp->count++;
            temp = root;
        }

        else{
            int index = sentence[i]+1;
            if(index>39){
                index-=3;
            }if(index>41){
                index-=3;
            }if(index>42){
                index-=12;
            }if(index>45){
                index-=29;
            }if(index>46){
                index-=1;
            }if(index>49){
                index-=26;
            }
            char value = sentence[i];
            if(temp->children[index] == NULL){
                //if number not in current word string, add new node and shift to that node
                temp->children[index] = new Trienode(value);
                temp->children[index]->par = temp;
                temp = temp->children[index];
            }else{
                temp = temp->children[index];
            }
        }

        if(i == sentence.size()-1){
            if(temp->curr==NULL){
                temp->curr=new StorageNode(book_code,page,paragraph);
                temp->list=temp->curr;
            }
            else{
                if(temp->curr->paragraph!=paragraph || temp->curr->book_code!=book_code or temp->curr->page!=page){
                    temp->curr->right=new StorageNode(book_code,page,paragraph);
                    temp->curr=temp->curr->right;
                }          
            }
            temp->curr->freq++;
            temp->is_terminal = true;
            temp->count++;
            break;
        }
        i++;
    }
    return;
}

int Dict::get_word_count(string word){
    int i = 0;
    Trienode* temp = root;
    while(i < word.size()){
        int index;
        char value;
        
        if(word[i]>47 && word[i]<58){
            index = word[i]-'0' + 26;
            value = char(index-26+48);
        }else if((word[i]>64 && word[i]<91) || (word[i]>96 && word[i]<123)){
            index = (word[i]>90) ? word[i]-'a' : word[i]-'A';
            value = char(index+97);
        }else{
            index = word[i]+1;
            if(index>39){
                index-=3;
            }if(index>41){
                index-=3;
            }if(index>42){
                index-=12;
            }if(index>45){
                index-=29;
            }if(index>46){
                index-=1;
            }if(index>49){
                index-=26;
            }

            value = word[i];
        }

        if(temp->children[index] == NULL){
            return 0;
        }else{
            temp = temp->children[index];
        }
        
        //if the last letter of the word is a terminal in trie, return true
        if(i == word.size()-1){
            if(temp->is_terminal == true){
                return temp->count;
            }else{
                return 0;
            }
        }
        i++;
    }
    return -1;
}


StorageNode* Dict::get_word(string word){
    int i = 0;
    Trienode* temp = root;
    while(i < word.size()){
        int index;
        char value;
        
        if(word[i]>47 && word[i]<58){
            index = word[i]-'0' + 26;
            value = char(index-26+48);
        }else if((word[i]>64 && word[i]<91) || (word[i]>96 && word[i]<123)){
            index = (word[i]>90) ? word[i]-'a' : word[i]-'A';
            value = char(index+97);
        }else{
            index = word[i]+1;
            if(index>39){
                index-=3;
            }if(index>41){
                index-=3;
            }if(index>42){
                index-=12;
            }if(index>45){
                index-=29;
            }if(index>46){
                index-=1;
            }if(index>49){
                index-=26;
            }

            value = word[i];
        }

        if(temp->children[index] == NULL){
            return 0;
        }else{
            temp = temp->children[index];
        }
        
        //if the last letter of the word is a terminal in trie, return true
        if(i == word.size()-1){
            if(temp->is_terminal == true){
                return temp->list;
            }else{
                return NULL;
            }
        }
        i++;
    }
    return NULL;
}
