import qbs.base
import qbs.File
import qbs.FileInfo

DynamicLibrary {
    name: "echoplugin"

    Depends { name: "Qt.core" }
    Depends { name: "cpp" }
    bundle.isBundle: false

    Group {
        condition: Qt.core.versionMajor >= 5
        files: [
            "echoplugin.h",
            "echoplugin.cpp",
            "echoplugin.json.source"
        ]
    }
    Group {
        condition: Qt.core.versionMajor < 5
        files: "echoplugin_dummy.cpp"
    }

    cpp.includePaths: buildDirectory

    Transformer {
        condition: Qt.core.versionMajor >= 5
        inputs: ["echoplugin.json.source"]
        Artifact {
            filePath: "echoplugin.json"
            fileTags: ["qt_plugin_metadata"]
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "generating " + FileInfo.fileName(output.filePath);
            cmd.sourceCode = function() {
                File.copy(input.filePath, output.filePath);
            }
            return cmd;
        }
    }
}
