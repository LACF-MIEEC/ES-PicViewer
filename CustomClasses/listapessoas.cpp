#include "listapessoas.h"

ListaPessoas::ListaPessoas(GestorBD *gestor)
{
    qDebug() << "Entered constructor";
    allocatedPeopleID.fill(0);
    allocatedPeopleID.insert(allocatedPeopleID.size(), 10, 0);

    maxPeopleID = 0;

    qDebug() << "vector size is " << allocatedPeopleID.size() << ", maxID is " << maxPeopleID;

    oGestor =gestor;

    People.clear();
    QVector<PersonParam*> PersonAtributes = oGestor->getPeople(this);
    for(int i=0;PersonAtributes.size();i++){
        People.append(new Pessoa(PersonAtributes[i]));
    }


}

ListaPessoas::~ListaPessoas(){
    for(int i=0;People.size();i++){
        People.at(i)->deleteSelf();
    }

    delete this;
}


Pessoa* ListaPessoas::createPerson(PersonParam atributes){
    atributes.ID=genPersonID();
    Pessoa* newPerson = new Pessoa(atributes);
    People.append(newPerson);
    return newPerson;
}

int ListaPessoas::generateID(QVector<int> &allocatedID, int &maxID)
{
    qDebug() << "Hello World";
    for (int index = 0; index < allocatedID.size(); index++ )
    {
        if (allocatedID.at(index) == 0)
        {
            qDebug() << "Free space found: index = " << index << ", vector[index] = " << allocatedID.at(index);

            allocatedID[index] = 1;
            qDebug() << ", vector[index] is now " << allocatedID.at(index);;

            return index;
        }
        if (index == maxID){
            qDebug() << "Incrementing maxID";
            maxID += 1;
            if (maxID == allocatedID.size())
            {
                qDebug() << "Allocating more space";
                allocatedID.insert(allocatedID.size(), 10, 0);
            }
            allocatedID[maxID] = 1;
            return maxID;
        }
    }
    // Program shouldn't get here...
    qDebug() << "Are you sure the program is correct?";
    // Are we here? vector is full, we need to append new values
    if (allocatedID.size() == maxID+1){
        qDebug() << "Incrementing maxID and allocating more space";
        allocatedID.insert(allocatedID.size(), 10, 0);
        maxID += 1;
        //allocatedID.append(1);
        allocatedID[maxID] = 1;
        return maxID;
        //return maxID;
    }
    // If the program gets here, something went wrong
    qDebug() << "Something went wrong generating an ID";
    qDebug() << "MaxID = " << maxID << ", vector size = " << allocatedID.size();
    return -1;


}

int ListaPessoas::genPersonID(){
    return generateID(allocatedPeopleID, maxPeopleID);
}
