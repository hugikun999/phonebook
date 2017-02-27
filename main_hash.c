#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define OUT_FILE "hash.txt"

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0, table_size;
    unsigned int hash_value;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;
    Hash_Table *hash_table;

    table_size = atoi(argv[1]);

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    hash_table = (Hash_Table *) malloc(sizeof(Hash_Table) * table_size);
    printf("Hash table size: %lu bytes\n", sizeof(Hash_Table) * table_size);
    for(int i = 0; i < table_size; i++) {
        (hash_table + i)->pHead = NULL;
        (hash_table + i)->pLast = NULL;
    }


#if defined(__GNUC__)
    __builtin___clear_cache((char *) hash_table, (char *) hash_table + (sizeof(Hash_Table) * table_size));
#endif

    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\n')
            i++;
        line[i] = '\0';
        i = 0;

        hash_value = BKDRHash(line);
        hash_value = hash_value % table_size;
        append_hash(line, (hash_table + hash_value));
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);


    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    hash_value = BKDRHash(input);
    hash_value = hash_value % table_size;

    assert(findName_hash(input, (hash_table + hash_value)) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName_hash(input, (hash_table + hash_value))->lastName, "zyxel"));

#if defined(__GNUC__)
    __builtin___clear_cache((char *) hash_table, (char *) hash_table + (sizeof(Hash_Table) * table_size));
#endif

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName_hash(input, (hash_table + hash_value));
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    printf("OUT_FILE is : %s\n", OUT_FILE);
    FILE *output = fopen(OUT_FILE, "a");
    fprintf(output, "%d %lf %lf\n", table_size, cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    free(hash_table);
    return 0;
}
