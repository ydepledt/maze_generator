CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS =

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))

TARGET = $(BINDIR)/maze_generator

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJFILES)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/maze_generator
