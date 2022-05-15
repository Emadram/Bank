#include "functions.h"

/* Global */
static int transactionIdNo = 0;
static int logId = 0;

/**
 * Function to get a digit and the newline character
 * @param value giving address of int
 */
void getInt(int *value)
{
    scanf("%d", value);
    getchar();
}

/**
 * Function helper for menu
 * @param times  number of times to print X_HOLDER
 */
void menuHelper(int times)
{
    TAB_TAB2;
    puts(X_LINE);
    TAB_TAB2;
    int flag = 0;
    while(times--)
    {
        if (flag == 2)
            printf("X               CLI BANK               X\n");
        else
            puts(X_HOLDER);
        TAB_TAB2;
        ++flag;
    }
    puts(X_LINE);
    putchar('\n');
}

/**
 * Function helper for Person dashboard
 * @param per person info
 */
void menuHelper2(struct Person per)
{
    TAB_TAB2;
    puts(X_LINE);
    TAB_TAB2;
    printf("X-Name: %s%s                            \n", per.name, per.lastName);
    TAB_TAB2;
    printf("X-Nationalcode: %s                              \n", per.nationalCode);
    TAB_TAB2;
    printf("X-Limited                              \n");
    TAB_TAB2;
    puts(X_LINE);
    putchar('\n');
}

/**
 * Function helper for Customer dashboard
 * @param customer customer info
 */
void menuHelper3(struct Customer customer)
{
    TAB_TAB2;
    puts(X_LINE);
    TAB_TAB2;
    printf("X-Name: %s%s                            \n", customer.person.name, customer.person.lastName);
    TAB_TAB2;
    printf("X-Nationalcode: %s                              \n", customer.person.nationalCode);

    TAB_TAB2;
    if (customer.stat == ACTIVE)
    {
        printf("X-Status: ACTIVE                              \n");
    }
    else
    {
        printf("X-Status: INACTIVE                              \n");
    }

    TAB_TAB2;
    if (customer.level < CUSTOMER)
    {
        printf("X-Level: NEWCUSTOMER                              \n");
    }
    else if (customer.level < LOYALCUSTOMER)
    {
        printf("X-Level: CUSTOMER                              \n");
    }
    else
    {
        printf("X-Level: LOYALCUSTOMER                              \n");
    }
    TAB_TAB2;
    puts(X_LINE);
    putchar('\n');
}

/**
 *Function helper for employee dashboard
 * @param employee employee info
 */
void menuHelper4(struct Employee employee)
{
    TAB_TAB2;
    puts(X_LINE);
    TAB_TAB2;
    printf("X-Name: %s%s                            \n", employee.person.name, employee.person.lastName);
    TAB_TAB2;
    printf("X-Nationalcode: %s                              \n", employee.person.nationalCode);
    TAB_TAB2;
    printf("X-ID: %d                              \n", employee.primaryKey);

    TAB_TAB2;
    if (employee.stat == ACTIVE)
    {
        printf("X-Status: ACTIVE                              \n");
    }
    else
    {
        printf("X-Status: INACTIVE                              \n");
    }

    TAB_TAB2;
    if (employee.level < INTERMEDIATE)
    {
        printf("X-Level: ENTRYLEVEL                              \n");
    }
    else if (employee.level >= EXECUTIVE)
    {
        printf("X-Level: EXECUTIVE                              \n");
    }
    else
    {
        printf("X-Level: INTERMEDIATE                              \n");
    }
    TAB_TAB2;
    puts(X_LINE);
    putchar('\n');
}

/**
 *Function for getting time
 * @return time struct tm
 */
struct tm *timeHelper()
{
    time_t rawTime;
    time (&rawTime);
    return localtime (&rawTime);
}

/**
 *Function for depositing action
 * @param transaction Giving transaction address
 * @param idx Giving index of account
 */
void depositHelper(struct Transaction *transaction, int idx)
{
    strcpy(transaction->value, get_unsigned_number());

    if (strcmp(transaction->account.accountNumber[idx].value, "0") == 0)
    {
        strcpy(transaction->account.accountNumber[idx].value, transaction->value);
    }
    else if (strlen(transaction->account.accountNumber[idx].value) > strlen(transaction->value))
    {
        strcpy(transaction->account.accountNumber[idx].value,
               add_unsigned_number(transaction->value,
                                   transaction->account.accountNumber[idx].value));
    }
    else
    {
        strcpy(transaction->account.accountNumber[idx].value,
               add_unsigned_number(transaction->account.accountNumber[idx].value,
                                   transaction->value));
    }
}

/**
 *Function for withdrawing action
 * @param transaction Giving transaction address
 * @param idx Giving index of account
 * @return -2 if failed 0 otherwise
 */
int withdrawHelper(struct Transaction *transaction, int idx)
{
    strcpy(transaction->value, get_unsigned_number());


    if (strlen(transaction->account.accountNumber[idx].value) > strlen(transaction->value))
    {
        strcpy(transaction->account.accountNumber[idx].value,
               subtract_unsigned_number(transaction->account.accountNumber[idx].value,
                                        transaction->value));
    }
    else
    {
        TAB_TAB2;
        puts("Not enough money you have to at least keep 10% of your money in bank");
        system("pause");
        system("cls");
        return -2;
    }
    return 0;
}

/**
 * Function for writing create log into log.dat
 * @param name Person, Customer or Employee
 * @param pKey privateKey of the account
 */
void createLog(char name[], int pKey)
{

    struct tm * timeinfo;
    timeinfo = timeHelper();

    FILE *report;
    report = fopen ("dat\\log.dat", "a");
    if (logId == 0)
        fprintf(report, "%s\n%s\n", D_LINE, D_LINE);

    fprintf(report, "%d-%sA %s has been created Pkey = [%d]",
            logId, asctime(timeinfo), name, pKey-1);
    fprintf(report, "\n%s\n", S_LINE);

    fclose(report);
    ++logId;
}

/**
 * Function for writing login log into log.dat
 * @param name Person, Customer or Employee
 * @param per Person info
 */
void loginLog(char name[], struct Person per)
{
    struct tm * timeinfo;
    timeinfo = timeHelper();

    FILE *report;
    report = fopen ("dat\\log.dat", "a");
    if (logId == 0)
        fprintf(report, "%s\n%s\n", D_LINE, D_LINE);

    fprintf(report, "%d-%s%s with name = [%s%s] and nationalCode = [%s] logged "
                    "Pkey = [%d]",
            logId, asctime(timeinfo), name, per.name, per.lastName,
            per.nationalCode, per.primaryKey);

    fprintf(report, "\n%s\n", S_LINE);

    fclose(report);
    ++logId;
}

/**
 *Function for writing created account log into log.dat
 *@param accCust accounts info
 *@param cust customer info
 */
void createAccLog(struct AccountCustomer accCust, struct Customer cust)
{
    struct tm * timeinfo;
    timeinfo = timeHelper();

    int idx = accCust.count - 1;
    FILE *report;
    report = fopen ("dat\\log.dat", "a");
    if (logId == 0)
        fprintf(report, "%s\n%s\n", D_LINE, D_LINE);

    fprintf(report, "%d-%sAn %s with accountNumber = [%u] and Pkey = [%d]"
                    "Has been created For customer with name = [%s%s] and nationalCode = [%s]",
            logId, asctime(timeinfo), "Account",
            accCust.accountNumber[idx].accountNumber, accCust.primaryKey, cust.person.name,
            cust.person.lastName, cust.person.nationalCode);

    fprintf(report, "\n%s\n", S_LINE);

    fclose(report);
    ++logId;
}

/**
 *Function for writing transaction log into transaction.dat
 * @param transAct
 * @param transActTo
 * @param code 1 = deposit // 2 = withdraw // 3 = transfer
 * @param number
 */
void createTransactionLog(struct Transaction transAct, struct Transaction transActTo, int code, int number)//
{
    struct tm * timeinfo;
    timeinfo = timeHelper();

    FILE *report;
    report = fopen ("dat\\transaction.dat", "a");
    if (logId == 0)
        fprintf(report, "%s\n%s\n", D_LINE, D_LINE);

    if (code == 1)//deposit
    {
        fprintf(report, "%d-%sA %s by account number = [%u] and transactionId = [%d] "
                        "and amount = [$%s] has been made account Pkey = [%d] customer Pkey = [%d]",
                logId, asctime(timeinfo), "Deposit",transAct.account.accountNumber[number].accountNumber,
                transAct.transactionId-1, transAct.value, transAct.account.primaryKey,
                transAct.account.customerKey);
    }
    else if (code == 2)// withdraw
    {
        fprintf(report, "%d-%sA %s by account number = [%u] and transactionId = [%d] "
                        "and amount = [-$%s] has been made account Pkey = [%d] customer Pkey = [%d]",
                logId, asctime(timeinfo), "Withdraw",transAct.account.accountNumber[number].accountNumber,
                transAct.transactionId-1, transAct.value, transAct.account.primaryKey,
                transAct.account.customerKey);
    }

    else//transfer
    {
        fprintf(report, "%d-%sA %s from account number = [%u] to account number = [%u] with transactionId = [%d] "
                        "and amount = [-$%s] has been made account Pkey = [%d] customer Pkey = [%d] to"
                        "account pKey = [%d] customer Pkey = [%d]",
                logId, asctime(timeinfo), "Transfer",transAct.account.accountNumber[number].accountNumber,
                transActTo.account.accountNumber[number].accountNumber, transAct.transactionId-1,
                transAct.value, transAct.account.primaryKey,transAct.account.customerKey
                ,transActTo.account.primaryKey,transActTo.account.customerKey);
    }
    fprintf(report, "\n%s\n", S_LINE);

    fclose(report);
    ++logId;
}

/**
 *Function for employee info and editing EXECUTIVE
 */
void employeeInfo()
{
    FILE *outfile;
    struct Employee emp;
    char code[MIN_SIZE];

    puts("\n\n");
    outfile = fopen ("dat\\employee.dat", "r");
    while(fread(&emp, sizeof(struct Employee), 1, outfile))
    {
        TAB_TAB2;
        printf("Employee Pkey = [%d] Ncode = [%s] Name = [%s%s] age = [%d]\n",
               emp.primaryKey, emp.person.nationalCode,
               emp.person.name, emp.person.lastName, emp.person.age);
        TAB_TAB2;
        if (emp.person.gender == MALE)
        {
            printf(" Gender = [MALE]");
        }
        else if(emp.person.gender == FEMALE)
        {
            printf(" Gender = [FEMALE]");
        }
        else
        {
            printf(" Gender = [OTHER]");
        }
        if (emp.stat == ACTIVE)
        {
            printf(" Status = [ACTIVE]");
        }
        else if (emp.stat == ACTIVE)
        {
            printf(" Status = [INACTIVE]");
        }
        if (emp.level <= ENTRYLEVEL)
        {
            printf(" Level = [ENTRYLEVEL]");
        }
        else if (emp.level < EXECUTIVE)
        {
            printf(" Level = [INTERMEDIATE]");
        }
        else
        {
            printf(" Level = [EXECUTIVE]");
        }
        putchar('\n');
        TAB_TAB2;
        puts(D_LINE);
    }
    TAB_TAB2;
    puts(CHA_HOLDER);
    system("pause");

    TAB_TAB;
    puts("Enter Employee nationalCode or \"cancel\" to cancel the edit operation:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (strcmp(code,"cancel") == 0)
    {
        TAB_TAB2;
        puts("Operation has been canceled");
        system("pause");
        system("cls");
        return;
    }
    struct Person per;
    strcpy(per.nationalCode, code);

    int idx = findEmployee(per, &emp);

    menuHelper4(emp);
    TAB_TAB2;
    puts("*Notice if you don't want to change the area enter 0\n");
    TAB_TAB2;
    puts("   Edit info:");
    TAB_TAB;
    puts("New name:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (code[0] != '0')
    {
        strcpy(emp.person.name, code);
    }
    TAB_TAB;
    puts("New lastName:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (code[0] != '0')
    {
        strcpy(emp.person.lastName, code);
    }
    TAB_TAB;
    puts("New nCode:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (code[0] != '0')
    {
        strcpy(emp.person.nationalCode, code);
    }
    TAB_TAB;
    puts("New age:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (code[0] != '0')
    {
        char *check;
        emp.person.age = (int) strtol(code, &check, 10);
        if (*check != END_OF_STR)
        {
            puts("Strtol problem");
            system("pause");
            return;
        }
    }
    updateEmployee(emp,idx);

    fclose(outfile);
    TAB_TAB2;
    puts("Operation has been completed");
    system("pause");
    system("cls");
}

/**
 *Function for customer info and editing for employee
 */
void customerInfo()
{
    FILE *outfile;
    struct Customer cust;
    char code[MIN_SIZE];

    puts("\n\n");
    outfile = fopen ("dat\\customer.dat", "r");
    while(fread(&cust, sizeof(struct Customer), 1, outfile))
    {
        TAB_TAB2;
        printf("Customer Pkey = [%d] Ncode = [%s] Name = [%s%s] age = [%d]\n",
               cust.primaryKey, cust.person.nationalCode,
               cust.person.name, cust.person.lastName, cust.person.age);
        TAB_TAB2;
        if (cust.person.gender == MALE)
        {
            printf(" Gender = [MALE]");
        }
        else if(cust.person.gender == FEMALE)
        {
            printf(" Gender = [FEMALE]");
        }
        else
        {
            printf(" Gender = [OTHER]");
        }
        if (cust.stat == ACTIVE)
        {
            printf(" Status = [ACTIVE]");
        }
        else if (cust.stat == ACTIVE)
        {
            printf(" Status = [INACTIVE]");
        }
        if (cust.level <= NEWCUSTOMER)
        {
            printf(" Level = [NEWCUSTOMER]");
        }
        else if (cust.level < LOYALCUSTOMER)
        {
            printf(" Level = [CUSTOMER]");
        }
        else
        {
            printf(" Level = [LOYALCUSTOMER]");
        }
        putchar('\n');
        TAB_TAB2;
        puts(D_LINE);
    }
    TAB_TAB2;
    puts(CHA_HOLDER);
    system("pause");

    TAB_TAB;
    puts("Enter Customer nationalCode or \"cancel\" to cancel the edit operation:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (strcmp(code,"cancel") == 0)
    {
        TAB_TAB2;
        puts("Operation has been canceled");
        system("pause");
        system("cls");
        return;
    }
    struct Person per;
    strcpy(per.nationalCode, code);

    int idx = findCustomer(per, &cust);

    menuHelper3(cust);
    TAB_TAB2;
    puts("*Notice if you don't want to change the area enter 0\n");
    TAB_TAB2;
    puts("   Edit info:");
    TAB_TAB;
    puts("New name:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (code[0] != '0')
    {
        strcpy(cust.person.name, code);
    }
    TAB_TAB;
    puts("New lastName:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (code[0] != '0')
    {
        strcpy(cust.person.lastName, code);
    }
    TAB_TAB;
    puts("New nCode:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (code[0] != '0')
    {
        strcpy(cust.person.nationalCode, code);
    }
    TAB_TAB;
    puts("New age:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (code[0] != '0')
    {
        char *check;
        cust.person.age = (int) strtol(code, &check, 10);
        if (*check != END_OF_STR)
        {
            puts("Strtol problem");
            system("pause");
            return;
        }
    }
    updateCustomer(cust,idx);

    fclose(outfile);
    TAB_TAB2;
    puts("Operation has been completed");
    system("pause");
    system("cls");
}

/**
 *Function for showing accounts info for employees
 * @param employee Giving employee info
 */
void accountsInfo(struct Employee employee)
{
    FILE *outfile;
    struct Customer cust;
    struct AccountCustomer acc;

    puts("\n\n");
    outfile = fopen ("dat\\customer.dat", "r");
    while(fread(&cust, sizeof(struct Customer), 1, outfile))
    {
        findAccount(&acc, cust.primaryKey);
        TAB_TAB2;
        printf("AccountMain Pkey = [%d] and Customer Pkey = [%d]\n", acc.primaryKey, acc.customerKey);
        if (employee.level >= INTERMEDIATE)
        {
            showAccount(cust, 0);
        }
        else
        {
            showAccount(cust, 1);
        }
        putchar('\n');
    }

    fclose(outfile);
    system("cls");
}

/**
 *Function for reading a file line by line
 * @param fileName Giving file name
 */
void readFile(char fileName[MIN_SIZE])
{
    FILE *report;
    report = fopen (fileName, "r");
    if (report == NULL)
    {
        return;
    }

    char inp[MIN_SIZE];
    puts("\n");
    while(fgets(inp,MIN_SIZE,report) != NULL)
    {
        printf("%s", inp);
    }
    puts("\n");
    fclose(report);
    system("pause");
    system("cls");
}

/**
 *Function to update account details
 * @param accCust Account to be updated
 * @param idx Index of account in file
 */
void updateAccount(struct AccountCustomer accCust, int idx)
{
    FILE *outfile = fopen ("dat\\accounts.dat", "r+");
    if (outfile == NULL)
    {//working
        printf("Error %d \n", errno);
        printf("It's null");
    }
    fseek(outfile,sizeof(struct AccountCustomer) * idx ,SEEK_CUR);// To set the pointer on the wanted account
    fwrite (&accCust, sizeof(struct AccountCustomer), 1, outfile);

    fclose(outfile);
}

/**
 *Function to update customer details
 * @param cust Customer to be updated
 * @param idx Index of customer in file
 */
void updateCustomer(struct Customer cust, int idx)
{
    FILE *outfile = fopen ("dat\\customer.dat", "r+");
    if (outfile == NULL)
    {//working
        printf("Error %d \n", errno);
        printf("It's null");
    }
    fseek(outfile,sizeof(struct Customer) * idx ,SEEK_CUR);// To set the pointer on the wanted account
    fwrite (&cust, sizeof(struct Customer), 1, outfile);

    fclose(outfile);
}
/**
 *Function to update employee details
 * @param empy Employee to be updated
 * @param idx Index of employee in file
 */
void updateEmployee(struct Employee empy, int idx)
{
    FILE *outfile = fopen ("dat\\employee.dat", "r+");
    if (outfile == NULL)
    {//working
        printf("Error %d \n", errno);
        printf("It's null");
    }
    fseek(outfile,sizeof(struct Employee) * idx ,SEEK_CUR);// To set the pointer on the wanted account
    fwrite (&empy, sizeof(struct Employee), 1, outfile);

    fclose(outfile);
}

/**
 *Function to find the person with the giving national code
 * @param per pointer to a person struct
 * @return 1 if the giving national code is available 0 otherwise
 */
int findPerson(struct Person *per)
{
    char code[MIN_SIZE];
    FILE *outfile;
    struct Person temp;

    TAB_TAB;
    puts("Enter persons nationalCode or \"cancel\" to cancel the operation:");
    TAB_TAB;
    fgets(code, MIN_SIZE, stdin);
    code[strlen(code)-1] = '\0';
    if (strcmp(code,"cancel") == 0)
        return -1;

    outfile = fopen ("dat\\person.dat", "r");

    int idx = 0;
    while(fread(&temp, sizeof(struct Person), 1, outfile))
    {
        if (strcmp(temp.nationalCode,code) != 0)
        {
            ++idx;
            continue;
        }
        *per = temp;
        fclose(outfile);
        return idx;
    }
    fclose(outfile);
    return -2;
}

/**
 *Function to check user and password
 * @param name name of Person
 * @param code nationalCode of Person
 * @param per Person structure address
 * @return 1 if Person is available -2 otherwise
 */
int loginFinder(char name[MIN_SIZE], char code[MIN_SIZE], struct Person *per)
{
    struct Person temp;
    FILE *outfile;

    outfile = fopen ("dat\\person.dat", "r");

    while(fread(&temp, sizeof(struct Person), 1, outfile))
    {
        if (strncmp(temp.nationalCode,code,strlen(temp.nationalCode)) == 0 &&
        strncmp(temp.name,name,strlen(temp.name)) == 0)
        {
            *per = temp;
            fclose(outfile);
            return 1;
        }
    }
    fclose(outfile);
    return -2;
}

/**
 *Function to find the giving person customer info
 * @param Person giving person info
 * @param Customer customer pointer to get the customer info
 * @return Index of the customer -2 otherwise
 */
int findCustomer(struct Person person, struct Customer *customer)
{
    FILE *outfile;
    struct Customer temp;

    outfile = fopen ("dat\\customer.dat", "r");

    int idx = 0;
    while(fread(&temp, sizeof(struct Customer), 1, outfile))
    {
        if (strcmp(temp.person.nationalCode, person.nationalCode) != 0)
        {
            ++idx;
            continue;
        }
        *customer = temp;
        fclose(outfile);
        return idx;
    }
    fclose(outfile);
    return -2;
}

/**
 *Function to find the giving person employee info
 * @param person giving person info
 * @param employee employee pointer to get the employee info
 * @return Index of the employee -2 otherwise
 */
int findEmployee(struct Person person, struct Employee *employee)
{
    FILE *outfile;
    struct Employee temp;

    outfile = fopen ("dat\\employee.dat", "r");

    int idx = 0;
    while(fread(&temp, sizeof(struct Employee), 1, outfile))
    {
        if (strcmp(temp.person.nationalCode, person.nationalCode) != 0)
        {
            ++idx;
            continue;
        }
        *employee = temp;
        fclose(outfile);
        return idx;
    }
    fclose(outfile);
    return -2;
}

/**
 *Function to find the giving customer account
 *@param accCust Address of accountcustomer
 *@param pKey Private key of customer
 *@return Index of account -2 otherwise
 */
int findAccount(struct AccountCustomer *accCust, int pKey)
{
    FILE *outfile;
    struct AccountCustomer temp;

    outfile = fopen ("dat\\accounts.dat", "r+");

    int idx = 0;
    while(fread(&temp, sizeof(struct AccountCustomer), 1, outfile))
    {
        if (temp.customerKey != pKey)
        {
            ++idx;
            continue;
        }
        *accCust = temp;
        fclose(outfile);
        return idx;
    }
    fclose(outfile);
    return -2;
}

/**
 *Function to find the giving accountNo
 *@param accCust Main account
 *@param accNo Account number
 *@return Index of account number -2 otherwise
 */
int findAccountNo(struct AccountCustomer accCust, int accNo)
{
    for (int idx = 0; idx < accCust.count; idx++)
    {
        if (accNo == accCust.accountNumber[idx].accountNumber)
        {
            return idx;
        }
    }
    return -2;
}

/**
 * Function for creating person
 */
void personMaker()
{
    int static personIndexer = 0;
    int static personCount = 0;
    struct Person person;
    menuHelper(5);
    TAB_TAB2;
    puts("   Create Person:");
    TAB_TAB;//name
    printf("Enter the name: ");
    fgets(person.name, MIN_SIZE, stdin);
    person.name[strlen(person.name)-1] = '\0';
    TAB_TAB;//lastname
    printf("Enter the lastname: ");
    fgets(person.lastName, MIN_SIZE, stdin);
    person.lastName[strlen(person.lastName)-1] = '\0';
    TAB_TAB;//nationalCode
    printf("Enter the nationalCode: ");
    fgets(person.nationalCode, MIN_SIZE, stdin);
    person.nationalCode[strlen(person.nationalCode)-1] = '\0';
    TAB_TAB;//age
    printf("Enter the age: ");
    getInt(&person.age);
    TAB_TAB;//gender
    int gen;
    printf("Enter the gender:\n%s0:MALE\n%s1:FEMALE\n%s2:OTHER\n%s", MULTI_TAB, MULTI_TAB, MULTI_TAB, MULTI_TAB);
    getInt(&gen);
    switch (gen)
    {
        case 0:
            person.gender = MALE;
            break;
        case 1:
            person.gender = FEMALE;
            break;
        default:
            person.gender = OTHER;
            break;
    }

    //init
    ++personCount;
    person.primaryKey = personIndexer;
    ++personIndexer;

    //file
    FILE *outfile;
    outfile = fopen ("dat\\person.dat", "a");
    fwrite(&person, sizeof(struct Person), 1, outfile);

    putchar('\n');
    TAB_TAB2;

    if (fwrite != NULL)
    {
        printf("*%s%s %d years old with nationalCode %s successfully created\n\n",
               person.name,person.lastName,person.age,person.nationalCode);
    }
    else
    {
        printf("error writing file !\n");
    }
    fclose(outfile);
    createLog("Person",personIndexer);

    system("pause");
}

/**
 *Function for creating customer
 */
void customerMaker()
{
    int static customerIndexer = 0;
    int static customerCount = 0;
    int static accountIndexer = 100;//-100
    struct Customer customer;
    struct AccountCustomer accCust;

    menuHelper(5);
    TAB_TAB2;
    puts("Create Customer:");
    while(1)
    {
        int status = findPerson(&customer.person);

        if (status == -1)
            return;

        else if (status == -2)
        {
            TAB_TAB2;
            puts("   Couldn't find person with this nationalCode tryAgain:");
        }
        else
        {
            TAB_TAB2;
            printf("Person %s%s age %d with nationalCode %s founded\n",
                   customer.person.name,customer.person.lastName,
                   customer.person.age,customer.person.nationalCode);
            break;
        }
    }
    TAB_TAB2;
    system("pause");

    //init
    ++customerCount;
    customer.personKey = customer.person.primaryKey;
    customer.primaryKey = customerIndexer;//
    ++customerIndexer;
    customer.level = NEWCUSTOMER;
    customer.stat = ACTIVE;

    accCust.primaryKey = accountIndexer;
    ++accountIndexer;
    accCust.customerKey = customer.primaryKey;//
    accCust.count = 0;
//    for (int i = 0; i < MIN_ACC; ++i) {
//        accCust.accountNumber[i].type = SALARY;
//        accCust.accountNumber[i].accountNumber = 3333;
//        strcpy(accCust.accountNumber[i].value, "0");
//    }

    //file
    FILE *outfile;
    outfile = fopen ("dat\\customer.dat", "a");
    fwrite(&customer, sizeof(struct Customer), 1, outfile);
    fclose(outfile);

    putchar('\n');
    TAB_TAB2;

    if (fwrite != NULL)
        printf("***Your request for creating a customer has been submitted***");

    else
        printf("error writing file !\n");


    FILE *accfile;
    accfile = fopen ("dat\\accounts.dat", "a");
    fwrite(&accCust, sizeof(struct AccountCustomer), 1, accfile);
    fclose(accfile);
    if (outfile==NULL)
    {
        printf("Error %d \n", errno);
        printf("It's null");
    }

    createLog("Customer",customerIndexer);
    createLog("CustomerAccount",customerIndexer);

    putchar('\n');
    TAB_TAB2;

    system("pause");
}

/**
 *Function for creating employee
 */
void employeeMaker()
{
    int static employeeIndexer = 700;//-700
    int static employeeCount = 0;
    struct Employee employee;
    menuHelper(5);
    TAB_TAB2;
    puts("Create Employee:");
    while(TRUE)
    {
        int status = findPerson(&employee.person);

        if (status == -1)
            return;

        else if (status == -2)
        {
            TAB_TAB2;
            puts("   Couldn't find person with this nationalCode tryAgain:");
        }
        else
        {
            TAB_TAB2;
            printf("Person %s%s age %d with nationalCode %s founded\n",
                   employee.person.name,employee.person.lastName,
                   employee.person.age,employee.person.nationalCode);
            break;
        }
    }
    TAB_TAB2;
    system("pause");

    //init
    employee.personKey = employee.person.primaryKey;
    employee.primaryKey = employeeIndexer;
    employee.level = ENTRYLEVEL;
    employee.stat = ACTIVE;
    employee.employeeId = employeeCount;
    ++employeeIndexer;
    ++employeeCount;

    //file
    FILE *outfile;
    outfile = fopen ("dat\\employee.dat", "a");
    fwrite(&employee, sizeof(struct Employee), 1, outfile);

    /*                                              */
    
    putchar('\n');
    TAB_TAB2;

    if (fwrite != NULL)
        printf("***Your request for creating a employee has been submitted***");

    else
        printf("error writing file !\n");

    fclose(outfile);
    char empInfo[20];
    sprintf(empInfo,"%d-%s",employeeCount,"Employer");

    createLog(empInfo,employeeIndexer);

    putchar('\n');
    TAB_TAB2;

    system("pause");
}

/**
 *Function for loan
 * @param customer Giving customer info
 */
void doLoan(struct Customer customer)
{
    struct Transaction transfer;

    menuHelper3(customer);
    if (customer.level < LOYALCUSTOMER)
    {
        TAB_TAB2;
        puts("***You don't have enough reputation in bank to get loan***");
        TAB_TAB2;
        puts("***reputation needed is LOYALCUSTOMER***");
        system("pause");
        system("cls");
        return;
    }
    int idx = findAccount(&transfer.account, customer.primaryKey);

    if (idx == -2)
    {
        TAB_TAB2;
        printf("You don't have any account!\n");
        system("pause");
        return;
    }
    TAB_TAB2;
    puts("Amount you get -> Amount you have to pay after 1 Year");
    TAB_TAB;
    puts("-$5,000 -> 5,063");
    TAB_TAB;
    puts("-$10,000 -> 10,125");
    TAB_TAB;
    puts("-$100,000 -> 101,250");
    TAB_TAB;
    puts("-$200,000 -> 202,500");
    TAB_TAB;
    puts("-$250,000 -> 253,126");
    /*When out return to the main page */
    doDeposit(customer, 1);
}

/**
 *Function to edit user info only name and lastname are allowed
 * @param customer Giving customer info
 */
void doEdit(struct Customer *customer)
{
    char input[MIN_SIZE];

    menuHelper3(*customer);
    TAB_TAB2;
    puts("*Notice if you don't want to change the area enter 0");
    TAB_TAB2;
    puts("   Edit info:");
    TAB_TAB;
    puts("New name:");
    TAB_TAB;
    fgets(input, MIN_SIZE, stdin);
    input[strlen(input)-1] = '\0';
    if (input[0] != '0')
    {
        strcpy(customer->person.name, input);
    }
    TAB_TAB;
    puts("New lastName:");
    TAB_TAB;
    fgets(input, MIN_SIZE, stdin);
    input[strlen(input)-1] = '\0';
    if (input[0] != '0')
    {
        strcpy(customer->person.lastName, input);
    }
    TAB_TAB2;
    puts("Operation has been complete");
    system("pause");
    system("cls");
}

/**
 *Function for depositing
 * @param customer Giving customer info
 * @param code 0 for default 1 for loan
 */
void doDeposit(struct Customer customer, int code)
{
    int static depositIdNo = 0;
    struct Deposit deposit;

    int idx = findAccount(&deposit.transaction.account, customer.primaryKey);

    if (idx == -2)
    {
        TAB_TAB2;
        printf("You don't have any account!\n");
        system("pause");
        return;
    }

    showAccount(customer, 0);
    puts("\n");
    TAB_TAB2;
    puts("Enter accountNumber or 0 to cancel the operation..");
    TAB_TAB;

    int accNo;
    getInt(&accNo);
    if (accNo == 0)
    {
        TAB_TAB2;
        puts("Operation has been canceled");
        system("pause");
        system("cls");
        return;
    }

    int fIdx = findAccountNo(deposit.transaction.account, accNo);

    TAB_TAB2;
    if (code == 0)
    {
        puts("Enter amount to deposit..");
    }
    else
    {
        puts("Enter amount..");
    }
    TAB_TAB;
    depositHelper(&deposit.transaction, fIdx);

    //time
    struct tm * timeinfo;
    timeinfo = timeHelper();

    //init
    deposit.depositId = depositIdNo;
    ++depositIdNo;

    //transaction
    ++transactionIdNo;
    deposit.transaction.transactionId = transactionIdNo;

    strcpy(deposit.transaction.transactionDate, asctime (timeinfo));

    customer.level += 2;
    customer.stat = ACTIVE;//updating status

    //update amount in acc  into function
    updateAccount(deposit.transaction.account, idx);

    //update customer status function
    struct Customer temp;
    int cIdx = findCustomer(customer.person, &temp);
    updateCustomer(customer, cIdx);

    //write in transaction.dat deposit = 1
    createTransactionLog(deposit.transaction, deposit.transaction, 1, fIdx);
    TAB_TAB2;
    puts("Operation has been complete");
    system("pause");
    system("cls");
}

/**
 *Function for withdrawing
 * @param customer Giving customer info
 */
void doWithdraw(struct Customer customer)
{
    int static withdrawIdNo = 0;
    struct Withdraw withdraw;

    int idx = findAccount(&withdraw.transaction.account, customer.primaryKey);

    if (idx == -2)
    {
        TAB_TAB2;
        printf("You don't have any account!\n");
        system("pause");
        return;
    }

    showAccount(customer, 0);
    puts("\n");
    TAB_TAB2;
    puts("Enter accountNumber or 0 to cancel the operation..");
    TAB_TAB;

    int accNo;
    getInt(&accNo);
    if (accNo == 0)
    {
        TAB_TAB2;
        puts("Operation has been canceled");
        system("pause");
        system("cls");
        return;
    }

    int fIdx = findAccountNo(withdraw.transaction.account, accNo);

    TAB_TAB2;
    puts("Enter amount to withdraw..");
    TAB_TAB;
    if (withdrawHelper(&withdraw.transaction, fIdx) == -2)
    {
        return;
    }

    //time
    struct tm * timeinfo;
    timeinfo = timeHelper();

    //init
    ++withdrawIdNo;
    withdraw.withdrawId = withdrawIdNo;
    //transaction
    ++transactionIdNo;
    withdraw.transaction.transactionId = transactionIdNo;

    strcpy(withdraw.transaction.transactionDate, asctime (timeinfo));

    ++customer.level;
    customer.stat = ACTIVE;//updating status

    //update amount in acc  into function
    updateAccount(withdraw.transaction.account, idx);

    //update customer status function
    struct Customer temp;
    int cIdx = findCustomer(customer.person, &temp);
    updateCustomer(customer, cIdx);

    //write in transaction.dat withdraw = 2
    createTransactionLog(withdraw.transaction, withdraw.transaction, 2, fIdx);
    TAB_TAB2;
    puts("Operation has been complete");
    system("pause");
    system("cls");
}

/**
 *Function for transferring
 * @param customer Giving customer info
 */
void doTransfer(struct Customer customer)
{
    int static transferIdNo = 0;
    struct Transfer transfer;
    struct Transfer transferTo;
    int idx = findAccount(&transfer.transaction.account, customer.primaryKey);

    if (idx == -2)
    {
        TAB_TAB2;
        printf("You don't have any account!\n");
        system("pause");
        return;
    }

    showAccount(customer, 0);
    puts("\n");
    TAB_TAB2;
    puts("Enter accountNumber or 0 to cancel the operation..");
    TAB_TAB;

    int accNo;
    getInt(&accNo);
    if (accNo == 0)
    {
        TAB_TAB2;
        puts("Operation has been canceled");
        system("pause");
        system("cls");
        return;
    }
    
    int fIdx = findAccountNo(transfer.transaction.account, accNo);
    /*                                              */

    TAB_TAB2;
    puts("Enter Customer nationalcode..");
    TAB_TAB;
    struct Person per;
    struct Customer cust;

    fgets(per.nationalCode, MIN_SIZE, stdin);
    per.nationalCode[strlen(per.nationalCode)-1] = '\0';

    int stat = findCustomer(per, &cust);

    int idxDest = findAccount(&transferTo.transaction.account, cust.primaryKey);

    if (idxDest == -2)
    {
        TAB_TAB2;
        printf("Giving customer doesn't have any accounts!\n");
        system("pause");
        system("cls");
        return;
    }

    showAccount(cust, 1);
    puts("\n");
    TAB_TAB2;
    puts("Enter accountNumber or 0 to cancel the operation..");
    TAB_TAB;

    getInt(&accNo);
    if (accNo == 0)
    {
        TAB_TAB2;
        puts("Operation has been canceled");
        system("pause");
        system("cls");
        return;
    }
    int dIdx = findAccountNo(transferTo.transaction.account, accNo);

    TAB_TAB2;
    puts("Enter amount to transfer..");
    TAB_TAB;
    if (withdrawHelper(&transfer.transaction, fIdx) == -2)
    {
        return;
    }
    TAB_TAB2;
    puts("Confirm amount to transfer..");
    TAB_TAB;
    depositHelper(&transferTo.transaction, dIdx);

    //time
    struct tm * timeinfo;
    timeinfo = timeHelper();

    //init
    ++transferIdNo;
    transferTo.transferId = transferIdNo;
    transfer.transferId = transferIdNo;

    ++cust.level;
    customer.level += 2;

    cust.stat = ACTIVE;
    customer.stat = ACTIVE;

    //transaction
    ++transactionIdNo;
    transfer.transaction.transactionId = transferIdNo;
    transferTo.transaction.transactionId = transferIdNo;

    strcpy(transfer.transaction.transactionDate, asctime (timeinfo));
    strcpy(transferTo.transaction.transactionDate, asctime (timeinfo));

    //update amount in acc  into function
    updateAccount(transfer.transaction.account, idx);
    updateAccount(transferTo.transaction.account, idxDest);

    //update customer status function
    struct Customer temp;
    int cIdx = findCustomer(customer.person, &temp);
    updateCustomer(customer, cIdx);
    cIdx = findCustomer(cust.person, &temp);
    updateCustomer(cust, cIdx);

    //write in transaction.dat transfer = 3
    createTransactionLog(transfer.transaction, transferTo.transaction, 3, fIdx);
    TAB_TAB2;
    puts("Operation has been complete");
    system("pause");
    system("cls");
}

/**
 *Function for Transactions
 * @param customer Giving customer info
 */
void customerTransaction(struct Customer customer)
{
    while (TRUE)
    {
        menuHelper3(customer);
        TAB_TAB;
        puts("1:..Deposit");
        TAB_TAB;
        puts("2:..Withdraw");
        TAB_TAB;
        puts("3:..Transfer");
        TAB_TAB;
        puts("0:..EXIT\n");
        TAB_TAB;

        /*When out return to the main page */
        int inp;
        getInt(&inp);
        system("cls");
        if (inp == 1)
        {
            doDeposit(customer, 0);
        }
        else if(inp == 2)
        {
            doWithdraw(customer);
        }
        else if (inp == 3)
        {
            doTransfer(customer);
        }
        else
        {
            return;
        }
    }
}

/**
 *Function for creating new account for customer
 * @param customer Giving customer info
 */
void createAccount(struct Customer customer)
{
    unsigned int static accountNo = 6104;//-6104
    struct Accounts acc;
    struct AccountCustomer accCust;

    strcpy(acc.value, "0");
    acc.accountNumber = accountNo;
    ++accountNo;

    menuHelper(5);
    TAB_TAB2;
    int typ;
    printf("Enter the Account type:\n%s0:SALARY\n%s1:SAVING\n%s2:FIXED\n", MULTI_TAB, MULTI_TAB, MULTI_TAB);
    printf("%s*Note you can only get Loan if you have FIXED account\n%s",MULTI_TAB, MULTI_TAB);
    getInt(&typ);
    switch (typ)
    {
        case 0:
            acc.type = SALARY;
            break;
        case 1:
            acc.type = SAVING;
            break;
        default:
            acc.type = FIXED;
            break;
    }


    int idx = findAccount(&accCust, customer.primaryKey);
    if (idx == -2)
        return;

    accCust.accountNumber[accCust.count] = acc;
    ++accCust.count;

    if (accCust.count > MIN_ACC)//check
    {
        --accountNo;//resting the counter
        --accCust.count;//no need for this
        TAB_TAB2;
        puts("You reached the account limit 5/5");
        system("pause");
        return;
    }

    TAB_TAB2;
    printf("***Account with account number = [%u] and value = [$%s] has been created***", acc.accountNumber, acc.value);

    updateAccount(accCust, idx);

    createAccLog(accCust, customer);//log

    putchar('\n');
    TAB_TAB2;
    system("pause");
}

/**
 *Function for displaying customer accounts almost like a helper function
 * @param customer Giving customer info
 * @param code For privacy 1 otherwise 0 ; 1 is used for transaction
 */
void showAccount(struct Customer customer, int code)
{
    struct AccountCustomer accCust;
    int idx = findAccount(&accCust, customer.primaryKey);
    if (idx == -2)
    {
        TAB_TAB2;
        printf("You don't have any account!\n");
        system("pause");
        return;
    }
    TAB_TAB2;
    puts(D_LINE);
    TAB_TAB2;
    printf("-NoAccounts: %d/%d                              \n", accCust.count, MIN_ACC);
    TAB_TAB2;
    puts(CHA_HOLDER);
    if (code == 0)
    {
        for (int i = 0; i < accCust.count; ++i) {
            TAB_TAB2;
            printf("-%d-Account number = [%d]  value = [$%s]",
                   i ,accCust.accountNumber[i].accountNumber, accCust.accountNumber[i].value);
            if (accCust.accountNumber[i].type == SALARY)
            {
                printf("  Type = [SALARY]\n");
            }
            else if(accCust.accountNumber[i].type == SAVING)
            {
                printf("  Type = [SAVING]\n");
            }
            else
            {
                printf("  Type = [FIXED]\n");
            }
            TAB_TAB2;
            puts(D_LINE);
        }
    }
    else
    {
        for (int i = 0; i < accCust.count; ++i) {
            TAB_TAB2;
            printf("-%d-Account number = [%d]  value = [$***]",i,
                   accCust.accountNumber[i].accountNumber);
            printf("  Type = [******]\n");
            TAB_TAB2;
            puts(D_LINE);
        }
    }


    TAB_TAB2;
    puts(CHA_HOLDER);
    printf("\n\n");
    system("pause");
}

/**
 *Function for Customer account control interface
 * @param customer Giving customer info
 */
void customerAccountControl(struct Customer customer)
{
    while (TRUE)
    {
        menuHelper3(customer);
        TAB_TAB;
        puts("1:..CreateAccount");
        TAB_TAB;
        puts("2:..MyAccounts");
        TAB_TAB;
        puts("0:..BACK\n");
        TAB_TAB;

        /*When out return to the main page */
        int inp;
        getInt(&inp);
        system("cls");
        if (inp == 1)
        {
            createAccount(customer);
        }
        else if(inp == 2)
        {
            showAccount(customer, 0);
        }
        else//Exit
            return;
        system("cls");
    }
}

/**
 *Function for PersonDashBoard interface
 * @param person Giving person info
 */
void personDashBoard(struct Person person)
{
    while (TRUE)
    {
        menuHelper2(person);
        TAB_TAB;
        puts("1:.......");
        TAB_TAB;
        puts("0:..EXIT\n");
        TAB_TAB;

        /*When out return to the main page */
        int inp;
        getInt(&inp);
        return;
    }
}

/**
 *Function for customerDashBoard interface
 * @param customer Giving customer info
 */
void customerDashBoard(struct Customer customer)
{
    while (TRUE)
    {
        menuHelper3(customer);
        TAB_TAB;
        puts("1:..Transaction");
        TAB_TAB;
        puts("2:..Accounts");
        TAB_TAB;
        puts("3:..Edit profile");
        TAB_TAB;
        puts("4:..Loan");
        TAB_TAB;
        puts("0:..EXIT\n");
        TAB_TAB;

        /*When out return to the main page */
        int inp;
        getInt(&inp);
        system("cls");
        if (inp == 1)
        {
            customerTransaction(customer);
        }
        else if(inp == 2)
        {
            customerAccountControl(customer);
        }
        else if (inp == 3)
        {
            int idx = findCustomer(customer.person, &customer);
            doEdit(&customer);
            updateCustomer(customer, idx);
            findCustomer(customer.person, &customer);
        }
        else if (inp == 4)
        {
            doLoan(customer);
        }
        else
        {
            return;
        }
    }
}

/**
 *Function for employeeDashBoard interface
 * @param employee
 */
void employeeDashBoard(struct Employee employee)
{
    while (TRUE)
    {
        menuHelper4(employee);
        TAB_TAB;
        puts("1:..Transactions");
        TAB_TAB;
        puts("2:..Logs");
        TAB_TAB;
        puts("3:..Accounts");
        TAB_TAB;
        puts("4:..Customers");
        if (employee.level >= EXECUTIVE)
        {
            TAB_TAB;
            puts("5:..Employees");
        }
        TAB_TAB;
        puts("0:..EXIT\n");
        TAB_TAB;

        /*When out return to the main page */
        int inp;
        getInt(&inp);
        system("cls");
        if (inp == 1)
        {
            readFile("dat\\transaction.dat");
        }
        else if(inp == 2)
        {
            readFile("dat\\log.dat");
        }
        else if (inp == 3)
        {
            accountsInfo(employee);
        }
        else if (inp == 4)
        {
            customerInfo();
        }
        else if (inp == 5)
        {
            if (employee.level < EXECUTIVE)
            {
                puts("Accesses Denied.....");
                system("pause");
                system("cls");
                continue;
            }
            employeeInfo();
        }
        else
        {
            return;
        }
        int idx = findEmployee(employee.person, &employee);
        employee.level += 2;
        updateEmployee(employee, idx);
        findEmployee(employee.person, &employee);
    }
}

/**
 *Function for login interface
 * @param pos position -> 1-Person 2-Customer 3-Employee
 */
void personLogin(int pos)
{
    struct Person person;
    while(TRUE)
    {
        menuHelper(5);
        char name[MIN_SIZE];
        char code[MIN_SIZE];
        TAB_TAB2;
        puts("Login............\n");
        TAB_TAB;
        printf("Username: ");
        fgets(name, MIN_SIZE, stdin);
        name[strlen(name) - 1] = '\0';
        TAB_TAB;
        printf("Password: ");
        fgets(code, MIN_SIZE, stdin);
        code[strlen(code) - 1] = '\0';
        TAB_TAB;

        int status = loginFinder(name ,code, &person);
        if (status == -2)
        {
            puts("Invalid username and password try again?(y/n)");
            TAB_TAB;
            char value = getchar();
            getchar();
            system("cls");
            if (value == 'y')
                continue;
            return;
        }
        else
        {
            TAB_TAB;
            puts("XXXXXX");
            system("pause");
            break;
        }

    }//dashboard PER->1 CUS->2 EMP->3

    if (pos == 1)
    {
        system("cls");
        loginLog("Person", person);//record
        personDashBoard(person);
    }
    else if(pos == 2)
    {
        struct Customer customer;
        if (findCustomer(person, &customer) == -2)
        {
            TAB_TAB;
            puts("\nNo such customer Exist!\n");
            system("pause");
            return;
        }
        loginLog("Customer", person);//record
        system("cls");
        customerDashBoard(customer);
    }
    else
    {
        struct Employee employee;
        if (findEmployee(person, &employee) == -2)
        {
            TAB_TAB;
            puts("\nNo such employee Exist!\n");
            system("pause");
            return;
        }
        loginLog("Employee", person);//record
        system("cls");
        employeeDashBoard(employee);
    }
}

/**
 *Function for showing options and returning status code
 * @return Status code
 */
int menu()
{
    system("cls");
    menuHelper(5);
    TAB_TAB2;
    puts("Welcome to CLI BANK\n");
    TAB_TAB;
    puts("1:..LOGIN");
    TAB_TAB;
    puts("2:..CREATE");
    TAB_TAB;
    puts("0:..EXIT");
    TAB_TAB;
    int inp;
    getInt(&inp);
    return inp;
}

/**
 *Function for showing option for login and returning status code
 * @return Status code
 */
int login()//login
{
    system("cls");
    menuHelper(5);
    TAB_TAB2;
    puts("*NOTICE: Your nationalCode is your password");
    TAB_TAB2;
    puts("   Login As:");
    TAB_TAB;
    puts("1:..PERSON");
    TAB_TAB;
    puts("2:..CUSTOMER");
    TAB_TAB;
    puts("3:..EMPLOYEE");
    TAB_TAB;
    puts("0:..BACK");
    TAB_TAB;
    int inp;
    getInt(&inp);
    return inp;
}

/**
 *Function for showing option for create and returning status code
 * @return Status code
 */
int create()//create
{
    system("cls");
    menuHelper(5);
    TAB_TAB2;
    puts("*NOTICE: To create a Employee or a Customer you first have to create a Person");
    TAB_TAB2;
    puts("   Create A:");
    TAB_TAB;
    puts("1:..PERSON");
    TAB_TAB;
    puts("2:..CUSTOMER");
    TAB_TAB;
    puts("3:..EMPLOYEE");
    TAB_TAB;
    puts("0:..BACK");
    TAB_TAB;
    int inp;
    getInt(&inp);
    return inp;
}

/**
 *Function for doing the action of the giving option
 * @param choice chosen option
 */
void option(int choice)
{
    switch (choice)
    {
        case 1://LOGIN
        {
            int stat = login();
            system("cls");
            switch (stat)
            {
            case 1:case 2: case 3:
                {
                    personLogin(stat);
                    break;
                }

                default://BACK
                {
                    return;
                }
            }
            break;
        }
        case 2://CREATE PART
        {
            int stat = create();
            system("cls");
            switch (stat)
            {
                case 1:
                {
                    personMaker();
                    break;
                }

                case 2:
                {
                    customerMaker();
                    break;
                }

                case 3:
                {
                    employeeMaker();
                    break;
                }

                default://BACK
                {
                    return;
                }
            }
            break;
        }

        default://EXIT
            return;
    }
}

/**
 *Function to flush the buffer until EOF or EOL
 * @param val : the last giving char in the buffer
 **/
void clean_buffer(char val)
{
    while (val != '\n' && val != EOF)
        val = getchar();
}

/**
 *Function to get unsigned numbers and ignores non digit
 *
 * @arr : used to hold the giving number
 * @c : used for getchar()
 * @i : for indexing @arr
 * @return unsigned number
 **/
char *get_unsigned_number()
{
    char *arr = (char*) malloc(MAX_VALUE);
    char c;
    int i;

    for (i = 0; i < MAX_VALUE && isdigit(c = getchar()); i++)
        *(arr+i) = c;

    *(arr+i) = END_OF_STR;
    clean_buffer(c);

    return arr;
}

/**
 *Function to get digit
 * @param: to store the digit value
 **/
void get_int(int *index)
{
    scanf("%d", index);
    getchar();
}

/**
 *Function to return the spatial value
 * @param: giving index
 * @param: giving number
 * @len: len of @param number1
 * @place: index of the giving value @param index
 * @return value of the digit in the giving index to the end e.g -> 12345 ;index = 2 -> 345
 **/
char *get_digit(char *number1, int index)
{
    unsigned int len = strlen(number1) - 1;
    unsigned int place = len - index;

    return number1 + place;
}

/**
 *Function to return the spatial value
 * @param: giving index
 * @param: giving number
 * @len: len of @param number1
 * @arr: used to store created number
 * @i: for indexing @arr
 * @return spatial value
 **/
char *get_value_of_digit(char *number1, int index)
{
    unsigned int len = strlen(number1) - 1;
    char *arr = (char*) malloc((len+1) * sizeof(char));

    int i;
    for (i = 0; i < index; ++i)
        *(arr+i) = '0';
    *(arr+i) = END_OF_STR;

    return arr;
}

/**
 *Function to reverse string
 * @param: giving number1
 * @rev: to store reversed string
 * @len: len of number1
 * @i: for indexing
 * @return reversed string
 **/
char *str_rev(char *number1)
{
    int len = strlen(number1) - 1;
    char *rev = (char*) malloc((len+1) * sizeof(char));

    for(int i = len; i >= 0; i--)
        *(rev+(len-i)) = *(number1+i);

    *(rev+len+1) = END_OF_STR;

    return rev;
}

/**
 *Function to return the sum of 2 long numbers
 * @param: giving number1
 * @param: giving number2
 * @len_1: len of @param number1
 * @len_2: len of @param number2
 * @arr: used to store sum of numbers
 * @carry: used to store carry of numbers sum
 * @temp: to store temporary num
 * @i: for indexing
 * @return sum of numbers
 **/
char* add_unsigned_number(char *number1, char *number2)
{
    char *arr = (char*) malloc((MAX_VALUE) * sizeof(char));
    int len_1 = strlen(number1);
    int len_2 = strlen(number2);

    number1 = str_rev(number1);
    number2 = str_rev(number2);

    int carry = 0;
    for (int i = 0; i < len_1; ++i)
    {
        int temp = (*(number1+i)-'0') + (*(number2+i)-'0') + carry;
        *(arr+i) = (temp % 10 + '0');
        carry = temp / 10;
    }
    int i;
    for (i = len_1; i < len_2; ++i)
    {
        int temp = (*(number2+i)-'0') + carry;
        *(arr+i) = (temp % 10 + '0');
        carry = temp / 10;
    }

    if (carry)
    {
        *(arr+i) = carry + '0';
        ++i;
    }
    *(arr+i) = END_OF_STR;

    return str_rev(arr);
}

/**
 *Function to return the sub of 2 long numbers
 * @param: giving number1
 * @param: giving number2
 * @len_1: len of @param number1
 * @len_2: len of @param number2
 * @arr: used to store Difference of numbers
 * @carry: used to store carry of numbers sum
 * @temp: to store temporary num
 * @i: for indexing
 * @return sub of numbers
 **/
char *subtract_unsigned_number(char *number1, char *number2)
{
    char *arr = (char*) malloc((MAX_VALUE) * sizeof(char));
    int len_1 = strlen(number1);
    int len_2 = strlen(number2);

    number1 = str_rev(number1);
    number2 = str_rev(number2);

    int carry = 0;
    for (int i = 0; i < len_2; ++i)
    {
        int temp = (*(number1+i)-'0') - (*(number2+i)-'0') - carry;

        if (temp < 0)
        {
            temp += 10;
            carry = 1;
        }
        else
            carry = 0;

        *(arr+i) = (temp + '0');
    }

    int i;
    for (i = len_2; i < len_1; ++i)
    {
        int temp = (*(number1+i)-'0') - carry;

        if (temp < 0)
        {
            temp += 10;
            carry = 1;
        }
        else
            carry = 0;

        *(arr+i) = (temp + '0');
    }

    *(arr+i) = END_OF_STR;

    return str_rev(arr);
}

/**
 *Function to return multiply of long number with a char
 * @param: giving number1
 * @param: giving char
 * @len: len of @param number1
 * @arr: used to store sum of n1*n2
 * @carry: used to store carry of numbers sum
 * @shifters -> shift_n1 and shift_n2 for shifting the carry and numbers on there turn
 * @i: for indexing
 * @idx: to make the number without redundant 0
 * @last_idx: for null terminator
 * @str: to store as char
 * @return multiplied number
 **/
char *multiply_unsigned_number_to_char(char *number1, char digit)
{
    if (digit == '0')
        return "0";

    else if(digit == '1')
        return number1;

    int arr[MAX_VALUE] = {0};
    int len = strlen(number1)-1;

    int shift_n1 = 0;
    int shift_n2 = 0;
    int n2 = digit - '0';

    for (int i = len; i >= 0; --i)
    {
        int carry = 0;
        int n1 = *(number1+i) - '0';
        shift_n2 = 0; //reset

        for (int j = 0; j >= 0 ; --j)
        {
            int sum = n1 * n2 + *(arr+shift_n2+shift_n1) + carry;
            carry = sum / 10;
            *(arr+shift_n2+shift_n1) = sum % 10;
            ++shift_n2;
        }

        if (carry)
            *(arr+shift_n2+shift_n1) += carry;

        ++shift_n1;
    }

    int idx;
    for (idx = MAX_VALUE-1; *(arr+idx) == 0; --idx);
    int last_idx = idx+1;
    char *str = (char*) malloc((MAX_VALUE) * sizeof(char));

    while(idx >= 0)
    {
        *(str+idx) = (*(arr+idx) + '0');
        --idx;
    }
    *(str+last_idx) = END_OF_STR;

    return str_rev(str);
}

/**
 *Function to return multiplication of 2 long number
 * @param: giving number1
 * @param: giving number2
 * @len_1: len of @param number1
 * @len_2: len of @param number2
 * @n1: store a digit from number1
 * @n2: store a digit from number2
 * @arr: used to store sum of n1*n2
 * @carry: used to store carry of numbers sum
 * @shifters -> shift_n1 and shift_n2 for shifting the carry and numbers on there turn
 * @i: for indexing
 * @idx: to make the number without redundant 0
 * @last_idx: for null terminator
 * @str: to store as char
 * @return multiplied number
 **/
char *multiply_unsigned_number(char *number1, char *number2)
{
    int arr[MAX_VALUE] = {0};
    int len_1 = strlen(number1)-1;
    int len_2 = strlen(number2)-1;

    if (len_1 == 0 && len_2 != 0)
    {
        char *str = (char*) malloc((MAX_VALUE) * sizeof(char));
        str = multiply_unsigned_number_to_char(number2, *(number1));
        return str;
    }
    else if(len_2 == 0)
    {
        char *str = (char*) malloc((MAX_VALUE) * sizeof(char));
        str = multiply_unsigned_number_to_char(number1, *(number2));
        return str;
    }

    int shift_n1 = 0;
    int shift_n2 = 0;

    for (int i = len_1; i >= 0; --i)
    {
        int carry = 0;
        int n1 = *(number1+i) - '0';

        shift_n2 = 0; //reset

        for (int j = len_2; j >= 0 ; --j)
        {
            int n2 = *(number2+j) - '0';
            int sum = n1 * n2 + *(arr+shift_n2+shift_n1) + carry;

            carry = sum / 10;
            *(arr+shift_n2+shift_n1) = sum % 10;
            ++shift_n2;
        }

        if (carry)
            *(arr+shift_n2+shift_n1) += carry;

        ++shift_n1;
    }

    int idx;
    for (idx = MAX_VALUE-1; *(arr+idx) == 0; --idx);
    int last_idx = idx+1;
    char *str = (char*) malloc((MAX_VALUE) * sizeof(char));

    while(idx >= 0)
    {
        *(str+idx) = (*(arr+idx) + '0');
        --idx;
    }
    *(str+last_idx) = END_OF_STR;

    return str_rev(str);
}

/**
 *Function to return number to specific power
 * @param: giving base
 * @param: giving power
 * @temp: for status of strtoll
 * @str: to store the number
 * @pow: used to store the returned number of strtoll
 * @return base^power
 **/
char *power_unsigned_number(char *base, char *power)
{
    char *temp;
    long long int pow = strtoll(power,&temp,0);
    if (*temp != END_OF_STR)
        return "Failed";

    char *str = (char*) malloc((MAX_VALUE) * sizeof(char));
    if (pow == 0)
        return "1";
    else if(pow == 1)
        return base;
    else if(pow >= 2)
        str = multiply_unsigned_number(base,base);

    pow -= 2;
    while(pow--)
    {
        str = multiply_unsigned_number(str,base);
    }
    return str;
}
