cls 

g++ -c src\*.cpp -std=c++14 -m64 -g -Wall -I include
g++ -c src\Core\*.cpp -std=c++14 -m64 -g -Wall -I include

g++ *.o -o .\bin\main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image 

.\bin\main.exe