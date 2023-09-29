INPUT='1.clike'

bison parse.y -dy
flex lex.l
gcc lex.yy.c y.tab.c -lfl
./a.out $INPUT
rm ./a.out