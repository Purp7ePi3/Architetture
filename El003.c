/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione:	Data una sequenza di bit, sapendo che ogni n bit (di dati) vi è
                un bit di parità (1 se il numero di bit a 1 fra i precedenti n è
                dispari), verificare se vi sono errori.

 ********************************************************************************/ //0000 1100 0 00110 11000 10100
#include <stdio.h>

int main()
{
    // Input
    unsigned char vet[] = { 0xE3,0xA5,0x0E,0x92,0x2F,0xB2,0x00 }; // 7 bit: 0001101
    unsigned int len = 50;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori
    int errore;
    unsigned char parola = 2;
    __asm
    {
        xor esi, esi    // contatore per la lettera
        xor edi, edi    //confronto con len per uscire dal ciclo senza errori
        xor ebx, ebx    //bh tiene conto degli elementi nel ciclo fino ad n, bl conta quanti sono i numeri pari ad 1
        xor eax, eax    //al contiene l'elemento di n di vet, ah QUI CI METTO IL CONTATORE FINO AD 8 BIT    /*USATI TUTTI E DUE I REIGISTRI DA 8*/

    PS:
        mov al, [vet + esi]
        inc esi
        xor ah, ah
    
    CNF:
        //ci sono le condizioni di uscita
        cmp ah, 8
        je PS
        cmp edi, len
        jg FINE
        cmp bh, n
        jg PARITA
       
        inc ah        
        inc edi
        //controlla se l'ultimo numero è uno zero o un uno, incrementa solo il contatore di bh se zero altrimenti anche quello di
        test al, 1
        jnz UNO
        jz ZERO

    UNO:
        inc bh
        inc bl
        shr al, 1
        jmp CNF

    ZERO:
        inc bh
        shr al, 1
        jmp CNF


    PARITA:
        // controlla quanti sono i bit a uno in quelli che dentro controllare, se sono dispari c'è un errrore, altrimenti continua
        // dopo il controllo resetto bh e bl
        test bl, 1
        jnz ERRORE
        xor bl, bl
        xor bh, bh
        jz CNF

    ERRORE:
        mov errori, 1
    
    FINE:
        mov errore, edi
        mov parola, ah
    }
    printf("bit letti: %d\n", errore);
    printf("bit letti parola: %d\n", parola);
    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));
    return 0;
}

