#pragma once
#include <QObject>

class QString;
class QStringListModel;
class QJsonParseError;
class QJasonObject;
class QFile;
class QDir;

namespace Ps{

typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrPair;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent, QString filename);
    void ParseJsonData();

signals:
    void NotifyStatusMessage(QString msg);

private:
    QString m_filename;
    QString m_applicationName;
    QString m_appShortName;
    QString m_hostName;
    quint64 m_portNumber;
    qint64 m_tcpLongWaitMs;
    qint64 m_tcpShortWaitMs;
    QStringListModel& m_modelCommands;

    QString ReadJsonFile();
    QString ReadJsonFileFromInternalResource();
    void SendErrorMessage(const QString &msg);
    JsonObjErrPair GetJsonObject(const QString &raw_jason);
    void ShowJsonParseError(QJsonParseError json_error);
    void SetupCommands(QJsonObject json_obj);
    QDir OpenConfigDirectory();
    void WriteDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &settings);

    // singleton
    explicit Settings(const Settings& rhs);
    Settings& operator= (const Settings& rhs);
};

} // namespace
