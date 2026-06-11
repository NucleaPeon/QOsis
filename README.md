=====
QOsis
=====

Introduction
============

QOSis is a Qt5 library, UI and CLI for handling osis xml files.

OSIS stands for Open Scriptural Information Standard™ and handles organization of
large texts and their metadata.

QOsis uses Qt's built in xml components to handle reading, writing, exporting and
importing to various formats, above and beyond what the core SWORD utility does.
It is a work in progress and some features may not yet be complete. See list below
for more details.

QOsis is broken down into three components:

1. Library: An xml parser that acts upon an osis file to create a structure,
   pull data and make edits.
2. CLI application: A program to handle exporting and importing, conversions,
   validation and batch processing of files.
3. GUI application: A program to handle single osis file viewing, exporting and
    importing.


(Only the library and the gui work right now)

Installation Procedure
======================

Depending on which component you want to install, navigate to that directory, go into the ``build/``
directory and run::

```
    cmake ..
    make -j
    sudo make install
```

**Both CLI and GUI components depend on having the library installed first.**


Code Example
============

```
#include <qosis.h>

...

void Class::ExampleFunction()
{

    QOsis* osis = new QOsis("/path/to/file.xml");
    QOsisReader* reader = osis->reader();
    OsisStructure* osis = reader->getOsisData();
    QList<OsisVerse*> verses = osis.find("BookName", 1, 1, 10)
    foreach(OsisVerse* verse, verses) {
        const QString v = verse->verse();
        // Do stuff with it
    }
}

void Class::importExportExample()
{
    QOsis* osis = new QOsis("/path/to/file.xml");
    QOsisReader* reader = osis->reader();
    OsisStructure* osis = reader->getOsisData();
    // We write to a temporary file
    const QString newpath = QString("%1/%2.json").arg(QDir::tempPath(), "test");
    QOsisExporter::writeJsonFile(newpath, st);
    // We load it back in
    QOsisStructure* st = QOsisImporter::importJsonFile(newpath);
    
    // When exporting and importing with json, you have the option of compressing
    // the file (1-9 range), <= 0 means uncompressed.
    // Using JSON to read/write osis books can be up to 40x faster than parsing XML 
    // (at least through Qt 5.3.2 on OS X with brief testing)
    
}

```


TODO List
=========

    [ ] Ensure OSIS Licensing is not infringed with our license and include it in the project
    
    [ ] GUI has non-functional about and preferences windows, only is used to read a file.
        [ ] Include export and import functions
        
    [ ] CLI has not been worked on, so is non-functional. Make it functional.
    
    [ ] Add documentation and instructions on how to build them
    
    [ ] Maybe rename test filenames from test_xml_ to test_

    [ ] Exporting into JSON loses some accuracy data (such as book ordering, chapter and verse numbering
                                                      and we assume based on array index instead)
    
    [ ] Have a test class that only measures benchmarks of different functions (ie: import,export,parse xml)


License
=======

This project and library are licensed under the GPL 2.0 license, however this does not override any
licenses that the OSIS project has in place.



Testing
=======

The xml XSD url is not valid anymore. To allow testing with Qt5 XML utilities, modify the xml file
to use local file 'osisCore.2.1.1.xsd'. See ``tests/`` code for more details.

Change the following tag in your xml file:

```
<osis xsi:schemaLocation='http://www.bibletechnologies.net/2003/OSIS/namespace http://www.bibletechnologies.net/osisCore.2.1.1.xsd' xmlns='http://www.bibletechnologies.net/2003/OSIS/namespace' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'>
```

to

```
<osis xsi:schemaLocation='http://www.bibletechnologies.net/2003/OSIS/namespace osisCore.2.1.1.xsd' xmlns='http://www.bibletechnologies.net/2003/OSIS/namespace' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'>
```

for any test files.
