#include "BTree.h"

static int pause = 0;

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
		cout << "FILS GAUCHE : Taille : " << x->m_size << endl;
		part3->m_part = part1;
		cout << "FILS DROIT : Taille : " << part3->m_size << endl;
		cout << "Pere : Taille : " << part1->m_size << endl;
		
		
	}
	else {

		cout << "SIZE0" << x->m_child[0]->m_size << endl;
		cout << "SIZE1" << x->m_child[1]->m_size << endl;
		if (x->m_child[0]->m_size >= m_b && x->m_child[1]->m_size >= m_b)
		{
			cout << "ICI" << endl;
			split_child(x->m_child[0],-1);
			split_child(x->m_child[1], -1);
			return mid;
		}
		cout << "que faisons nous la, i ?" << i << endl;
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
			/*cout << "3y : " << y->m_data[3].first << endl;
			cout << " 0w: " << x->m_child[1]->m_data[0].first << endl;

			y->m_data[y->m_size-1]= x->m_child[1]->m_data[0];
			y->m_size++;
			cout << "Taille y : " << y->m_size << endl;

			for (int i = 0; i < x->m_child[1]->m_size-1; ++i) {
				x->m_child[1]->m_data[i] = x->m_child[1]->m_data[i + 1];
			}
			x->m_child[1]->m_data[x->m_child[1]->m_size - 1] = make_pair(0, "");
			x->m_child[1]->m_size--;
			*/
			x->m_data[0] = y->m_data[0];
			cout << "0 : " << x->m_data[0].first << endl;
			x->m_data[1] = y->m_data[y->m_size - 1];
			cout << "1 : " << x->m_data[1].first << endl;
			x->m_data[2] = x->m_child[1]->m_data[0];
			cout << "2 : " << x->m_data[2].first << endl;
			x->m_data[3] = x->m_child[1]->m_data[x->m_child[1]->m_size - 1];
			cout << "3 : " << x->m_data[3].first << endl;


		};
	}
	return mid;

}

void BTree::insert(pair<int, string> a)
{
	cout << "IN INSERT" << endl;
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

				for (index = 0; index < m_part->m_size-1; ++index) {
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
				if (m_part->m_child[(int) index/ ((m_part->m_size/2)+1)]->m_size == m_b && m_part->m_child[(int)index / ((m_part->m_size / 2) + 1)]->m_leaf)
				{
					pause++;
					if (pause == 7) {
						cout << "PAUSE" << endl;
						system("pause");
					}
						
					cout << "RAPPEL, i :" << (int)index / ((m_part->m_size / 2) + 1) << endl;
					temp = split_child(m_part, (int)index / ((m_part->m_size / 2) + 1));
				//	m_part->m_data[m_part->m_size-1] = temp;
					//m_part->m_size++;

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
