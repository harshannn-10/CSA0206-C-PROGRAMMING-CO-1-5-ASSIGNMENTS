/* CO2 - operators, decisions, bitwise operations and loops */
#include <stdio.h>
#include <limits.h>

static double pharmacy_bill(double price, int qty, int senior)
{
    double gross = price * qty;
    double discount = senior ? gross * 0.15 : 0.0;
    double taxable = gross - discount;
    double tax = taxable * 0.05;
    double total = taxable + tax;
    return total > 1000.0 ? total - 50.0 : total;
}

static unsigned char switch_on(unsigned char r, int d)
{ return (unsigned char)(r | (1u << d)); }
static unsigned char switch_off(unsigned char r, int d)
{ return (unsigned char)(r & ~(1u << d)); }
static unsigned char toggle(unsigned char r, int d)
{ return (unsigned char)(r ^ (1u << d)); }
static int is_on(unsigned char r, int d)
{ return (r & (1u << d)) != 0; }

static char grade(int marks)
{
    if (marks < 0 || marks > 100) return '?';
    switch (marks / 10) {
        case 10: case 9: return 'S';
        case 8: return 'A';
        case 7: return 'B';
        case 6: return 'C';
        case 5: return 'D';
        default: return 'F';
    }
}

static int prime_counted(unsigned long n, unsigned long *checks)
{
    *checks = 0;
    if (n < 2) return 0;
    for (unsigned long i=2; i <= n/i; ++i) {
        ++*checks;
        if (n % i == 0) return 0;
    }
    return 1;
}

static void loan_schedule(double principal, double rate, double repayment)
{
    double balance=principal, interest_total=0.0;
    int month=0;
    if (principal <= 0 || rate < 0 || repayment <= 0) {
        puts("Invalid loan inputs."); return;
    }
    while (balance > 0.005 && month < 360) {
        double interest=balance*rate/100.0;
        double due=balance+interest;
        double paid=repayment < due ? repayment : due;
        if (paid <= interest) {
            puts("Repayment does not exceed interest; loan will not reduce.");
            return;
        }
        balance=due-paid;
        if (balance < 0.005) balance=0;
        interest_total += interest;
        ++month;
        printf("Month %d: interest %.2f, paid %.2f, balance %.2f\n",
               month, interest, paid, balance);
    }
    if (balance == 0) printf("Months=%d Total interest=%.2f\n",month,interest_total);
    else puts("Safety limit reached (360 months).");
}

int main(void)
{
    printf("Pharmacy example: Rs %.2f\n", pharmacy_bill(100.0, 5, 1));
    unsigned char reg=0;
    reg=switch_on(reg,0); reg=switch_on(reg,2);
    printf("Register after LIGHT and AC: %u\n", (unsigned)reg);
    reg=toggle(reg,1); reg=switch_off(reg,0);
    printf("Register after toggle FAN and switch off LIGHT: %u; AC=%d\n",
           (unsigned)reg,is_on(reg,2));
    int tests[]={100,95,83,50,49,-5,101};
    for (int i=0;i<7;i++) printf("%d:%c ",tests[i],grade(tests[i]));
    puts("");
    unsigned long checks;
    unsigned long nums[]={97,100,7919,1000003};
    for (int i=0;i<4;i++) {
        int result=prime_counted(nums[i],&checks);
        printf("%lu prime=%d divisions=%lu\n",nums[i],result,checks);
    }
    loan_schedule(10000,2,2000);
    return 0;
}
