#include <iostream>
#include <vld.h> //检测内存泄漏，可以去掉
using namespace std;

struct Node
{
	int data;
	Node* next;
	Node(int data) :data(data), next(nullptr) {}
};

class HashTable
{
public:
	HashTable();
	~HashTable();
	void insert(int insertData);
	Node* Find(int findData);
	bool del(int deldata);
private:
	Node* createNode(int insertData);
private:
	Node* p[10][10][10];
};

HashTable::HashTable()
{
	memset(p, NULL, sizeof(p));
}

HashTable::~HashTable()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (p[i][j][k])
				{
					delete p[i][j][k];
					p[i][j][k] = nullptr;
				}
			}
		}
	}
}

void HashTable::insert(int insertData)
{
	int bai = insertData / 100 % 10;
	int shi = insertData / 10 % 10;
	int ge = insertData % 10;

	//p[bai][shi][ge] = Node;
	Node* pNew = createNode(insertData);
	if (pNew == nullptr)
	{
		cout << "PNew为空!\n";
		return;
	}
	if (p[bai][shi][ge])
	{
		//寻找插入位置
		auto temp = p[bai][shi][ge];
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = pNew;
	}
	else//如果为NULL
	{
		p[bai][shi][ge] = pNew;
	}
}

Node* HashTable::Find(int findData)
{
	int bai = findData / 100 % 10;
	int shi = findData / 10 % 10;
	int ge = findData % 10;

	auto FNode = p[bai][shi][ge];
	while (FNode)
	{
		if (FNode->data == findData) return FNode;
		FNode = FNode->next;
	}
	return FNode;
}


bool HashTable::del(int deldata)
{
	int bai = deldata / 100 % 10;
	int shi = deldata / 10 % 10;
	int ge = deldata % 10;

	Node* pDel = p[bai][shi][ge];//当前要删除的节点
	Node* parent = nullptr;	//删除所需要的父节点
	while (pDel)
	{
		if (pDel->data == deldata) break;
		parent = pDel;
		pDel = pDel->next;
	}
	if (pDel == nullptr)
	{
		//没有找到
		return false;
	}
	if (pDel == p[bai][shi][ge])
	{
		//要删除的是根节点
		p[bai][shi][ge] = pDel->next;
		delete pDel;
		pDel = nullptr;
		return true;
	}
	//要删除的不是根节点
	parent->next = pDel->next;
	delete pDel;
	pDel = nullptr;
	return true;
}

Node* HashTable::createNode(int insertData)
{
	Node* pNew = new Node{ insertData };
	return pNew;
}

int main()
{
	HashTable h;
	int arr[] = { 125,654,987,165,666,888,1165,2165 };
	for (auto beg = begin(arr); beg != end(arr); beg++)
	{
		h.insert(*beg);
	}
	cout << "Find 125:" << h.Find(125)->data << endl;
	cout << "Find 654:" << h.Find(654)->data << endl;
	cout << "Find 165:" << h.Find(165)->data << endl;
	cout << "Find 666:" << h.Find(666)->data << endl;
	cout << "Find 1165:" << h.Find(1165)->data << endl;
	//cout << "Find 9999:" << h.Find(9999)->data << endl;
	h.del(125);
	h.del(165);
	h.del(888);
	h.del(2165);

	return 0;
}