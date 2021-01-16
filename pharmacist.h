//
// Created by SAMMU on 4/6/20.
//

#ifndef CMINIPROJECT_PHARMACIST_H
#define CMINIPROJECT_PHARMACIST_H

#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

typedef struct{
  char mobile[11];
  char password[11];

}pharmacist;

void add_drug(char fname[]);
void delete_drug(char fname[]);
void update_drug(char fname[]);
void alert(char fname[]);
void account_pharmacist(void);
int login_pharmacist(char fname[]);
void print_stock(char fname[]);

int rand_id(void);

#endif // CMINIPROJECT_PHARMACIST_H
