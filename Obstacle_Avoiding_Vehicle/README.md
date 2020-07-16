# Design Laboratory/Technika Mikroprocesorowa 2

Design Laboratory/Technika Mikroprocesorowa 2
Monika Lis, Wojciech Przybyło, Nowak Artur 
III rok semestr zimowy 2019/2020
Elektronika i Telekomunikacja





Głównym założeniem projektu było stworzenie pojazdu poruszającego się w dwóch trybach:

a) tryb sterowania za pomocą pilota przewodowego
	
W tym trybie pojazd porusza się do w zależności od tego który guzik na pilocie został wciśnięty. Pojazd może poruszać się do przodu, do tyłu, w prawo i w lewo. Dodany został piąty przycisk służący jako klakson.

b) tryb poruszania się do przodu do momentu wykrycia możliwości kolizji

W tym trybie pojazd się samodzielnie do przodu do momentu w którym sonar 
zasygnalizuje zdefiniowaną w oprogramowaniu przez użytkownika odległość. W naszym przykładzie ta odległość będzie wynosić 50 cm.

Pierwotnym projektem był pojazd podążający za dźwiękiem (np. klaskaniem) realizowany za pomocą macierzy kierunkowej Matrix Creator, jednakże ze względu na ograniczone możliwości czasowe i trudny kontakt z producentem wyżej wymienionej macierzy nie byliśmy w stanie uporać się z trudnościami z nią związanymi na czas oddania projektu.




Dla użytkownika:

a) tryb sterowania za pomocą pilota przewodowego

Działanie pilota zostało zrealizowane za pomocą przycisków dołączonych do płytki prototypowej, znajduje się na niej 5 przycisków odpowiadających za jazdę w przód, skręt w prawo, skręt w lewo, jazdę w tył oraz przycisk klaksonu. Są one połączone przewodowo z płytką STM na której odpowiednie piny GPIO ustawiane są w stan wysoki lub niski. O tym czy sterowanie odbywa się za pomocą pilota czy sonaru decyduje użytkownik wciskając odpowiednio przełącznik na pilocie.


b) tryb poruszania się do przodu do momentu wykrycia możliwości kolizji

Działanie czujnika ultradźwiękowego jako sonaru zostało zrealizowane za pomocą mikrokontrolera KL46Z zgodnie z zamieszczoną instrukcją do laboratorium czwartego przedmiotu “Technika Mikroprocesorowa 2”. Jedyną różnicą jest to, że sonar przy odczytaniu wykryciu odległości krótszej niż 50cm ustawia jeden z pinów GPIO, połączonego do mikrokontrolera STM, w stan wysoki. O tym czy sterowanie odbywa się za pomocą pilota czy sonaru decyduje użytkownik wciskając odpowiednio przełącznik na pilocie.


