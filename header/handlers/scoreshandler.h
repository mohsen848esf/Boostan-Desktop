#ifndef SCORESHANDLER_H
#define SCORESHANDLER_H

#include "abstractxmldatahandler.h"
#include <QDebug>

class ScoresHandler : public AbstractXmlDataHandler
{
    Q_OBJECT

private:
    QVariantList scores;
    QVariantMap score_brief;

    // Forced implementation of AbstractXmlDataHandler pure function
    bool    getIsEmpty              () const override;

    // normalize the name and remove ugly chars
    void    normalizeName(QString& name);
    bool    extractScores(const QString& data);
    bool    extractBirefScores(const QString& data);

public:
    enum status
    {
        Passed,
        Failed,
        Deleted,
        Temporary,
        Undefined
    };
    Q_ENUM(status)

    ScoresHandler();

public slots:
    void start();
    QVariantList getScores() const;
};

#endif // SCORESHANDLER_H
