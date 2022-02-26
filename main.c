#include "headers.h"
#include "functions.h"

/* Bank Project */
int main(void)
{
    while(TRUE)
    {
        int stat = menu();
        if (stat == 0)
        {
            system("cls");
            menuHelper(5);
            TAB_TAB2;
            puts("Have a good day\n");
            system("pause");
            return 0;
        }
        option(stat);
    }
}