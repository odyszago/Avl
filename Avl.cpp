#include "Avl.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
#define max(a,b) (a < b ? b : a)
ofstream myfile;

bool Avl::insert(int input)
{
    //Create new node or root
    node *existed_node;
    node *newNode;
    newNode = new node;

    if (root != NULL)
    {
        //Find where to put the new node
        existed_node = binSearch(input,root);

        if (existed_node == NULL)
        {
            return false;
        }

        newNode->prev = existed_node;
        newNode->url  = input;
        if (existed_node->url < input)
        {
            existed_node->right =  newNode;
        }
        else
        {
            existed_node->left  =  newNode;
        }
        balance(newNode->prev);
    }
    else
    {
        root = newNode;
        root->url = input;
    }
    return true;
}

node* Avl::binSearch(int input, node *root)
{
    while (1)
    {
        if (root->url == input)
            return NULL;
        else if (root->left == NULL && root->url > input)
            return root;
        else if(root->right == NULL && root->url < input)
            return root;
        else
        {
            if (root->url > input)
                root = root->left;
            else
                root = root->right;
        }
    }
}

void Avl::balance(node *currentNode)
{
    while (currentNode != NULL)
    {
        if ((checkNull(currentNode->right) ? currentNode->right->height + 1 : 0) > currentNode->height ||
                (checkNull(currentNode->left)  ? currentNode->left->height + 1 : 0) > currentNode->height
           )
            currentNode->height += 1;

        if (abs(balanceFactor(currentNode))  >= 2)
        {
            if (currentNode == root)
                root = makeRotation(currentNode);
            else
                currentNode = makeRotation(currentNode);
        }

        currentNode = currentNode->prev;
    }
}

bool Avl::checkNull(node *tmp)
{
    if (tmp != NULL) return true;
    return false;
}

int Avl::balanceFactor(node *myNode)
{
    int ret =  (myNode->right == NULL ? 0 : (myNode->right->height + 1)) - (myNode->left  == NULL ? 0 : (myNode->left->height+1))  ;
    return ret;
}

int Avl::getHeight(node *currentNode)
{
    if (currentNode == NULL)
        return 0;

    return max(getHeight(currentNode->left),getHeight(currentNode->right)) +1;
}

node* Avl::makeRotation(node *root)
{

    if (balanceFactor(root) < 0 )
        if (balanceFactor(root->left) > 0 )
            root = left_rightRotation(root);
        else
            root = rightRotation(root);
    else if (balanceFactor(root->right) < 0 )
        root = right_leftRotation(root);
    else
        root = leftRotation(root);
    return root;
}

node* Avl::leftRotation(node *root)
{

    node B,G;
    node *one,*two,*three;

    memcpy(&B,root->right,sizeof(node));
    memcpy(&G,root->right->right,sizeof(node));

    one   = root;
    two   = root->right;
    three = root->right->right;

    //Node B
    root->right->prev = root->prev;
    root->right->left = root;
    //Node A
    root->right = B.left;
    root->prev  = G.prev;

    root = G.prev;
    if (root->prev != NULL)
    {
        if (root->prev->right == one)
            root->prev->right = root;
        else
            root->prev->left = root;
    }
    if (root->left->right != NULL) root->left->right->prev = root->left ;

    rotateFixHeights(one,two,three);
    return root;

}

node* Avl::rightRotation(node *root)
{
    node B,G;
    node *one,*two,*three;

    memcpy(&B,root->left,sizeof(node));
    memcpy(&G,root->left->left,sizeof(node));

    one   = root;
    two   = root->left;
    three = root->left->left;

    //Node B
    root->left->prev = root->prev;
    root->left->right = root;
    //Node A
    root->left = B.right;
    root->prev  = G.prev;
    //Node B

    root = G.prev;
    if (root->prev != NULL)
    {
        if (root->prev->right == one)
            root->prev->right = root;
        else
            root->prev->left = root;
    }
    if (root->right->left != NULL) root->right->left->prev = root->right ;

    rotateFixHeights(one,two,three);

    return root;

}

node* Avl::right_leftRotation(node *root)
{
    node *one,*two,*three;

    one = root;
    two = root->right;
    three = root->right->left;

    //Node B
    two->left = three->right;
    two->prev = three;
    if (two->left != NULL) two->left->prev = two;

    //Node G right
    three->right = two;
    three->prev = one;

    root->right = three;
    root = leftRotation(root);

    return root;
}

node* Avl::left_rightRotation(node *root)
{
    node *one,*two,*three;

    one = root;
    two = root->left;
    three = root->left->right;

    //Node B
    two->right = three->left;
    two->prev = three;
    if (two->right != NULL) two->right->prev = two;

    //Node G right
    three->left = two;
    three->prev = one;

    root->left = three;
    root = rightRotation(root);
    //Returns the NEW root of the two nodes
    return root;
}

void Avl::rotateFixHeights(node *one,node *two,node *three)
{
    one->height   = max((one->right != NULL ? one->right->height +1: -1),
                        (one->left  != NULL ? one->left->height  +1: -1)
                       );
    if (one->height == -1) one->height = 0;

    three->height = max((three->right != NULL ? three->right->height +1: -1),
                        (three->left  != NULL ? three->left->height  +1: -1)
                       );
    if (three->height == -1) three->height = 0 ;
    two->height = max(two->right->height, two->left->height) + 1;

}

node* Avl::search(int key)
{
    node *p=root;
    while(p!=NULL)
    {
        if(key<p->url)
            p=p->left;
        else if(key>p->url)
            p=p->right;
        else
            return p;
    }
    return NULL;
}


void Avl::display(node *ptr, int level)
{
    int i,l1,l2,l3;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);

        cout<<endl;
        if (ptr == root)
            cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        l1 = checkNull(ptr->left)  ? ptr->left->url : 0;
        l2 = checkNull(ptr->right) ? ptr->right->url : 0;
        l3 = checkNull(ptr->prev)  ? ptr->prev->url : 0;
        cout<< ptr->url << "-" << ptr->height<<"("<<balanceFactor(ptr)<<")["<<l1<<"-"<<l2<<"-"<<l3<<"]";//<<","<<ptr->prev<<")";

        display(ptr->left, level + 1);
        cout<<endl;
    }
}

void Avl::dispalyMe()
{
    display(root,1);
}

bool Avl::remove(int key)
{
    node deleted;
    node *tmp=NULL,moved,*tmp2=NULL;

    tmp = search(key);

    if (tmp == NULL)
        return false;

    memcpy(&deleted,tmp,sizeof(node));

    tmp = tmp2;

    if (deleted.right == NULL && deleted.left == NULL && deleted.prev == NULL) //If root last man standing
    {
        root = NULL;
    }
    else if (deleted.right == NULL && deleted.left == NULL)
    {
        if (deleted.prev->url > deleted.url)
            deleted.prev->left  = NULL;
        else
            deleted.prev->right = NULL;
        balanceDelete(deleted.prev);
    }
    else if (deleted.right == NULL)   //If deleted node right child is null
    {
        deleted.left->prev = deleted.prev;
        if (deleted.prev == NULL)
            root = deleted.left;
        else
        {
            if (deleted.prev->url > deleted.url)
                deleted.prev->left  = deleted.left;
            else
                deleted.prev->right = deleted.left;
        }
        balanceDelete(deleted.left->prev);
    }
    else if (deleted.left == NULL)   //If deleted node right child is null
    {
        deleted.right->prev = deleted.prev;
        // Ptrs of previous node
        if (deleted.prev == NULL)
            root = deleted.right;
        else
        {
            if (checkNull(deleted.prev->right))
            {
                if (deleted.prev->right->url == deleted.url )
                    deleted.prev->right =  deleted.right;
                else
                    deleted.prev->left =  deleted.right;
            }
            else
                deleted.prev->left =  deleted.right;
        }
        balanceDelete(deleted.right->prev);
    }
    else if (deleted.right->left == NULL)    //If deleted node right->left child is null
    {
        deleted.right->left   = deleted.left;
        deleted.right->prev   = deleted.prev;
        deleted.right->height = deleted.height;

        if (deleted.prev == NULL)
            root = deleted.right;
        else
        {
            if (checkNull(deleted.prev->right))
            {
                if (deleted.prev->right->url == deleted.url )
                    deleted.prev->right =  deleted.right;
                else
                    deleted.prev->left =  deleted.right;
            }
            else
                deleted.prev->left =  deleted.right;
        }
        if (checkNull(deleted.left))  deleted.left->prev = deleted.right;
        balanceDelete(deleted.right);
    }
    else
    {
        //tmp node to become root
        tmp = deleted.right;
        while (tmp->left != NULL)
            tmp = tmp->left;
        //moved node to become root backup
        memcpy(&moved,tmp,sizeof(node));
        tmp->left   = deleted.left;
        tmp->right  = deleted.right;
        tmp->prev   = deleted.prev;
        tmp->height = deleted.height;
        tmp->left->prev = tmp;
        tmp->right->prev = tmp;

        if (deleted.prev == NULL)
        {
            //If is the root of the avl
            root = tmp;
            if (checkNull(root->left)) root->left->prev = root;
            if (checkNull(root->right)) root->right->prev = root;
        }
        else
        {
            if (checkNull(deleted.prev->right) )
            {
                if (deleted.prev->right->url == deleted.url )
                    deleted.prev->right =  tmp;
                else
                    deleted.prev->left =  tmp;
            }
            else
                deleted.prev->left =  tmp;
        }
        if (moved.right != NULL)
        {
            moved.prev->left = moved.right;
            moved.right->prev = moved.prev;
        }
        else
        {
            moved.prev->left = NULL;
        }
        if (checkNull(moved.prev->right))
        {
            if (abs(balanceFactor(moved.prev))  >= 2)
            {
                tmp->right = makeRotation(tmp->right);
                moved.prev = tmp->right;
                tmp->height -= 1;
            }
        }
        balanceDelete(moved.prev);
    }
    delete tmp2;
    return true;
}

void Avl::balanceDelete(node *currentNode) //Where to start Balance. Starts at the input node
{
    while (currentNode != NULL)
    {
        if (currentNode->right == NULL && currentNode->left == NULL)
            currentNode->height = 0;

        else if (currentNode->right == NULL)
            currentNode->height = currentNode->left->height + 1;

        else if ( currentNode->left == NULL)
            currentNode->height = currentNode->right->height + 1;
        else
            currentNode->height = max(currentNode->right->height,currentNode->left->height) + 1;

        if (abs(balanceFactor(currentNode))  >= 2)
        {
            if (currentNode == root)
            {
                root = makeRotation(currentNode);
            }
            else
                currentNode = makeRotation(currentNode);
        }
        currentNode = currentNode->prev;
    }
}

void Avl::inorder(node *tree,char* s)
{
    int coun=0;
    int coun2=-1;
    if (tree==NULL)
        return;
    inorder (tree->left,s);
    inorder2(tree->subAvl->root,coun);
    if(!myfile.is_open())
        myfile.open(s);
    myfile<<tree->url<<", "<<coun;
    inorder2(tree->subAvl->root,coun2);
    myfile<<"\n";
    inorder (tree->right,s);
}
void Avl::inorder2(node *tree,int &coun)
{
    if (tree==NULL)
        return;

    inorder2(tree->left,coun);
    if(coun==-1)
        myfile<<", "<<tree->url;
    else
        coun++;
    inorder2(tree->right,coun);

}
void Avl::closefile()
{
    myfile.close();
}
void Avl::closeEverything()
{
    closefile();
}
