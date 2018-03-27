
gcc: smartptr.cpp
	g++ -Wall -Wpedantic -Wextra -Wno-unused -std=gnu++17 -g -ggdb $^ -o smartptr

gcc7: smartptr.cpp
	g++-7 -Wall -Wpedantic -Wextra -Wno-unused -std=gnu++17 -g -ggdb $^ -o smartptr

gcc6: smartptr.cpp
	g++-6 -Wall -Wpedantic -Wextra -Wno-unused -std=gnu++17 -g -ggdb $^ -o smartptr

gcc5: smartptr.cpp
	g++-5 -Wall -Wpedantic -Wextra -Wno-unused -std=gnu++17 -g -ggdb $^ -o smartptr

clang5: smartptr.cpp
	clang++-5.0 -Wall -Wpedantic -Wextra -Wno-unused -Wno-unused-parameter -std=gnu++1z -g -ggdb $^ -o smartptr

clang4: smartptr.cpp
	clang++-4.0 -Wall -Wpedantic -Wextra -Wno-unused -Wno-unused-parameter -std=gnu++1z -g -ggdb $^ -o smartptr

# Does not seem to work
clang: smartptr.cpp
	clang++-3.8 -Wall -Wpedantic -Wextra -Wno-unused -Wno-unused-parameter -std=gnu++1z -g -ggdb $^ -o smartptr
