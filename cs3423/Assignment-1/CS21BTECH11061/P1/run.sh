INPUT='1.txt'

flex lex_source_program.l
gcc lex.yy.c
./a.out $INPUT