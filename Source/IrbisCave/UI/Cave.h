#pragma once
#include <QWidget>
#include <QString>

class DatabaseManager;

class Cave : public QWidget {
    Q_OBJECT

public:
    Cave(const QString& filePath);
    ~Cave();

    void newIrbis(const QString& path);
    void openIrbis(const QString& path);
    void copyIrbis(const QString& path);
    void closeIrbis();

    QString filePath() const;

private:
    QString _filePath;
    DatabaseManager* _databaseManager;
};
