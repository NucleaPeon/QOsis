#include "test_xml_json.h"

void TestXmlJSON::init()
{
    // Use name that doesn't exist. It will be used later for saving json content but isn't needed
    // for conversion or anything like that.
    _json = new QOsisJson("kjv.json");
}

void TestXmlJSON::testXmlToJson()
{
    QOsisReader *reader = new QOsisReader(TEST_FILE);
    reader->initReader();
    _json->process(reader);
}


void TestXmlJSON::cleanup()
{
    delete _json;
}

