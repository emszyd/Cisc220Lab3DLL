
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
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
		DNode *n = new DNode (n, a, m, s);
        if (!first) {
          first = last = n;
          } else{
            last->next = n;
            n->prev = last;
            last = n;
        }
        numSongs++;
    }

	Song *DLL::pop() { //does what you'd think
		if (!last) return NULL;
        DNode *temp = last;
        last = last->prev;
        if (last) last->next = NULL;
        else first = NULL;
        numSongs--;
        Song *song = new Song(temp->title, temp->artist, temp->min, temp->sec);
        delete temp;
        return song;
        }

	void DLL::printList() {
          DNode *current = first;
          while (current){
            cout << current->title << ", " << current->artist << "..............." << current->min << ":";
            cout << (current->sec < 10 ? "0" : "") << current->sec << endl;
            current = current->next;
            }
	}

	void DLL::moveUp(string s) {
          DNode *current = first;
          while (current && current->title != s) {
            current = current->next;
            }
            if (!current || !current->prev) return;

            DNode *prevNode = current->prev;
            if (prevNode->prev) prevNode->prev->next = current;
            else first = current;

            current->prev = prevNode->prev;
            prevNode->next = current->next;
            if (current->next) current->next->prev = prevNode;
            else last = prevNode;

            current->next = prevNode;
            prevNode->prev = current;
	}

	void DLL::listDuration(int *tm, int *ts) {
          DNode *current = first;
          while (current){
            *tm += current->min;
            *ts += current->sec;
            current = current->next;
            }
	}
	void DLL::moveDown(string s) {
          DNode *current = first;
          while (current && current->title != s) {
            current = current->next;
            } if (!current || !current->next) return;

            DNode *nextNode = current->next;
            if (nextNode->next) nextNode->next->prev = current;
            else last = current;

            current->next = nextNode->next;
            nextNode->prev = current->prev;
            if (current->prev) current->prev->next = nextNode;
            else first = nextNode;

            current->prev = nextNode;
            nextNode->next = current;
			}
	void DLL::makeRandom() {
          srand(time(NULL));
          if (numSongs < 2) return;

          for (int i = 0; i < numSongs * 2; i++) {
            int swap1 = rand() % numSongs;
            int swap2 = rand() % numSongs;
            if (swap1 == swap2) continue;

            DNode *node1 = first;
            for (int j = 0; j < swap1; j++) node1 = node1->next;

            DNode *node2 = first;
            for (int j = 0; j < swap2; j++) node2 = node2->next;

            swap(node1->title, node2->title);
            swap(node1->artist, node2->artist);
            swap(node1->min, node2->min);
            swap(node1->sec, node2->sec);
          }
		}

	int DLL::remove(string s) {  
// note that the int returned is the index - this is standard for a remove, but we won't be using it.
    	DNode *current = first;
        while (current && current->title != s) {
          current = current->next
		}
                if (!current) return -1;
                if (current->prev) current->prev->next = current->next;
                else first = current->next;

                if (current->next) current->next->prev = current->prev;
                else last = current->prev;

                delete current;
                numSongs--;
                return 0;
       }

	DLL::~DLL(){
          while (first) {
            DNode *temp = first;
            first = first->next;
            delete temp;
          }
	}
