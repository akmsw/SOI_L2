# Laboratorio Nº2 - Repaso del lenguaje C

Para comenzar, se debe clonar el repositorio. Una vez hecho, podemos compilar todo el proyecto aprovechando el archivo `makefile`, con el comando:

`make all`

Esto compilará todo con las flags indicadas en la consigna:

`gcc -Wall -Werror -pedantic`

Se organizó el proyeto en distintas carpetas para un mejor manejo de archivos. El código fuente en lenguaje C que resuelve los primeros dos ejercicios se encuentra en la carpeta `src`. Los headers y cuerpos de las librerías estáticas propias se encuentran en `src/include`. En la carpeta `e3` se encuentran los archivos provistos inicialmente en el repositorio para resolver la actividad 3.

Se crean carpetas adicionales para los archivos `.a`, `.o` y para el ejecutable.

Para ejecutar el archivo que muestra la resolución de las actividades 1 y 2, luego de compilar todo con el archivo makefile, se debe ingresar por consola:

`./bin/mainL2`

### **El proyecto ha sido documentado en su totalidad explicando cómo y por qué cada función hace lo que hace.**

## RESPUESTAS

# 1.- **C - strings**
Esta primera actividad tiene como objetivo repasar el manejo de strings en lenguaje C. Para ello, se pide buscar información específica sobre la memoria y la unidad central de procesamiento (CPU) del sistema en los archivos */proc/meminfo* y */proc/cpuinfo* respectivamente, y mostrarlo en pantalla.

Del archivo */proc/meminfo* se extrajeron los siguientes campos:
- Memoria RAM total (en MB)
- Memoria RAM libre (en MB)
- Memoria RAM disponible (en MB)
- Memoria SWAP ocupada (en MB)

Del archivo */proc/version* se extrajeron los siguientes campos:
- Modelo de CPU
- Cantidad de cores
- Cantidad de threads por core

Para modularizar aún más el programa, se optó por desarrollar una librería estática propia (`file_utilities`) que contenga funciones útiles para varias actividades comunes que se repiten. Por poner un ejemplo, se desarrolló una función `open_file` que se encarga de abrir un archivo indicado por parámetros y dejarlo listo para poder trabajar con el mismo, cosa que se repite varias veces para buscar la información. Se tuvo el cuidado de cerrar el archivo utilizado cada vez que se termina de trabajar con él para evitar inconvenientes.

También se desarrolló una librería para almacenar allí las funciones claves para este laboratorio particular (`lab2_utilities`), y dejar el archivo `main` lo más limpio y sencillo posible.

Se menciona que la información de la cantidad de threads por core no está explícita en el archivo */proc/cpuinfo*, por lo que se la tuvo que calcular. Para esto, se acudió a la siguiente ecuación:

`cantidad_de_threads = threads_por_core * cores_por_socket * sockets`

Este sistema en particular posee un solo socket para procesador, por lo que podemos reescribir la ecuación de la forma:

`cantidad_de_threads = threads_por_core * cores_por_socket`

De aquí, despejando `threads_por_core` obtenemos:

`threads_por_core = cantidad_de_threads / cores_por_socket`

En este sistema, al tener sólo un socket, la variable `cores_por_socket` es simplemente la cantidad de cores del procesador, dejando la ecuación más legible aún:

`threads_por_core = cantidad_de_threads / cantidad_de_cores`

Simplificando aún más la notación, obtenemos:

`threads_por_core = threads / cores`

La cantidad de threads figura como `siblings` en el archivo */proc/cpuinfo*, y la cantidad de cores figura como `cpu cores`.

De manera similar, la cantidad de memoria SWAP ocupada no figura explícitamente en el archivo */proc/meminfo*, pero puede calcularse fácilmente haciendo la diferencia:

`memoria_swap_ocupada = memoria_swap_total - memoria_swap_libre`

No hubo mayores inconvenientes en esta actividad.

# 2.- **Arreglos**

El propósito de esta actividad es el de repasar los conceptos de memoria estática y dinámica, y con ello manejar arreglos dinámicos.

Se pide leer el archivo */proc/version* almacenando cada palabra en un arreglo dinámico, imprimir en pantalla todas las palabras convertidas a mayúsculas, y liberar la memoria que se haya alocado.

Para esto, se trabajó con las reconocidas funciones `malloc` y `realloc`. Se empieza con un doble puntero `char **` que representaría un puntero a arreglos de caracteres. Al principio, este arreglo tiene memoria alocada para sólo un puntero `char *` (una sola palabra), pero a medida que se encuentran palabras en el archivo, se expande esta memoria por medio de `realloc`, siempre testeando que no haya ningún `NULL` por fallas en la alocación de memoria.

Se optó por almacenar las palabras directamente en mayúsculas. Cada letra de cada palabra se analiza individualmente y si su valor en ASCII coincide con los de las letras minúsculas, se hace uso de la función `toupper` de la librería `ctype.h` para obtener su equivalente en mayúsuclas, y se reemplaza en la palabra.

Finalmente, se recorre este arreglo dinámico imprimiendo cada palabra por consola, y luego se procede a liberar la memoria alocada en este arreglo mediante la función `free` de la librería `stdio.h`.

# 3.- **Estructuras**

## a. ¿Cómo utilizar typedef junto a struct? ¿Para qué sirve? Ejemplo.

La palabra reservada `typedef` se utiliza para asignar un alias a un tipo de dato existente o definido por el usuario.

En general, podemos hacer uso de typedef con algún tipo de dato que se use mucho en nuestro código y su declaración sea muy extensa. Por ejemplo, si tenemos que trabajar con variables de tipo `unsigned short int`, podemos asignarle un alias al principio de nuestro programa de la forma:

`typedef unsigned short int MI_VARIABLE;`

y a partir de ese punto, declarar una variable de tipo `MI_VARIABLE` es lo mismo que declarar una variable de tipo `unsigned short int`.

La palabra reservada `typedef` puede utilizarse también junto a `struct`. Supongamos que tenemos una estructura como la siguiente:

`struct my_struct`\
`{`\
`⠀⠀⠀⠀int my_int;`\
`⠀⠀⠀⠀char my_char;`\
`};`

Si quisiéramos declarar una instancia de la misma, habría que hacerlo de la manera:

`struct my_struct instance_name;`

Si tuviéramos que declarar muchas instancias de esta estructura en distintos lugares, tendríamos que escribir **siempre** la palabra reservada `struct` para indicar que estamos utilizando un tipo de dato definido por nosotros.

Podemos definir la estructura con `typedef` de las siguientes formas:

- FORMA 1\
`typedef struct my_struct`\
`{`\
`⠀⠀⠀⠀int my_int;`\
`⠀⠀⠀⠀char my_char;`\
`} my_struct;`

- FORMA 2\
`struct my_struct`\
`{`\
`⠀⠀⠀⠀int my_int;`\
`⠀⠀⠀⠀char my_char;`\
`};`\
\
`typedef struct my_struct my_struct;`

Cualquiera de las dos formas hace que a partir de ese momento, si quiero declarar una instancia de la estructura, sólo tendría que hacerlo de la manera:

`my_struct instance_name;`

facilitando así la legibilidad del código.

## b. ¿Qué es packing y padding?

### ***Padding***
El 'padding' es una técnica empleada para reducir la cantidad de ciclos del procesador para acceder a cierta información, ocupando más memoria de la necesaria.

Supongamos que estamos trabajando en un sistema de 32 bits (con un tamaño de palabra de 4 bytes) y tomemos el ejemplo de una estructura como la siguiente:

`typedef struct s_name`\
`{`\
`⠀⠀⠀⠀char char1;`\
`⠀⠀⠀⠀char char2;`\
`⠀⠀⠀⠀int int1;`\
`} s_name;`

De esta manera, una variable de tipo `char` ocupa un total de 1 byte, mientras que una variable de tipo `int` ocupa 4 bytes.

Si sumamos el total de bytes que en teoría estaríamos ocupando, veríamos que sería:

> 1B + 1B + 4B = 6B

Sin embargo, si corremos la siguiente línea de código:

`sizeof(s_name);`

obtendríamos un total de 8B.\
Para resolver esta duda, tenemos que ver cómo accede el procesador a la memoria.\
Podríamos pensar que la manera más óptima de almacenar una instancia de tipo `s_name` en memoria sería:

![padding_1](https://user-images.githubusercontent.com/66426042/130160847-ed7321f6-28bb-4af6-97b0-be9dd27a69af.png)

Sin embargo, a la hora de acceder a los datos para utilizarlos, el procesador tiene un ancho de palabra de 4 bytes, por lo que lo que encontraría en el primer ciclo sería:

![padding_2](https://user-images.githubusercontent.com/66426042/130161058-7ad560c4-f783-4484-9817-ff2f005e5c04.png)

Como se ve, para obtener el valor de `int1` no basta con una simple búsqueda. El procesador necesitará buscar nuevamente, obteniendo otra palabra de 4 bytes de la forma:

![padding_3](https://user-images.githubusercontent.com/66426042/130161202-2ebdfca3-46df-48b8-b1f8-2dbd1ca921e6.png)

Esto nos muestra que para acceder a la variable int1 se necesitan **dos** ciclos.\
Si tuviéramos una estructura más compleja aún con tipos de datos que ocupen más memoria, puede que para obtener el valor de una sola variable hagan falta incluso más de dos ciclos de búsqueda. Para esto, el sistema aplica automáticamente la técnica de *padding*, que consiste en distribuir en memoria los datos de tal manera que la cantidad de ciclos que se necesiten para acceder a cada uno sea la menor posible.

En este caso, obtenemos un sizeof de 8B porque al hacerse automáticamente el padding, las variables de la estructura se almacenan de la siguiente forma:

![padding_4](https://user-images.githubusercontent.com/66426042/130162086-932b610a-af34-47d2-bd41-0773b6c11d33.png)

Aquí vemos que para obtener los dos `char` necesitamos un sólo ciclo de búsqueda, e igualmente necesitamos sólo un ciclo de búsqueda para obtener la variable `int`, a costa de ocupar 2 palabras de 4 bytes cada una.

El padding depende de cómo está declarada una estructura. Si a la misma estructura la declaramos de la siguiente forma:

`typedef struct s_name`\
`{`\
`⠀⠀⠀⠀char char1;`\
`⠀⠀⠀⠀int int1;`\
`⠀⠀⠀⠀char char2;`\
`} s_name;`

Ahora, si calculamos `sizeof(s_name);` obtendríamos un total de 12B.\
Esto es porque el padding distribuirá en memoria las variables de la siguiente manera:

![padding_5](https://user-images.githubusercontent.com/66426042/130163221-48758f85-f827-40af-95e5-4aae2a2c6786.png)

Aquí tenemos 3 palabras de 4B cada una, teniendo así:

>  4B + 4B + 4B = 3 * 4B = 12B

Así, concluímos que el *padding* reduce la cantidad de ciclos de CPU para acceder a los datos a costa de utilizar más memoria de la necesaria. Se suele utilizar en sistemas en los que la velocidad de procesamiento es muy imporante y cada ciclo de CPU cuenta, sin importar si se malgasta memoria.

### ***Packing***
Debido al padding de estructuras, el tamaño de las mismas se ve incrementado (aveces demasiado), malgastando así memoria.\
Si estamos trabajando para un sistema en el que un recurso como la memoria es limitado y muy importante, y la velocidad de procesamiento no es una gran prioridad, el concepto de *packing* viene muy bien.\
Se puede evitar el malgasto de memoria mediante la directiva de procesamiento: `#pragma pack(1)`.\
Esta directiva se encarga de almacenar la menor cantidad de memoria requerida para los datos. Si retomamos la primera estructura que con padding ocupaba 8B, aplicándole esta directiva al mismo código, la función `sizeof(s_name)` nos retornaría el valor esperado de 6B.\
Podemos ver que, entonces, el concepto de *packing* minimiza el uso de memoria, causando un posible malgasto de ciclos de CPU.

## c. Respuestas a las preguntas de los archivos struct.h y lab2.c

### c.1) Explique a qué se deben los tamaños de cada una de las estructuras

Los tamaños que se muestran por terminal son debidos al orden en que fueron almacenadas las variables
de cada estructura, haciendo que el 'padding' desperdicie más (o menos) memoria.

Por ejemplo, en el primer caso, el 'padding' almacenaría las variables de la forma:

![e3_1](https://user-images.githubusercontent.com/66426042/130272582-be85c1be-dd3a-4728-b8fa-6ab36a77d5ef.png)


Total de bytes ocupados = 20 bytes

Y en el segundo caso, el 'padding' almacenaría las variables de la forma:

![e3_2](https://user-images.githubusercontent.com/66426042/130272870-d80a9ee6-f312-4161-b951-35be251ddd5e.png)

Total de bytes ocupados = 16 bytes

Para los demás casos es lo mismo, sólo que teniendo en cuenta los tamaños de cada tipo de variable:

`sizeof(char)` = 1 byte\
`sizeof(unsigned short int)` = 2 bytes\
`sizeof(int)` = 4 bytes\
`sizeof(long unsigned int)` = 8 bytes

### c.2) Explique por qué las expresiones que calculan `limit` y `limit_aux` generan el mismo resutado

En el cálculo de `limit` estamos primero apuntando al comienzo de `data` y nos corremos tantos bytes como el tamaño de `BaseData` (20 bytes), y en el cálculo de `limit_aux` hacemos uso de la aritmética de punteros para desplazarnos un tipo de dato `BaseData`, lo que termina resultando en un desplazamiento de la misma cantidad de bytes en ambos casos, llegando así a apuntar a la misma dirección de memoria.

### c.3) Explique los valores que se muestran en pantalla en cada iteracion del ciclo `for`

Los valores obtenidos son debido al 'padding' explicado anteriormente para la struct BaseData. Podemos ver que en los bytes 00 y 01 se almacenan los valores `0x01` y `0x03`, pero en los bytes 02 y 03 no se almacena nada, ya que el siguiente dato es un int que ocupa 4 bytes y no estamos haciendo packing.\
En el byte 04 se almacena `0x0f` que es el valor 15 (el valor de .x en data) y en los bytes 05, 06 y 07 vemos que tienen `0x00` porque sólo hace falta un byte para representar el número 15.\
En los bytes 08 y 09 tenemos `0xff` en ambos porque el parámetro .y es de tipo unsigned short int (2 bytes) y el mayor número que puede representar es 65535 (que coincide con el valor asignado a .y y se representa con `0xffff`, por lo que lo mostramos en dos bytes).\
En el byte 10 tenemos almacenado `0x80` porque al asignar el valor 128 a .c sin comillas simples estamos haciendo referencia al caracter 128 decimal de la tabla ASCII (cuyo valor hexadecimal es `0x80`), que corresponde al caracter Ç.\
El byte 11 es basura. Con cada corrida del programa vemos que su valor varía.\
Los bytes 12 y 13 almacenan `0xff` cada uno, ya que la variable que representan (.z) es de tipo unsigned short int y esto implica que al asignarle un valor de -1 tendremos un underflow, volviendo al número más grande de representar posible para este tipo de dato (65535).\
Los bytes 14, 15 y 16 almacenan los elementos del arreglo de caracteres (.d).\
Los bytes 17, 18 y 19 son basura. Sus valores cambian con cada corrida del programa.\
En total vemos que los bytes 00-19 conforman los 20 bytes correspondientes a la estructura BaseData.\

## d. Ejercicio de lista simplemente enlazada.

Se desarrolló un programa en C con una estructura simple de nodos que contienen un valor entero y un puntero a otro nodo del mismo tipo.\
Además, se tiene una función que permite agregar nuevos nodos al final de la lista. La documentación está en el archivo `linked_list.c`.

Se debe abrir una terminal y dirigirse a la carpeta `e3`. Si se corre el comando `ls` allí dentro, se podrá ver un archivo `makefile` distinto al de los ejercicios 1 y 2. Este nuevo makefile es más simple y sólo compila el archivo `linked_list.c` con las flags indicadas en la consigna.

Para compilar este ejercicio, basta con ejecutar este makefile en la terminal de la manera:

`make all`

Finalmente, se puede ejecutar el programa para ver el resultado desde la terminal de la forma:

`./bin/linked_list`

# 4.- **Conclusiones**

Este trabajo fue muy útil tanto para refrescar conceptos del lenguaje de programación C, como para familiarizarse con la jerarquía de archivos del sistema, aprender a manejar nuevas herramientas de compilación como es un makefile, descubrir nuevo instrumental para consultar documentación como es el comando `man` (que ha ayudado demasiado), y para aprender a utilizar comandos en la terminal del sistema que pueden agilizar mucho distintos tipos de tareas.
