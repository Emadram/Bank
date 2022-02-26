#ifndef TYPES_H
#define TYPES_H

#define MAX_VALUE 55 /*1001*/
#define MIN_SIZE 30  /*101*/
#define MIN_ACC 5  /*101*/
#define CHAR_VALUE 10

/* Enums */

typedef enum
{
    FALSE,
    TRUE
} boolean;

enum Gender
{
    MALE,
    FEMALE,
    OTHER
};

enum Status
{
    INACTIVE,
    ACTIVE
};

enum CustomerLevel
{
    NEWCUSTOMER = 0,
    CUSTOMER = 6,
    LOYALCUSTOMER = 12,
};

enum EmployeeLevel
{
    ENTRYLEVEL = 0,
    INTERMEDIATE = 16,
    EXECUTIVE = 48
};

enum AccountType
{
    SALARY,
    SAVING,
    FIXED
};

/* Structures */

struct Person;
struct Employee;
struct Customer;
struct Accounts;
struct AccountCustomer;
struct Transaction;
struct Deposit;
struct Withdraw;
struct Transfer;

struct Person
{
    char name[MIN_SIZE];
    char lastName[MIN_SIZE];
    char nationalCode[MIN_SIZE];
    enum Gender gender;
    int age;
    int primaryKey;
};

struct Employee
{
    struct Person person;
    enum EmployeeLevel level;
    enum Status stat;
    int employeeId;
    int personKey;
    int primaryKey;
};

struct Customer
{
    struct Person person;
    enum CustomerLevel level;
    enum Status stat;
    int personKey;
    int primaryKey;
};

struct Accounts
{
    unsigned int accountNumber;
    enum AccountType type;
    char value[MAX_VALUE];
};

struct AccountCustomer
{
    struct Accounts accountNumber[MIN_ACC];
    int count;
    int customerKey;
    int primaryKey;
};

struct Transaction
{
    struct AccountCustomer account;
    int transactionId;
    char transactionDate[MIN_SIZE];
    char value[MAX_VALUE];
};

struct Deposit
{
    struct Transaction transaction;
    int depositId;
};

struct Withdraw
{
    struct Transaction transaction;
    int withdrawId;
};

struct Transfer
{
    struct Transaction transaction;
    int transferId;
};

#endif /* TYPES_H */