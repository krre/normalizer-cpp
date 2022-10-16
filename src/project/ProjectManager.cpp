#include "ProjectManager.h"
#include "Database.h"
#include "ProjectTemplate.h"
#include "TokenFactory.h"
#include "core/Constants.h"
#include "core/Utils.h"
#include "norm/project/Project.h"
#include <QtCore>

ProjectManager::ProjectManager() {
    tokenFactory.reset(new TokenFactory);
    database.reset(new Database(this));
}

ProjectManager::~ProjectManager() {

}

QString ProjectManager::path() const {
    return m_path;
}

Norm::Project::Target ProjectManager::target() const {
    Norm::Project* project = static_cast<Norm::Project*>(database->token(Const::Norm::Token::Project, 1));

    if (!project) {
        throw std::runtime_error("Project token not exists");
    }

    return project->target();
}

void ProjectManager::create(const QString& path, Norm::Project::Target target) {
    m_path = path;

    QString filePath;
    ProjectTemplate projectTemplate(this);

    switch (target) {
        case Norm::Project::Target::Application:
            filePath = Utils::applicationPath(path);
            projectTemplate.createApp();
            break;
        case Norm::Project::Target::Library:
            filePath = Utils::libraryPath(path);
            projectTemplate.createLib();
            break;
        default: throw std::runtime_error("Unknown project target"); break;
    }

    write(filePath);
}

void ProjectManager::open(const QString& path) {
    m_path = path;
    QString filePath = Utils::applicationPath(path) + Const::Project::Extension::Binary;

    if (QFileInfo::exists(filePath)) {
        read(filePath);
        return;
    }

    filePath = Utils::libraryPath(path) + Const::Project::Extension::Binary;

    if (QFileInfo::exists(filePath)) {
        read(filePath);
        return;
    }
}

void ProjectManager::close() {
    m_path = QString();
}

void ProjectManager::write(const QString& filePath) {
    QString binaryPath = filePath + Const::Project::Extension::Binary;
    QFile file(binaryPath);

    if (!file.open(QIODeviceBase::WriteOnly)) {
        qWarning().noquote() << "Failed to open binary file for writing:" << binaryPath;
        return;
    }

    QDataStream stream(&file);
    database->serialize(stream);
}

void ProjectManager::read(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODeviceBase::ReadOnly)) {
        qWarning().noquote() << "Failed to open binary file for reading:" << filePath;
        return;
    }

    QDataStream stream(&file);
    database->deserialize(stream);
}

Norm::Token* ProjectManager::createToken(Norm::Code code) const {
    auto token = tokenFactory->create(code);
    database->addToken(token);
    return token;
}

void ProjectManager::removeToken(Norm::Token* token) {
    database->removeToken(token);
}
