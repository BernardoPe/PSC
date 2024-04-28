Descompactar o pacote com os programas de teste
numa diretoria relativa à realização da série de exercicios.
Recomenda-se a seguinte estrutura de diretorias:

home
└── aluno
    └── psc
        └── 2324inv
              ├── serie1
              ├── serie2
              └── serie3

$ cd ~/psc/2324inv/serie2
$ unzip ~/Downloads/serie2_entrega.zip

Depois da descompactação deve verificar o seguinte conteúdo:

$ tree serie2_entrega

serie2_entrega
├── exercicio1
│   ├── build.sh
│   ├── next_pow2.s     <-- a realizar pelo aluno
│   └── next_pow2_test.c
├── exercicio2
│   ├── build.sh
│   ├── my_strtok_asm.s     <-- a realizar pelo aluno
│   ├── my_strtok.c
│   └── my_strtok_test.c
├── exercicio3
│   ├── build.sh
│   ├── compare_offset_asm.s     <-- a realizar pelo aluno
│   ├── compare_offset.c
│   ├── compare_offset_test.c
│   └── struct_values.h
├── exercicio4
│   ├── build.sh
│   ├── bubble_sort_asm.s     <-- a realizar pelo aluno
│   ├── bubble_sort.c
│   ├── bubble_sort_test.c
│   └── compare.s
├── invoke
│   └── invoke.s
├── readme.txt
└── test_all.sh


Os nomes dos ficheiros com o programa em assembly têm a forma xxx_asm.s,
em que xxx corresponde ao nome da função que contêm.
Os nomes dos ficheiros com o programa de teste têm a forma xxx_test.c,
em que xxx corresponde ao nome da função em teste.

Nos exercicios 1, 3 e 4, para testar a versão assembly deve alterar o script build.sh,
substituindo a mensão ao ficheiro xxx.c por xxx_asm.s.

A entrega deve ser realizada no Moodle através da submissão de um pacote zip
gerado da seguinte forma:

$ cd ~/psc/2324inv/serie2
$ zip -r serie2_entrega.zip serie2_entrega
