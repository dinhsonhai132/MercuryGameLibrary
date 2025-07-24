all:
	g++ -shared -o init.dll init.cpp -I "C:\MerGame\SDL\x86_64-w64-mingw32\include" -L "C:\MerGame\SDL\x86_64-w64-mingw32\lib" -lSDL3