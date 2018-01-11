#ifndef XML_FILE_H
#define XML_FILE_H

#include <QObject>
#include <QtXml/QDomDocument>
#include <QList>
#include <QVariant>
#include <QFile>
#include <QDebug>

struct Person
{
    QString qstruser;
    QString qstrpasswd;
    int     nType;
    int     nAge;

};
Q_DECLARE_METATYPE(Person)

class XML_FILE : public QObject
{
    Q_OBJECT
public:
    explicit XML_FILE(QObject *parent = 0);
    ~XML_FILE();

    bool SaveXmlFile();
    bool CreateXMLFile();
    bool LoadXmlFile();
    void SetFileName(QString qstrFileName);
    bool SetChangeXmlChild(QVariant);
    bool GetXmlFile(QList<QVariant>&);
signals:

public slots:

private:
    QString m_qstrFileName;
    QDomDocument m_XmlDocument;
};

#endif // XML_FILE_H
