#pragma once
#include <QString>

class Global {
public:
    Global();
    static QString workspacePath();
    static bool restoreSession();
};

