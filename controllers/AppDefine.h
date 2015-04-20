#ifndef APPDEFINE_H
#define APPDEFINE_H

//#define SIMULATOR_MODE

#ifndef SIMULATOR_MODE
const QString API_PATH = "/usr/local/modules/api/";
#else
const QString API_PATH = "./";
#endif

#endif // APPDEFINE_H
