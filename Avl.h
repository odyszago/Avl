#ifndef AVL_H
#define AVL_H
#include <iostream>

struct node;

class Avl{
	public:
		bool insert(int);
		bool remove(int);
	    node* search(int);
	    void inorder(node *,char *);
       	void closeEverything();
		void dispalyMe();
		node *root = NULL;

	private:

        void inorder2(node *,int&);
		void  display(node *,int);
	    node* binSearch(int,node *);
		int   balanceFactor(node *);
		int   getHeight(node *);
		void  balance(node *);
		int   getBalance(node *);
		void  balanceDelete(node *);
		node* makeRotation(node *);
		node* rightRotation(node *);
		node* leftRotation(node *);
		node* right_leftRotation(node *);
		node* left_rightRotation(node *);
		void  rotateFixHeights(node *,node *,node *);
		bool  checkNull(node *);
		void closefile();

};

struct  node
{
    node *prev;
    int  url;
    node *left;
    node *right;
    int  height;
    Avl  *subAvl;
    //Initialize default values
    node():prev(NULL),left(NULL),right(NULL),url(-1),height(0),subAvl(NULL) {}
};


#endif // AVL_H
