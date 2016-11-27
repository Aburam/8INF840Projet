#pragma once
#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;
class BTree
{
public:
	BTree();
	BTree();

	void parcours(BTree* p);

	void sort(int* p, int size);

	int split_child(BTree * x, int i);

	void insert(int a);
	

private:
		

	int* m_data;
	bool m_leaf;
	int m_size;
	BTree** m_child;
	BTree* m_root;
	BTree* m_part;

};

#endif // !BTREE
