//CAPIRE IN CHE PUNTO DEVO FAR TORNARE LA LA SECONDA MATRICE A PARTIRE DA 0 MA PENSO SOLO QUANDO TROVA CHE LA MAT DI 1 é MULTIPLO;IL RESTO é STORIA; CONTAOLLA BENE ANCHE 
//IL CONTO PERCHé FATTO COSI SALTA LA LA RIGA x*n

#include <stdio.h>

int main() {
    unsigned int m = 32; // numero di righe della prima matrice
    unsigned int n = 2; // numero di colonne della prima matrice
    unsigned int k = 32; // numero di colonne della seconda matrice
    short int mat1[] = {
        // Prima riga
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,

        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,5
    };
    short int mat2[] = {
        // Prima riga
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2
    };
    int mat3[1024]; // matrice risultato
    int val;
    __asm {
        //Contatori
        xor esi, esi
        xor edi, edi
        xor ebx, ebx

        mov ecx, m   // Numero di righe
        imul ecx, k   // Numero totale di elementi di mat3
        mov ebx, ecx

    MAT3_ZERO:
        mov[mat3 + edi * 4], 0 // Inizializza l'elemento corrente di mat3 a zero
        inc edi
        cmp edi, ecx
        jl MAT3_ZERO

        // non sono mai da riscrivere
        xor esi, esi
        xor edi, edi
        xor ecx, ecx

            
        //Codizioni di uscita
    RIGA:
        mov eax, m
        mov ebx, k
        imul ebx, eax
        cmp ecx, ebx
        je FINE

       

        movsx eax, [mat1 + esi * 2]
        movsx ebx, [mat2 + edi * 2]
        imul ebx, eax
        add[mat3 + ecx * 4], ebx    // moltiplico e inserisco dentro mat3   
        // incremento la posizione si di mat2 sia di mat3

        inc ecx
        inc edi 

        mov eax, n
        mov ebx, k
        imul ebx, eax
        cmp ebx, edi
        je DACAPO   //riporta a zero mat2 quando arriva all'ultimo elemento

        mov eax, edi
        mov ebx, k
        xor edx, edx
        div ebx
        test edx, edx
        jz RIGAFINITA   // se è mutiplo di k vuol dire che la riga è finita e devo fare +1 su esi
        jmp RIGA


    RIGAFINITA:
        inc esi
        mov eax, esi
        mov ebx, n
        xor edx, edx
        div ebx
        test edx, edx
        je RIGA
        sub ecx, k
        jmp RIGA

    DACAPO:
        xor edi,edi
        jmp RIGAFINITA


    FINE:
        
    }

    printf("%d\n", val);
    // Stampa il risultato
    unsigned int i, j, h = 0;
    printf("Matrice prodotto:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < k; j++, h++)
            printf("%6d ", mat3[h]);
        printf("\n");
    }

    return 0;
}
