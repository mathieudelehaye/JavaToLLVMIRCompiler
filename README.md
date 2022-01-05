# BisonParsers
Some parsers and lexical analysers created with GNU Bison and Flex open source tools

Use example:

```
bison rpcalc.y -o generated/rpcalc.tab.c     
cc generated/rpcalc.tab.c -lm -o build/rpcalc
build/rpcalc # Ctrl+D to leave
```
