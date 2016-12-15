#include "SBTree.h"

static int pause = 0;


SBTree::SBTree() : m_n(0), m_B(0), m_b(0), m_suffixSize(0), m_lcp(0), m_height(0)
{
	
}
SBTree::SBTree(const string text, int maxlcp, int B)
{
	m_n = text.size();
	m_suffixSize = m_n + 1;
	m_lcp = maxlcp + 1;
	m_B = B;
	m_b = 4;
	m_height = (int) (log(m_n) / log(m_b) + 1);

	cout << "n = " << m_n << endl;
	cout << "suffixSize = " << m_suffixSize << endl;
	cout << "lcp = " << m_lcp << endl;
	cout << "b = " << m_b << endl;
	cout << "B = " << m_B << endl;
	cout << "height = " << m_height << endl;

	init(text);

	

}

SBTree::~SBTree()
{
}

void SBTree::init(string text)
{
	char* pointer = 0;
	istringstream iss(text);
	string word;
	int index = 0;
	m_root = new BTree(m_b);

	while (iss >> word) {
		index = text.find(word) + 1;
		string wordFixe = word;
		for (int i = 0; i < word.size(); ++i) {
			string pointer = &word[i];
			cout << index << ", " << pointer << endl;
			m_nodes.push_back(new Leaf(index, pointer));
			try {
				m_root->insert(make_pair(index, pointer));
			}
			catch (logic_error le) {
				cout << "Logic error: " << le.what() << endl;
			}
			

			++index;
		}
	}
	cout << "Parcours : " << endl;
	m_root->parcours();

	cout << "Fin Parcours" << endl;
}

void SBTree::insert(string text)
{
	int index = 0;
	istringstream iss(text);
	string word;
	while (iss >> word) {
		index = m_n+1+ text.find(word) + 1;
		string wordFixe = word;
		for (int i = 0; i < word.size(); ++i) {
			string pointer = &word[i];
			cout << index << ", " << pointer << endl;
			m_nodes.push_back(new Leaf(index, pointer));
			try {
				m_root->insert(make_pair(index, pointer));
			}
			catch (logic_error le) {
				cout << "Logic error: " << le.what() << endl;
			}


			++index;
		}
	}
	m_n = index-1;

}

void SBTree::display()
{
	m_root->parcours();
}

bool SBTree::seek(string word)
{
	bool ret = m_root->searchDown(word);
	if (!ret) {
		cout << ":( " << word << " non trouve..." << endl;
	}
	return ret;
}

bool SBTree::seekSuffix(string word)
{
	bool ret = m_root->searchDownSuffix(word);
	if (!ret) {
		cout << ":( " << word << " non trouve..." << endl;
	}
	return ret;
}
