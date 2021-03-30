#ifndef COURSESCHEDULEHANDLER_H
#define COURSESCHEDULEHANDLER_H

/*
    * Class: CourseScheduleHandler
    * Files: courseschedulehandler.h, courseschedulehandler.cpp
    * The task of this class is to get the courses weekly schedule (and related informations)
    * from Golestan and send them to QML in proper structure.

    * The data structure we are using is based on ScheduleTable (refer to the scheduletable.cpp comments)
*/

#include "abstractxmldatahandler.h"
#include "../controls/scheduletable.h"
#include <QStringBuilder>

class CourseScheduleHandler : public AbstractXmlDataHandler
{
    Q_OBJECT

private:
    /** Properties **/

    const QString   schedule_url          {QStringLiteral("/Forms/F0202_PROCESS_REP_FILTER/F0202_01_PROCESS_REP_FILTER_DAT.ASPX?r=0.10057227848084405&fid=1;423&b=0&l=0&&lastm=20190829142532&tck=")};
    // container for storing the ScheduleTable material
    QVariantList    weekly_schedule;
    QString semester;

    /** Functions **/

    // set semester to sem
    void    setSemester                 (const QString& sem);

    // extract weekly course schedule from 'response' and fill 'weekly_schedule'
    bool    extractWeeklySchedule       (QString& response);

    // request validators for being able to make further requests
    bool    requestTokens();
    // request the weekly schedule
    bool    requestSchedule();

    // calculate the corresponding row(in scheduleTable component) for the given day
    int     calculateScheduleRow        (const QString& day) const;
    // calculate the corresponding column(in scheduleTable component) for the given hour
    float   calculateScheduleColumn     (const QString& hour) const;
    // calculate the the duration of a course in hour.
    float   calculateScheduleLen        (const QString& hour, const float start_column) const;

    // forced getter implementation (because of abstract parent class) for is_empty
    bool    getIsEmpty() const override;

private slots:
    // parse the validators from request requestTokens()
    void    parseTokens                 (QNetworkReply& reply);
    // parse the weekly schedule
    void    parseSchedule               (QNetworkReply& reply);

public slots:
    // start the process for recieving data from Golestan for semester 'current_semester'
    void            start               (const QString current_semester);
    // return the ScheduleTable materials
    QVariantList    getSchedule         () const;

public:
    CourseScheduleHandler();
};

#endif // COURSESCHEDULEHANDLER_H
