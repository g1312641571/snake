#include "rankData.h"
#pragma execution_character_set("utf-8")

RankData::RankData(): fileName("data.in"), rankSize(5),
    data(rankSize)
{
    readFile();
}


void RankData::readFile()
{
    QFile file("data.in");
    if(!file.open(QIODevice::ReadOnly))
    {
        //qDebug() << "Err1";
        return resetFile();
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        //qDebug() << "Err2";
        file.close();
        return resetFile();
    }
    file.close();

    bool fileOk = true;//For check

    QDomElement root = doc.documentElement();

    int cnt = 0;
    for(QDomNode node = root.firstChild(); !node.isNull(); node = node.nextSibling())
    {
        QDomElement e =  node.toElement();
        QDomNodeList infoList = e.childNodes();

        //Get name and score
        data[cnt].setName(infoList.at(0).toElement().text());
        data[cnt].setScore(infoList.at(1).toElement().text().toInt(&fileOk));
        if(++cnt == rankSize + 1)
        {
            fileOk = false;
            break;
        }
    }
    for(int i = 0; i != rankSize - 1; ++i)
        if(data[i] < data[i + 1])
        {
            fileOk = false;
            break;
        }
    if(!fileOk)
        resetFile();
}


void RankData::appendData(QString name, int score)
{
    if(score < data[rankSize - 1].getScore())
        return;
    data[rankSize - 1] = playerData(name, score);
    for(int i = rankSize - 1; i != 0 ;--i)
    {
        if(data[i] < data[i - 1])
            break;
        data[i].swap(data[i - 1]);
    }
}

void RankData::resetFile(bool reset)
{
    QDomDocument doc;
    //Create xml header
    QDomProcessingInstruction ins = doc.createProcessingInstruction(
        "xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(ins);

    //Create root node
    QDomElement root = doc.createElement("RankData");
    doc.appendChild(root);

    //Create player child node
    for(int i = 0; i != rankSize; ++i)
    {
        QDomElement player = doc.createElement("player");
        player.setAttribute("rank", i + 1);
        root.appendChild(player);
        //Set name
        QDomElement name = doc.createElement("name");
        QDomText nameText;
        if(reset)
            nameText = doc.createTextNode("Anonymity");
        else
            nameText = doc.createTextNode(data[i].getName());
        name.appendChild(nameText);
        player.appendChild(name);

        //Set score
        QDomElement scoreEle = doc.createElement("score");
        player.appendChild(scoreEle);
        QDomText scoreText;
        if(reset)
            scoreText = doc.createTextNode("0");
        else
            scoreText = doc.createTextNode(QString::number(data[i].getScore()));
        scoreEle.appendChild(scoreText);
    }

    //Output to the file
    QFile file("data.in");
    if(!file.open(QFile::WriteOnly | QFile::Truncate | QIODevice::Text))
        return;

    QTextStream out_stream(&file);
    doc.save(out_stream, 4);
    file.close();
}

void RankData::writeFile()
{
    resetFile(false);
}

QString RankData::getName(int rank)
{
    if(rank > rankSize)
        return("Anonymity");
    else
        return data[rank - 1].getName();
}

int RankData::getScore(int rank)
{
    if(rank > rankSize)
        return(0);
    else
        return  data[rank - 1].getScore();
}
