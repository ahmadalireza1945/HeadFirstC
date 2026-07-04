#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *question;
    struct node *no;
    struct node *yes;
} node;

int yes_no(char *question) {
    char answer[3];
    printf("%s (y/n) : ", question);
    fgets(answer, 3, stdin);
    return answer[0] == 'y';
}

node* create(char *question) {
    node *n = malloc(sizeof(node));
    n->question = strdup(question);
    n->no = NULL;
    n->yes = NULL;
    return n;
}

void release(node *n) {
    if (n) {
        if (n->no)
            release(n->no);
        if (n->yes)
            release(n->yes);
        if (n->question)
            free(n->question);
        free(n);
    }
}

int main(int argc, char *argv[]) {
    char question[80];
    char suspect[20];
    node *start_node = create("Does suspect have mustache ?");
    start_node->no = create("Loretta Barnswort ");
    start_node->yes = create("Vinny the spoon ");

    node *current;
    do {
        current = start_node;
        while (1) {
            if (yes_no(current->question)) {
                if (current->yes) {
                    current = current->yes;
                }else {
                    printf("suspect identification");
                    break;
                }
            } else if (current->no) {
                current = current->no;
            }else {
                printf("who the suspect ?");
                fgets(suspect, 20, stdin);
                node *yes_node = create(current->question);
                current->yes = yes_node;

                node *no_node = create(current->question);
                current->no = no_node;

                printf("give me a question that is true for %s but not for %s ", suspect,current->question);
                fgets(question, 80, stdin);
                    current->question = strdup(question);

                break;
            }

        }
    }
    while (yes_no("run again "));
    release(start_node);
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data untuk node pohon biner
typedef struct node {
    char *question;
    struct node *no;
    struct node *yes;
} node;

// Fungsi pembantu untuk menghapus karakter newline (\n) di akhir input fgets
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Fungsi untuk menerima input keputusan ya atau tidak
int yes_no(char *question) {
    char answer[3];
    printf("%s? (y/n): ", question);
    fgets(answer, 3, stdin);
    return answer[0] == 'y' || answer[0] == 'Y';
}

// Fungsi untuk membuat node baru secara dinamis
node* create(char *question) {
    node *n = malloc(sizeof(node));
    n->question = strdup(question);
    n->no = NULL;
    n->yes = NULL;
    return n;
}

// Fungsi rekursif untuk menghapus seluruh node dari memori (mencegah memory leak)
void release(node *n) {
    if (n) {
        if (n->no) release(n->no);
        if (n->yes) release(n->yes);
        if (n->question) free(n->question);
        free(n);
    }
}

int main() {
    char question[80];
    char suspect[20];

    // Inisialisasi pohon keputusan awal
    node *start_node = create("Does suspect have a mustache");
    start_node->no = create("Loretta Barnsworth");
    start_node->yes = create("Vinny the Spoon");

    node *current;
    do {
        current = start_node;
        while (1) {
            if (yes_no(current->question)) {
                if (current->yes) {
                    current = current->yes;
                } else {
                    printf("SUSPECT IDENTIFIED\n");
                    break;
                }
            } else if (current->no) {
                current = current->no;
            } else {
                // Blok ini berjalan jika suspek salah dan sistem ingin belajar suspek baru
                printf("Who's the suspect? ");
                fgets(suspect, 20, stdin);
                trim_newline(suspect); // Bersihkan newline

                node *yes_node = create(suspect);
                current->yes = yes_node;

                // Salin suspek/pertanyaan lama ke node "no"
                node *no_node = create(current->question);
                current->no = no_node;

                // Minta pertanyaan pembeda baru
                printf("Give me a question that is TRUE for %s but not for %s? ", suspect, current->question);
                fgets(question, 80, stdin);
                trim_newline(question); // Bersihkan newline

                // PERBAIKAN BUG: Bebaskan memori string lama sebelum diganti dengan strdup baru
                free(current->question);
                current->question = strdup(question);
                break;
            }
        }
    } while (yes_no("Run again"));

    // Bebaskan seluruh memori yang digunakan sebelum program selesai
    release(start_node);
    return 0;
}
*/
