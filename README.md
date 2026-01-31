=====
QOsis
=====

Introduction
============

QOSis is a Qt5 utility for handling OSIS file formats.

OSIS stands for Open Scriptural Information Standard™ and is an XML description
of files used generally for biblical texts.

QOsis uses Qt's built in xml components to handle reading, writing, exporting and
importing to various formats, above and beyond what the core SWORD utility does
as this project is to be integrated with SundayBeacon and therefore handle
other presentation software formats as well as SundayBeacon's own, as well as
various text formats (pdf, html, latex) in addition to being a gui and/or cli
application.

QOsis is broken down into three components:

1. Library: An xml parser that acts upon an osis file to create a structure,
   pull data and make edits.
2. CLI application: A program to handle exporting and importing, conversions,
   validation and batch processing
3. GUI application: A program which does what the CLI does but in a graphical
   form for users who do not wish to use the cli and/or prefer a nicer viewing
   utility.


As a developer or integrator, you should know that you can build one or many parts
of the above components by using CMake declarations.

For example, if you wish to build QOsis as just a library (libqosis) then specify:

.. code::

    cd build/ && cmake .. -DONLY_LIBRARY && make && sudo make install

There are 3 declaratives that specify ONLY the component to be built:

    -DONLY_LIBRARY: only build the library component which can be used in other projects
    -DONLY_CLI: Only build the command line interface (will fail if library hasn't been built and is discoverable)
    -DONLY_GUI: Only build the graphical application (will fail if library hasn't been built and is discoverable)

There are 3 declaratives that are *additive* and all specified will be built:

    -DBUILD_LIBRARY: Includes building the library in the cmake command
    -DBUILD_CLI: Includes building the cli in the cmake command
    -DBUILD_GUI: Includes building the gui in the cmake command

Additional Notes:

* ``ONLY_`` declaratives will be prioritized. If specifying multiple ``-DONLY_`` commands,
    the last one will be the one that is recognized.
* ``BUILD_`` declaratives will be appended to a list of projects to be built.
    Can be specified multiple times, but won't have any additional effect.

How to Use
==========

```
#include <qosis.h>

...

void Class::Test()
{

    QOsisReader* reader = new QOsisReader("/path/to/file.xml");
    OsisStructure* osis = reader->getOsisData();
    QList<OsisVerse*> verses = osis.find("Gen", 1, 1, 10)
    foreach(OsisVerse* verse, verses) {
        const QString v = verse->verse();
        // Do stuff with it
    }
}

```


Testing
=======

Due to the xml xsd url not being valid anymore, we modify the kjv.xml file to use local file
'osisCore.2.1.1.xsd' for testing only, although if its absence prevents us from utilitizing
said xml files, we'll have to modify them (automatically?) to use local xsd.


LEFT OFF NOTES
==============

[ ] Finish up xml to structure conversion.

[ ] Projects that depend on the library should attempt to import and if they fail, attempt to include relative
    paths to get access to the code we need.
[ ] When handling <work> tags, ref doc pdf chapter 7 goes over what is valid in each
    tag. Validate those.
[ ] In tests/, create a source and header that contains an actual osis formatted book
    in xml and pass it by reference to all tests so they can act on an actual book
    without having to re-read it and waste memory.
[ ] Download a full bible osis format file and validate/parse it using tests and
    ensure rules are followed.
[ ] Download the xml spec so it can be loaded in. Looks like Qt5 expects a QApplication
    when loading from the network.







Validation
==========

XML Format key points:

    * <osis> </osis> is the main tag (also <osis:osis > </osis:osis> works)
    * OSIS documents can either be a corpus of multiple works, or merely a single text like the KJV Bible
        - <osisText> is the tag to use for a text. <osisCorpus> for multiple <osisText> tags
    * Needs an xml:lang parameter (restrictive compared to osis's own lang)
        *	ISO 639: http://lcweb.loc.gov/standards/iso639-2/langhome.html, or
        *	IANA: ftp://ftp.isi.edu/in-notes/iana/assignments/languages/tags

    * The canonical attribute is available on all elements. It has a ‘default’ value
        - When canonical="true", it means that the content of that element is a part of the text being encoded.
            - canonical attribute should not be used to reflect theological judgment about the content of a text
        - Titles are not generally canonical, but in the case of Psalms, it is.
    * p element is a child of the osisText element
    * The first element following osisText is required to be header
        - The header contains the revisionDesc, work, and workPrefix elements for a particular work. These elements must be entered in that order, although each may occur an unlimited number of times.
    * A work element provides information comparable to that found on the title page of a printed work, using the
    fields defined by the Dublin Core Initiative (see http://dublincore.org/).
    * workPrefix tag at end, after all the <work>
        - "//note/@annotateRef": Needs a leading "//", which means that this will find any note element in the document, wherever it may be found.
        - Needs the /@ and an attribute name after //
    * The div element has a scope attribute that should be used when it contains less than a complete work.



License
=======

This project and library are licensed under the GPL 3.0 license.




