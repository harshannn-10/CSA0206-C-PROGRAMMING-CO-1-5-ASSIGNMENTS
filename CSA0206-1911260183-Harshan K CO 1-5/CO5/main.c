/* CO5 - modular functions, recursion, pointers, allocation and files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long long calls=0;
static long long power_linear(long long base,int exp)
{
    ++calls;
    if(exp==0) return 1;
    return base*power_linear(base,exp-1);
}
static long long power_fast(long long base,int exp)
{
    ++calls;
    if(exp==0) return 1;
    long long half=power_fast(base,exp/2);
    return (exp%2)?base*half*half:half*half;
}
static int digital_root(int n)
{
    if(n<10) return n;
    int sum=0;
    while(n){sum+=n%10;n/=10;}
    return digital_root(sum);
}
typedef struct { int id; char group[4]; } Donor;
typedef struct { Donor *data; size_t size,capacity; } DonorList;
static int add_donor(DonorList *list,int id,const char *group)
{
    if(list->size==list->capacity){
        size_t cap=list->capacity?list->capacity*2:2;
        Donor *tmp=realloc(list->data,cap*sizeof *tmp);
        if(!tmp) return 0;
        list->data=tmp; list->capacity=cap;
    }
    list->data[list->size].id=id;
    snprintf(list->data[list->size].group,sizeof list->data[list->size].group,"%s",group);
    ++list->size;
    return 1;
}
typedef struct { int group_code,units; } Stock;
static int update_units(FILE *fp,long index,int units)
{
    Stock s;
    if(fseek(fp,index*(long)sizeof s,SEEK_SET)!=0) return 0;
    if(fread(&s,sizeof s,1,fp)!=1) return 0;
    s.units=units;
    if(fseek(fp,-(long)sizeof s,SEEK_CUR)!=0) return 0;
    return fwrite(&s,sizeof s,1,fp)==1;
}
int main(void)
{
    calls=0; long long pl=power_linear(2,30);
    printf("2^30 linear=%lld calls=%lld\n",pl,calls);
    calls=0; long long pf=power_fast(2,30);
    printf("2^30 fast=%lld calls=%lld\n",pf,calls);
    printf("Digital root of 9875 = %d\n",digital_root(9875));
    DonorList list={NULL,0,0};
    const char *groups[]={"O+","A+","B-","AB+","O-"};
    for(int i=0;i<5;i++){
        if(!add_donor(&list,7001+i,groups[i])){perror("realloc");free(list.data);return 1;}
        printf("Donor %d %s size=%zu capacity=%zu\n",list.data[i].id,
               list.data[i].group,list.size,list.capacity);
    }
    free(list.data); list.data=NULL;

    FILE *fp=tmpfile();
    if(!fp){perror("tmpfile");return 1;}
    Stock initial[5]={{1,40},{2,25},{3,12},{4,8},{5,30}};
    if(fwrite(initial,sizeof initial[0],5,fp)!=5){perror("fwrite");fclose(fp);return 1;}
    printf("Update record 3: %s\n",update_units(fp,3,20)?"done":"failed");
    printf("Update record 9: %s\n",update_units(fp,9,20)?"done":"failed");
    rewind(fp); Stock s;
    while(fread(&s,sizeof s,1,fp)==1) printf("%d:%d ",s.group_code,s.units);
    puts(""); fclose(fp);
    return 0;
}
