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

#define MYPORT 4950   //makra

#define MAXBUFLEN 100

int main( int argc, char * argv[] )
{
    int sockfd;                              // deskryptor gniazda
    struct sockaddr_in their_addr;          // struktura
    struct hostent * he;				//zadeklarowanie w strukturze typu hostent "he"
    int addr_len, numbytes; //numbytes - liczba bajtow wyslanych/odebranych
    char buf[ MAXBUFLEN ];  //bufor

    if( argc != 2 ) {
        fprintf( stderr, "uzycie: klient adres\n" );	//jesli kots poda wiecej niz 3 argumenty wywala blad (nazwe programu, IP, wiadomosc)
        exit( 1 );
    }

    if(( he = gethostbyname( argv[ 1 ] ) ) == NULL ) {   //jezeli funkcja gethostbyname zwroci wartosc null tzn ze nie udalo sie zdobyc adresu IP serwera i program sie kuńczy
        perror( "gethostbyname" );
        exit( 1 );
    }

    if(( sockfd = socket( AF_INET, SOCK_DGRAM, 0 ) ) == - 1 ) {  //tworzenie gniazda UDP
        perror( "socket" );
        exit( 1 );
    }

    their_addr.sin_family = AF_INET;								//ustawienie rodziny adresu
    their_addr.sin_port = htons( MYPORT );							//ustawienie portu
    their_addr.sin_addr = *(( struct in_addr * ) he->h_addr );		//przypisanie do adresu IP eeeeee



    memset( &( their_addr.sin_zero ), '\0', 8 );   // wyrównanie struktury

addr_len = sizeof( struct sockaddr ); //ustawienie dlugosci adresu 


char nazwa[99] ; //wskaznik na tablice 10elementową
int znak;
char literka;
char literaaa[1];
literaaa[0] = literka;

for(;;){

znak = getchar(); //wprowadzenie znaku
literka = znak;
literaaa[0] = literka;
nazwa[0] = literaaa[0];


    	if(( numbytes = sendto( sockfd, nazwa, strlen( nazwa), 0, ( struct sockaddr * ) & their_addr, sizeof( struct sockaddr ) ) ) == - 1 ) {
        perror( "sendto" );
        exit( 1 );
    	}

    	printf( "wyslano %d bajtow do %s\n", numbytes,		 //wyswietl liczbe wyslanych bajtow
    	inet_ntoa( their_addr.sin_addr ) );

	for(;;)
	{

		if(( numbytes = recvfrom( sockfd, buf, MAXBUFLEN - 1, 0, ( struct sockaddr * ) & their_addr, & addr_len ) ) == - 1 ) 
		{
        	perror( "recvfrom" );
        	exit( 1 );
        	}
		else
		{
		printf( "haslo: \"%s\"\n", buf ); 
		break;
		}
	}


	for(;;)
	{

		if(( numbytes = recvfrom( sockfd, buf, MAXBUFLEN - 1, 0, ( struct sockaddr * ) & their_addr, & addr_len ) ) == - 1 ) 
		{
        	perror( "recvfrom" );
        	exit( 1 );
        	}
		else
		{
		printf( "Wykorzystane litery: \"%s\"\n", buf ); 
		break;
		}
	}

	if(strstr(buf, "Wygrana!!!") != NULL || strstr(buf, "Przegrana!!!") != NULL)
	{
		break;
	}


	for(;;)
	{

		if(( numbytes = recvfrom( sockfd, buf, MAXBUFLEN - 1, 0, ( struct sockaddr * ) & their_addr, & addr_len ) ) == - 1 ) 
		{
        	perror( "recvfrom" );
        	exit( 1 );
        	}
		else
		{
		printf( "pozostalo prob: \"%s\"\n", buf ); 
		break;
		}
	}
	znak = getchar();    //znowu pobiera znak (moze mozna usunać?)


//char * argv2[1];
//argv2[1] = "tescik";

//for(;;)
//{

//znak = getchar();



//sendto( sockfd, argv2[1], strlen( argv2[1] ), 0,
   // ( struct sockaddr * ) & their_addr, sizeof( struct sockaddr ) ); 
	//{
    //    perror( "sendto2" );
    //    exit( 1 );
    //	}

//}

}
    close( sockfd );  //zamknij soketa
   
    return 0;
}
