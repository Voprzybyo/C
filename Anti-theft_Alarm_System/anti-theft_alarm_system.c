#include <Keypad.h> //biblioteka od klawiatury
 
const byte ROWS = 4; // ile wierszy
const byte COLS = 4; //ile kolumn
 
byte rowPins[ROWS] = {5, 4, 3, 2}; //piny wierszy
byte colPins[COLS] = {6, 7, 8, 9}; //piny kolumn
 
char keys[ROWS][COLS] = { //mapowanie klawiatury
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //inicjalizacja klawiatury

 int var0;
volatile int stanAlarmu = 1;
int pinAlarmuPozycja = 1;
char pinCyfra1 = '1';
char pinCyfra2 = '2';
char pinCyfra3 = '3';
char pinCyfra4 = '4';
 
int ileCzasuMinelo = 0;
 
void setup() {
  Serial.begin(9600); 
 pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
   pinMode(A0, INPUT);
}
 
void loop() {
  var0 = analogRead(A0);
    Serial.println(var0);
  char klawisz = 0; //zmienna do przetrzymywania znakow z klawiatury
  char klawisz2 = 0;
  int i = 0; //zmienna pomocnicza do pêtli
  switch(stanAlarmu) { //Wykonywania akcji odpowiedniej dla danego stanu
    case 1:
      //Czuwanie
   digitalWrite(11, HIGH);
      klawisz = klawiatura.getKey();
      if (klawisz == 'A') { //Czy uzbroic alarm?
                      digitalWrite(10, HIGH);
          delay(100);
          digitalWrite(10, LOW);
        for (i = 1; i < 4; i++) {
   digitalWrite(11, HIGH);
          delay(300);
          digitalWrite(11, LOW);
               delay(300);
        } 

              digitalWrite(10, HIGH);
          delay(100);
          digitalWrite(10, LOW);

       
        
      for (i = 1; i < 4; i++) {
   digitalWrite(11, HIGH);
          delay(100);
          digitalWrite(11, LOW);
               delay(100);
        } 
 for (i = 0; i < 4; i++) {  
              digitalWrite(10, HIGH);
          delay(100);
          digitalWrite(10, LOW);
               delay(100);//Jesli sprawdzamy 4 pozycje PINu
            stanAlarmu = 1; //Wszystkie 4 cyfry kodu sa poprawne      
        }
               stanAlarmu = 2;
               
        } else  {

        stanAlarmu = 1;
      
        }
    break;
    
    case 2:
     //Monitorowanie
       digitalWrite(11, HIGH);
      delay(700);
       digitalWrite(11, LOW);
      delay(700);
 
      if (var0<50 ) {
        stanAlarmu = 3; 
      }
       ileCzasuMinelo= 0; //Zerowanie zmiennej
    break;
     case 3:
      //Rozbrajanie
      klawisz = klawiatura.getKey();
      if (klawisz) {
        //Czy kolejna podana cyfra jest poprawna?
        if (pinAlarmuPozycja == 1 && klawisz == pinCyfra1) { //Jesli sprawdzamy 1 pozycje PINu
          pinAlarmuPozycja++;    digitalWrite(10, HIGH);  delay(30); digitalWrite(10, LOW);
          //Cyfra poprawna, mozna sprawdzic na kolejna
        } else if (pinAlarmuPozycja == 2 && klawisz == pinCyfra2) { //Jesli sprawdzamy 2 pozycje PINu
          pinAlarmuPozycja++; digitalWrite(10, HIGH);  delay(30); digitalWrite(10, LOW); //Cyfra poprawna, mozna sprawdzic na kolejna         
        } else if (pinAlarmuPozycja == 3 && klawisz == pinCyfra3) { //Jesli sprawdzamy 3 pozycje PINu
          pinAlarmuPozycja++;  digitalWrite(10, HIGH);  delay(30); digitalWrite(10, LOW);//Cyfra poprawna, mozna sprawdzic na kolejna        
        } else if (pinAlarmuPozycja == 4 && klawisz == pinCyfra4) {
            for (i = 0; i < 4; i++) {  
              digitalWrite(10, HIGH);
          delay(100);
          digitalWrite(10, LOW);
               delay(100);//Jesli sprawdzamy 4 pozycje PINu
            stanAlarmu = 1; //Wszystkie 4 cyfry kodu sa poprawne      
        }} else {
           stanAlarmu = 4; //Blad w kodzie PIN - wlacz alarm
        }
      }
 
      delay(100);
      ileCzasuMinelo++;
 
      if (ileCzasuMinelo >= 200) {
        stanAlarmu = 4;
      }
    break;
    case 4:
      //Sygnalizacja alarmu
      for (i = 0; i < 20; i++) {  
              digitalWrite(10, HIGH);
          delay(100);
          digitalWrite(10, LOW);
               delay(100);

 klawisz2 = klawiatura.getKey();
      if (klawisz2 == '*') { //Czy rozbroic alarm?
         stanAlarmu = 3;
        break;
        } 
break;
      }

     break;
  }
}
 

 