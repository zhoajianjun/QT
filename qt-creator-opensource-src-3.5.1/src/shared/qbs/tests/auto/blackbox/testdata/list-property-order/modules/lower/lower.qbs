import qbs

Module {
    property stringList listProp

    Rule {
        inputs: ["intype"]
        Artifact {
            filePath: "dummy.out"
            fileTags: "outtype"
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.sourceCode = function() {
                print("listProp = "
                      + JSON.stringify(product.moduleProperty("lower", "listProp")));
            };
            var prop = product.moduleProperty("lowerlevel", "prop");
            cmd.silent = true;
            return [cmd];
        }
    }
}
