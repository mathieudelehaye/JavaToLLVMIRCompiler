rp:
	bison rpcalc.y -o ../generated/rpcalc.tab.c
	cc -c ../generated/rpcalc.tab.c -o ../build/rpcalc.tab.o
	cc -c calc_main.c -o ../build/calc_main.o
	cc ../build/rpcalc.tab.o ../build/calc_main.o -o ../build/rpcalc
clean:
	rm ../build/*
	rm ../generated/*