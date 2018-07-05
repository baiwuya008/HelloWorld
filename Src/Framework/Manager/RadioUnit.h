#ifndef RADIOUNIT_H
#define RADIOUNIT_H

//for ASIA
#define AM_MIN   531
#define AM_MAX   1602
#define AM_STEP  9

#define FM_MIN   87500
#define FM_MAX   108000
#define FM_STEP  100

typedef enum {
    BAND_FM=1,
    BAND_AM,
    BAND_UNKNOW,
}BAND;

typedef enum {
    DIR_UP=1,
    DIR_DOWN,
}DIRECT;
#endif // RADIOUNIT_H
