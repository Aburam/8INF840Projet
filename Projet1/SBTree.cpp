#include "SBTree.h"



using namespace std;
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


}

SBTree::~SBTree()
{
}
