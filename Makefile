RIOT_BASE = RIOT

static-test:
	$(shell git clone -q git@github.com:Mesh4all/RIOT.git)
	./dist/tools/ci/static_tests.sh

all: 
	static-tests

clean:
	$(shell rm -rf RIOT)