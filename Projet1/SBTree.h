#pragma once
#ifndef SBTREE_H
#define SBTREE_H

#include <math.h>
#include <iostream>
#include <string.h>

using namespace std;

class SBTree
{

	typedef struct {
		int data[0];
	} diskpage;

	typedef struct {
		
	} sbtree;

public:
	
	SBTree();
	SBTree(const string text, int maxlcp, int B);

	~SBTree();

private:
	int m_B; /* page size*/
	int m_b; /* each node in the tree contains b <= x <= 2b suffixes */
	int m_n; /* number of suffix*/
	int m_height; /* height of tree */
	int m_suffixSize; 
	int m_lcp;
	char* m_text;
	diskpage* m_root;

};

#endif // !SBTREE_H


