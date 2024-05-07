#include <stdio.h>

int main() {
    char* strings[] = {"cangnolinii","cangnolina"};
    int num = sizeof(strings) / sizeof(strings[0]);
    printf("Parole: %d\n", num);

    __asm {
        xor edx, edx    //contatore lettere in comune
        
        xor eax, eax    //contenitore parola 0
        xor ebx, ebx    //contenitore parola n

        // contatori di poszione degli elementi
        xor edi, edi     
        xor ecx, ecx

    CICLONE:
            mov eax, dword ptr[strings + edi * 4]
            mov ecx, edi

    PS: //parola successiva serve per prendere la parola seguente alla prima, che penso sia ordinata
            inc ecx
            cmp ecx, num
            je PD
            mov ebx, dword ptr[strings + ecx * 4]
            xor esi, esi

    CNF: //confronta metto dentro dh e dl i singoli caratteri uso un registro in comune "esi" che mi permettete di scorrere le lettere simultaneamente
            mov dh, [eax + esi]
            mov dl, [ebx + esi]
            //se la prima parola è zero vado alla parola successiva, perchè in questo caso so che è minore di quella dopo, peffo
            cmp dh, 0
            je PS
            //cmp dh, dl //ORDINA IN MODO CRESCENTE
            cmp dl, dh
            je NL
            ja PS
            //inverto l'ordine dei puntatori della prima parola e della parola n e li scambio
            xchg eax, ebx
            mov dword ptr[strings + edi * 4], eax
            mov dword ptr[strings + ecx * 4], ebx
            cmp edi, num
            jb CICLONE
            jmp FINE

    PD: //non mi ricordo il nome ma serve per incremenetare la prima parola e controllare quando arriva la fine dell'array in modo da terminare
            inc edi
            cmp edi, num
            je FINE
            jmp CICLONE

    NL://next letter, aumento la variabile esi in modo da andare alla lettera successiva dell'elemento, poi torno dentro il confronto
            inc esi
            jmp CNF

    FINE:
    }

    printf("Stringhe ordinate:\n");
    for (int i = 0; i < num; i++) {
        printf("%s\n", strings[i]);
    }
    return 0;
}
