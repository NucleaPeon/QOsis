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
    Can be specified multiple times, not sure why you'd want to.


LEFT OFF NOTES
==============

[ ] Projects that depend on the library should attempt to import and if they fail, attempt to include relative
    paths to get access to the code we need.
