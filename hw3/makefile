F = smartptr.cpp

gcc: $(F)
	g++ -Wall -Wpedantic -Wextra -Wno-unused -std=gnu++17 -g -ggdb $^ -o smartptr

clang: $(F)
	clang++ -Wall -Wpedantic -Wextra -Wno-unused -Wno-unused-parameter -std=c++14 -g -ggdb $^ -o smartptr

# Version specific

gcc7: $(F)
	g++-7 -Wall -Wpedantic -Wextra -Wno-unused -std=gnu++17 -g -ggdb $^ -o smartptr

gcc6: $(F)
	g++-6 -Wall -Wpedantic -Wextra -Wno-unused -std=gnu++17 -g -ggdb $^ -o smartptr

gcc5: $(F)
	g++-5 -Wall -Wpedantic -Wextra -Wno-unused -std=gnu++17 -g -ggdb $^ -o smartptr

clang5: $(F)
	clang++-5.0 -Wall -Wpedantic -Wextra -Wno-unused -Wno-unused-parameter -std=gnu++1z -g -ggdb $^ -o smartptr

clang4: $(F)
	clang++-4.0 -Wall -Wpedantic -Wextra -Wno-unused -Wno-unused-parameter -std=gnu++1z -g -ggdb $^ -o smartptr

# Does not seem to work
clang3.8: $(F)
	clang++-3.8 -Wall -Wpedantic -Wextra -Wno-unused -Wno-unused-parameter -std=c++14 -g -ggdb $^ -o smartptr
