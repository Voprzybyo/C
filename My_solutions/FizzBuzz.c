
#include <stdio.h>

int main()
{
    printf("Hello World");
    
    for(int i = 0 ; i <= 100 ; i++){
        
        if(i%3 == 0 && i%5 != 0){
            printf("Fizz \n");
            continue;
        }else if(i%3 != 0 && i%5 == 0){
            printf("Buzz \n");
            continue;
        }else if(i%3 == 0 && i%5 == 0){
            printf("FizzBuzz \n");
            continue;
        }

        printf("%d \n",i);
    }

    return 0;
}
