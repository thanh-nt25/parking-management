all: compile run clean
compile: main.c libs/bst.c libs/bst_traversal.c libs/data_t.c libs/stack.c libs/queue.c
	@gcc -o main main.c libs/bst.c libs/bst_traversal.c libs/data_t.c libs/stack.c libs/queue.c
run: main
	@./main
clean: 
	@rm ./main


