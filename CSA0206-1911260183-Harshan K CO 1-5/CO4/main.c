/* CO4 - structures, nested structures, unions and storage classes */
#include <stdio.h>
#include <string.h>

typedef struct { int day,month,year; } Date;
typedef struct { int systolic,diastolic; } BloodPressure;
typedef struct {
    char name[40], phone[11];
    int age;
    BloodPressure bp;
    Date visit;
} Patient;

typedef struct { int day,month,year; } ParcelDate;
typedef struct { char city[20]; int pincode; } Address;
typedef struct { int id; float weight; Address to; ParcelDate booked; } Parcel;

enum Kind { TEMPERATURE,HUMIDITY,STATUS };
typedef struct {
    enum Kind type;
    union { float celsius; int percent; char status[8]; } value;
} Reading;

typedef struct { int number; double balance; } Account;

static void add_patient(Patient *p,const char *name,int age,const char *phone,
                        int sys,int dia,Date d)
{
    snprintf(p->name,sizeof p->name,"%s",name);
    snprintf(p->phone,sizeof p->phone,"%s",phone);
    p->age=age; p->bp=(BloodPressure){sys,dia}; p->visit=d;
}
static void print_parcel(const Parcel *p)
{
    printf("%d %.1f kg %s-%d %02d/%02d/%04d\n",p->id,p->weight,
           p->to.city,p->to.pincode,p->booked.day,p->booked.month,p->booked.year);
}
static void sort_parcels(Parcel p[],int n)
{
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++) if(p[j].weight<p[min].weight) min=j;
        if(min!=i){Parcel t=p[i];p[i]=p[min];p[min]=t;}
    }
}
static void show_reading(const Reading *r)
{
    switch(r->type){
        case TEMPERATURE: printf("Temp %.1f C\n",r->value.celsius);break;
        case HUMIDITY: printf("Humidity %d %%\n",r->value.percent);break;
        case STATUS: printf("Status %s\n",r->value.status);break;
    }
}
static void add_interest(Account *a,double rate)
{ a->balance += a->balance*rate/100.0; }
static int next_token(void)
{ static int token=1000; return ++token; }

int main(void)
{
    Patient p;
    add_patient(&p,"Arun",19,"9876543210",120,80,(Date){21,11,2026});
    printf("Patient %s age %d BP %d/%d\n",p.name,p.age,p.bp.systolic,p.bp.diastolic);
    Parcel list[3]={
        {501,4.5f,{"Madurai",625001},{12,10,2026}},
        {502,1.2f,{"Chennai",600077},{12,10,2026}},
        {503,2.8f,{"Coimbatore",641001},{13,10,2026}}
    };
    sort_parcels(list,3);
    for(int i=0;i<3;i++) print_parcel(&list[i]);
    Reading readings[3]={
        {TEMPERATURE,{.celsius=31.5f}},
        {HUMIDITY,{.percent=68}},
        {STATUS,{.status="OK"}}
    };
    printf("sizeof union=%zu struct=%zu\n",sizeof readings[0].value,sizeof readings[0]);
    for(int i=0;i<3;i++) show_reading(&readings[i]);
    Account accounts[]={{101,5000},{102,12000},{103,800}};
    for(int i=0;i<3;i++) add_interest(&accounts[i],4);
    printf("Balances: %.2f %.2f %.2f\n",accounts[0].balance,
           accounts[1].balance,accounts[2].balance);
    int token1=next_token();
    int token2=next_token();
    int token3=next_token();
    printf("Tokens: %d %d %d\n",token1,token2,token3);
    return 0;
}
