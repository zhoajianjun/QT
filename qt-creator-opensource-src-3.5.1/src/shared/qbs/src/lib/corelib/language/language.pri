include(../../../install_prefix.pri)

HEADERS += \
    $$PWD/artifactproperties.h \
    $$PWD/asttools.h \
    $$PWD/builtindeclarations.h \
    $$PWD/builtinvalue.h \
    $$PWD/deprecationinfo.h \
    $$PWD/evaluationdata.h \
    $$PWD/evaluator.h \
    $$PWD/evaluatorscriptclass.h \
    $$PWD/filecontext.h \
    $$PWD/filecontextbase.h \
    $$PWD/filetags.h \
    $$PWD/forward_decls.h \
    $$PWD/functiondeclaration.h \
    $$PWD/identifiersearch.h \
    $$PWD/item.h \
    $$PWD/itemdeclaration.h \
    $$PWD/itemobserver.h \
    $$PWD/itempool.h \
    $$PWD/itemreader.h \
    $$PWD/itemreaderastvisitor.h \
    $$PWD/itemreadervisitorstate.h \
    $$PWD/jsimports.h \
    $$PWD/language.h \
    $$PWD/loader.h \
    $$PWD/moduleloader.h \
    $$PWD/modulemerger.h \
    $$PWD/preparescriptobserver.h \
    $$PWD/projectresolver.h \
    $$PWD/property.h \
    $$PWD/propertydeclaration.h \
    $$PWD/propertymapinternal.h \
    $$PWD/qualifiedid.h \
    $$PWD/resolvedfilecontext.h \
    $$PWD/scriptengine.h \
    $$PWD/scriptpropertyobserver.h \
    $$PWD/value.h

SOURCES += \
    $$PWD/artifactproperties.cpp \
    $$PWD/asttools.cpp \
    $$PWD/builtindeclarations.cpp \
    $$PWD/builtinvalue.cpp \
    $$PWD/evaluator.cpp \
    $$PWD/evaluatorscriptclass.cpp \
    $$PWD/filecontext.cpp \
    $$PWD/filecontextbase.cpp \
    $$PWD/filetags.cpp \
    $$PWD/identifiersearch.cpp \
    $$PWD/item.cpp \
    $$PWD/itemdeclaration.cpp \
    $$PWD/itempool.cpp \
    $$PWD/itemreader.cpp \
    $$PWD/itemreaderastvisitor.cpp \
    $$PWD/itemreadervisitorstate.cpp \
    $$PWD/language.cpp \
    $$PWD/loader.cpp \
    $$PWD/moduleloader.cpp \
    $$PWD/modulemerger.cpp \
    $$PWD/preparescriptobserver.cpp \
    $$PWD/projectresolver.cpp \
    $$PWD/propertydeclaration.cpp \
    $$PWD/propertymapinternal.cpp \
    $$PWD/qualifiedid.cpp \
    $$PWD/resolvedfilecontext.cpp \
    $$PWD/scriptengine.cpp \
    $$PWD/value.cpp

qbs_enable_unit_tests {
    HEADERS += $$PWD/tst_language.h
    SOURCES += $$PWD/tst_language.cpp
    OTHER_FILES += $$PWD/testdata/*
}

!qbs_no_dev_install {
    language_headers.files = $$PWD/forward_decls.h
    language_headers.path = $${QBS_INSTALL_PREFIX}/include/qbs/language
    INSTALLS += language_headers
}
