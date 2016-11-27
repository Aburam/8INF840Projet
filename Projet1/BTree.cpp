#include "BTree.h"



BTree::BTree()
{
	int index;
	m_data = new int[5];
	m_child = new BTree *[6];
	m_leaf = true;
	m_size = 0;
	for (index = 0; index < 6; ++index) {
		m_child[index] = 0;
	}
}


BTree::~BTree()
{
}

void BTree::parcours(BTree * p)
{
	cout << endl;
	int index;
	for (index = 0; index < m_size; ++index) {
		if (m_leaf == false) {
			parcours(p->m_child[index]);
		}
		cout << " " << p->m_data[index];

	}
	if (p->m_leaf == false) {
		parcours(p->m_child[index]);
	}
	cout << endl;

}

void BTree::sort(int * p, int size)
{
	int i, j, temp;
	for (i = 0; i < size; i++)
	{
		for (j = i; j <= size; j++)
		{
			if (p[i] > p[j])
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}

}

int BTree::split_child(BTree *x, int i) {
	int j, mid;
	BTree *part1, *part3, *y;
	part3 = new BTree();
	if (i == -1)
	{
		mid = x->m_data[2];
		x->m_data[2] = 0;
		x->m_size--;
		part1 = new BTree();
		part1->m_leaf = false;
		x->m_leaf = true;
		for (j = 3; j < 5; ++j) {
			part3->m_data[j - 3] = x->m_data[j];
			part3->m_child[j - 3] = x->m_child[j];
			part3->m_size++;
			x->m_data[j] = 0;
			x->m_size--;
		}
		for (j = 0; j < 6; ++j) {
			x->m_child[j] = NULL;
		}
		part1->m_data[0] = mid;
		part1->m_child[part1->m_size] = x;
		part1->m_child[part1->m_size + 1] = part3;
		part1->m_size++;
		m_root = part1;
	}
	else {
		y = x->m_child[i];
		mid = y->m_data[2];
		y->m_data[2] = 0;
		y->m_size--;
		for (j = 3;j < 5;j++) {
			part3->m_data[j - 3] = x->m_data[j];
			part3->m_size++;
			y->m_data[j] = 0;
			y->m_size--;
		}
		x->m_child[i + 1] = y;
		x->m_child[i + 1] = part3;
	}
	return mid;

}

void BTree::insert(int a)
{
	int index, temp;
	m_part = m_root;
	if (m_root == NULL)
	{
		m_root = new BTree();
		m_part = m_root;
	}
	else {
		if (m_part->m_leaf == true && m_part->m_size == 5)
		{
			temp = split_child(m_part, -1);
			m_part = m_root;
			for (index = 0; index < (m_part->m_size); index++) {
				if ((a > m_part->m_data[index]) && (a < m_part->m_data[index + 1]))
				{
					++index;
					break;
				}
				else if (a < m_part->m_data[0])
				{
					break;
				}
			}
			m_part = m_part->m_child[index];
		}
		else {
			while (m_part->m_leaf == false)
			{
				for (index = 0; index < (m_part->m_size); ++index) {
					if ((a>m_part->m_data[index]) && (a <m_part->m_data[index+1]))
					{
						++index;
						break;
					}
					else if (a < m_part->m_data[0])
					{
						break;
					}
				}
				if (m_part->m_child[index]->m_size == 5)
				{
					temp = split_child(m_part, index);
					m_part->m_data[m_part->m_size] = temp;
					m_part->m_size++;
				}
				else {
					m_part = m_part->m_child[index];
				}
			}
		}
	}
	//ajout de l'élément dans le bon cluster
	m_part->m_data[m_part->m_size] = a;
	//reorganisation du cluster
	sort(m_part->m_data, m_part->m_size);
	m_part->m_size++;
}
