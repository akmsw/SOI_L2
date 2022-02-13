#include <stdio.h>
#include "structs.h"

int main()
{
    const BaseData data = {
                .a = 1,
                .b = 3,
                .x = 15,
                .y = 65535,
                .c = 128,
                .z = -1, 
                .d = {1,1,1}
    };

    /* Explique a que se debe los tamanios de cada una de las estructuras */
    printf("base     struct size  %zu \n", sizeof(BaseData));
    printf("reorder  struct size  %zu \n", sizeof(ReorderData));
    printf("extended struct size  %zu \n", sizeof(ExtendedData));
    printf("packed   struct size  %zu \n\n", sizeof(BaseDataPacked));

    /* explique por que la expresion que calcula  limit y limit_aux generan el mismo resutado */
    /* hint : investigar sobre reglas de aritmetica de punteros */
    
    char *limit = ((char *) &data + sizeof(BaseData)); 
    char *limit_aux =(char *) (&data + 1);

    printf("limit     value is %p \n", limit); 
    printf("limit_aux value is %p \n\n", limit_aux); 

    int i = 0;
    /* Explique los valores que se muestran en pantalla en cada iteracion del for */
    for (char *c = (char *) &data; c < limit; c++, i++ ){
        printf("byte %02d : 0x%02hhx \n", i, *c);
    }
}
