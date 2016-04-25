import qbs

Project {
    Product {
        name: "p1"
        type: "blubb1"
        Transformer {
            Artifact {
                filePath: "dummy1.txt"
                fileTags: product.type
            }
            prepare: {
                var cmd = new JavaScriptCommand();
                cmd.silent = true;
                cmd.sourceCode = function() {
                    print(product.buildDirectory);
                }
                return cmd;
            }
        }
    }
    Product {
        name: "p2"
        type: "blubb2"
        Depends { name: "p1" }
        Rule {
            inputsFromDependencies: "blubb1"
            Artifact {
                filePath: "dummy2.txt"
                fileTags: product.type
            }
            prepare: {
                var cmd = new JavaScriptCommand();
                cmd.silent = true;
                cmd.sourceCode = function() {
                    print(product.buildDirectory);
                    print(project.buildDirectory);
                    print(project.sourceDirectory);
                }
                return cmd;
            }
        }
    }
}
