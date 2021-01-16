//
// Created by SAMMU on 5/6/20.
//

#include "customer.h"


//add drug to cart

void add_cart(drug *ptr, int no_sellers, char **sellers, int id, int quantity,int cart_count) {

  FILE *fp, *fp_tmp;

  int found = 0;

  drug new_drug;

  pharmacist person;

  for (int i = 0; i < no_sellers; i++) {

    fp = fopen(*(sellers + i), "r");

    fscanf(fp, "%s %s", person.mobile, person.password);

    if (feof(fp)) {

      fclose(fp);

      printf("\nInventory empty!!!");

      return;
    }

    fp_tmp = fopen("tmp.txt", "a");

    fprintf(fp_tmp, "%s %s", person.mobile, person.password);

    while (fscanf(fp, "%d %s %d %d %d %d %d %d %d %d", &new_drug.id,
                  new_drug.name, &new_drug.mfg.day, &new_drug.mfg.month,
                  &new_drug.mfg.year, &new_drug.expiry.day,
                  &new_drug.expiry.month, &new_drug.expiry.year,
                  &new_drug.price, &new_drug.stock) != EOF) {
      if (id == new_drug.id) {

        found = 1;

        if (new_drug.stock == 0 || (new_drug.stock - quantity) < 0) {
          printf("\n%s has sold out!!!", new_drug.name);

          fprintf(fp_tmp, " %d %s %d %d %d %d %d %d %d %d", new_drug.id,
                  new_drug.name, new_drug.mfg.day, new_drug.mfg.month,
                  new_drug.mfg.year, new_drug.expiry.day, new_drug.expiry.month,
                  new_drug.expiry.year, new_drug.price, new_drug.stock);

          continue;
        }

        new_drug.stock -= quantity;

        fprintf(fp_tmp, " %d %s %d %d %d %d %d %d %d %d", new_drug.id,
                new_drug.name, new_drug.mfg.day, new_drug.mfg.month,
                new_drug.mfg.year, new_drug.expiry.day, new_drug.expiry.month,
                new_drug.expiry.year, new_drug.price, new_drug.stock);

        new_drug.stock = quantity;

        ptr[cart_count] = new_drug;

        printf("\n%s added to cart!", new_drug.name);

      } else {

        fprintf(fp_tmp, " %d %s %d %d %d %d %d %d %d %d", new_drug.id,
                new_drug.name, new_drug.mfg.day, new_drug.mfg.month,
                new_drug.mfg.year, new_drug.expiry.day, new_drug.expiry.month,
                new_drug.expiry.year, new_drug.price, new_drug.stock);
      }
    }

    fclose(fp);
    fclose(fp_tmp);

    remove(*(sellers + i));
    rename("tmp.txt", *(sellers + i));

    if (!found) {
      printf("\n%d not found in inventory.", id);
    }

  }

  return;
}

//remove drug from cart

void delete_cart(drug *ptr, int no_sellers, char **sellers, int id, int quantity,
                drug *ptr1,int cart_count,int new_cart_count) {


  FILE *fp,*fp_tmp;

  int found = 0;

  drug new_drug;

  pharmacist person;

  for (int i = 0; i < no_sellers; i++) {

    fp = fopen(*(sellers + i), "r");

    fscanf(fp,"%s %s",person.mobile,person.password);

    if(feof(fp)){

      fclose(fp);

      printf("\nInventory empty!!!");

      return;
    }

    fp_tmp = fopen("tmp.txt", "w");

    fprintf(fp,"%s %s",person.mobile,person.password);

    while (fscanf(fp," %d %s %d %d %d %d %d %d %d %d",&new_drug.id,new_drug.name,&new_drug.mfg.day,&new_drug.mfg.month,&new_drug.mfg.year,&new_drug.expiry.day,&new_drug.expiry.month,&new_drug.expiry.year,&new_drug.price,&new_drug.stock)!=EOF
        ){
      if (id == new_drug.id) {

        found = 1;

        new_drug.stock += quantity;

        fprintf(fp_tmp," %d %s %d %d %d %d %d %d %d %d",new_drug.id,new_drug.name,new_drug.mfg.day,new_drug.mfg.month,new_drug.mfg.year,new_drug.expiry.day,new_drug.expiry.month,new_drug.expiry.year,new_drug.price,new_drug.stock);


      }
      else {

        fprintf(fp_tmp," %d %s %d %d %d %d %d %d %d %d",new_drug.id,new_drug.name,new_drug.mfg.day,new_drug.mfg.month,new_drug.mfg.year,new_drug.expiry.day,new_drug.expiry.month,new_drug.expiry.year,new_drug.price,new_drug.stock);

      }
    }

    fclose(fp);
    fclose(fp_tmp);

    remove(*(sellers + i));
    rename("tmp.txt", *(sellers + i));
  }

  for(int i= 0;i<new_cart_count;i++){

    for(int j=0;j<cart_count;j++) {

      if (ptr[j].id != id) {

        ptr1[i]=ptr[j];

      }
    }
  }
  if (!found) {
    printf("\n%d not found in cart.", id);

  }

  return;
}

void buy(drug *ptr,char fname_customer[]){

  int i=0,order;

  FILE *fp;

  char address[50];

  printf("\nEnter your address: ");

  scanf("%s",address);

  getchar();

  fp= fopen(fname_customer, "a");

  date today=sys_date();

  order=rand_order();

  printf("\n\n\n         ORDER-SVS%d",order);
  printf("\n\n%d/%d/%d",today.day,today.month,today.year);
  printf("\nYour order: ");

  fprintf(fp," %d/%d/%d",today.day,today.month,today.year);


  while((ptr+i)&&(ptr+i)->stock!=0){

    fprintf(fp," %d %s -%d units",(ptr+i)->id,(ptr+i)->name,(ptr+i)->stock);

    printf("%d %s - %d units",(ptr+i)->id,(ptr+i)->name,(ptr+i)->stock);

    i++;
  }

  printf("\nThe above items will be shipped to \n %s \n within 1 week.Only cash on delivery will be accepted.\n\n\n",address);

  fclose(fp);

 return;
}

//register a account-create new file

void account_customer(void) {

  customer person;

  printf("\nCreate an account......\nEnter your name,email and mobile number: ");

  scanf("%s %s %s",person.name,person.email,person.mobile);

  char fname[15];

  strcpy(fname,person.mobile);

  strcat(fname,".txt");

  FILE *fp;

  fp=fopen(fname,"r");

  if(fp){

    printf("\nAn account is already registered in this number!\nTry logging in...");

    fclose(fp);

    return;
  }

  fclose(fp);

  printf("\nEnter a password of your choice: ");

  scanf("%s",person.password);

  fp=fopen(fname,"w");

  fprintf(fp,"%s %s %s %s",person.name,person.email,person.mobile,person.password);

  fclose(fp);

  printf("\nCongratulations your account has been created!!! Access it with your mobile number as the username and the password you have entered.");

  return;

}

//login

int login_customer(char fname[]){


  customer person;

  printf("\nLogin......\nEnter your mobile number: ");

  scanf("%s",person.mobile);

  strcpy(fname,person.mobile);

  strcat(fname,".txt");

  FILE *fp;

  fp=fopen(fname,"r");

  if(fp==NULL){

    fclose(fp);
    printf("\nAccount does not exist!");

    return 2;
  }

  fscanf(fp,"%s %s %s %s",person.name,person.email,person.mobile,person.password);

  char psw[11];

  printf("\nEnter your password: ");

  scanf("%s",psw);

  if(strcmp(person.password,psw)==0){

    printf("\nYou have logged in!");

    fclose(fp);

    return 1;
  }
  else{
    printf("\nYou have typed in the wrong password!");

    fclose(fp);

    return 0;
  }

}

int no_sellers(void){

  FILE *fp;

  int i=0;

  char seller[15];

  fp=fopen("sellers.txt","r");

  while(fscanf(fp,"%s",seller)!=EOF){

    i++;
  };

  fclose(fp);

  return i;
}


//print cart

void print_cart(drug *ptr,int cart_count) {

  printf("\nYour cart contains: ");

  for(int i=0;i<cart_count;i++){

    printf("%s %d units",(ptr+i)->name,(ptr+i)->stock);

  }

  return;
}



