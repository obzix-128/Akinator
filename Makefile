FLAGS := -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
         -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
		 -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions \
		 -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security \
		 -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers \
		 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 \
		 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla \
		 -D_DEBUG -D_EJUDGE_CLIENT_SIDE -I./include -I./Stack/include

CC := g++
objects := $(patsubst source/%.cpp, objects/%.o, $(wildcard source/*.cpp))
objectsStack := $(patsubst Stack/source/%.cpp, Stack/objects/%.o, $(wildcard Stack/source/*.cpp))

.PHONY: call

all: call do.exe

call:
	@cd Stack && make all

do.exe: $(objects)
	@$(CC) $^ $(objectsStack) $(FLAGS) -o $@

objects/%.o: source/%.cpp
	@$(CC) -c $^ $(FLAGS) -o $@

clean:
	@rm -rf objects/*.o do
	@cd Stack && make $@

