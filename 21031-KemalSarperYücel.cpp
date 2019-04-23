#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
struct ArrayNode
{
	ArrayNode(const int &xval=0, const string &theside="a", const int &building=0): x(xval),side(theside),b(building){}//Constructor
	int x;//x-coordinate
	string side;//l or r
	int b;//building number
};
template <class Comparable>
struct Node
{
	Comparable value;
	int label;

	Node(const Comparable &v = 0, const int &l = 0) :value(v), label(l) {}
};
template <class Comparable>
class ModifiedPQ	//This is the modified priority queue class described in the pdf
{
public:
	ModifiedPQ(unsigned int c = 100):heap(c+1),location(c+1),capacity(c),size(0){}//Constructor
	~ModifiedPQ<Comparable>()//Destructor
	{
		capacity = 0;
		size = 0;
	}
	bool isFull()
	{
		return capacity == size;
	}
	bool isEmpty()
	{
		return size == 0;
	}
	void insert(Comparable v,int l)
	{
		if (!isFull())
		{
			int hole = ++size;
			//Percolate up
			for (; hole > 1 && v > heap[hole / 2].value; hole /= 2)
			{
				heap[hole] = heap[hole / 2];
				location[heap[hole].label] = hole;	//Update the location
			}
			Node<Comparable> t(v, l);
			heap[hole] = t;//Create a new node at the give location
			location[l] = hole;//store the position of the node inside the location array, so that searching for a label takes O(1) time
		}
	}
	Comparable remove(const int &l)
	{
		int loc = location[l];
		Node<Comparable> temp = heap[loc];
		heap[loc] = heap[size--];
		location[heap[loc].label] = loc;
		percolateDown(loc);
		return temp.value;
	}
	Comparable getMax()const
	{
		return heap[1].value;
	}
	int getLabel(const int &pos)
	{
		return heap[1].label;
	}
private:
	void percolateDown(int hole)
	{
		int child;
		Node<Comparable> tmp = heap[hole];
		for (; hole * 2 <= size; hole = child)
		{
			child = hole * 2;
			if (child != size && heap[child].value < heap[child + 1].value)
				child++;//get the largest child
			if (heap[child].value > tmp.value)
			{
				heap[hole] = heap[child];
				location[heap[hole].label] = hole;
			}
			else
				break;
		}
		heap[hole] = tmp;
		location[tmp.label] = hole;
	}
	vector<Node<Comparable>> heap;
	vector<int> location;
	unsigned int capacity;
	unsigned int size;
};
bool compare(ArrayNode a, ArrayNode b) {
	return a.x < b.x;
}
void print(const vector<ArrayNode> &xvals, const vector<int> &yvals)
{
	ModifiedPQ<int> mpq(xvals.size());
	mpq.insert(0, 0);//create a 0-height building for the initial print
	int x = 0, prev = -1, iterator = 0, useless;
	while (iterator < xvals.size())
	{
		while (iterator<xvals.size() && (x == xvals[iterator].x) && (xvals[iterator].side == "l"))//edited//"iterator<xvals.size() &&" added tothe while loop
		{
			mpq.insert(yvals[xvals[iterator].b], xvals[iterator].b);
			iterator++;
		}
		while (iterator<xvals.size() && (x == xvals[iterator].x) && (xvals[iterator].side == "r"))//edited//"iterator<xvals.size() &&" added tothe while loop
		{
			useless = mpq.remove(xvals[iterator].b);
			iterator++;
		}
		if (prev != mpq.getMax())
		{
			prev = mpq.getMax();
			cout << x << " " << prev << endl;
		}
		x++;
	}
}
int main()
{
	ifstream in;
	in.open("input.txt");//edited//inputb.txt changed to input.txt
	int num, xl, xr, y;
	//Get input	
	in >> num;
	vector<ArrayNode> xcoors(num * 2);//array of size 2*numberOfBuildings
	vector<int> ycoors(num + 1);
	for (int i = 0; i < num; i++)
	{
		in >> xl;
		ArrayNode templ(xl, "l", (i + 1));
		xcoors[i] = templ;
		in >> y;
		ycoors[i + 1] = y;//store y coordinates in the array at the position of the building number
		in >> xr;
		ArrayNode tempr(xr, "r", (i  + 1));
		xcoors[num*2 - 1 - i] = tempr;
	}
	in.close();
	sort(xcoors.begin(),xcoors.end(),compare);//sort funtion of algorithm
	print(xcoors, ycoors);
	system("pause");
	return 0;
}