#ifndef SDMSCDRIVER_H
#define SDMSCDRIVER_H

#include "usbd_msc.h"

bool initSDIOThread();
void xSDIOThread(void *pvParameters);
void xSDTestThread(void *pvParameters);

extern USBD_StorageTypeDef SdMscDriver;

#endif // SDMSCDRIVER_H
