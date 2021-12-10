RIOT_BASE = RIOT

static-test:
	$(shell git clone https://github.com/Mesh4all/RIOT.git)
	./dist/tools/ci/static_tests.sh

all: static-test

clean:
	$(shell rm -rf RIOT)

docs:
	cd doc/doxygen && make
