# Variaveis
CC = g++
EXT = cpp
APPDIR = app
BINDIR = bin
INCDIR = inc
LIBDIR = lib
OBJDIR = obj
SRCDIR = src
FLAGS = -O3 -Wall -Wextra -g3
ECHO ?=
APP ?=

# Verificação do nome do aplicativo
ifeq ($(APP),)
$(error No app specified. Use: make APP=<app_name>)
endif

# Encontra todos os arquivos-fonte (.$(EXT)) dentro do diretório especificado, exceto o arquivo principal
SOURCES := $(filter-out $(SRCDIR)/$(APP).$(EXT), $(wildcard $(SRCDIR)/*.$(EXT)))

# Gera a lista de objetos (.o) a partir dos nomes dos arquivos-fonte
OBJECTS := $(patsubst $(SRCDIR)/%.$(EXT), $(OBJDIR)/%.o, $(SOURCES))

# Encontra todos os arquivos de bibliotecas (.a) no diretório de bibliotecas
LIBRARIES := $(wildcard $(LIBDIR)/*.a)

#Executa o make
all: clean folder exe

# Criação dos diretórios
folder:
ifeq ($(OS),Windows_NT)
	@ if not exist "$(BINDIR)" mkdir $(BINDIR)
	@ if not exist "$(OBJDIR)" mkdir $(OBJDIR)
else
	@ if [ -d "$(BINDIR)" ]; then mkdir -p $(BINDIR); fi
	@ if [ -d "$(OBJDIR)" ]; then mkdir -p $(OBJDIR); fi
endif

# Compilação do programa executável
exe: objs
	$(if $(ECHO),@echo Makefile: Compiling)
	@ $(CC) $(FLAGS) $(APPDIR)/$(APP).$(EXT) $(OBJECTS) -I $(INCDIR) -L $(LIBDIR) $(LIBRARIES) -o $(BINDIR)/$(APP)
	$(if $(ECHO),@echo Makefile: Compiled Successfully)
	@ $(MAKE) -s run

# Compilação dos objetos
objs: $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(EXT) $(INCDIR)/%.h
	@ $(CC) $(FLAGS) -c $< -I $(INCDIR) -o $@

run:
	$(if $(ECHO),@echo Makefile: Running Program)
	$(if $(ECHO),@echo =-=-=-=-=-=-=-=-=-=-=-=-=)
	@ $(BINDIR)/$(APP)
	$(if $(ECHO),@echo =-=-=-=-=-=-=-=-=-=-=-=-=)
	$(if $(ECHO),@echo Makefile: Program Ended)
	@ $(MAKE) -s clean

# Limpeza dos arquivos
.PHONY: clean

clean:
	$(if $(ECHO),@echo Makefile: Cleaning)
ifeq ($(OS),Windows_NT)
	@ if exist "$(BINDIR)" rd /s /q $(BINDIR)
	@ if exist "$(OBJDIR)" rd /s /q $(OBJDIR)
else
	@ if [ -d "$(BINDIR)" ]; then rm -rf $(BINDIR); fi
	@ if [ -d "$(OBJDIR)" ]; then rm -rf $(OBJDIR); fi
endif
	$(if $(ECHO),@echo Makefile: Cleaned Successfully)