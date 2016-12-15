#include "BTree.h"


BTree::BTree()
{
}

BTree::BTree(int b)
{
	int index;
	m_b = b;
	m_data = new pair<int, string>[b];
	m_child = new BTree *[2];
	m_leaf = true;
	m_size = 0;
	for (index = 0; index < 2; ++index) {
		m_child[index] = 0;
	}
}


BTree::~BTree()
{
	release(m_root);
	
	
}

void BTree::parcours() {
	parcours(this->m_root);
}

void BTree::parcours(BTree * p)
{

	cout << endl;

	

	int index;

	if (p->m_leaf == false) {
		cout << "***";
		for (index = 0; index < p->m_size; ++index) {

			cout << " [" << p->m_data[index].first << ", " << p->m_data[index].second << "] ";

		}
		cout << "***" << endl;
		parcours(p->m_child[0]);
		parcours(p->m_child[1]);
	}
	else {
		for (index = 0; index < p->m_size; ++index) {

			cout << " [" << p->m_data[index].first << ", " << p->m_data[index].second << "] ";

		}
	}

	cout << endl;

}

void BTree::sort(pair<int, string>* p, int size)

{
	int i, j;
	pair<int, string> temp;
	for (i = 0; i < size; i++)
	{
		for (j = i; j <= size; j++)
		{
			if (!p[i].second.empty() && !p[j].second.empty()) {

				if (p[i].second.compare(p[j].second)>0)
				{
					temp.first = p[i].first;
					temp.second = p[i].second;
					p[i].first = p[j].first;
					p[i].second = p[j].second;
					p[j].first = temp.first;
					p[j].second = temp.second;
				}
			}
			else {
				throw logic_error("ERREUR fusion, Une valeur est mise à 0");
			}
		}
	}
}

bool BTree::searchDown(string word)
{
	BTree* current = m_root;
	while (!current->m_leaf) {
		if (word.compare(current->m_data[0].second) == 0) {
			while (!current->m_leaf) {
				current = current->m_child[0];
			}
			break;
		}
		else if (word.compare(current->m_data[3].second) == 0) {
			while (!current->m_leaf) {
				current = current->m_child[1];
			}
			break;
		}

		if ((word.compare(current->m_data[0].second) >= 0 || (word.at(0)== current->m_data[0].second.at(0))) && word.compare(current->m_data[1].second) <= 0 ) {
			current = current->m_child[0];
		}
		else if ((word.compare(current->m_data[2].second) >= 0 || (word.at(0) == current->m_data[2].second.at(0))) && word.compare(current->m_data[3].second) <= 0) {
			current = current->m_child[1];
		}
		else {
			return false;
		}
	}
	for (int i = 0; i < current->m_size; ++i) {
		std::size_t found = current->m_data[i].second.find(word);
		if (found != string::npos){
			cout << "Trouve ! " << word << " est la sous-chaine de [" << current->m_data[i].first << ", " << current->m_data[i].second << "]" << endl;
			return true;
		}
	}
	return false;
}

bool BTree::searchDownSuffix(string word)
{
	BTree* current = m_root;
	while(!current->m_leaf){
		if (word.compare(current->m_data[0].second) == 0) {
			while (!current->m_leaf) {
				current = current->m_child[0];
			}
			break;
		}
		else if (word.compare(current->m_data[3].second) == 0) {
			while (!current->m_leaf) {
				current = current->m_child[1];
			}
			break;
		}

		if (word.compare(current->m_data[0].second) >= 0 && word.compare(current->m_data[1].second) <= 0){
			current = current->m_child[0];
		}
		else if (word.compare(current->m_data[2].second) >= 0 && word.compare(current->m_data[3].second) <= 0) {
			current = current->m_child[1];
		}
		else {
			return false;
		}
	}
	for (int i = 0; i < current->m_size; ++i) {
		if (word.compare(current->m_data[i].second) == 0) {
			cout << "Trouve ! [" << current->m_data[i].first << ", " << current->m_data[i].second << "]" << endl;
			return true;
		}
	}
	return false;
}

pair<int, string> BTree::split_child(BTree *x, int i) {
	int j;
	pair<int, string>mid;
	BTree *part1, *part3, *y;
	part3 = new BTree(m_b);
	m_leaf=true;

	if (i == -1)
	{
			mid = x->m_data[(int)(m_b/2)];
			x->m_data[(int)(m_b/2)] = make_pair(0, "");
			x->m_size--;
			part1 = new BTree(m_b);
			part1->m_leaf = false;
			x->m_leaf = true;
			for (j = (int)(m_b / 2)+1; j < m_b; ++j) {
				part3->m_data[j - ((int)(m_b / 2))] = x->m_data[j];
				part3->m_child[j - ((int)(m_b / 2)+1)] = x->m_child[j];
				part3->m_size++;
				x->m_data[j] = make_pair(0, "");
				x->m_size--;
			}
			part3->m_data[0] = mid;
			part3->m_size++;
			for (j = 0; j < 2; ++j) {
				x->m_child[j] = NULL;
			}
		part1->m_data[0] = x->m_data[0];
		part1->m_data[1] = x->m_data[x->m_size-1];
		part1->m_data[2] = part3->m_data[0];
		part1->m_data[3] = part3->m_data[part3->m_size - 1];
		part1->m_child[0] = x;
		part1->m_child[1] = part3;
		part1->m_size++;
		part1->m_size++;
		part1->m_size++;
		part1->m_size++;

		if (x == m_root) {
			m_root = part1;
		}
		else {
			part1->m_part = x->m_part;
			if (part1->m_part->m_child[0] == x) {
				part1->m_part->m_child[0] = part1;
			}
			else {
				part1->m_part->m_child[1] = part1;
			}
		}
		x->m_part = part1;
		part3->m_part = part1;
		
	}
	else {

		if (x->m_child[0]->m_size >= m_b && x->m_child[1]->m_size >= m_b)
		{
			split_child(x->m_child[0],-1);
			split_child(x->m_child[1], -1);
			return mid;
		}
		y = x->m_child[i];
		if (i == 1) {
			x->m_child[0]->m_data[x->m_child[0]->m_size] = y->m_data[0];
			x->m_child[0]->m_size++;
			for (int i = 0; i < y->m_size-1; ++i) {
				y->m_data[i] = y->m_data[i + 1];
			}
			y->m_data[y->m_size-1] = make_pair(0, "");
			y->m_size--;

			x->m_data[0] = x->m_child[0]->m_data[0];
			x->m_data[1] = x->m_child[0]->m_data[x->m_child[0]->m_size - 1];
			x->m_data[2] = y->m_data[0];
			x->m_data[3] = y->m_data[y->m_size - 1];

		}

		else if (i == 0) {

			x->m_child[1]->m_size++;
			for (int i = x->m_child[1]->m_size - 2; i >= 0; --i) {
				x->m_child[1]->m_data[i+1] = x->m_child[1]->m_data[i];
			}
			x->m_child[1]->m_data[0] = y->m_data[y->m_size - 1];
			y->m_data[y->m_size - 1] = make_pair(0, "");
			y->m_size--;

			x->m_data[0] = y->m_data[0];
			x->m_data[1] = y->m_data[y->m_size - 1];
			x->m_data[2] = x->m_child[1]->m_data[0];
			x->m_data[3] = x->m_child[1]->m_data[x->m_child[1]->m_size - 1];

		};
	}
	return mid;

}

void BTree::release(BTree * p)
{
	int index;
	if (p->m_leaf == false) {
		delete p->m_data;
		release(p->m_child[0]);
		release(p->m_child[1]);
		delete p->m_child;
	}
	p->m_part = 0;
}

void BTree::insert(pair<int, string> a)
{
	int index;
	pair<int, string> temp;
	m_part = m_root;
	if (m_root == NULL)
	{
		m_root = new BTree(m_b);
		m_part = m_root;
	}
	else {
		if (m_part->m_leaf == true && m_part->m_size == m_b)
		{

			temp = split_child(m_part, -1);
			m_part = m_root;
			for (index = 0; index < m_part->m_size-1; index++) {
				if (!a.second.empty() && !m_part->m_data[index].second.empty() && !m_part->m_data[index + 1].second.empty()) {

				
					if ((a.second.compare(m_part->m_data[index].second)>=0) && (a.second.compare(m_part->m_data[index + 1].second)<0))
					{
						++index;
						break;
					}
					else if (a.second.compare(m_part->m_data[0].second)<0)
					{
						break;
					}
				}
				else {
					throw logic_error("ERREUR, insertion sur une feuille, Une valeur est mise à 0");
				}
			}

			if (index == 0) {
				m_part->m_data[0] = a;
			}
			else if (index-1 == m_part->m_child[(int)index / ((m_part->m_size / 2) + 1)]->m_size+1) {

				m_part->m_data[m_part->m_size-1] = a;
			}
			m_part = m_part->m_child[(int)index / ((m_part->m_size / 2)+1)];
		}
		else {

			while (m_part->m_leaf == false)
			{

				for (index = 0; index < m_part->m_size-1; ++index) {
					if (!a.second.empty() && !m_part->m_data[index].second.empty() && !m_part->m_data[index + 1].second.empty()) {

						if ((a.second.compare(m_part->m_data[index].second) >= 0) && (a.second.compare(m_part->m_data[index + 1].second) < 0))
						{
							++index;
							break;
						}
						else if (a.second.compare(m_part->m_data[0].second) < 0)
						{

							break;
						}
					}
					else {
						throw logic_error("ERREUR, insertion sur les enfants d'un noeud, Une valeur est mise à 0");
						
					}
				}
				//Attention on gère les enfants donc index / msize/2
				if (m_part->m_child[(int) index/ ((m_part->m_size/2)+1)]->m_size == m_b && m_part->m_child[(int)index / ((m_part->m_size / 2) + 1)]->m_leaf)
				{
					
					int i = (int)index / ((m_part->m_size / 2) + 1);
					
					if (!(m_part->m_child[0]->m_size == m_b && m_part->m_child[1]->m_size < m_b)) {
						temp = split_child(m_part, i);
					}
					else {
						if (a.second.compare(m_part->m_child[0]->m_data[m_part->m_child[0]->m_size - 1].second) < 0) {
							if (m_part->m_child[0]->m_leaf) {
								temp = split_child(m_part, i);
							}
						}
						else {
							m_part = m_part->m_child[1];
						}
					}

				}
				else {
					m_part = m_part->m_child[index / ((m_part->m_size / 2)+1)];
				}
			}
		}
	}
	//ajout de l'élément dans le bon cluster
	m_part->m_data[m_part->m_size] = a;
	//reorganisation du cluster
	sort(m_part->m_data, m_part->m_size);
	m_part->m_size++;
	BTree* temp2 = m_part;
	while (temp2 != m_root) {
		temp2 = temp2->m_part;
		BTree* x = temp2->m_child[0];
		BTree* part3 = temp2->m_child[1];
		temp2->m_data[0] = x->m_data[0];
		temp2->m_data[1] = x->m_data[x->m_size - 1];
		temp2->m_data[2] = part3->m_data[0];
		temp2->m_data[3] = part3->m_data[part3->m_size - 1];
	}
	
}
