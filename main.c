#include <stdio.h>
#include <stdlib.h>
int main(){
  int arra1[50],arry2[50],array3[50];
  int n,i,j=0,k=0;
  printf("Enter the element of that array:");
  scanf("%d", &n);
  for(i = 0; i < n;i++){
    scanf("%d", &arra1[i]);
  }
  //logic
  for(i = 0; i < n; i++){
    if(arra1[i] % 2 == 0){
        arry2[i] = arra1[i];
        j++;
    } else {
        array3[k] = arra1[i];
        k++;
    }
  }
  for(i = 0; i < j; i++){
    printf("The odd number is: %d", arry2[i]);
  }
  for(i = 0; i < k; i++){
    printf("%d", array3[i]);
  }
  return 0;
}
