# Nom de l'exécutable final
TARGET = main

# Options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g

# Liste des fichiers sources
SRCS = main.c 

# Génère une liste des fichiers objets correspondants
OBJS = $(SRCS:.c=.o)

# Répertoire pour les objets
OBJ_DIR = build

# Répertoire pour les sources
SRC_DIR = src

# Ajoute les répertoires aux chemins
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(OBJS)))

# Règle par défaut : compile le programme
all: $(TARGET)

# Règle pour générer l'exécutable en liant les objets
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Règle de compilation pour chaque fichier .c en un fichier .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés (.o et l'exécutable)
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Règle pour tout nettoyer, y compris les fichiers temporaires
veryclean: clean
	rm -f *~ *.bak

# Règle pour recompiler en nettoyant d'abord
rebuild: clean all

# Indique au Makefile que 'clean', 'veryclean' et 'rebuild' ne sont pas des fichiers
.PHONY: all clean veryclean rebuild
