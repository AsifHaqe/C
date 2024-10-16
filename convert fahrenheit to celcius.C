#include<stdio.h>

int main(){
    float farenheit , celsius;

    printf("enter temparature into farenheit:");
    scanf("%f", &farenheit);

    celsius = (farenheit - 32) * 5 / 9;
    printf("temparature in celsius: %.2f\n", celsius);
    return 0;
}
