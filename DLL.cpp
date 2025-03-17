
#include "DNode.hpp"
#include "DLL.hpp"
#include "Song.hpp"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//Check Playlist.cpp for instructions of what to write here and how to test it


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numSongs = 0;
	}
	DLL::DLL(string t, string l, int m, int s){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,l,m,s);
		first = n;
		last = n;
		numSongs=1;
	}
	void DLL::push(string n, string a, int m, int s) {  // does what you'd think
		DNode *newNode = new DNode (n, a, m, s);
        if (numSongs == 0) {
          first = newNode;
          last = first;
          } else{
            newNode->prev = last;
          	last->next = newNode;
            last = newNode;
        }
        numSongs++;
    }

	Song *DLL::pop() { //does what you'd think
        DNode *temp = last;
		Song *song = temp->song;
        last = last->prev;
		delete temp;
		last->next = NULL;
		numSongs--;
		return song;
        }

	void DLL::printList() {
          DNode *current = first;
          while (current != NULL){
            cout << current->song->title << ", " << current->song->artist << "..............." << current->song->min << ":";
            cout << (current->song->sec < 10 ? "0" : "") << current->song->sec << endl;
            current = current->next;
          }
	}

	void DLL::moveUp(string t) {
          DNode *current = first;
          while (current && current->song->title != t) {
            current = current->next;
            }
            //if nothings found or its already at the front, do nothing
            if (!current || !current->prev) return;

            DNode *prevNode = current->prev;
            DNode *prevPrev = prevNode->prev;
            DNode *nextNode = current->next;

            //if current was second then update the first ptr
            if (!prevPrev) {
              first = current;
            } else {
              prevPrev->next = current;
            }

            //if current was last then update last ptr
            if (!nextNode) {
              last = prevNode;
            } else {
              nextNode->prev = prevNode;
            }

            //swap positions
            current->prev = prevPrev;
            prevNode->next = nextNode;
			prevNode->prev = current;
			current->next = prevNode;
	}

	void DLL::listDuration(int *tm, int *ts) {
          DNode *current = first;
          while (current != NULL){
            //sums total seconds and minutes
            *tm += current->song->min;
            *ts += current->song->sec;
            //moves to the next song
            current = current->next;
            }
	}
	void DLL::moveDown(string t) {
          DNode *current = first;
          //find the node with the given title
          while (current && current->song->title != t) {
            current = current->next;
            }
            //if not found or is last then do nothing
            if (!current || !current->next) return;

            DNode *nextNode = current->next;
            DNode *nextNext = nextNode->next;
            DNode *prevNode = current->prev;

            if (!prevNode) {
              first = nextNode;
            }else{
              prevNode->next = nextNode;
            }

            if (!nextNext) {
              last = current;
            } else {
              nextNext->prev = current;
            }

            current->next = nextNext;
            current->prev = nextNode;
            nextNode->prev = prevNode;
            nextNode->next = current;
			}

   //shuffles songs in a random order
	void DLL::makeRandom() {

          srand(time(NULL));

          for (int i = 0; i < numSongs * 2; i++) { //shuffles multiple times
            int swap1 = rand() % numSongs;
            int swap2 = rand() % numSongs;
            if (swap1 == swap2) continue; //if same index, swapping stops

            //finds the two nodes at swap1 and swap2
            DNode *node1 = first;
            for (int j = 0; j < swap1; j++) node1 = node1->next;

            DNode *node2 = first;
            for (int j = 0; j < swap2; j++) node2 = node2->next;

            swap(node1->song, node2->song);

          }
		}

	int DLL::remove(string t) {
// note that the int returned is the index - this is standard for a remove, but we won't be using it.
    	DNode *current = first;
        int x=0;
        while (current != NULL && x==0) {
          if (current->song->title == t) {
            if (current == last){
              if (current->song->sec <10){
                cout << "Taking out:" <<current->song->title << ", " <<current->song->artist << ".............." << current->song->min<< ":0" << current->song->sec << endl;
          } else{
          	cout << "Taking out:" << current->song->title << ", " << current->song->artist << ".............." << current->song->min<< ":" << current->song->sec << endl;
          }
          pop();
          x=1;
		} else if (current==first){
                  if (current->song->sec <10){
                  	cout << "Taking out:" <<current->song->title << ", " <<current->song->artist << ".............." << current->song->min<< ":0" << current->song->sec << endl;
                  } else{
                  	cout << "Taking out:" << current->song->title << ", " << current->song->artist << ".............." << current->song->min<< ":" << current->song->sec << endl;
                  }
                  first=current->next;
                  x=1;
                  } else{
                    if (current->song->sec <10){
                    	cout << "Taking out:" <<current->song->title << ", " <<current->song->artist << ".............." << current->song->min<< ":0" << current->song->sec << endl;
                    } else{
                    	cout << "Taking out:" << current->song->title << ", " << current->song->artist << ".............." << current->song->min<< ":" << current->song->sec << endl;
                    }
                    current->prev->next=current->next;
                    current->next->prev=current->prev;
                    x=1;
                    }
                    }
                    else{
                      current = current->next;
                      }
       }
       delete current;
       return x;
       }


	DLL::~DLL(){
          DNode *current = first;
          DNode *next;

          while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
          }
          last = NULL;
          first = NULL;
          numSongs = 0;
	}
