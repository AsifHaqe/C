#include<stdio.h>

int main(){
    int overalldays = 0, years = 0, month = 0, days = 0;

    printf("Enter the total number of days:");
    scanf("%d", &overalldays);
    years = overalldays / 365;
    overalldays =% 365;
    month = overalldays / 30;
    overalldays =% 30;
    days = overalldays;
    printf("%d %d %d", years, month, days);

    return 0;

}