mkdir files

g++ -c Number/NumberStaticLibrary.cpp -o files/NumberStaticLibrary.o
ar rc files/NumberStaticLibrary.lib files/NumberStaticLibrary.o

echo building vector
g++ -c -I Number Vector/VectorLibrary.cpp -o files/VectorLibrary.o
g++ files/NumberStaticLibrary.lib files/VectorLibrary.o -shared -o files/VectorLibrary.dll

echo building main
g++ -o files/test Test/lab1.cpp files/NumberStaticLibrary.lib files/VectorLibrary.dll -I Number -I Vector
.\files\test

rm -R files