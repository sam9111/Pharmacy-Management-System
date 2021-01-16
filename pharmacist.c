//
// Created by SAMMU on 4/6/20.
//

#include "pharmacist.h"




//generate random id for each drug

int rand_id(void) {

  int num=0;

  srand(time(0));

  num= (rand() % (2000 - 1000 + 1)) + 1000;

  return num;

}

//add drug to inventory

void add_drug(char fname[]){

  FILE *fp;

  fp=fopen(fname,"a");

  drug new_drug;

  new_drug.id=rand_id();

  printf("\nDrug: ");
  scanf("%s",new_drug.name);

  printf("\nManufacturing date(DD MM YY): ");
  scanf("%d %d %d",&new_drug.mfg.day,&new_drug.mfg.month,&new_drug.mfg.year);

  printf("\nExpiry date: ");
  scanf("%d %d %d",&new_drug.expiry.day,&new_drug.expiry.month,&new_drug.expiry.year);

  printf("\nPrice: ");
  scanf("%d",&new_drug.price);

  getchar();

  printf("\nNumber of units to be added to inventory: ");
  scanf("%d",&new_drug.stock);


  fprintf(fp," %d %s %d %d %d %d %d %d %d %d",new_drug.id,new_drug.name,new_drug.mfg.day,new_drug.mfg.month,new_drug.mfg.year,new_drug.expiry.day,new_drug.expiry.month,new_drug.expiry.year,new_drug.price,new_drug.stock);


  printf("\nDrug added to inventory!");

  fclose(fp);

  return;

}

//delete drug

void delete_drug(char fname[]){

  FILE *fp,*fp_tmp;

  drug new_drug;

  int found=0;

  fp=fopen(fname,"r");

  pharmacist person;

  fscanf(fp,"%s %s",person.mobile,person.password);

  if(feof(fp)){

    fclose(fp);

    printf("\nInventory empty!!!");

    return;
  }

  fp_tmp=fopen("tmp.txt", "a");

  if (!fp_tmp) {

    fclose(fp);
    fclose(fp_tmp);

    printf("\nUnable to open temp file.");
    return;
  }
  fprintf(fp_tmp,"%s %s",person.mobile,person.password);


  int drug_id;
  printf("\nDrug ID to be deleted: ");
  scanf("%d",&drug_id);




  while (fscanf(fp,"%d %s %d %d %d %d %d %d %d %d",&new_drug.id,new_drug.name,&new_drug.mfg.day,&new_drug.mfg.month,&new_drug.mfg.year,&new_drug.expiry.day,&new_drug.expiry.month,&new_drug.expiry.year,&new_drug.price,&new_drug.stock)!=EOF
  ) {

    if (drug_id==new_drug.id) {
      printf("\nDrug found and deleted from inventory.");
      found=1;
    }
    else {
      fprintf(fp_tmp," %d %s %d %d %d %d %d %d %d %d",new_drug.id,new_drug.name,new_drug.mfg.day,new_drug.mfg.month,new_drug.mfg.year,new_drug.expiry.day,new_drug.expiry.month,new_drug.expiry.year,new_drug.price,new_drug.stock);

    }
  }
  if (! found) {
    printf("\n%d not found in inventory.",drug_id);
  }

  fclose(fp);
  fclose(fp_tmp);

  remove(fname);
  rename("tmp.txt", fname);

  return;
}

//update details of particular drug in inventory

void update_drug(char fname[]){

  FILE *fp,*fp_tmp;

  drug new_drug;

  int choice;

  int found=0;

  pharmacist person;

  fp=fopen(fname,"r");



  fscanf(fp,"%s %s",person.mobile,person.password);



  if(feof(fp)){

    fclose(fp);

    printf("\nInventory empty!!!");

    return;
  }

  fp_tmp=fopen("tmp.txt", "a");

  if (!fp_tmp) {
    printf("\nUnable to open temp file.");
    return;
  }

  fprintf(fp_tmp,"%s %s",person.mobile,person.password);

  int drug_id;

  printf("\nDrug id to be updated: ");
  scanf("%d",&drug_id);


  while (fscanf(fp,"%d %s %d %d %d %d %d %d %d %d",&new_drug.id,new_drug.name,&new_drug.mfg.day,&new_drug.mfg.month,&new_drug.mfg.year,&new_drug.expiry.day,&new_drug.expiry.month,&new_drug.expiry.year,&new_drug.price,&new_drug.stock)!=EOF
  ) {
    if (drug_id==new_drug.id) {

      found=1;

      printf("\nWhich information would you like to update?"
             "\n1.Name"
             "\n2.Manufacturing date"
             "\n3.Expiry date"
             "\n4.Price"
             "\n5.Stock left"
             "\nEnter number: \n");

      scanf("%d",&choice);

      printf("\nEnter new information: ");

      switch (choice) {

      case 1:

        scanf("%s",new_drug.name);

        break;

      case 2:

        scanf("%d %d %d",&new_drug.mfg.day,&new_drug.mfg.month,&new_drug.mfg.year);

        break;

      case 3:

        scanf("%d %d %d",&new_drug.expiry.day,&new_drug.expiry.month,&new_drug.expiry.year);

        break;

      case 4:

        scanf("%d",&new_drug.price);

        break;

      case 5:

        scanf("%d",&new_drug.stock);

        break;

      }

      fprintf(fp_tmp, " %d %s %d %d %d %d %d %d %d %d", new_drug.id,
              new_drug.name, new_drug.mfg.day, new_drug.mfg.month,
              new_drug.mfg.year, new_drug.expiry.day, new_drug.expiry.month,
              new_drug.expiry.year, new_drug.price, new_drug.stock);

    }
    else {

      fprintf(fp_tmp, " %d %s %d %d %d %d %d %d %d %d", new_drug.id,
              new_drug.name, new_drug.mfg.day, new_drug.mfg.month,
              new_drug.mfg.year, new_drug.expiry.day, new_drug.expiry.month,
              new_drug.expiry.year, new_drug.price, new_drug.stock);
    }
  }
  if (! found) {
    printf("\n%d not found in inventory.",drug_id);
  }

  fclose(fp);
  fclose(fp_tmp);

  remove(fname);
  rename("tmp.txt", fname);

  return;
}

//check inventory for drugs that are expiring in one month

void alert(char fname[]){

  FILE *fp;

  int sys_day,sys_mon,sys_year;

  date today;

  drug new_drug;

  today=sys_date();

  sys_day=today.day;

  sys_mon=today.month;

  sys_mon == 12 ? (sys_mon = 1) : ++sys_mon;

  sys_year=today.year;

  pharmacist person;

  fp=fopen(fname,"r");


  fscanf(fp,"%s %s",person.mobile,person.password);


  if(feof(fp)){

    fclose(fp);

    printf("\nInventory empty!!! No alerts...");

    return;
  }


  while(fscanf(fp,"%d %s %d %d %d %d %d %d %d %d",&new_drug.id,new_drug.name,&new_drug.mfg.day,&new_drug.mfg.month,&new_drug.mfg.year,&new_drug.expiry.day,&new_drug.expiry.month,&new_drug.expiry.year,&new_drug.price,&new_drug.stock)
  ){

    if(new_drug.expiry.day==sys_day&&new_drug.expiry.month==sys_mon&&new_drug.expiry.year==sys_year&&!feof(fp)){

      printf("\nALERT: %s is going to expire in 1 month!!!",new_drug.name);

    }
    if(new_drug.stock==0&&!feof(fp)){

      printf("\nALERT: %s is out of stock!!!!",new_drug.name);
    }
    else if(feof(fp)){
      printf("\n\nNo alerts for now....");
      break;
    }
  }

  fclose(fp);

  return;

}

//register account-create new file

void account_pharmacist(void) {

  pharmacist person;

  printf("\nCreate an account......\nEnter your mobile number: ");

  scanf("%s",person.mobile);

  char fname[15];

  strcpy(fname,person.mobile);

  strcat(fname,".txt");

  FILE *fp1;

  fp1=fopen("sellers.txt","a");

  fprintf(fp1," %s",fname);

  fclose(fp1);


  FILE *fp;

  fp=fopen(fname,"r");

  if(fp){

    printf("\nAn account is already registered in this number!\nTry logging in...");

    fclose(fp);

    return;
  }

  fclose(fp);

  printf("\nEnter a password of your choice(min 10 characters): ");

  scanf("%s",person.password);

  fp=fopen(fname,"w");

  fprintf(fp,"%s %s",person.mobile,person.password);

  fclose(fp);

  printf("\nCongratulations your account has been created!!! Access it with your mobile number as the username and the password you have entered.");

  return;

}

//login

int login_pharmacist(char fname[]){

  pharmacist person;

  printf("\nLogin......\nEnter your mobile number: ");

  scanf("%s",person.mobile);

  strcpy(fname,person.mobile);

  strcat(fname,".txt");


  FILE *fp;

  fp=fopen(fname,"r");

  if(fp==NULL){

    printf("\nAccount does not exist!");

    fclose(fp);

    return 2;
  }

  fscanf(fp,"%s %s",person.mobile,person.password);

  fclose(fp);

  char psw[11];

  printf("\nEnter your password: ");

  scanf("%s",psw);

  getchar();

  if (strcmp(person.password,psw) == 0) {

    printf("\nYou have logged in!");

    return 1;
  }

  else {

    printf("\nYou have typed in the wrong password!");



    return 0;
  }
}

// Prints out the existing inventory of drugs
void print_stock(char fname[]){

  FILE *fp;

  drug new_drug;

  pharmacist person;

  fp=fopen(fname,"r");

  fscanf(fp,"%s %s",person.mobile,person.password);

  if(feof(fp)){

    fclose(fp);

    printf("\nInventory empty!!! No stocks to be displayed...");

    return;
  }

  while(fscanf(fp,"%d %s %d %d %d %d %d %d %d %d",&new_drug.id,new_drug.name,&new_drug.mfg.day,&new_drug.mfg.month,&new_drug.mfg.year,&new_drug.expiry.day,&new_drug.expiry.month,&new_drug.expiry.year,&new_drug.price,&new_drug.stock))
  {

    printf("\nID-%d %s\nMfg: %d/%d/%d\nExpiry: %d/%d/%d\nPrice: $%d\n%d left\n",new_drug.id,
           new_drug.name,new_drug.mfg.day,new_drug.mfg.month,new_drug.mfg.year,
           new_drug.expiry.day,new_drug.expiry.month,new_drug.expiry.year,
           new_drug.price,new_drug.stock);

    if(feof(fp)){

      break;
    }
  }

  fclose(fp);

  return;
}

