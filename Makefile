CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS =

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
TESTDIR = test

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
TESTFILES = $(wildcard $(TESTDIR)/test-*.c)
TESTOBJFILES = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TESTFILES))

TARGET = $(BINDIR)/maze_generator
TEST_TARGET = $(BINDIR)/test_suite

.PHONY: all clean test

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJFILES)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@

$(TEST_TARGET): $(TESTOBJFILES) $(filter-out $(OBJDIR)/main.o,$(OBJFILES))
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/maze_generator $(BINDIR)/test_suite

test: $(TEST_TARGET)
	@./$(TEST_TARGET)