all:
	@echo Compiling...
	@gcc -g3 -O2 *.c

clean:
	@echo Cleaning...
	@rm -fr a.out
