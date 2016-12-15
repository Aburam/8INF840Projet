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
}

void BTree::parcours() {
	cout << m_root->m_size << endl;
	parcours(this->m_root);
}

void BTree::parcours(BTree * p)
{

	cout << endl;

	

	int index;

	if (p->m_leaf == false) {
		cout << "NOEUD PARENT :";
		for (index = 0; index < p->m_size; ++index) {

			cout << " [" << p->m_data[index].first << ", " << p->m_data[index].second << "] ";

		}
		cout << "FIN NOEUD PARENT" << endl;
		parcours(p->m_child[0]);
		parcours(p->m_child[1]);
	}
	else {
		for (index = 0; index < p->m_size; ++index) {

			cout << " [" << p->m_data[index].first << ", " << p->m_data[index].second << "] ";

		}
	}

	
	if (p->m_leaf == false) {
		
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

			
				cout << "TEST1 : pi : " << i << p[i].second << "pj: " << p[j].second << endl;

				if (p[i].second.compare(p[j].second)>0)
				{
					cout << "TEST2 : pi : " <<p[i].second << "pj: " << p[j].second << endl;
					temp.first = p[i].first;
					temp.second = p[i].second;
					p[i].first = p[j].first;
					p[i].second = p[j].second;
					p[j].first = temp.first;
					p[j].second = temp.second;
				}
			}
			else {
				cout << "ERREUR 33333333 !!!!!!!!" << endl;
			}
		}
	}

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

		/*for (int i = 0; i < m_b; ++i) {

		}
		part1->m_data[0] = part1->m_child[0]->m_data[0];
		part1->m_data[1] = part1->m_child[0]->m_data[m_b-1];
		part1->m_data[2] = part1->m_child[1]->m_data[0];
		part1->m_data[3] = part1->m_child[1]->m_data[m_b-1];*/
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

		m_root = part1;
	}
	else {
		cout << "que faisons nous la, i ?" << i << endl;
		y = x->m_child[i];
		mid = y->m_data[(int)(m_b / 2)];
		y->m_data[(int)(m_b / 2)] = make_pair(0, "");
		y->m_size--;
		for (j = (int)(m_b / 2)+1;j < m_b;j++) {
			part3->m_data[j - ((int)(m_b / 2)+1)] = x->m_data[j];
			part3->m_size++;
			y->m_data[j] = make_pair(0, "");
			y->m_size--;
		}
		x->m_child[i + 1] = y;
		x->m_child[i + 1] = part3;
	}
	return mid;

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
			cout << "On doit etre la ????????? " << temp.first << endl;

			m_part = m_root;
			for (index = 0; index < m_part->m_size; index++) {
				if (!a.second.empty() && !m_part->m_data[index].second.empty() && !m_part->m_data[index + 1].second.empty()) {

				
					if ((a.second.compare(m_part->m_data[index].second)>0) && (a.second.compare(m_part->m_data[index + 1].second)<0))
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
					cout << "ERREUR !!!!!!!!!!" << endl;
				}
			}

			cout << "Calcul : "  << index / ((m_part->m_size / 2)+1) << endl;
			cout << "INDEX: " << index << endl;

			cout << "TAILLE ENFANT:"<<m_part->m_child[(int)index / ((m_part->m_size / 2) + 1)]->m_size + 1 << endl;

			if (index == 0) {
				cout << "NOON!" << endl;

				m_part->m_data[0] = a;
			}
			else if (index-1 == m_part->m_child[(int)index / ((m_part->m_size / 2) + 1)]->m_size+1) {
				cout << "OOUI!" << endl;

				m_part->m_data[m_part->m_size-1] = a;
			}
			m_part = m_part->m_child[(int)index / ((m_part->m_size / 2)+1)];
			cout << "EST-CE la bonne ? " << m_part->m_data[0].first << endl;
		}
		else {

			while (m_part->m_leaf == false)
			{

				for (index = 0; index < m_part->m_size; ++index) {
					if (!a.second.empty() && !m_part->m_data[index].second.empty() && !m_part->m_data[index + 1].second.empty()) {


						if ((a.second.compare(m_part->m_data[index].second) > 0) && (a.second.compare(m_part->m_data[index + 1].second) < 0))
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
						cout << "ERREUR 222222 !!!!!!!!!!" << endl;
					}
				}
				//Attention on gère les enfants donc index / msize/2
				if (m_part->m_child[(int) index/ ((m_part->m_size/2)+1)]->m_size == m_b)
				{
					temp = split_child(m_part, (int)index / ((m_part->m_size / 2) + 1));
					m_part->m_data[m_part->m_size-1] = temp;
					m_part->m_size++;

				}
				else {
					m_part = m_part->m_child[index / ((m_part->m_size / 2)+1)];
					cout << "On doit etre la parmi plein" << endl;
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
