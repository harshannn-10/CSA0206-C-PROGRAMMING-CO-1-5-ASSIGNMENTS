/* CO3 - searching, sorting, merging, 2-D arrays and strings */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int comparisons;
static int linear_search(const int a[], int n, int key)
{
    comparisons=0;
    for (int i=0;i<n;i++) { ++comparisons; if (a[i]==key) return i; }
    return -1;
}
static int binary_search(const int a[], int n, int key)
{
    int low=0, high=n-1; comparisons=0;
    while (low<=high) {
        int mid=low+(high-low)/2; ++comparisons;
        if (a[mid]==key) return mid;
        if (a[mid]<key) low=mid+1; else high=mid-1;
    }
    return -1;
}
static void insertion_sort(int a[], int n)
{
    for (int i=1;i<n;i++) {
        int key=a[i],j=i-1;
        while (j>=0 && a[j]>key) { a[j+1]=a[j]; --j; }
        a[j+1]=key;
    }
}
static int merge_desc(const int a[],int na,const int b[],int nb,int out[])
{
    int i=0,j=0,k=0;
    while(i<na && j<nb) out[k++]=(a[i]>=b[j])?a[i++]:b[j++];
    while(i<na) out[k++]=a[i++];
    while(j<nb) out[k++]=b[j++];
    return k;
}
static int word_count(const char s[])
{
    int count=0, inside=0;
    for(int i=0;s[i];i++) {
        if (isspace((unsigned char)s[i])) inside=0;
        else if (!inside) { ++count; inside=1; }
    }
    return count;
}
static int palindrome(const char s[])
{
    int l=0,r=(int)strlen(s)-1;
    while(l<r) {
        while(l<r && !isalpha((unsigned char)s[l])) ++l;
        while(l<r && !isalpha((unsigned char)s[r])) --r;
        if(tolower((unsigned char)s[l])!=tolower((unsigned char)s[r])) return 0;
        ++l;--r;
    }
    return 1;
}
int main(void)
{
    int a[]={1021,1048,1103,1190,1222,1305,1377,1402,1460,1533};
    int keys[]={1021,1305,1533,1400};
    int linear_pos=linear_search(a,10,1400);
    printf("Linear search 1400 -> %d comparisons=%d\n",linear_pos,comparisons);
    for(int i=0;i<4;i++) {
        int p=binary_search(a,10,keys[i]);
        printf("Book %d -> index %d, comparisons=%d\n",keys[i],p,comparisons);
    }
    int x[]={9,2,7,1,5}; insertion_sort(x,5);
    printf("Sorted: "); for(int i=0;i<5;i++) printf("%d ",x[i]); puts("");
    int ca[]={98,91,85,72}, cb[]={95,91,80}, out[7];
    int n=merge_desc(ca,4,cb,3,out);
    printf("Merged: "); for(int i=0;i<n;i++) printf("%d ",out[i]); puts("");
    int rain[3][4]={{10,20,30,40},{5,15,25,35},{8,18,28,38}};
    for(int i=0;i<3;i++){int total=0;for(int j=0;j<4;j++)total+=rain[i][j];
        printf("District %d total=%d\n",i+1,total);}
    const char msg[]="  Meet at  the library at 5 PM ";
    printf("Words=%d palindrome=%d/%d\n",word_count(msg),
           palindrome("Madam, I'm Adam"),palindrome("Hello"));
    return 0;
}
