//
// Created by ukio on 1/24/22.
//

#include "ApplicationData.hpp"


/* Private (Not allowed in singleton) */

ApplicationData::ApplicationData() { }

ApplicationData::ApplicationData(const ApplicationData &other) { }

ApplicationData &ApplicationData::operator=(const ApplicationData &other) { return *this; }

ApplicationData::~ApplicationData() { }

ApplicationData::Ptr ApplicationData::instance() {
    static Ptr result (new ApplicationData);
    return result;
}



