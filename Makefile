CC := gcc
CFLAGS := -Wall -Wextra -std=c11
CPPFLAGS := -Ilib/data_queue -Ilib/data_stack -Ilib/interface_stack -Ilib/reg

TARGET := registers
SOURCES := main.c \
	$(wildcard lib/data_queue/*.c) \
	$(wildcard lib/data_stack/*.c) \
	$(wildcard lib/interface_stack/*.c) \
	$(wildcard lib/reg/*.c)
OBJECTS := $(SOURCES:%.c=build/%.o)

.PHONY: all run clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJECTS) -o $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build bin

rebuild: clean all
