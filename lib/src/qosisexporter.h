#ifndef QOSISEXPORTER_H
#define QOSISEXPORTER_H


#include "qosiscommons.h"

namespace QOSIS {

class QOsisExporter : public QOsisCommons {
public:
    explicit QOsisExporter();
    QOsisExporter(const QString path);
    ~QOsisExporter();

};

}

#endif
