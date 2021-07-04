cls 

del bin\*.exe
del obj\*.o

g++ -c src\Vendor\TinyXML\*.cpp -std=c++14 -m64 -g -Wall
g++ -c src\*.cpp -std=c++14 -m64 -g -Wall -I include
g++ -c src\Core\*.cpp -std=c++14 -m64 -g -Wall -I include
g++ -c src\Graphics\*.cpp -std=c++14 -m64 -g -Wall -I include
g++ -c src\Characters\*.cpp -std=c++14 -m64 -g -Wall -I include
g++ -c src\Animation\*.cpp -std=c++14 -m64 -g -Wall -I include
g++ -c src\Inputs\*.cpp -std=c++14 -m64 -g -Wall -I include
g++ -c src\Timer\*.cpp -std=c++14 -m64 -g -Wall -I include 
g++ -c src\Map\*.cpp -std=c++14 -m64 -g -Wall -I include
g++ -c src\Camera\*.cpp -std=c++14 -m64 -g -Wall -I include

move *.o obj

g++ .\obj\*.o -o .\bin\main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image 

.\bin\main.exe