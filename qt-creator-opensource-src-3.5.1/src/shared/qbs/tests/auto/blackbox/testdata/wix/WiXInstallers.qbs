import qbs
import qbs.FileInfo

Project {
    WindowsInstallerPackage {
        name: "QbsSetup"
        targetName: "qbs-" + qbs.architecture
        files: ["QbsSetup.wxs", "ExampleScript.bat"]
        wix.defines: ["scriptName=ExampleScript.bat"]
        wix.extensions: ["WixBalExtension", "WixUIExtension"]

        Export {
            Depends { name: "wix" }
            wix.defines: base.concat(["msiName=" +
                FileInfo.joinPaths(product.buildDirectory,
                    product.targetName + wix.windowsInstallerSuffix)])
        }
    }

    WindowsSetupPackage {
        Depends { name: "QbsSetup" }
        condition: qbs.hostOS.contains("windows") // currently does not work in Wine with WiX 3.9
        name: "QbsBootstrapper"
        targetName: "qbs-setup-" + qbs.architecture
        files: ["QbsBootstrapper.wxs"]
    }

    WindowsInstallerPackage {
        name: "RegressionBuster9000"
        files: ["QbsSetup.wxs", "Qt.wxs", "de.wxl"]
        wix.defines: ["scriptName=ExampleScript.bat"]
        wix.cultures: []
    }
}
