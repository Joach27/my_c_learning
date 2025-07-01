# Nom de l'exécutable
EXEC = game

# Répertoire de build pour les .o
BUILD_DIR = build

# Fichiers source
SRCS = main.c board.c

# Fichiers objets dans le dossier build
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(BUILD_DIR)/, $(OBJS))

# Compilateur
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Règle par défaut
all: $(EXEC)

# Édition de liens
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Compilation des .c en .o dans ./build
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Créer le dossier build si absent
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Nettoyer
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

# Forcer recompilation
re: clean all
