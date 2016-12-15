#pragma once
#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <exception>


using namespace std;
class BTree
{
public:
	BTree();
	BTree(int b);
	~BTree();

	void parcours();

	void parcours(BTree* p);

	void sort(pair<int, string>* p, int size);

	bool searchDown(string word);

	bool searchDownSuffix(string word);

	void insert(pair<int, string> a);

	void release(BTree* p);


private:

	pair<int, string> split_child(BTree * x, int i);

		
	int m_b;
	pair<int, string>* m_data;
	bool m_leaf;
	int m_size;
	BTree** m_child;
	BTree* m_root;
	BTree* m_part;

};

#endif // !BTREE
