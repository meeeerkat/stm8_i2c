
SDCC=sdcc -lstm8 -mstm8 --out-fmt-ihx --std-sdcc11

.PHONY=clean, test, build


build: i2c.lib

test: test.ihx
	sudo stm8flash -c stlinkv2 -p stm8s003f3 -w test.ihx
	sleep 1



test.ihx: i2c.lib
	${SDCC} test.c i2c.lib

i2c.lib: i2c.rel
	sdar -rc i2c.lib i2c.rel

i2c.rel:
	${SDCC} -c i2c.c

clean:
	rm *.lib *.mem *.rel *.ihx *.rst *.map *.lk *.sym *.asm *.lst 2> /dev/null
