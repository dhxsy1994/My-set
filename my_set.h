 //
 /// @file    my_set2.h
 /// @author  hessen(dhxsy1994@gmail.com)
 /// @date    2018-10-09 19:45:50
 ///
#include "rb_tree.h"
template <class T>
class RB_Tree;//fore declearation

template <class T>
class RB_Node;



template <class T>
class my_set
{
	public:
		my_set();
		~my_set();

		void insert(T num);
		void remove(T num);
		bool find(T num);
		void print();
		T findmax();
		T findmin();
	private:
		RB_Tree<T>* tree;
};

template <class T>
my_set<T>::my_set():
tree(new RB_Tree<T>())	
{
	cout << "my_set() constructor"<<endl;
}

template <class T>
my_set<T>::~my_set()
{
	tree->~RB_Tree();
	cout << "~my_set()"<<endl;
}


template <class T>
void my_set<T>::insert(T num)
{
	tree->insert(num);	
	cout << "insert ok" <<endl ;
}

template <class T>
void my_set<T>::remove(T num)
{
	tree->remove(num);
	cout << "remove ok"<<endl;
}

template <class T>
bool my_set<T>::find(T num)
{
	RB_Node<T>* ret;
	ret = tree->search(num);
	if(ret == NULL)
	{
		return false;
	}
	else{
		return true;
	}

}
template <class T>
T my_set<T>::findmax()
{
	tree->max();
}

template <class T>
T my_set<T>::findmin()
{
	tree->min();
}

template <class T>
void my_set<T>::print()
{
	//preorder to output key;
	tree->inOrder();
	//can not -> to complete
}


