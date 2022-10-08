#pragma once
#include <QString>
#include <QObject>

namespace Const {

namespace Version {

}

namespace App {
    constexpr auto Organization = "Norm Group";
    constexpr auto Name = "Normalizer";
    constexpr auto Status = ""; // Release, Beta, Alpha
    constexpr auto Url = "https://github.com/krre/normalizer";
    constexpr auto CopyrightYear = "2022";
    constexpr auto BuildDate = __DATE__;
    constexpr auto BuildTime = __TIME__;
}

namespace Window {
    constexpr int MaxRecentFiles = 10;
    constexpr auto BackgroundColor = 0x4d4d4f;
}

namespace Project {
    constexpr auto WorkspaceDir = "NormProjects";
    constexpr auto DataDir = ".normalizer";
    constexpr auto OutputDir = "output";
    constexpr auto SettingsFile = "settings.json";
    constexpr auto SessionFile = "session.json";

    namespace Extension {
        constexpr auto Binary = ".norm";
    }

    namespace Target {
        namespace Application {
            const QString Name = QObject::tr("Application");
            constexpr auto Source = "app";
        }

        namespace Library {
            const QString Name = QObject::tr("Library");
            constexpr auto Source = "lib";
        }
    }
}

}
