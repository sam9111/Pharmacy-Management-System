//
// Created by SAMMU on 5/6/20.
//

#ifndef CMINIPROJECT_GENERAL_H
#define CMINIPROJECT_GENERAL_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{

  int day,month,year;
}date;

typedef struct{

  int id;

  char name[50];

  date mfg,expiry;

  int price;

  int stock;

}drug;


date sys_date(void);

int rand_order(void);


#endif // CMINIPROJECT_GENERAL_H
