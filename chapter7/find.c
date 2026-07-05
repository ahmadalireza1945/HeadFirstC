
#include <stdio.h>
#include <string.h>
int NUM_ADS = 7;
char *ADS[] = {
    "William: SBM GSOH likes sports, TV, dining",
    "Matt: SWM NS likes art, movies, theater",
    "Luis: SLM ND likes books, theater, art",
    "Mike: DWM DS likes trucks, sports and bieber",
    "Peter: SAM likes chess, working out and art",
    "Josh: SJM likes sports, movies and theater",
    "Jed: DBM likes theater, books and dining"
};

int ns_movies_books(char *name) {
    return strstr(name, "NS") && strstr(name, "movies") || strstr(name, "books");
}

void find(int (*funtion)(char *)) {
    int i;
    puts("search result");
    puts("----------");

    for (i = 0; i < NUM_ADS; i++) {
        if ((*funtion)(ADS[i]))
        printf("%s\n", ADS[i]);
    }
    puts("-----------");
}

int main(int argc, char *argv[]) {
    find(&ns_movies_books);
    return 0;
}
