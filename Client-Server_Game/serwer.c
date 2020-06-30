#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<time.h>

 
#define MYPORT 4950    
 
#define MAXBUFLEN 100


struct Haslaaa
{
 char nazwa[10];
}pies, slon, zebra, kura, indyk, polska, niemcy, korfu, rosja, drzwi;




 
int main( void )
{
    int sockfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int addr_len, numbytes;
    char buf[ MAXBUFLEN ];
 
    char tablica_podlog[10]="_";
 
    if(( sockfd = socket( AF_INET, SOCK_DGRAM, 0 ) ) == - 1 ) {
        perror( "socket" );
        exit( 1 );
    }
 
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons( MYPORT );
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset( &( my_addr.sin_zero ), '\0', 8 );
 
    if( bind( sockfd,( struct sockaddr * ) & my_addr,
    sizeof( struct sockaddr ) ) == - 1 ) {
        perror( "bind" );
        exit( 1 );
    }
 
//const char *nazwaa[1] ;
//nazwaa[0] = "WITAJ W GRZE WISIELEC! ";
 
//char tablica_liter[10] ;
char tablica_liter[99] = "0";
char komunikat[99] = "87654321";

//char wygrana[99] = "\nWygrana!!!"; //DODANE
//tablica_liter[0];
int licznik = 0;
int licznik2 = 0;
char lit[ 1 ];
int z = 1;
char haslo[10];
int win = 0;

srand(time(NULL));

int b = rand()%10+1;

//printf("b= \"%i\"\n", b);

strcpy(pies.nazwa, "pies");
strcpy(slon.nazwa, "slon");
strcpy(zebra.nazwa, "zebra");
strcpy(kura.nazwa, "kura");
strcpy(indyk.nazwa, "indyk");
strcpy(drzwi.nazwa, "drzwi");
strcpy(polska.nazwa, "polska");
strcpy(niemcy.nazwa, "niemcy");
strcpy(rosja.nazwa, "rosja");
strcpy(korfu.nazwa, "korfu");








if(b==1)
{
strcpy(haslo, pies.nazwa);
}

if(b==2)
{
strcpy(haslo, slon.nazwa);
}

if(b==3)
{
strcpy(haslo, zebra.nazwa);
}

if(b==4)
{
strcpy(haslo, kura.nazwa);
}

if(b==5)
{
strcpy(haslo, indyk.nazwa);
}

if(b==6)
{
strcpy(haslo, polska.nazwa);
}

if(b==7)
{
strcpy(haslo, niemcy.nazwa);
}

if(b==8)
{
strcpy(haslo, rosja.nazwa);
}

if(b==9)
{
strcpy(haslo, korfu.nazwa);
}

if(b==10)
{
strcpy(haslo, drzwi.nazwa);
}



//printf("haslo: \"%s\"\n", haslo);


if(strlen(haslo) == 2)
{
    strcat(tablica_podlog,"_");
}
if(strlen(haslo) == 3)
{
    strcat(tablica_podlog,"__");
}
if(strlen(haslo) == 4)
{
    strcat(tablica_podlog,"___");
}
if(strlen(haslo) == 5)
{
    strcat(tablica_podlog,"____");
}
if(strlen(haslo) == 6)
{
    strcat(tablica_podlog,"_____");
}
if(strlen(haslo) == 7)
{
    strcat(tablica_podlog,"______");
}
if(strlen(haslo) == 8)
{
    strcat(tablica_podlog,"_______");
}
if(strlen(haslo) == 9)
{
    strcat(tablica_podlog,"________");
}

 
for(;;)
{
//komunikat[0] = licznik;
memset( buf, '\0', 1 );
 
char komunikat2[10];

    for(;;)
    {
 
            if(( numbytes = recvfrom( sockfd, buf, MAXBUFLEN - 1, 0,( struct sockaddr * ) &their_addr, &addr_len ) ) == - 1 )
        {
            perror( "recvfrom" );
            exit( 1 );
            }
        else
        {
 
        printf( "Klient przeslal litery: \"%c\"\n", buf[0] );
 
        tablica_liter[licznik2] = buf[0];
 	
        for(int i=0; i<10; i++)
        {
 
            if(haslo[i]==buf[0])
            {
 
           // printf("znalazlem litere \"%c\" ", buf[0]);
            //printf("na pozycji \"%i\"\n", i + 1);
	    win = win + 1;
            char litera=buf[0];
            memset(tablica_podlog + i, litera, 1);
            //printf("haslo: \"%s\"\n", pies);
            licznik = licznik - 1;
z=z-1;
            }
        }
 
        break;
        }
    }
 
 
    //strcpy(komunikat2, pies); //DODANE
 
 
 
 
    if(win == strlen(tablica_podlog))
    {
       
        strcat(tablica_liter, "\nWygrana!!!"); //DODANE
       
 
    }

    if(licznik == 7)
    {
 	strcat(tablica_liter, "\nPrzegrana!!!"); //DODANE

    }





komunikat2[0] = komunikat[z];


    if(( numbytes = sendto( sockfd, tablica_podlog, strlen(tablica_podlog), 0, ( struct sockaddr * ) & their_addr, sizeof( struct sockaddr ) ) ) == - 1 )
    {
        perror( "sendto1" );
        exit( 1 );
        }
 
 
    sleep(1);
 
    if(( numbytes = sendto( sockfd, tablica_liter, 99, 0, ( struct sockaddr * ) & their_addr, sizeof( struct sockaddr ) ) ) == - 1 )
    {
        perror( "sendto1" );
        exit( 1 );
        }
 
 
sleep(1);
if(( numbytes = sendto( sockfd, komunikat2, sizeof(komunikat2), 0, ( struct sockaddr * ) & their_addr, sizeof( struct sockaddr ) ) ) == - 1 )
    {
        perror( "sendto2" );
        exit( 1 );
        }
 
    z=z+1;
    licznik = licznik + 1;
   licznik2 = licznik2 + 1;
    //printf( "Pozostalo: \"%i\"\n", 8 - licznik );
 
    if(licznik == 8)
    {
        //printf("Przegrana!!!\n");
        break;
    }
	
    if(win == strlen(tablica_podlog))
    {
       
        break;
    }
 
}
 
    close( sockfd );
 
    return 0;
}
