//
// Created by emmas on 3/16/2025.
//
#include "DNode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DNode::DNode(){
  song = new Song();
  prev = NULL;
  next = NULL;
  }

DNode::DNode(string s, string a, int lenmin, int lensec){
    song = new Song(s, a, lenmin, lensec);
    next = NULL;
    prev = NULL;
    }