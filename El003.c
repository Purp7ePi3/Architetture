/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione:	Data una sequenza di bit, sapendo che ogni n bit (di dati) vi è
                un bit di parità (1 se il numero di bit a 1 fra i precedenti n è
                dispari), verificare se vi sono errori.

 ********************************************************************************/
#include <stdio.h>

int main()
{
    // Input
    unsigned char vet[] = {3,5}; // 7 bit: 0001101
    unsigned int len = 15;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori
    int errore;
    __asm
    {
        xor esi, esi    // contatore per la lettera
        xor edi, edi    //confronto con len per uscire dal ciclo senza errori
        xor ebx, ebx    //bh tiene conto degli elementi nel ciclo fino ad n, bl conta quanti sono i numeri pari ad 1
        xor eax, eax    //al contiene l'elemento di n di vet, ah QUI CI METTO IL CONTATORE FINO AD 8 BIT    /*USATI TUTTI E DUE I REIGISTRI DA 8*/

    PS:
        mov al, [vet + esi]
        inc esi

    CNF:
        inc edi
        cmp edi, len
        je FINE
        inc ah
        cmp ah,8
        je PS

        cmp bh, n
        je PARITA
        test al, 1
        jnz UNO
        jz ZERO

    UNO:
        inc bl
        inc bh
        shr al, 1
        jmp CNF

    ZERO:
        inc bh
        shr al, 1
        jmp CNF

    PARITA:
        xor bh, bh
        shr al, 1
        test al,1 
        jnz DISPARI
        jz PARI

    DISPARI:
        test bl, 1
        jz ERRORE
        xor bl, bl
        shr al, 1
        jmp CNF

    PARI:
        test bl, 1
        jnz ERRORE
        xor bl, bl
        shr al, 1
        jmp CNF


    ERRORE:
        mov errori, 1
    
    FINE:
        mov errore, edi
    }
    printf("%d\n\n", errore);
    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));
    return 0;
}

