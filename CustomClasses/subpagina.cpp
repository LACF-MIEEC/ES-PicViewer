#include "pagina.h"

//===============================================================================
//--------------------------------SubClasses------------------------------------
// ------------- VIAGEM ----------------------------

PaginaViagem::PaginaViagem(PageParam atributes):
    Pagina(atributes)
{
    StartDate   =   atributes.StartDate;
    EndDate     =   atributes.EndDate;
}

pageType_t PaginaViagem::getType()
{
    return viagem;
}

QDate PaginaViagem::getStartDate(){
    return StartDate;
}
QDate PaginaViagem::getEndDate(){
    return EndDate;
}
QString PaginaViagem::getPartyType(){
    return QString();
}

QString PaginaViagem::createFolderName(){
    QString folderName;
    QStringList trimedDesc;
    QString NormalizedDesc,ShortDesc;

    folderName.append("Viagem_");

    folderName.append(StartDate.toString(Qt::ISODate));
    folderName.append("_");
    folderName.append(EndDate.toString(Qt::ISODate));

    //Tirar caracteres especiais e acentos
//    trimedDesc=Description.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]"))).split(" ",QString::SkipEmptyParts);
    trimedDesc=Description.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\[\]\\\]"))).split(" ",QString::SkipEmptyParts);

    folderName.append("_");

    for(int i=0;(i<trimedDesc.size())||(i<2);i++){
        ShortDesc.append(trimedDesc.at(i));
    }

    NormalizedDesc=ShortDesc.normalized(QString::NormalizationForm_D);
    for (int i=0;i<NormalizedDesc.length(); i++)
    {
        if (NormalizedDesc.at(i).category()!=QChar::Mark_NonSpacing &&
                NormalizedDesc.at(i).category()!=QChar::Mark_SpacingCombining &&
                NormalizedDesc.at(i).category()!=QChar::Mark_Enclosing)
        {
            folderName.append(NormalizedDesc.at(i));
        }
    }
    folderName.append("_");
    folderName.append(QString::number(ID));
    return folderName;
}
// ------------- FESTA ----------------------------

PaginaFesta::PaginaFesta(PageParam atributes):
    Pagina(atributes)
{
    Date        =   atributes.StartDate;
    PartyType   =   atributes.PartyType;
}

pageType_t PaginaFesta::getType()
{
    return festa;
}

QDate PaginaFesta::getStartDate(){
    return Date;
}
QDate PaginaFesta::getEndDate(){
    return QDate();

}
QString PaginaFesta::getPartyType(){
    return PartyType;
}

QString PaginaFesta::createFolderName(){
    QString folderName;
    QStringList trimedDesc;
    QString NormalizedDesc,ShortDesc;

    folderName.append("Festa_");
    folderName.append(getPartyType());
    folderName.append("_");
    folderName.append(Date.toString(Qt::ISODate));

    //Tirar caracteres especiais e acentos
//    trimedDesc=Description.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]"))).split(" ",QString::SkipEmptyParts);
    trimedDesc=Description.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\[\]\\\]"))).split(" ",QString::SkipEmptyParts);

    folderName.append("_");
    for(int i=0;(i<trimedDesc.size())||(i<2);i++){
        ShortDesc.append(trimedDesc.at(i));
    }
    NormalizedDesc=ShortDesc.normalized(QString::NormalizationForm_D);
    for (int i=0;i<NormalizedDesc.length(); i++)
    {
        if (NormalizedDesc.at(i).category()!=QChar::Mark_NonSpacing &&
                NormalizedDesc.at(i).category()!=QChar::Mark_SpacingCombining &&
                NormalizedDesc.at(i).category()!=QChar::Mark_Enclosing)
        {
            folderName.append(NormalizedDesc.at(i));
        }
    }
    folderName.append("_");
    folderName.append(QString::number(ID));
    return folderName;
}
// ------------- COISA OU PESSOA ----------------------------

PaginaCoisaPessoa::PaginaCoisaPessoa(PageParam atributes):
    Pagina(atributes)
{
}

pageType_t PaginaCoisaPessoa::getType()
{
    return coisaPessoa;
}

QDate PaginaCoisaPessoa::getStartDate(){
    return QDate();
}
QDate PaginaCoisaPessoa::getEndDate(){
    return QDate();
}
QString PaginaCoisaPessoa::getPartyType(){
    return QString();
}

QString PaginaCoisaPessoa::createFolderName(){
    QString folderName;
    QStringList trimedDesc;
    QString NormalizedDesc,ShortDesc;

    folderName.append("CoisaOuPessoa");

    //Tirar caracteres especiais e acentos
//    trimedDesc=Description.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]"))).split(" ",QString::SkipEmptyParts);
    trimedDesc=Description.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\[\]\\\]"))).split(" ",QString::SkipEmptyParts);
    folderName.append("_");

    for(int i=0;(i<trimedDesc.size())||(i<2);i++){
        ShortDesc.append(trimedDesc.at(i));
    }
    NormalizedDesc=ShortDesc.normalized(QString::NormalizationForm_D);
    for (int i=0;i<NormalizedDesc.length(); i++)
    {
        if (NormalizedDesc.at(i).category()!=QChar::Mark_NonSpacing &&
                NormalizedDesc.at(i).category()!=QChar::Mark_SpacingCombining &&
                NormalizedDesc.at(i).category()!=QChar::Mark_Enclosing)
        {
            folderName.append(NormalizedDesc.at(i));
        }
    }
    folderName.append("_");
    folderName.append(QString::number(ID));
    return folderName;
}
// ------------- OUTRO ----------------------------

PaginaOutro::PaginaOutro(PageParam atributes):
    Pagina(atributes)
{
    StartDate   =   atributes.StartDate;
    EndDate     =   atributes.EndDate;
}

pageType_t PaginaOutro::getType()
{
    return outro;
}

QDate PaginaOutro::getStartDate(){
    return StartDate;
}
QDate PaginaOutro::getEndDate(){
    return EndDate;
}
QString PaginaOutro::getPartyType(){
    return QString();
}

QString PaginaOutro::createFolderName(){
    QString folderName;
    QStringList trimedDesc;
    QString NormalizedDesc,ShortDesc;

    folderName.append("Outro");
    folderName.append("_");

    folderName.append(StartDate.toString(Qt::ISODate));
    folderName.append("_");
    folderName.append(EndDate.toString(Qt::ISODate));

    //Tirar caracteres especiais e acentos
//    trimedDesc=Description.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]"))).split(" ",QString::SkipEmptyParts);
    trimedDesc=Description.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\[\]\\\]"))).split(" ",QString::SkipEmptyParts);

    folderName.append("_");

    for(int i=0;(i<trimedDesc.size())||(i<2);i++){
        ShortDesc.append(trimedDesc.at(i));
    }

    NormalizedDesc=ShortDesc.normalized(QString::NormalizationForm_D);
    for (int i=0;i<NormalizedDesc.length(); i++)
    {
        if (NormalizedDesc.at(i).category()!=QChar::Mark_NonSpacing &&
                NormalizedDesc.at(i).category()!=QChar::Mark_SpacingCombining &&
                NormalizedDesc.at(i).category()!=QChar::Mark_Enclosing)
        {
            folderName.append(NormalizedDesc.at(i));
        }
    }

    folderName.append("_");
    folderName.append(QString::number(ID));
    return folderName;
}
