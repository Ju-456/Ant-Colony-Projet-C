# Nom de l'exécutable final
TARGET = main

# Options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g

# Répertoires
SRC_DIR = src        # Répertoire contenant les sources .c
OBJ_DIR = build      # Répertoire contenant les objets .o

# Liste des fichiers sources
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Générer la liste des fichiers objets correspondants
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Règle par défaut pour compiler le programme
all: $(TARGET)

# Règle pour générer l'exécutable à partir des objets
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Règle pour compiler chaque fichier .c en un fichier .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Règle pour forcer une recompilation complète
rebuild: clean all

# Indique au Makefile que les règles suivantes ne sont pas des fichiers
.PHONY: all clean rebuild
