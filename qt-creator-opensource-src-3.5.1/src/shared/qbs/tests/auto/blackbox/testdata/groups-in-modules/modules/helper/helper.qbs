import qbs
import qbs.FileInfo

Module {
    Depends { name: "cpp" }
    Depends { name: "helper2" }

    additionalProductTypes: ["diamond"]

    Group {
        name: "Helper Sources"
        prefix: path + "/"
        files: ["diamondc.c"]
    }

    Group {
        name: "Additional Chunk"
        prefix: path + "/"
        files: ["chunk.coal"]
    }

    FileTagger {
        patterns: ["*.coal"]
        fileTags: ["coal"]
    }

    Rule {
        inputs: ["coal"]
        explicitlyDependsOn: ["application"]

        Artifact {
            filePath: FileInfo.joinPaths(product.destinationDirectory, input.baseName + ".diamond")
            fileTags: ["diamond"]
        }

        prepare: {
            var cmd = new Command(FileInfo.joinPaths(product.buildDirectory, product.targetName), [input.filePath, output.filePath]);
            cmd.description = "compile " + input.fileName + " => " + output.fileName;
            return [cmd];
        }
    }
}
