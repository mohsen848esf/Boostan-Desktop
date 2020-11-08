#include "header/errors.h"

Errors::Errors(QObject *parent) : QObject(parent), error_code{0}
{

}

QString Errors::getErrorString() const
{
    return Constants::Errors::error_strings[error_code];
}

QString Errors::getErrorSolution() const
{
    return Constants::Errors::error_solutions[error_code];
}

int Errors::getErrorCode() const
{
    return error_code;
}

/*
 * set 'error_code' to proper code by parsing 'ecode'
 */
void Errors::setErrorCode(int ecode)
{
    if (error_code == ecode) return;
    // check if ecode is one of QNetworkReply::Error's then mark them all as ServerConnectionError
    if (ecode >= (QNetworkReply::ConnectionRefusedError + Constants::Errors::qt_offset) && ecode <= (QNetworkReply::UnknownServerError + Constants::Errors::qt_offset)){
        error_code = Constants::Errors::ServerConnenctionError;
    } else {
        error_code = ecode;
    }
    emit errorCodeChanged();
}

/*
 * return type of error
 */
//! TODO: change uint to error_type
uint Errors::getCriticalStatus() const
{
    return Constants::Errors::critical_status.value(error_code, Constants::Errors::Normal);
}

void Errors::reset()
{
    setErrorCode(Constants::Errors::NoError);
}
