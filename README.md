# Implementacja Algorytmu RSA w C++
Edukacyjna implementacja RSA w języku C++. Projekt wykorzystuje bibliotekę Boost Multiprecision do obsługi wielkich liczb całkowitych (1024-bitowych i większych).

## Funkcjonalności
Projekt oferuje kompletny zestaw narzędzi do generowania kluczy oraz szyfrowania danych:

- Generowanie kluczy 1024-bitowych: Wykorzystanie generatora liczb losowych oraz testu pierwszości Millera-Rabina do znajdowania dużych liczb pierwszych.
- Implementacja rozszerzonego algorytmu Euklidesa, potęgowania modularnego oraz odwrotności modulo.
- Szyfrowanie i deszyfrowanie: Obsługa zarówno liczb (BigInt), jak i ciągów znaków (tekstu).
- Testy jednostkowe: Wbudowany moduł testujący poprawność algorytmu Euklidesa.
- Obsługa plików: Możliwość zapisu kluczy oraz szyfrogramów do plików tekstowych.

## Wymagania
- Kompilator C++ wspierający standard C++11 lub nowszy.
- Biblioteka Boost (wymagane nagłówki: boost/multiprecision/cpp_int.hpp, boost/random.hpp).

## Instrukcja kompilacji (GCC):

```
g++ main.cpp rsa.cpp demo.cpp test.cpp -o rsa_app
g++ secure_demo.cpp rsa.cpp -o secure_demo
g++ decrypt_file.cpp rsa.cpp -o decrypt
```
- lub ze zdefiniowna ścieżką do biblioteki boost, najczęściej jak niżej, gdyby było innaczej trzeba podmienić na swoją
```
g++ -std=c++17 -I/opt/homebrew/include main.cpp rsa.cpp test.cpp -o rsa_app
```
- rsa_app - aplikacja demonstracyjna wykonująca całą logike bez ingerencji użytkownika

- secure_demo - umożliwia wpisanie dowolnego tekstu do zaszyfrowania z klawiatury

- decrypt - Umożliwia tylko odszyfrowanie wiadomości podanej w formie klucza oraz szyfrogramu. W naszym wypadku: 
```
./decrypt keys.txt cipher.txt
```


**Gotowe skompilowane pliki sa dołączone do projektu**

## Struktura
- `rsa.h / rsa.cpp`: Główna biblioteka zawierająca logikę matematyczną (generowanie liczb pierwszych, operacje modulo, szyfrowanie RSA).
- `main.cpp`: Główny program demonstracyjny. Testuje algorytm Euklidesa, generuje pary kluczy i szyfruje przykładową liczbę.
- `secure_demo.cpp`: Rozszerzone demo interaktywne. Pobiera wiadomość od użytkownika, zapisuje klucze do `keys.txt`, a zaszyfrowaną wiadomość do `cipher.txt`, po czym ją odszyfrowuje.
- `demo.h / demo.cpp`: Funkcje pomocnicze do konwersji ciągów tekstowych (std::string) na duże liczby i odwrotnie.
- `test.cpp`: Zawiera funkcję test_euklides(), która wykonuje 10 000 prób losowych w celu weryfikacji poprawności obliczania NWD i współczynników Bezouta.

## Działanie

1.  **Generowanie Liczb Pierwszych:** System losuje dwie liczby pierwsze ($p$ i $q$) o długości 1024 bitów każda. Każda liczba przechodzi probabilistyczny test **Millera-Rabina**, aby potwierdzić jej pierwszość.
2.  **Obliczanie Parametrów RSA:** Program wylicza moduł $n = p \cdot q$ oraz funkcję Eulera $\phi(n) = (p-1)(q-1)$. Następnie dobierany jest publiczny wykładnik $e$ (standardowo 65537).
3.  **Wyznaczanie Klucza Prywatnego:** Za pomocą **rozszerzonego algorytmu euklidesa** obliczana jest wartość $d$, będąca odwrotnością modularną $e$ względem $\phi(n)$.
4.  **Eksport Kluczy:** Wygenerowane parametry ($n, e, d$) są zapisywane do pliku tekstowego `keys.txt`.
5.  **Przygotowanie Wiadomości:** Tekst wprowadzony przez użytkownika jest dzielony na znaki, a każdy z nich zamieniany jest na odpowiadający mu kod liczbowy (ASCII).
6.  **Szyfrowanie:** Każda liczba $m$ (znak) jest podnoszona do potęgi $e$ modulo $n$ ($c = m^e \pmod{n}$). Wynikowy szyfrogram trafia do pliku `cipher.txt`.
7.  **Deszyfrowanie:** Program odczytuje szyfrogram oraz klucz prywatny $d$. Wykonuje operację odwrotną: $m = c^d \pmod{n}$.
8.  **Rekonstrukcja Tekstu:** Otrzymane liczby są zamieniane z powrotem na znaki i wyświetlane jako oryginalna wiadomość.

## Autorzy
- Mateusz Hutorowicz
- Daniel Wybranowski
- Michał Zduńczyk


---

