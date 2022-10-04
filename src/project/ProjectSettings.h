#pragma once
#include "core/CommonTypes.h"
#include <QJsonObject>

class ProjectSettings {
public:
    ProjectSettings();

    void create();
    void load();
    void save();
    void clear();

    bool isValid() const;

    QString projectPath() const;
    void setProjectPath(const QString& path);

    QString outputPath() const;

    FileFormat format() const;
    void setFormat(FileFormat format);

private:
    QString dirPath() const;
    QString filePath() const;

    QString m_projectPath;
    QJsonObject settings;
};
