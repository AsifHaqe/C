#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array[100];
    int pos,n,i;
    printf("Enter the number of that array :");
    scanf("%d", &n);
    printf("Enter the element :");
    for(i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }
    printf("Enter the position you wanna delete");
    scanf("%d", &pos);
    if(pos >= n+1){
        printf("The deleting array is not possible");
    } else{
        for(i = pos-1;i < n; i++){
            array[i] = array[i+1];
        }
        for(i = 0;i<n;i++){
            printf("%d", array[i]);
        }
    }
    return 0;
}
