rp:
	bison rp/rpcalc.y -o ../generated/rp/rpcalc.tab.c
	if [ ! -d "../build" ]; then mkdir ../build; fi
	if [ ! -d "../build/common" ]; then mkdir ../build/common; fi
	if [ ! -d "../build/rp" ]; then mkdir ../build/rp; fi
	cc -c ../generated/rp/rpcalc.tab.c -o ../build/rp/rpcalc.tab.o
	cc -c common/calc_main.c -o ../build/common/calc_main.o
	cc ../build/rp/rpcalc.tab.o ../build/common/calc_main.o -o ../build/rp/rpcalc
in:
	bison in/incalc.y -o ../generated/in/incalc.tab.c
	if [ ! -d "../build" ]; then mkdir ../build; fi
	if [ ! -d "../build/common" ]; then mkdir ../build/common; fi
	if [ ! -d "../build/in" ]; then mkdir ../build/in; fi
	cc -c ../generated/in/incalc.tab.c -o ../build/in/incalc.tab.o
	cc -c common/calc_main.c -o ../build/common/calc_main.o
	cc ../build/in/incalc.tab.o ../build/common/calc_main.o -o ../build/in/incalc
mf:
	bison mf/mfcalc.y -o ../generated/mf/mfcalc.tab.c
	if [ ! -d "../build" ]; then mkdir ../build; fi
	if [ ! -d "../build/mf" ]; then mkdir ../build/mf; fi
	cc -c ../generated/mf/mfcalc.tab.c -o ../build/mf/mfcalc.tab.o
	cc -c mf/mfcalc_main.c -o ../build/mf/mfcalc_main.o
	cc ../build/mf/mfcalc.tab.o ../build/mf/mfcalc_main.o -o ../build/mf/mfcalc
clean:
	if [ -d "../build" ]; then rm -R ../build; fi
	if [ -f "../generated/rp/rpcalc.tab.c" ]; then rm ../generated/rp/rpcalc.tab.c; fi
	if [ -f "../generated/in/incalc.tab.c" ]; then rm ../generated/in/incalc.tab.c; fi
	if [ -f "../generated/mf/mfcalc.tab.c" ]; then rm ../generated/mf/mfcalc.tab.c; fi
	