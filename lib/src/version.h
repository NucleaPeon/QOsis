#ifndef QOSIS_LIB_VERSION_H
#define QOSIS_LIB_VERSION_H

// Compiler accessible definitions

#define QOSIS_LIBRARY_VERSION_RELEASE "1"
#define QOSIS_LIBRARY_VERSION_MAJOR "0"
#define QOSIS_LIBRARY_VERSION_MINOR "11"
#define QOSIS_LIBRARY_VERSION_PATCH "2"

// Program accessible definitions

namespace QOSIS {
    namespace Library {
        namespace Version {
            const int RELEASE = 1;
            const int MAJOR = 0;
            const int MINOR = 11;
            const int PATCH = 2;
        }
    }
}

#endif // QOSIS_LIB_VERSION_H
