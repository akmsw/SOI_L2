#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char a;
    char b;
    int  x;
    unsigned short int y;
    char c;
    unsigned short int z;
    char d[3];
} BaseData;


typedef struct {
    char a;
    char b;
    int  x;
    unsigned short int y;
    unsigned short int z;
    char c;
    char d[3];
} ReorderData;


typedef struct {
    long unsigned int ll;
    char a;
    char b;
    unsigned short int y;
    int  x;
    unsigned short int z;
    unsigned short int w;
    char c;
    char d[3];
} ExtendedData;

typedef struct  __attribute__((packed)) {
    char a;
    char b;
    int  x;
    unsigned short int y;
    char c;
    unsigned short int z;
    char d[3];
} BaseDataPacked;

#endif

