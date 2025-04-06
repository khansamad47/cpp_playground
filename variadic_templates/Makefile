default:
	g++ main.cpp

tidy:
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S. -B build
	clang-tidy -checks=* -p=build/ main.cpp
	
valgrid:
	valgrind --leak-check=full ./a.out
