#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "headers.h"
#include "types.h"

#define END_OF_STR '\0'
#define MULTI_TAB "\t\t\t\t"
#define MULTI_TAB2 "\t\t"
#define X_LINE    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#define S_LINE    "****************************************"
#define D_LINE    "-----------------------------------------"
#define X_HOLDER  "X                                      X"
#define CHA_HOLDER  "-------------------===-------------------"
#define TAB_TAB   printf(MULTI_TAB)
#define TAB_TAB2   printf(MULTI_TAB2)

/*Main functions
 *
 *TODO : Void -> Int for status
 *TODO : Some part of the code is repeated should be converted to function
 *TODO : Functions to be separated into more headers
 */
void getInt(int *value);

void menuHelper(int times);
void menuHelper2(struct Person per);
void menuHelper3(struct Customer cust);
void menuHelper4(struct Employee empy);
struct tm *timeHelper();

void depositHelper(struct Transaction *transaction, int idx);
int withdrawHelper(struct Transaction *transaction, int idx);

void createLog(char name[], int pKey);
void loginLog(char name[], struct Person per);
void createAccLog(struct AccountCustomer accCust, struct Customer cust);
void createTransactionLog(struct Transaction transAct, struct Transaction transActTo, int code, int number);

void employeeInfo();
void customerInfo();
void accountsInfo(struct Employee employee);
void readFile(char fileName[MIN_SIZE]);

void updateAccount(struct AccountCustomer accCust, int idx);
void updateCustomer(struct Customer cust, int idx);
void updateEmployee(struct Employee empy, int idx);

int findPerson(struct Person *per);
int loginFinder(char name[MIN_SIZE], char code[MIN_SIZE], struct Person *per);
int findCustomer(struct Person person, struct Customer *customer);
int findEmployee(struct Person person, struct Employee *employee);
int findAccount(struct AccountCustomer *accCust, int pKey);
int findAccountNo(struct AccountCustomer accCust, int accNo);

void personMaker();
void customerMaker();
void employeeMaker();

void doLoan(struct Customer customer);
void doEdit(struct Customer *customer);

void doDeposit(struct Customer customer, int code);
void doWithdraw(struct Customer customer);
void doTransfer(struct Customer customer);
void customerTransaction(struct Customer customer);

void createAccount(struct Customer customer);
void showAccount(struct Customer customer, int code);
void customerAccountControl(struct Customer customer);

void personDashBoard(struct Person person);
void customerDashBoard(struct Customer customer);
void employeeDashBoard(struct Employee person);

void personLogin(int pos);

int menu();
int login();
int create();
void option(int choice);

/*Calculator sideProject*/

void clean_buffer(char val);
char *get_unsigned_number();
void get_int(int *index);
char *get_digit(char *number1, int index);
char *get_value_of_digit(char *number1, int index);

char *str_rev(char *number1);

char *add_unsigned_number(char *number1, char *number2);
char *subtract_unsigned_number(char *number1, char *number2);
char *multiply_unsigned_number_to_char(char *number1, char digit);
char *multiply_unsigned_number(char *number1, char *number2);
char *power_unsigned_number(char *base, char *power);

#endif /* FUNCTIONS_H */