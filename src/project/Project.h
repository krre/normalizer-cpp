#pragma once
#include <QString>
#include <QScopedPointer>

namespace Unit {
    class Flow;
}

class Header;
class Root;
class Node;

class Project {
public:
    enum class Target {
        Application,
        Library
    };

    Project();
    ~Project();

    QString path() const;
    Target target() const;

    void create(const QString& path, Target target);
    void open(const QString& path);
    void close();

    void write(const QString& filePath);
    void read(const QString& path);

private:
    void createApp();
    void createLib();
    void createFlow(Unit::Flow* flow);

    QString m_path;
    Target m_target;

    QScopedPointer<Header> header;
    QScopedPointer<Root> root;
};
