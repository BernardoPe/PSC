Descompactar o pacote com os programas de teste
numa diretoria relativa à realização da série de exercicios.
Recomenda-se a seguinte estrutura de diretórios:

home
└── aluno
    └── psc
        └── 2324inv
              ├── serie1
              ├── serie2
              └── serie3

$ cd ~/psc/2324inv/serie1
$ unzip ~/Downloads/serie1_entrega.zip

Depois da descompactação deve verificar o seguinte conteúdo:

$ tree serie1_entrega

serie1_entrega
├── exercicio1
│   ├── build.sh
│   ├── max_value.c	*
│   └── max_value_test.c
├── exercicio2
│   ├── build.sh
│   ├── bits.c	*
│   └── bits_test.c
├── exercicio3
│   ├── build.sh
│   ├── string_split.c *
│   └── string_split_test.c
├── exercicio4
│   ├── build.sh
│   ├── string_to_time.c *
│   └── string_to_time_test.c
├── exercicio5
│   ├── build.sh
│   ├── test.sh
│   ├── input.csv
│   ├── csv_filter_ref
│   └── csv_filter.c *
├── readme.txt
└── test.sh

Nas diretorias `exercicio1`, `exercicio2`, `exercicio3`, e `exercicio4`,
existe um ficheiro separado para o código proposto como resolução do exercício.
O nome do ficheiro é igual ao nome da função que contém.
Por exemplo max_value.c para o caso do exercício1.

Os ficheiros assinalados com * estão originalmente vazios.
O aluno deve substitui-los ou preenche-los com a sua proposta de resolução.

Os nomes dos ficheiros com o programa de teste têm a forma `xxx_test.c`,
em que ``xxx`` corresponde ao nome da função em teste.

Após a descompactação, os ficheiros *script* (extensão `.sh`)
e o executável de referência no exercício5 (`csv_filter_ref`)
podem não possuir o atributo de executável.
Para atribuir essa capacidade deve fazer-se:

$ cd serie1_entrega
$ chmod +x exercicio1/build.sh

$ chmod +x exercicio5/csv_filter_ref

Pode testar individualmente cada programa,
invocando o executável produzido pelos *script* `build.sh`.

$ cd serie1_entrega/exercicio1
$ ./build.sh
$ ./max_value_test

No final pode confirmar todos os testes invocando:

$ cd serie1_entrega
$ ./test_all.sh

A entrega deve ser realizada no Moodle através da submissão do pacote **zip**
gerado da seguinte forma:

$ zip -r serie1_entrega.zip serie1_entrega

