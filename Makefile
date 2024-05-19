all: install

install: uninstall clean
	@mkdir -p obj
	@gcc -c libs/logic.c -o obj/logic.o
	@gcc -c libs/draw.c -o obj/draw.o
	@mkdir build
	@gcc obj/draw.o obj/logic.o tank_T-39.c -o build/tank_T-39 -lncurses

clean:
	@rm -rf obj

uninstall:
	@rm -rf build

run:
	@./build/tank_T-39

.PHONY: all build clean
