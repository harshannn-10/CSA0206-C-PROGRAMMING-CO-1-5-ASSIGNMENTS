/* CO1 - Reliable rural electricity billing */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0L
#define RATE2_PAISE 225L
#define RATE3_PAISE 450L
#define FIXED_CHARGE_PAISE 5000LL

typedef unsigned short meter_t;

static unsigned int consumption(meter_t previous, meter_t current)
{
    /* Unsigned 16-bit arithmetic performs modulo 65536 subtraction. */
    return (unsigned short)(current - previous);
}

static long long compute_bill(unsigned int units)
{
    long long energy = 0;
    if (units > SLAB2_UNITS)
        energy = (SLAB2_UNITS-SLAB1_UNITS)*RATE2_PAISE
               + (long long)(units-SLAB2_UNITS)*RATE3_PAISE;
    else if (units > SLAB1_UNITS)
        energy = (long long)(units-SLAB1_UNITS)*RATE2_PAISE;
    else
        energy = (long long)units*RATE1_PAISE;
    return FIXED_CHARGE_PAISE + energy;
}

static void print_money(long long paise)
{
    printf("Rs %lld.%02lld", paise/100, llabs(paise%100));
}

int main(void)
{
    meter_t previous, current;
    unsigned int units;
    long long bill;
    printf("Enter previous and current meter readings (0..65535): ");
    if (scanf("%hu %hu", &previous, &current) != 2) {
        fprintf(stderr, "Invalid input: enter two integer readings.\n");
        return 1;
    }
    units = consumption(previous, current);
    bill = compute_bill(units);
    printf("Units consumed: %u\nBill: ", units);
    print_money(bill);
    putchar('\n');

    printf("Rollover test 65400 -> 120: %u units\n",
           consumption((meter_t)65400, (meter_t)120));
    printf("Tariff test 150 units: ");
    print_money(compute_bill(150));
    putchar('\n');
    return 0;
}
