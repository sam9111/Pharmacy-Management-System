//
// Created by SAMMU on 5/6/20.
//

#ifndef CMINIPROJECT_CUSTOMER_H
#define CMINIPROJECT_CUSTOMER_H

#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pharmacist.h"

typedef struct{
  char name[50];
  char email[50];
  char mobile[11];
  char password[11];
}customer;

void buy(drug *ptr,char fname_customer[]);
void account_customer(void);
int login_customer(char fname[]);
int no_sellers(void);
void add_cart(drug *ptr,int no_sellers,char **sellers,int id,int quantity,int cart_count);
void print_cart(drug *ptr,int cart_count);
void delete_cart(drug *ptr, int no_sellers, char **sellers, int id, int quantity,drug *ptr1,int cart_count,int new_cart_count);



#endif // CMINIPROJECT_CUSTOMER_H
