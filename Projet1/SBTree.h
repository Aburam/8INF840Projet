#pragma once
#ifndef SBTREE_H
#define SBTREE_H

#include <math.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include "BTree.h"

using namespace std;

class SBTree
{

	typedef struct {
		int data[0];
	} diskpage;

	

public:
	
	SBTree();
	SBTree(const string text, int maxlcp, int B);

	~SBTree();

	void init(string text);

	void insert(string text);
	void display();

private:

	class Leaf {
		public:
			int index;
			const string suffix;
			Leaf(int i, const string suf) : index(i), suffix(suf) {}

	};

	int m_B; /* page size*/
	int m_b; /* each node in the tree contains b <= x <= 2b suffixes */
	int m_n; /* number of suffix*/
	int m_height; /* height of tree */
	int m_suffixSize; 
	int m_lcp;
	char* m_text;
	BTree* m_root;
	std::vector<Leaf*> m_nodes;

};

#endif // !SBTREE_H


