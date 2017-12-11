all: simple_cpp async_cpp simple_c

simple_cpp: simple.cc
	g++ -g -Werror -Wno-variadic-macros -Wall -Wextra -Weffc++ -pedantic $< -o $@ -lwebsms

async_cpp: async.cc
	g++ -g -Werror -Wno-variadic-macros -Wall -Wextra -Weffc++ -pedantic $< -o $@ \
	-lwebsms -lboost_thread-mt

simple_c: simple.c
	gcc -g -Werror -Wno-variadic-macros -Wall -Wextra -pedantic $< -o $@ -lwebsms

clean:
	rm -rf simple_cpp async_cpp simple_c core

.PHONY: all clean
