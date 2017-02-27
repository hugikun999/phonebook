CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99 -pg
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_opt phonebook_hash

GIT_HOOKS := .git/hooks/pre-commit

.PHONY: all
all: $(GIT_HOOKS) clean $(EXEC) 

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	rm -rf $@
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL=" \"$@.h\" " -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	rm -rf $@
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL=" \"$@.h\" "	-DOPT	-DSELF_MET	-o $@ \
		$(SRCS_common) $@.c

phonebook_hash: main_hash.c phonebook_hash.c phonebook_hash.h
	rm -rf $@
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\""	-o $@ \
		main_hash.c $@.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

rm_file:
	rm -rf output.txt orig.txt opt.txt hash.txt runtime.png

cache-test: $(EXEC) rm_file
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_hash 997

hash_test: phonebook_hash
	for i in `seq 10 1 997 `; \
	do \
	./phonebook_hash $$i; \
	done

output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png
