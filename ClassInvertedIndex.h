#ifndef CLASSINVERTEDINDEX_H
#define CLASSINVERTEDINDEX_H
#include<iostream>
#include "Avl.h"

class ClassInvertedIndex
{
    public:
        ClassInvertedIndex();
        ClassInvertedIndex(char *name);
        void commands_file();
        Avl *myAvl;

    private:
        char *fi;
        void is_read();
        void is_write();
        void is_insert();
        void is_delete();
        int cmdtype();

};

#endif // CLASSINVERTEDINDEX_H

