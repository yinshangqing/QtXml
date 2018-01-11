#include "xml_file.h"

XML_FILE::XML_FILE(QObject *parent) :
    QObject(parent)
{
}

XML_FILE::~XML_FILE()
{

}

bool XML_FILE::SaveXmlFile()
{
    QFile file(m_qstrFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);
    m_XmlDocument.save(out,4);

    file.close();
    return true;
}

bool XML_FILE::CreateXMLFile()
{
    QFile file(m_qstrFileName);
    file.open(QIODevice::ReadWrite);
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement("test");
    doc.appendChild(root);
    QDomText text = doc.createTextNode("");
    root.appendChild(text);
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}

bool XML_FILE::LoadXmlFile()
{
    QFile file(m_qstrFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;
    if (!m_XmlDocument.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
        qDebug(errorStr.toLatin1());
        file.close();
        return false;
    }
    file.close();

    return true;
}

void XML_FILE::SetFileName(QString qstrFileName)
{
    m_qstrFileName = qstrFileName;
}

bool XML_FILE::SetChangeXmlChild(QVariant qvar)
{
    Person tag = qvar.value<Person>();
    QDomNode domnode = m_XmlDocument.documentElement().firstChildElement("person_msg").firstChild();
    while (!domnode.isNull())
    {
        QDomElement child_domelement = domnode.toElement();
        if (child_domelement.tagName() == "person")
        {
            if (child_domelement.attribute("qstruser") == tag.qstruser)
            {
                child_domelement.setAttribute("qstruser", tag.qstruser);
                child_domelement.setAttribute("qstrpasswd", tag.qstrpasswd);
                child_domelement.setAttribute("nType", tag.nType);
                child_domelement.setAttribute("nAge", tag.nAge);
                SaveXmlFile();

                return false;
            }
        }

        domnode = domnode.nextSibling();
    }

    QDomElement child_domelement = m_XmlDocument.createElement("person");
    child_domelement.setAttribute("qstruser", tag.qstruser);
    child_domelement.setAttribute("qstrpasswd", tag.qstrpasswd);
    child_domelement.setAttribute("nType", tag.nType);
    child_domelement.setAttribute("nAge", tag.nAge);
    m_XmlDocument.documentElement().firstChildElement("person_mrg").appendChild(child_domelement);

    return SaveXmlFile();
}

bool XML_FILE::GetXmlFile(QList<QVariant> &qlist)
{
    QDomNode domnode = m_XmlDocument.documentElement().firstChildElement("person_mrg").firstChild();
    while (!domnode.isNull())
    {
        QDomElement child_domelement = domnode.toElement();
        if (child_domelement.tagName() == "person")
        {
            Person tag;
            tag.qstruser = child_domelement.attribute("qstruser");
            tag.qstrpasswd = child_domelement.attribute("qstrpasswd");
            tag.nType = child_domelement.attribute("nType");
            tag.nAge = child_domelement.attribute("nAge");
            qlist.push_back(QVariant::fromValue(tag));
        }

        domnode = domnode.nextSibling();
    }

    return true;
}
