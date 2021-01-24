#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;
	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

int LargestSum(Node* pRoot)
{
	if (!pRoot) {return 0;}
	int R_Side = LargestSum(pRoot->pRight);
	int L_Side = LargestSum(pRoot->pLeft);
	return (max(R_Side + pRoot->i, L_Side + pRoot->i));
}

vector<int> holder;

bool PathOfLargestSum(Node* pRoot, int sum)
{
	if (sum == 0) {return true;}
	if (!pRoot) {return false;}
	bool R_Side = PathOfLargestSum(pRoot->pRight, sum - pRoot->i);
	bool L_Side = PathOfLargestSum(pRoot->pLeft, sum - pRoot->i);
	if (R_Side || L_Side){
		holder.push_back(pRoot->i);
	}
	return (R_Side || L_Side);
}


void PrintMaximumSumAndItsPath(Node* pRoot) {

	cout << "Branch with the largest sum is: ";
	PathOfLargestSum(pRoot, LargestSum(pRoot));

	for (int a = holder.size() - 1; a>=0 ; a-- ) {
		cout << holder[a] <<" ";
	}
	cout << " -> SUM = " << LargestSum(pRoot) ;
}

void main()
{
	int i;
	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}
	PrintTree(pRoot, 1);
	PrintMaximumSumAndItsPath(pRoot);
}