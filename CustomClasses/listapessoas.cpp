#include "listapessoas.h"

ListaPessoas::ListaPessoas(GestorBD *gestor)
{
    qDebug() << "ListaPessoas: Initializing PeopleID.";
    allocatedPeopleID.clear();
    allocatedPeopleID.insert(allocatedPeopleID.size(), 10, 0);
    allocatedPeopleID.replace(0, 1);
    maxPeopleID = 0;
    qDebug() << "ListaPeople: allocatedPeopleID size is " << allocatedPeopleID.size() << ", maxPeopleID is " << maxPeopleID;

    oGestor =gestor;
    People = new QVector<Pessoa*>();
}

ListaPessoas::~ListaPessoas(){
    for(int i=0;People->size();i++){
        delete People->at(i);
    }
    delete People;
}

bool ListaPessoas::loadPeople(GestorBD* gestor){
    if(gestor==0)
        gestor=oGestor;
    if(gestor==0){
        qDebug() << "ListaPessoas.load():ERROR GestorBD not set.";
        return false;
    }

    QVector<PersonParam*> *PersonAtributes = gestor->getPeople(this);
    if(!PersonAtributes){
        qDebug() << "ListaPessoas.load(): ERROR GestorBD->Fail to load.";
        delete PersonAtributes;
        return false;
    }

    People->clear();
    for(int i=0;i<PersonAtributes->size();i++){
        People->append(new Pessoa(*PersonAtributes->at(i)));
    }
    delete PersonAtributes;

    return true;
}

Pessoa* ListaPessoas::createPerson(PersonParam atributes){
    atributes.ID=genPersonID();
    Pessoa* newPerson = new Pessoa(atributes);
    if(!oGestor->addPerson(&atributes)){
        qDebug() << "ListaPessoas:Unable to Save Person";
        delete newPerson;
        return nullptr;
    }
    else{
        qDebug() << "ListaPessoas:Person Saved";
        People->append(newPerson);
        return newPerson;
    }
}

int ListaPessoas::generateID(QVector<int> &allocatedID, int &maxID)
{
    for (int index = 0; index < allocatedID.size(); index++ )
    {
        if (allocatedID.at(index) == 0)
        {
            qDebug() << "ListaPessoas::generateID() ->Free ID found " << index << ", Vector[index] = " << allocatedID.at(index);
            allocatedID.replace(index,1);
            qDebug() << "ListaPessoas::generateID() ->Vector[index] replaced by" << allocatedID.at(index);;
            return index;
        }
        if (index == maxID){
            qDebug() << "ListaPessoas::generateID() -> Incrementing maxID.";
            maxID += 1;
            if (maxID == allocatedID.size())
            {
                qDebug() << "ListaPessoas::generateID() -> Vector full Allocating more space.";
                allocatedID.insert(allocatedID.size(), 10, 0);
            }
            allocatedID.replace(maxID,1);
            return maxID;
        }
    }
    //This Should't happen!!
    if (allocatedID.size() == maxID+1){
        qDebug() << "ListaPessoas::generateID() -> Index Problem: Allocating more space";
        allocatedID.insert(allocatedID.size(), 10, 0);
        maxID += 1;
        allocatedID.replace(maxID,1);
        return maxID;
    }
    qDebug() << "ListaPessoas:Something went wrong generating an ID";
    qDebug() << "ListaPessoas:MaxID = " << maxID << ", vector size = " << allocatedID.size();
    return -1;


}

int ListaPessoas::genPersonID(){
    return generateID(allocatedPeopleID, maxPeopleID);
}
