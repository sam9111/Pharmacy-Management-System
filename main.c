#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pharmacist.h"
#include "customer.h"




int main() {

  char c;

  int c1;
  char login[15];
  int success;
  int logout = 0;

  printf("                          WELCOME!"
         "\n               ...SVS ONLINE PHARMACY..."
         "\n          All your medicines in one place!!!");

  printf("\n\nAre you the pharmacist or a customer?(p/c) ");

  c = getchar();

  getchar();

  switch (c) {

  case 'p':

    printf("\nDo you have an account?(y/n) ");

    c1 = getchar();

    getchar();

    if (c1 == 'n') {

      account_pharmacist();
    }

    do {
      success = login_pharmacist(login);

      if (success == 2) {
        account_pharmacist();
      }

    } while (success != 1);

    print_stock(login);

    alert(login);

    while (logout == 0) {

      printf("\n\nWhat would you like to do?"
             "\n1.Add drug"
             "\n2.Delete drug"
             "\n3.Update drug"
             "\n4.View inventory"
             "\n5.Logout\n");

      scanf("%d", &c1);

      switch (c1) {

      case 1:

        add_drug(login);
        break;

      case 2:

        delete_drug(login);
        break;

      case 3:

        update_drug(login);
        break;

      case 4:

        print_stock(login);
        break;

      case 5:

        logout = 1;
        break;

      default:

        printf("\nInvalid choice!!! Please try again.....");
        break;
      }
    }

    break;

  case 'c': {

    printf("\nDo you have an account?(y/n) ");

    c1 = getchar();

    getchar();

    if (c1 == 'n') {

      account_customer();
    }

    do {
      success = login_customer(login);
      if (success == 2) {
        account_customer();
      }
    } while (success != 1);

    int seller_count;

    FILE *fp1;

    seller_count = no_sellers();

    char **sellers = (char **)malloc(seller_count * sizeof(char *));

    for (int i = 0; i < seller_count; i++) {
      sellers[i] = (char *)malloc(15 + 1);
    }

    fp1 = fopen("sellers.txt", "r");

    printf("\n\nShop medicines....");

    for (int i = 0; i < seller_count; i++) {

      while (fscanf(fp1, "%s", *(sellers + i)) != EOF) {

        print_stock(*(sellers + i));
      }
    }

    fclose(fp1);

    int cart_count;
    int new_cart_count, drug_id, quantity, remove;

    printf("\nYour cart is empty!!!....\nHow many medicines would you like to add from the list above to the cart? ");

    scanf("%d", &cart_count);

    drug *cart = (drug *)malloc(cart_count * sizeof(drug));

    printf("\nEnter the medicine's ID you would like to purchase and their respective quantities....");

    for (int j = 0; j < cart_count; j++) {

      printf("\nID,Quantity: ");
      scanf("%d %d", &drug_id, &quantity);
      add_cart(cart, seller_count, sellers, drug_id, quantity, j);
    }

    char c2;

      while (logout == 0) {

        printf("\nWhat would you like to do next? "
               "\n1.Add to cart."
               "\n2.Delete from cart."
               "\n3.Clear cart and add new medicines."
               "\n4.Buy."
               "\n5.View cart."
               "\n6.View medicines."
               "\n7.Logout.\n");

        scanf("%d", &c1);

        switch (c1) {

        case 1: {

          printf("\nHow many medicines would you like to add from the list to the cart? ");

          scanf("%d", &new_cart_count);

          cart_count += new_cart_count;

          cart = realloc(cart, sizeof(drug) * cart_count);

          printf("\nEnter medicine IDs and quantities you would like to add to cart.... ");

          for (int j = 0; j < new_cart_count; j++) {
            printf("\nID,Quantity:  ");

            scanf("%d %d", &drug_id, &quantity);

            add_cart(cart, seller_count, sellers, drug_id, quantity, j);
          }
          break;
        }

        case 2: {

          printf("\nNote:You cannot remove everything from the cart...Type # if you want to do so and then select option 3 or press enter if not ...");

          c2 = getchar();

          getchar();

          if (c2 == '#') {

            break;
          }
          printf(
              "\nHow many medicines would you like to remove from the cart? ");

          scanf("%d", &remove);

          new_cart_count = cart_count - remove;

          drug *new_cart = (drug *)malloc((new_cart_count) * sizeof(drug));

          printf("\nEnter medicine IDs and quantities you would like to remove from cart.... ");

          for (int j = 0; j < remove; j++) {
            printf("\nID,Quantity: ");

            scanf("%d %d", &drug_id, &quantity);

            delete_cart(cart, seller_count, sellers, drug_id, quantity,
                        new_cart, cart_count, new_cart_count);
          }

          break;
        }

        case 3: {

          free(cart);

          printf("\nYour cart is empty!!!....\nWould you like to 1.Add medicines or 2.Logout? ");

          c2 = getchar();

          getchar();

          if (c2 == '1') {

            printf("\nHow many medicines would you like to add from the list to the cart? ");

            scanf("%d", &cart_count);

            drug *cart = (drug *)malloc(cart_count * sizeof(drug));

            printf("\nEnter the medicine's ID you would like to purchase and their respective quantities....");

            for (int j = 0; j < cart_count; j++) {

              printf("\nID,Quantity: ");
              scanf("%d %d", &drug_id, &quantity);
              add_cart(cart, seller_count, sellers, drug_id, quantity, j);
            }
          } else {

            logout = 1;
          }
          break;
        }

        case 4:

          buy(cart, login);

          break;

        case 5:

          print_cart(cart, cart_count);

          break;

        case 6: {

          fp1 = fopen("sellers.txt", "r");

          for (int i = 0; i < seller_count; i++) {

            while (fscanf(fp1, "%s", *(sellers + i)) != EOF) {

              print_stock(*(sellers + i));
            }
          }

          fclose(fp1);

          break;
        }

        case 7:

          logout = 1;

          break;
        }
      }

      free(cart);
      free(sellers);

      break;
    }
  }

    printf("                       THANK YOU for visiting our website!!!....STAY SAFE AND STAY HOME!");

    exit(0);
  }

