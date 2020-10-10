#include <stdio.h>

int isPalindrom(char *word){
    
    int j = strlen(word) - 1 ; 
    int counter = 0;
    for(int i = 0; i < strlen(word); i++,j--){
         printf("%d%d\n", i,j);
         printf("%c%c\n", word[i],word[j]);
        if(word[i] == word[j]){
            counter++;
            printf("counter:%d\n", counter);
        }
    }
    printf("%d\n", counter);
        if(counter == strlen(word)){
            return 1;
        }
        return 0;
}


int main()
{
    char *tekst = "kajak";
    
    int res = isPalindrom(tekst);
    if(res == 1){
    printf("It is palindrom! Res = %d", res);
    }else{
    printf("It is not palindrom :c ... Res = %d", res);
    }
     return 0;
}
