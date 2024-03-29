CC=gcc
CFLAGS=-m32 -Og

OUT=./out

# Problem list
PROBLEMS=problem1.c problem2.c problem3.c problem4.c problem5.c problem6.c problem7.c example.c

# Ensures the directory where the output file will live exists
dir_guard=@mkdir -p $(@D)

.PHONY: clean binaries diff

all: binaries diff

# Build all the binaries
binaries: $(addprefix $(OUT)/, $(basename $(PROBLEMS)))

# Pattern rule for compling binaries
$(OUT)/%: %.c
	$(dir_guard)
	$(CC) $(CFLAGS) $^ -o $@

# Problem 2 has special compilation needs
$(OUT)/problem2: problem2.c
	$(dir_guard)
	$(CC) $(CFLAGS) -fno-stack-protector -no-pie $^ -o $@

# Problem 3 has special compilation needs
$(OUT)/problem3: problem3.c
	$(dir_guard)
	$(CC) $(CFLAGS) -fstack-protector $^ -o $@

# Problem 7 needs to be compiled with threading support
$(OUT)/problem7: problem7.c
	$(dir_guard)
	$(CC) $(CFLAGS) -pthread $^ -o $@

# Generate diffs for all the patches
DIFF_DIR=./diff
diff: $(addprefix $(DIFF_DIR)/, $(addsuffix .diff, $(basename $(PROBLEMS))))

$(DIFF_DIR)/%.diff: .originals/%.c %.c
	$(dir_guard)
	-diff --color -u $^ > $@

clean: 
	rm -rf $(OUT) $(DIFF_DIR)
