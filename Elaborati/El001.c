#include <stdio.h>

int main() {
    char* strings[] = {97, 200, 100, 101, 211, 107, 83, 55, 192, 34, 77, 123, 65, 88, 209, 150, 72, 178, 43, 99, 202, 116, 35, 77, 153, 44, 21, 66, 198, 112, 176, 240, 77, 94, 62, 189, 115, 208, 71, 29, 144, 201, 87, 150, 245, 33, 80, 222, 187, 64, 239, 50, 113, 156, 77, 222, 155, 91, 12, 88, 209, 171, 244, 210, 201, 167, 34, 19, 112, 209, 51, 42, 118, 57, 221, 177, 233, 49, 60, 222, 97, 223, 198, 132, 105, 194, 145, 209, 241, 82, 30, 77, 201, 28, 155, 248, 39, 58, 179, 57, 108, 243, 142, 64, 90
};


        int num = sizeof(strings) / sizeof(strings[0]);
    __asm {
        sub num, 1
    inizio :
        xor ecx, ecx //inizializzo ecx a 0
        xor ebx, ebx//inizializzo a 0 il counter di swap

    loop_iniziale:
        xor edx, edx //inizializzo edx a 0 perchè sarà il mio offset dei caratteri
       

        mov esi, dword ptr[strings + ecx * 4] //muovo in esi il puntatore all primo carattere della stringa
        mov edi, dword ptr[strings + ecx * 4 + 4] //muovo in edi il puntatore al primo carattere della stringa precedente
            cmp ecx, num
            je fine
            
            inc ecx
    compare:
            mov ah, [esi + edx]
            mov al, [edi + edx]
            //se la prima parola è zero vado alla parola successiva, perchè in questo caso so che è minore di quella dopo, peffo
            cmp ah, 0
            je loop_iniziale
            //cmp dh, dl //ORDINA IN MODO CRESCENTE
            cmp al, ah
            je prossimo_carattere
            ja loop_iniziale
            //inverto l'ordine dei puntatori della prima parola e della parola n e li scambio
            dec ecx
            xchg esi, edi
            mov dword ptr[strings + ecx * 4], esi
            mov dword ptr[strings + ecx * 4 + 4], edi
            inc ecx
            jmp inizio

    prossimo_carattere:
        inc edx
        jmp compare//incremento il mio offset
        //ripeti il confronto finché non si raggiunge la fine della stringa

    //scambio i registri
    next:
        cmp ebx, 1 //se è stato fatto uno swap rinizio
        je inizio

        fine:
    }
    printf("Stringhe ordinate:\n");
    for (int i = 0; i < num; i++) {
        printf("%s\n", strings[i]);
    }
    return 0;
}
