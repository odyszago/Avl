#include "ClassInvertedIndex.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include<cstdlib>

using namespace std;

ifstream f;

ClassInvertedIndex::ClassInvertedIndex()
{
    myAvl = new Avl;
    fi=NULL;
}

ClassInvertedIndex::ClassInvertedIndex(char *name)
{
    fi=name;
    myAvl = new Avl;
    f.open(fi);
}

void ClassInvertedIndex::commands_file()
{
    if (f.is_open())
    {
        while (!f.eof())
        {
            switch (cmdtype())
            {
            case 1:
            {
                is_read();
                break;
            }
            case 2:
            {
                is_write();
                break;
            }
            case 3:
            {
                is_insert();
                break;
            }
            case 4:
            {
                is_delete();
                break;
            }
            case 0:
            {
                cout<<"False Command in Commands.txt\n";
                continue;
            }
            }
        }
    }
    f.close();
}

int ClassInvertedIndex::cmdtype()
{
    char B[100];
    f.clear();
    f>>B;
    if (!strcmp(B,"READ_DATA"))
        return 1;
    else
    {
        if (!strcmp(B,"WRITE_INDEX"))
            return 2;
        else
        {
            if (!strcmp(B,"INSERT_LINK"))
                return 3;
            else
            {
                if (!strcmp(B,"DELETE_LINK"))
                    return 4;
                else
                    return 0;
            }
        }
    }
}


void ClassInvertedIndex::is_read()
{
    node *result=NULL;//pointer to num
    int num=-1;//the previus number which we add to the avl
    char s[100];
    f.clear();
    f>>s;
    ifstream fl;
    fl.open(s);
    int l1,l2;
    cout<<"please wait until the file load\n";
    while(!fl.eof())
    {
        fl>>l1>>l2;
        if(num!=l1)//chech if the previus number is same with the number which we try to add now
        {
            result = myAvl->search(l1);//if the numbers arent the same then update
            num=l1;
        }

        if (result == NULL)
        {
            myAvl->insert(l1);
            result = myAvl->search(l1);
        }


        if (result->subAvl == NULL)
        {
            result->subAvl = new Avl;
        }

        if (result->subAvl->search(l2) == NULL)
            result->subAvl->insert(l2);

    }
    cout<<"file loaded\n";
}

void ClassInvertedIndex::is_write()
{
    char s[100];
    f>>s;
    myAvl->inorder(myAvl->root,s);
    myAvl->closeEverything();
    f.close();
    exit(1);
}

void ClassInvertedIndex::is_insert()
{
    node* result;
    int a1,a2;
    f.clear();
    f>>a1>>a2;
    result = myAvl->search(a1);
    if (result == NULL)
    {
        myAvl->insert(a1);
        result = myAvl->search(a1);
    }


    if (result->subAvl == NULL)
        result->subAvl = new Avl;


    if (result->subAvl->search(a2) == NULL)
        result->subAvl->insert(a2);
}

void ClassInvertedIndex::is_delete()
{
    int a1,a2;
    f.clear();
    f>>a1>>a2;
    node *tmp;
    tmp=myAvl->search(a1);
    if(tmp!=NULL)
    {
        tmp->subAvl->remove(a2);

        if(tmp->subAvl->root==NULL)
        {
            delete tmp->subAvl;
            myAvl->remove(a1);
        }
    }
}


