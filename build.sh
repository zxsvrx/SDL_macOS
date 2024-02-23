gcc -Iinclude -c -o SDLM_Timer.o src/SDLM_Timer.m

ar rcs libSDLM_Timer.a SDLM_Timer.o

if [ ! -d "build" ]; then
	mkdir build
fi

mv libSDLM_Timer.a build/libSDLM_Timer.a

rm SDLM_Timer.o

