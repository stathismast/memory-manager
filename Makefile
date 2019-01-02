all:
	@echo Compiling...
	@gcc -g3 *.c

clean:
	@echo Cleaning...
	@rm -fr a.out
