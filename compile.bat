set projectDir=%cd%
set gppDir=%C:\mingw64\bin%

cd %projectDir%

%gppDir%\x86_64-w64-mingw32-g++.exe -Wall -fexceptions -g -lglfw3dll -lglfw -ldl -DGLFW_INCLUDE_NONE -Ilib\glad\include -Ilib\glfw\include -Iincludes -Ilib -Ilib\assimp\include -Iinclude -Ithe_rise -Ilib\glm\include -c ./Bones.cpp -o obj\Debug\Bones.o
%gppDir%\x86_64-w64-mingw32-gcc.exe -Wall -fexceptions -g -lglfw3dll -lglfw -ldl -DGLFW_INCLUDE_NONE -Ilib\glad\include -Ilib\glfw\include -Iincludes -Ilib -Ilib\assimp\include -Iinclude -Ithe_rise -Ilib\glm\include -c lib\glad\src\glad.c -o obj\Debug\lib\glad\src\glad.o
%gppDir%\x86_64-w64-mingw32-g++.exe -Wall -fexceptions -g -lglfw3dll -lglfw -ldl -DGLFW_INCLUDE_NONE -Ilib\glad\include -Ilib\glfw\include -Iincludes -Ilib -Ilib\assimp\include -Iinclude -Ithe_rise -Ilib\glm\include -c main.cpp -o obj\Debug\main.o
%gppDir%\x86_64-w64-mingw32-g++.exe -Wall -fexceptions -g -lglfw3dll -lglfw -ldl -DGLFW_INCLUDE_NONE -Ilib\glad\include -Ilib\glfw\include -Iincludes -Ilib -Ilib\assimp\include -Iinclude -Ithe_rise -Ilib\glm\include -c Mesh.cpp -o obj\Debug\Mesh.o
%gppDir%\x86_64-w64-mingw32-g++.exe -Wall -fexceptions -g -lglfw3dll -lglfw -ldl -DGLFW_INCLUDE_NONE -Ilib\glad\include -Ilib\glfw\include -Iincludes -Ilib -Ilib\assimp\include -Iinclude -Ithe_rise -Ilib\glm\include -c Model.cpp -o obj\Debug\Model.o
%gppDir%\x86_64-w64-mingw32-g++.exe -Wall -fexceptions -g -lglfw3dll -lglfw -ldl -DGLFW_INCLUDE_NONE -Ilib\glad\include -Ilib\glfw\include -Iincludes -Ilib -Ilib\assimp\include -Iinclude -Ithe_rise -Ilib\glm\include -c Stage.cpp -o obj\Debug\Stage.o

%gppDir%\x86_64-w64-mingw32-g++.exe -L ./ -o bin\Debug\main.exe obj\Debug\Bones.o obj\Debug\lib\glad\src\glad.o obj\Debug\main.o obj\Debug\Mesh.o obj\Debug\Model.o obj\Debug\Stage.o  -static-libstdc++ -static-libgcc -static  lib\glfw\lib-mingw-w64\libglfw3dll.a lib\assimp\lib\libassimp.dll.a

