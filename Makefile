# --- COMPILATION CONFIG ---
CC = g++
CFLAGS = -std=c++17 -Wall -I./src -I./libs/glm -I/usr/include/freetype2
LDFLAGS = -Wl,-rpath,'$$ORIGIN/libs'
LIBS = /usr/local/lib/libbbop.a \
       /usr/local/lib/libglfw3.a \
       /usr/local/lib/libLDtkLoader.a

# --- SOURCES ---
SRCS = main.cpp $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp)
OBJDIR = build
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
TARGET = final

# --- DEPENDENCIES DYNamiques (copier dans ./libs) ---
DYNLIBS = /usr/lib/x86_64-linux-gnu/libGLEW.so.2.2 \
          /usr/lib/x86_64-linux-gnu/libGL.so.1 \
          /usr/lib/x86_64-linux-gnu/libfreetype.so.6

LIBDIR = libs

# --- RULES ---
all: $(TARGET) copy_assets copy_dynlibs

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) -lGLEW -lGL -lfreetype
	@echo "Build terminé : $(TARGET)"

# Compile .cpp -> .o
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilé : $<"

# --- COPY DYNAMIC LIBRARIES ---
copy_dynlibs:
	@mkdir -p $(LIBDIR)
	@echo "Copie des librairies dynamiques dans $(LIBDIR)..."
	@for f in $(DYNLIBS); do \
		cp -u $$f $(LIBDIR)/; \
	done

# --- COPY ASSETS (assumes ./assets folder) ---
copy_assets:
	@mkdir -p assets
	@echo "Assets prêts (vérifie le dossier ./assets)"

# --- RUN ---
run: $(TARGET)
	./$(TARGET)

# --- CLEAN ---
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Nettoyage terminé"

.PHONY: all clean run copy_dynlibs copy_assets