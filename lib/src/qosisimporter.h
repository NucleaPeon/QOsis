#ifndef QOSISIMPORTER_H
#define QOSISIMPORTER_H

#include "qosiscommons.h"

namespace QOSIS {

class QOsisImporter : public QOsisCommons {

public:
    explicit QOsisImporter();
    QOsisImporter(const QString path);
    ~QOsisImporter();

};

}

#endif
