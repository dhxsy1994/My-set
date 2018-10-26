///
/// @file    my_set.h
/// @author  hessen(dhxsy1994@gmail.com)
///

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using namespace std;


enum RBTcolor{RED,BLACK};

template<class T>
class RB_Node
{
	public:
		RBTcolor color;
		T key;
		RB_Node* left;
		RB_Node* right;
		RB_Node* parent;


		RB_Node(T value, RBTcolor c, RB_Node *p, RB_Node *l, RB_Node *r):
		key(value),color(c),parent(),left(l),right(r) 
		{
		//cout << "node ok"<<endl;	
		}
};

template<class T>
class RB_Tree
{
	private:
		RB_Node<T> *mRoot;
	public:
		RB_Tree();
		~RB_Tree();

		void preOrder();//order output
		void inOrder();
		void postOrder();
		RB_Node<T>* search(T key);//search the key
		T min();//search the whole tree max and min
		T max();

		RB_Node<T>* successor(RB_Node<T>* x);//find the successor
		RB_Node<T>* predeccessor(RB_Node<T>* x);//find the predeccessor

		void insert(T key);
		void remove(T key);
		void destroy();
		void print();
	private:
		void preOrder(RB_Node<T>* tree) const;//three ways to output
		void inOrder(RB_Node<T>* tree) const;
		void postOrder(RB_Node<T>* tree) const;
		//rotate
		void leftRotate( RB_Node<T>* &root, RB_Node<T>* x);
		void rightRotate(RB_Node<T>* &root,RB_Node<T>* y);
		//inset,remove and fixup
		void insert(RB_Node<T>* &root,RB_Node<T>* node);
		void insertFixUp(RB_Node<T>* &root,RB_Node<T>* node);
		void remove(RB_Node<T>* &root, RB_Node<T> *node);	
		void removeFixUp(RB_Node<T>* &root, RB_Node<T> *node, RB_Node<T> *parent);
		//find the key in rbtree which the root is x
		RB_Node<T>* search(RB_Node<T>* x, T key) const;

		//find the min and max in tree or subtree	
		RB_Node<T>* min(RB_Node<T>* tree);
		RB_Node<T>* max(RB_Node<T>* tree);

		void destroy(RB_Node<T>* &tree);
		void print(RB_Node<T>* tree,T key,int direction);



#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do {(r)->color = BLACK; } while (0)
#define rb_set_red(r)  do {(r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do {(r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do {(r)->color = (c); } while (0)

};

	template <class T>
RB_Tree<T>::RB_Tree():mRoot(NULL)
{
	mRoot = NULL;
};//constructor

	template <class T>
RB_Tree<T>::~RB_Tree()
{
	destroy();
}

template <class T>
void RB_Tree<T>::preOrder(RB_Node<T>* tree) const
{
	if(tree != NULL)
	{
		cout << tree->key <<" ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template <class T>
void RB_Tree<T>::inOrder(RB_Node<T>* tree) const
{
	if(tree != NULL)
	{
		inOrder(tree->left);
		cout<< tree->key << " ";
		inOrder(tree->right);
	}

}
template <class T>
void RB_Tree<T>::postOrder(RB_Node<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout<< tree->key << " " ;
    }
}
template <class T>
void RB_Tree<T>::preOrder()
{
	preOrder(mRoot);
	cout<<endl;
}

template <class T>
void RB_Tree<T>::inOrder()
{
	inOrder(mRoot);
	cout<<endl;
}

template <class T>
void RB_Tree<T>::postOrder()
{
	postOrder(mRoot);
	cout<<endl;
}

template <class T>
RB_Node<T>* RB_Tree<T>::search(RB_Node<T>* x,T key )const
{
	if(x == NULL || x->key == key)
	{
		return x;
	}
	if(key < x->key)
	{
		return	search(x->left,key);
	}else
	{
		return search(x->right,key);
	}
}
	template <class T>
RB_Node<T>* RB_Tree<T>::search(T key)
{
	search(mRoot,key);
}

	template <class T>
RB_Node<T>* RB_Tree<T>::min(RB_Node<T>* tree)
{
	if(tree == NULL)
	{
		return NULL;
	}
	while(tree->left != NULL)
	{
		tree = tree->left;
	}
	//tree = new RB_Tree<T>();
	return tree;
}

	template <class T>
T RB_Tree<T>::min()
{
	RB_Node<T> *p = min(mRoot);
	if (p != NULL)
	{
		return p->key;
	}
	return (T)NULL;
}

	template <class T>
RB_Node<T>* RB_Tree<T>::max(RB_Node<T>* tree)
{
	if(tree == NULL)
	{
		return NULL;
	}
	while(tree->right != NULL)
	{
		tree = tree->right;
	}
	return tree;
}
	template <class T>
T RB_Tree<T>::max()
{
	RB_Node<T> *p = max(mRoot);
	if(p != NULL)
	{
		return p->key;
	}
	return (T)NULL;
}

	template <class T>
RB_Node<T>* RB_Tree<T>::successor(RB_Node<T> *x)
{
	if(x->right != NULL)
	{
		return min(x->right);
	}
	RB_Node<T>* y = x->parent;
	while ((y!=NULL) && (x==y->right))
	{

		x = y;
		y = y->parent;
	}
	return y;
}

	template <class T>
RB_Node<T>* RB_Tree<T>::predeccessor(RB_Node<T>* x)
{
	if(x->left != NULL)
	{
		return max(x->left);
	}
	RB_Node<T>*y = x->parent;
	while((y!= NULL) &&(x == y->left))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

	template <class T>
void RB_Tree<T>::leftRotate(RB_Node<T>* &root, RB_Node<T>* x)
{

	//设置x的右孩子为y
	RB_Node<T> *y = x->right;

	// 将 “y的左孩子” 设为 “x的右孩子”；
	// 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// 将 “x的父亲” 设为 “y的父亲”
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
	}
	else
	{

		if (x->parent->left == x)
			x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
		else
			x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
	}

	// 将 “x” 设为 “y的左孩子”
	y->left = x;
	// 将 “x的父节点” 设为 “y”
	x->parent = y;

}

	template <class T>
void RB_Tree<T>::rightRotate(RB_Node<T>* &root, RB_Node<T>* y)
{

	// 设置x是当前节点的左孩子。
	RB_Node<T> *x = y->left;

	// 将 “x的右孩子” 设为 “y的左孩子”；
	// 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// 将 “y的父亲” 设为 “x的父亲”
	x->parent = y->parent;

	if (y->parent == NULL) 
	{

		root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点

	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
		else
			y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
	}

	// 将 “y” 设为 “x的右孩子”
	x->right = y;

	// 将 “y的父节点” 设为 “x”
	y->parent = x;

}

	template <class T>
void RB_Tree<T>::insert(RB_Node<T>* &root, RB_Node<T>* node)
{

	RB_Node<T> *y = NULL;
	RB_Node<T> *x = root;

	// 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
	while (x != NULL)
	{

		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;

	}

	node->parent = y;
	if (y!=NULL)
	{

		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;

	}
	else
		root = node;

	// 2. 设置节点的颜色为红色
	node->color = RED;

	// 3. 将它重新修正为一颗二叉查找树
	insertFixUp(root, node);

}


	template <class T>
void RB_Tree<T>::insertFixUp(RB_Node<T>* &root, RB_Node<T>* node)
{

	RB_Node<T> *parent, *gparent;

	// 若“父节点存在，并且父节点的颜色是红色”
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{

		gparent = rb_parent(parent);

		//若“父节点”是“祖父节点的左孩子”
		if (parent == gparent->left)
		{

			// Case 1条件：叔叔节点是红色
			{

				RB_Node<T> *uncle = gparent->right;
				if (uncle && rb_is_red(uncle))
				{

					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;

				}

			}

			// Case 2条件：叔叔是黑色，且当前节点是右孩子
			if (parent->right == node)
			{

				RB_Node<T> *tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;

			}

			// Case 3条件：叔叔是黑色，且当前节点是左孩子。
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);

		} 
		else//若“z的父节点”是“z的祖父节点的右孩子”
		{

			// Case 1条件：叔叔节点是红色
			{

				RB_Node<T> *uncle = gparent->left;
				if (uncle && rb_is_red(uncle))
				{

					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;

				}

			}

			// Case 2条件：叔叔是黑色，且当前节点是左孩子
			if (parent->left == node)
			{

				RB_Node<T> *tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;

			}

			// Case 3条件：叔叔是黑色，且当前节点是右孩子。
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);

		}

	}
	// 将根节点设为黑色
	rb_set_black(root);

}

	template <class T>
void RB_Tree<T>::insert(T key)
{

	RB_Node<T> *z=NULL;

	// 如果新建结点失败，则返回。
	if ((z=new RB_Node<T>(key,BLACK,NULL,NULL,NULL)) == NULL)
		return ;

	insert(mRoot, z);

}

	template <class T>
void RB_Tree<T>::remove(RB_Node<T>* &root, RB_Node<T> *node)
{

	RB_Node<T> *child, *parent;
	RBTcolor color;

	// 被删除节点的"左右孩子都不为空"的情况。
	if ( (node->left!=NULL) && (node->right!=NULL) ) 
	{

		// 被删节点的后继节点。(称为"取代节点")
		// 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
		RB_Node<T> *replace = node;

		// 获取后继节点
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node节点"不是根节点(只有根节点不存在父节点)
		if (rb_parent(node))
		{

			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;

		} 
		else 
			// "node节点"是根节点，更新根节点。
			root = replace;

		// child是"取代节点"的右孩子，也是需要"调整的节点"。
		// "取代节点"肯定不存在左孩子！因为它是一个后继节点。
		child = replace->right;
		parent = rb_parent(replace);
		// 保存"取代节点"的颜色
		color = rb_color(replace);

		// "被删除节点"是"它的后继节点的父节点"
		if (parent == node)
		{

			parent = replace;

		} 
		else
		{

			// child不为空
			if (child)
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);

		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		return ;

	}

	if (node->left !=NULL)
		child = node->left;
	else 
		child = node->right;

	parent = node->parent;
	// 保存"取代节点"的颜色
	color = node->color;

	if (child)
		child->parent = parent;

	// "node节点"不是根节点
	if (parent)
	{

		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;

	}
	else
		root = child;

	if (color == BLACK)
		removeFixUp(root, child, parent);
	delete node;

}

template <class T>
void RB_Tree<T>::removeFixUp(RB_Node<T>* &root, RB_Node<T> *node, RB_Node<T> *parent)
{
    RB_Node<T> *other;

    while ((!node || rb_is_black(node)) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                leftRotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rightRotate(root, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                rightRotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    leftRotate(root, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

template <class T>
void RB_Tree<T>::remove(T key)
{
    RB_Node<T> *node; 

    // 查找key对应的节点(node)，找到的话就删除该节点
    if ((node = search(mRoot, key)) != NULL)
        remove(mRoot, node);
}

template <class T>
void RB_Tree<T>::destroy(RB_Node<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree=NULL;
}

template <class T>
void RB_Tree<T>::destroy()
{
    destroy(mRoot);
}




template <class T>
void RB_Tree<T>::print(RB_Node<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            cout << std::setw(2) << tree->key << "(B) is root" << endl;
        else                // tree是分支节点
            cout << std::setw(2) << tree->key <<  (rb_is_red(tree)?"(R)":"(B)") << " is " << std::setw(2) << key << "'s "  << std::setw(12) << (direction==1?"right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <class T>
void RB_Tree<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}











