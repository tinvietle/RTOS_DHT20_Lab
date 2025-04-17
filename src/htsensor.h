#ifndef __HTSENSOR_H__
#define __HTSENSOR_H__

#include <DHT20.h>

extern DHT20 dht20;
extern uint8_t count;

void readDHT(void);

#endif