#include "listaalbuns.h"
#include "debugES.h"
#include <iostream>
#include <sstream>

ListaAlbuns::ListaAlbuns()
{
    debugMsg( "Entered constructor");
    allocatedAlbumID.fill(0);
    allocatedAlbumID.insert(allocatedAlbumID.size(), 10, 0);

    maxAlbumID = 0;



    std::cout << "vector size is " << allocatedAlbumID.size() << ", maxID is " << maxAlbumID << std::endl;

}


int ListaAlbuns::generateID(QVector<int> &allocatedID, int &maxID)
{
    debugMsg( "Hello World");
    for (int index = 0; index < allocatedID.size(); index++ )
    {
        if (allocatedID[index] == 0)
        {
            std::ostringstream msg;
            msg << "Free space found: index = " << index << ", vector[index] = " << allocatedID[index];
            debugMsg(msg.str());
            msg.str("");

            allocatedID[index] = 1;
            msg << ", vector[index] is now " << allocatedID[index] << std::endl;
            debugMsg(msg.str());

            return index;
        }
        if (index == maxID){
            debugMsg( "Incrementing maxID");
            maxID += 1;
            if (maxID == allocatedID.size())
            {
                debugMsg( "Allocating more space");
                allocatedID.insert(allocatedID.size(), 10, 0);
            }
            allocatedID[maxID] = 1;
            return maxID;
        }
    }
    // Program shouldn't get here...
    std::cout << "Are you sure the program is correct?" << std::endl;
    // Are we here? vector is full, we need to append new values
    if (allocatedID.size() == maxID+1){
        debugMsg( "Incrementing maxID and allocating more space");
        allocatedID.insert(allocatedID.size(), 10, 0);
        maxID += 1;
        //allocatedID.append(1);
        allocatedID[maxID] = 1;
        return maxID;
        //return maxID;
    }
    // If the program gets here, something went wrong
    debugMsg( "Something went wrong generating an ID");
    std::cout << "MaxID = " << maxID << ", vector size = " << allocatedID.size() << std::endl;
    return -1;


}
