//
// Created by SAMMU on 5/6/20.
//

#include "general.h"

//get system date

date sys_date(void){

  date sys_date;

  time_t T= time(NULL);
  struct tm tm;
  tm = *localtime(&T);

  sys_date.day=tm.tm_mday;

  sys_date.month=tm.tm_mon+1;

  sys_date.year=tm.tm_year+1900;

  return sys_date;

}




//generate random id

int rand_order(void){

  srand(time(0));

  int num = (rand() % (200000 - 100000 + 1)) + 1000;

  return num;

}
