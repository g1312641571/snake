#ifndef RANKDATA_H
#define RANKDATA_H

#include <QFile>
#include <QtXml>
#include <QTextStream>
#include <QDomDocument>

class RankData
{
    class playerData
    {
    public:
        playerData(QString n = "Anonymity", int s = 0):name(n), score(s){}
        inline QString getName(){return name;}
        inline int getScore(){return score;}
        inline void setName(QString n){name = n;}
        inline void setScore(int s){score = s;}

        bool operator<(const playerData &pDat){return (this->score < pDat.score);}
        bool operator>(const playerData &pDat){return !(*this < pDat);}
        bool operator==(const playerData &pDat){return (this->score == pDat.score);}
        bool operator!=(const playerData &pDat){return !(*this == pDat);}
        void swap(playerData &pDat){qSwap(pDat.score, this->score); qSwap(pDat.name, this->name);}
    private:
        QString name;
        int score;
    };


public:
    RankData();
    void appendData(QString name, int score);
    void writeFile();
    QString getName(int rank);
    int getScore(int rank);

private:
    QString fileName;
    int rankSize;
    QVector<playerData> data;

    void readFile();
    void resetFile(bool reset = true);
};

#endif // RANKDATA_H
