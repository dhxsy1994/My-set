 ///
 /// @file    my_set.cc
 /// @author  hessen(dhxsy1994@gmail.com)
 ///
 
#include <iostream>
#include "my_set.h"
using std::cout;
using std::endl;


int main()
{
	int a[] = {1,9,8,10,4,100,20,30,12,15};
	int len = sizeof(a)/sizeof(a[0]);
	//test the rbtree
/*	RB_Tree<int>* tree = new RB_Tree<int>();
	for(int i =0;i < len;i++)
	{
		tree->insert(a[i]);
		cout << "==add int :" <<a[i]<<endl;
		cout << "==the tree is: "<<endl;
		tree->print();
	}
*/

	my_set<int> set;
	cout << "ins 100";
	set.insert(100);
	cout << "ins 5";
	set.insert(5);
	cout << "ins 7";
	set.insert(7);
	cout << "ins 10";
	set.insert(10);
	cout << "ins 66";
	set.insert(66);

	set.print();

	cout << "max is "<<set.findmax() <<endl;
	
	cout << "min is "<< set.findmin()<<endl;
	cout <<"remove 5";
	set.remove(5);

	set.print();
}
