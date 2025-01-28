#include <stdio.h>
#include <stdlib.h>
//reverse array
int main()
{
    int array[100],array1[100];
    int n,i;
    printf("Enter an array number :");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }
    for(i = 0; i < n; i++){
        array1[i] = array[i];
    }
    for(i = 0; i < n; i++){
        printf("%d",array[i]);
    }
    printf("The first array element are :");
    for(i = 0; i < n;i++){
        printf("%d", array[i]);
    }
    printf("The second array element are :");
    for(i = 0; i < n;i++){
        printf("%d", array1[i]);
    }


}
