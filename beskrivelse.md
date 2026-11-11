# Softwarebeskrivelse – Timer1 og UART0

## Formål

I denne opgave har jeg lavet et program i C til en ATmega328PB Xplained Mini.

Programmet skal få en LED til at blinke og samtidig kunne modtage og sende tekst til en PC. Begge dele skal fungere ved hjælp af interrupts.

## Programmets opbygning

Programmet starter i `main()`, hvor PB0 bliver sat som output, da det er denne pin, LED'en er tilsluttet.

Derefter kaldes to funktioner:

- `timer1_init()` – indstiller timeren, som styrer LED'en.
- `uart0_init()` – indstiller kommunikationen mellem mikrocontrolleren og PC'en.

Med `sei()` aktiveres interrupts, og programmet går derefter ind i en uendelig `while(1)`-løkke.

## Timer1 – LED

Timer1 bruges til at få LED'en til at blinke.

Timeren er sat op med en prescaler på 256 og en compare-værdi på 31249. Det giver et interval på cirka 500 ms ved en clockfrekvens på 16 MHz.

Når timeren når denne værdi, bliver der udløst et interrupt.

I interruptfunktionen bruges:

`PORTB ^= (1 << PB0);`

Denne linje skifter PB0 mellem HIGH og LOW, så LED'en skiftevis tænder og slukker.

## UART0 – Kommunikation

UART0 bruges til kommunikationen mellem ATmega328PB og PC'en.

Jeg bruger Hercules til at sende og modtage tekst gennem COM-porten. Baudraten er indstillet til 9600 på både PC'en og mikrocontrolleren.

Når der modtages et tegn, bliver der udløst et UART-interrupt.

Programmet læser tegnet og undersøger, om det er et stort eller lille bogstav. Store bogstaver bliver lavet om til små, og små bogstaver bliver lavet om til store.

Det gøres ved at lægge 32 til eller trække 32 fra tegnets ASCII-værdi.

Tal og specialtegn bliver sendt tilbage uden ændringer.

## Interrupts

Et interrupt gør, at mikrocontrolleren kan reagere på en hændelse uden hele tiden at skulle kontrollere, om den er sket.

Jeg bruger to interrupts i programmet. Det ene bliver udløst af Timer1, og det andet bliver udløst, når UART0 modtager et tegn.

På den måde kan LED'en fortsætte med at blinke, samtidig med at jeg sender tekst fra Hercules.

## Test

Jeg har testet programmet på mit ATmega328PB Xplained Mini-board.

LED'en blinker, og jeg kan sende og modtage tekst gennem Hercules.

Eksempel:

**Sendt:** `Hello123!`

**Modtaget:** `hELLO123!`

Det viser, at bogstaverne bliver ændret korrekt, mens tal og specialtegn forbliver uændrede.

## Konklusion

Jeg har fået begge dele af programmet til at fungere ved hjælp af interrupts.

Opgaven har givet mig en introduktion til, hvordan man kan bruge timere og seriel kommunikation i embedded programmering.
