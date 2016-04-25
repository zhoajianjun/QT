import qbs

QtApplication {
    type: ["application", "autotest"]
    consoleApplication: true
    property string testName
    name: "tst_" + testName
    Depends { name: "Qt.test" }
    Depends { name: "qbscore" }
    cpp.includePaths: "../../../src"
    cpp.cxxLanguageVersion: "c++11"
    destinationDirectory: "bin"
    Group {
        name: "logging"
        prefix: "../../../src/app/shared/logging/"
        files: [
            "coloredoutput.cpp",
            "coloredoutput.h",
            "consolelogger.cpp",
            "consolelogger.h"
        ]
    }
}
