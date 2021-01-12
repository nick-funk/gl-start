if not exist output/ mkdir output

copy dependencies\glfw\lib-mingw-w64\glfw3.dll output\glfw3.dll

tools\mingw64\bin\g++ dependencies/glad/src/glad.c src/core.cpp src/main.cpp -I ./dependencies/glfw/include/ -I ./dependencies/glad/include -L ./dependencies/glfw/lib-mingw-w64/ -o output/output.exe -lglfw3 -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic