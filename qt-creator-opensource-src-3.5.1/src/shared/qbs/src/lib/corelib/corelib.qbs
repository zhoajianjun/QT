import qbs 1.0
import QbsFunctions

QbsLibrary {
    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: ["script", "xml"] }
    Depends { condition: project.enableProjectFileUpdates; name: "Qt.gui" }
    Depends { condition: project.enableUnitTests; name: "Qt.test" }
    name: "qbscore"
    cpp.includePaths: base.concat([
        ".",
        "../.." // for the plugin headers
    ])
    property stringList projectFileUpdateDefines:
        project.enableProjectFileUpdates ? ["QBS_ENABLE_PROJECT_FILE_UPDATES"] : []
    cpp.defines: base.concat([
        "QBS_VERSION=\"" + version + "\"",
        "QT_CREATOR", "QML_BUILD_STATIC_LIB",   // needed for QmlJS
        "SRCDIR=\"" + path + "\""
    ]).concat(projectFileUpdateDefines)

    Properties {
        condition: qbs.targetOS.contains("windows")
        cpp.dynamicLibraries: base.concat(["Psapi"])
    }
    Properties {
        condition: qbs.targetOS.contains("freebsd")
        cpp.dynamicLibraries: base.concat(["util"])
    }
    cpp.dynamicLibraries: base

    Properties {
        condition: qbs.targetOS.contains("darwin")
        cpp.frameworks: "Foundation"
    }

    Group {
        name: product.name
        files: ["qbs.h"]
        qbs.install: project.installApiHeaders
        qbs.installDir: headerInstallPrefix
    }
    Group {
        name: "project file updating"
        condition: project.enableProjectFileUpdates
        prefix: "api/"
        files: [
            "changeset.cpp",
            "changeset.h",
            "projectfileupdater.cpp",
            "projectfileupdater.h",
            "qmljsrewriter.cpp",
            "qmljsrewriter.h",
        ]
    }

    Group {
        name: "api"
        prefix: name + '/'
        files: [
            "internaljobs.cpp",
            "internaljobs.h",
            "jobs.cpp",
            "languageinfo.cpp",
            "project.cpp",
            "project_p.h",
            "projectdata.cpp",
            "projectdata_p.h",
            "propertymap_p.h",
            "rulecommand.cpp",
            "rulecommand_p.h",
            "runenvironment.cpp",
        ]
    }
    Group {
        name: "public api headers"
        qbs.install: project.installApiHeaders
        qbs.installDir: headerInstallPrefix + "/api"
        prefix: "api/"
        files: [
            "jobs.h",
            "languageinfo.h",
            "project.h",
            "projectdata.h",
            "rulecommand.h",
            "runenvironment.h"
        ]
    }
    Group {
        name: "buildgraph"
        prefix: name + '/'
        files: [
            "abstractcommandexecutor.cpp",
            "abstractcommandexecutor.h",
            "artifact.cpp",
            "artifact.h",
            "artifactcleaner.cpp",
            "artifactcleaner.h",
            "artifactset.cpp",
            "artifactset.h",
            "artifactvisitor.cpp",
            "artifactvisitor.h",
            "buildgraph.cpp",
            "buildgraph.h",
            "buildgraphnode.cpp",
            "buildgraphnode.h",
            "buildgraphloader.cpp",
            "buildgraphloader.h",
            "buildgraphvisitor.h",
            "command.cpp",
            "command.h",
            "cycledetector.cpp",
            "cycledetector.h",
            "depscanner.cpp",
            "depscanner.h",
            "emptydirectoriesremover.cpp",
            "emptydirectoriesremover.h",
            "executor.cpp",
            "executor.h",
            "executorjob.cpp",
            "executorjob.h",
            "filedependency.cpp",
            "filedependency.h",
            "inputartifactscanner.cpp",
            "inputartifactscanner.h",
            "jscommandexecutor.cpp",
            "jscommandexecutor.h",
            "nodeset.cpp",
            "nodeset.h",
            "nodetreedumper.cpp",
            "nodetreedumper.h",
            "processcommandexecutor.cpp",
            "processcommandexecutor.h",
            "productbuilddata.cpp",
            "productbuilddata.h",
            "productinstaller.cpp",
            "productinstaller.h",
            "projectbuilddata.cpp",
            "projectbuilddata.h",
            "qtmocscanner.cpp",
            "qtmocscanner.h",
            "rescuableartifactdata.cpp",
            "rescuableartifactdata.h",
            "rulegraph.cpp",
            "rulegraph.h",
            "rulenode.cpp",
            "rulenode.h",
            "rulesapplicator.cpp",
            "rulesapplicator.h",
            "rulesevaluationcontext.cpp",
            "rulesevaluationcontext.h",
            "scanresultcache.cpp",
            "scanresultcache.h",
            "timestampsupdater.cpp",
            "timestampsupdater.h",
            "transformer.cpp",
            "transformer.h"
        ]
    }
    Group {
        name: "public buildgraph headers"
        qbs.install: project.installApiHeaders
        qbs.installDir: headerInstallPrefix + "/buildgraph"
        files: "buildgraph/forward_decls.h"
    }
    Group {
        name: "jsextensions"
        prefix: name + '/'
        files: [
            "file.cpp",
            "file.h",
            "jsextensions.cpp",
            "jsextensions.h",
            "moduleproperties.cpp",
            "moduleproperties.h",
            "process.cpp",
            "process.h",
            "temporarydir.cpp",
            "temporarydir.h",
            "textfile.cpp",
            "textfile.h",
            "domxml.cpp",
            "domxml.h"
        ]
    }
    Group {
        name: "jsextensions (Darwin-specific)"
        prefix: "jsextensions/"
        condition: qbs.targetOS.contains("darwin")
        files: [
            "propertylist.h",
            "propertylist.mm",
            "propertylistutils.h",
            "propertylistutils.mm"
        ]
    }
    Group {
        name: "language"
        prefix: name + '/'
        files: [
            "artifactproperties.cpp",
            "artifactproperties.h",
            "asttools.cpp",
            "asttools.h",
            "builtindeclarations.cpp",
            "builtindeclarations.h",
            "builtinvalue.cpp",
            "builtinvalue.h",
            "deprecationinfo.h",
            "evaluationdata.h",
            "evaluator.cpp",
            "evaluator.h",
            "evaluatorscriptclass.cpp",
            "evaluatorscriptclass.h",
            "filecontext.cpp",
            "filecontext.h",
            "filecontextbase.cpp",
            "filecontextbase.h",
            "filetags.cpp",
            "filetags.h",
            "functiondeclaration.h",
            "identifiersearch.cpp",
            "identifiersearch.h",
            "item.cpp",
            "item.h",
            "itemdeclaration.cpp",
            "itemdeclaration.h",
            "itemobserver.h",
            "itempool.cpp",
            "itempool.h",
            "itemreader.cpp",
            "itemreader.h",
            "itemreaderastvisitor.cpp",
            "itemreaderastvisitor.h",
            "itemreadervisitorstate.cpp",
            "itemreadervisitorstate.h",
            "jsimports.h",
            "language.cpp",
            "language.h",
            "loader.cpp",
            "loader.h",
            "moduleloader.cpp",
            "moduleloader.h",
            "modulemerger.cpp",
            "modulemerger.h",
            "preparescriptobserver.cpp",
            "preparescriptobserver.h",
            "projectresolver.cpp",
            "projectresolver.h",
            "property.h",
            "propertydeclaration.cpp",
            "propertydeclaration.h",
            "propertymapinternal.cpp",
            "propertymapinternal.h",
            "qualifiedid.cpp",
            "qualifiedid.h",
            "resolvedfilecontext.cpp",
            "resolvedfilecontext.h",
            "scriptengine.cpp",
            "scriptengine.h",
            "scriptpropertyobserver.h",
            "value.cpp",
            "value.h"
        ]
    }
    Group {
        name: "public language headers"
        qbs.install: project.installApiHeaders
        qbs.installDir: headerInstallPrefix + "/language"
        files: "language/forward_decls.h"
    }
    Group {
        name: "logging"
        prefix: name + '/'
        files: [
            "ilogsink.cpp",
            "logger.cpp",
            "logger.h",
            "translator.h"
        ]
    }
    Group {
        name: "public logging headers"
        qbs.install: project.installApiHeaders
        qbs.installDir: headerInstallPrefix + "/logging"
        files: "logging/ilogsink.h"
    }
    Group {
        name: "parser"
        prefix: name + '/'
        files: [
            "qmlerror.cpp",
            "qmlerror.h",
            "qmljsast.cpp",
            "qmljsast_p.h",
            "qmljsastfwd_p.h",
            "qmljsastvisitor.cpp",
            "qmljsastvisitor_p.h",
            "qmljsengine_p.cpp",
            "qmljsengine_p.h",
            "qmljsglobal_p.h",
            "qmljsgrammar.cpp",
            "qmljsgrammar_p.h",
            "qmljskeywords_p.h",
            "qmljslexer.cpp",
            "qmljslexer_p.h",
            "qmljsmemorypool_p.h",
            "qmljsparser.cpp",
            "qmljsparser_p.h"
        ]
    }
    Group {
        name: "tools"
        prefix: name + '/'
        files: [
            "architectures.cpp",
            "buildgraphlocker.cpp",
            "buildgraphlocker.h",
            "buildoptions.cpp",
            "cleanoptions.cpp",
            "codelocation.cpp",
            "commandechomode.cpp",
            "error.cpp",
            "executablefinder.cpp",
            "executablefinder.h",
            "fileinfo.cpp",
            "fileinfo.h",
            "filetime.h",
            "generateoptions.cpp",
            "hostosinfo.h",
            "id.cpp",
            "id.h",
            "installoptions.cpp",
            "persistence.cpp",
            "persistence.h",
            "persistentobject.h",
            "preferences.cpp",
            "processresult.cpp",
            "processresult_p.h",
            "processutils.cpp",
            "processutils.h",
            "profile.cpp",
            "progressobserver.cpp",
            "progressobserver.h",
            "projectgeneratormanager.cpp",
            "propertyfinder.cpp",
            "propertyfinder.h",
            "qbsassert.cpp",
            "qbsassert.h",
            "qttools.cpp",
            "qttools.h",
            "scannerpluginmanager.cpp",
            "scannerpluginmanager.h",
            "scripttools.cpp",
            "scripttools.h",
            "settings.cpp",
            "settingsmodel.cpp",
            "setupprojectparameters.cpp",
            "shellutils.cpp",
            "shellutils.h",
            "version.cpp",
            "version.h",
            "weakpointer.h"
        ]
    }
    Group {
        name: "public tools headers"
        prefix: "tools/"
        files: [
            "architectures.h",
            "buildoptions.h",
            "cleanoptions.h",
            "codelocation.h",
            "commandechomode.h",
            "error.h",
            "generateoptions.h",
            "installoptions.h",
            "preferences.h",
            "processresult.h",
            "profile.h",
            "projectgeneratormanager.h",
            "qbs_export.h",
            "settings.h",
            "settingsmodel.h",
            "setupprojectparameters.h",
        ]
        qbs.install: project.installApiHeaders
        qbs.installDir: headerInstallPrefix + "/tools"
    }
    Group {
        condition: qbs.targetOS.contains("windows")
        name: "tools (Windows)"
        prefix: "tools/"
        files: [
            "filetime_win.cpp"
        ]
    }
    Group {
        condition: qbs.targetOS.contains("unix")
        name: "tools (Unix)"
        prefix: "tools/"
        files: [
            "filetime_unix.cpp"
        ]
    }
    Group {
        name: "use_installed.pri"
        files: [
            "use_installed_corelib.pri",
            "../../../qbs_version.pri"
        ]
        qbs.install: project.installApiHeaders
        qbs.installDir: headerInstallPrefix
    }
    Group {
        condition: project.enableUnitTests
        name: "tests"
        cpp.defines: outer.filter(function(def) { return def !== "QT_NO_CAST_FROM_ASCII"; })
        files: [
            "buildgraph/tst_buildgraph.cpp",
            "buildgraph/tst_buildgraph.h",
            "language/tst_language.cpp",
            "language/tst_language.h",
            "tools/tst_tools.h",
            "tools/tst_tools.cpp"
        ]
    }
    Export {
        Depends { name: "Qt"; submodules: ["script", "xml"] }
        cpp.defines: product.projectFileUpdateDefines
    }
}
