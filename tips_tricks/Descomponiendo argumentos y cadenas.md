En C y en casi todos los lenguajes de programación se tienen la posibilidad de pasar argumentos al programa para su ejecución, divididos en argc y argv.
1.  **`argc`**  es un entero que representa la cantidad de argumentos que se han enviado al programa.
2.  **`argv`**  es un arreglo de punteros de caracteres, que contiene el nombre del programa como primer elemento, seguido de los argumentos con los que se ejecutó el programa o cualquier elemento en el arreglo.

Por ejemplo, en lenguajes como java y python la representación es de la siguiente manera

```java
...
public static void main(String[] args) {
...
```

```python
# main.py
import sys

if __name__ == "__main__":
    print(f"Arguments count: {len(sys.argv)}")
    for i, arg in enumerate(sys.argv):
        print(f"Argument {i:>6}: {arg}")
```

Para el caso de C, la lectura de un argumento y su iteración entre cada uno de sus elementos sería de la siguiente manera:

```C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int i;
	char *num = argv[1];

	fprintf(stdout, "arg[1] = %s \n", argv[1]);
	
	for (i = 0; i < strlen(argv[1]); i++)
		fprintf(stdout, "num[%d] = %c \n", i, num[i]);

	return 0;
}
```

Dando una salida de la siguiente manera al momento de ejecutarse
```bash
$ ./read_string.o 410692696
arg[1] = 410692696 
num[0] = 4 
num[1] = 1 
num[2] = 0 
num[3] = 6 
num[4] = 9 
num[5] = 2 
num[6] = 6 
num[7] = 9 
num[8] = 6 
$
```