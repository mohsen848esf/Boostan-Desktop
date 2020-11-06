#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include "handler.h"

class LoginHandler : public Handler
{
    Q_OBJECT
private:
    const QString   login_url{"/Forms/AuthenticateUser/AuthUser.aspx?fid=0;1&tck=&&&lastm=20190219160242"};
    QString         user_name;

    bool            extractName (QString& response);

private slots:
    bool            parseLogin  (QNetworkReply& reply);

public:
    LoginHandler();
    Q_INVOKABLE bool    tryLogin(const QString username, const QString password, const QString captcha);
    Q_INVOKABLE QString getName() const;
};

#endif // LOGINHANDLER_H
