#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void helping() {
    printf("�� ������� �� ������!\n\n");
    printf("������� WordCount\n\n");
    printf("������� WordCount ������������ ���������� �����, ���� � ���� ��� ���������� �����.\n");
    printf("�������� ����� � ����� ���������� ����� ��������� ��������� ������ � ��������� �������:\n\n");
    printf("WordCount.exe [OPTION] filename\n\n");
    printf("���\tfilename - �������� ���������������� ����� (���� ������ ������������)\n�\t[OPTION] - ��� �����\n\n");
    printf("�������������� �����:\n");
    printf("-h, --help\t����� ������ (������ ���� ��� ������������ ��������)\n");
    printf("-l, --lines\t����� ���������� ����� � �����\n");
    printf("-c, --bytes\t����� ������� ����� � ������\n");
    printf("-w, --words\t����� ���������� ���� � �����");
    printf("\n\n��� ������ ���������� �����, ��������� ��������� � �������\nbytes -> lines -> words");
}

bool check_file_accuracy(char *name) { /* ������� �������� ����. ����� �� ������������ */
    if (strchr(name, 46) > 0) {
        return true;
    }
    return false;
}

bool check_argument(char *argument, char *option) { /* ������� �������� ������������ ��������� ��������� ������ */
    if (strcmp(argument, option) == 0) {
        return true;
    }
    return false;
}

int main(int argv, char **argc) {
    char *filename = argc[argv - 1];
    if (argv <= 1) {
        printf("\a�� �� ����� ����������");
        return 0;
    } else if (argv == 2) {
        if ((check_argument(argc[1], "--help")) || (check_argument(argc[1], "-h"))) {
            helping();
            return 0;
        } else if (check_file_accuracy(filename)) {
            printf("\a�� �� ����� ���������� ��� ����� %s", filename);
            return 0;
        } else {
            printf("\a�������� ����");
            return 0;
        }
    } else {
        printf("���� %s\n", filename);
        if (check_file_accuracy(filename)) {
            bool byte = false;
            bool line = false;
            bool word = false;
            for (int i = 1; i < argv; i++) {
                if ((check_argument(argc[i], "--bytes")) || (check_argument(argc[i], "-c"))) { byte = true; }
                if ((check_argument(argc[i], "--lines")) || (check_argument(argc[i], "-l"))) { line = true; }
                if ((check_argument(argc[i], "--words")) || (check_argument(argc[i], "-w"))) { word = true; }
            }
            if ((byte) || (line) || (word)) {
                FILE *file;
                file = fopen(filename, "r");
                if (file == NULL) {
                    printf("\a����� �� ����������!");
                    return 0;
                }
                if (byte) {
                    fseek(file, 0L, SEEK_END);
                    unsigned long int size_of_file = ftell(file);
                    printf("������ �����: %lu ����\n", size_of_file);
                    rewind(file);
                }
                if ((line) || (word)) {
                    int amount_of_lines = 1;
                    long int amount_of_words = 0;
                    int c;
                    int c_prev = 32;
                    c = fgetc(file);
                    while (c != EOF) {
                        if (c == 10) {
                            amount_of_lines = amount_of_lines + 1;
                        }
                        if (((c == 10) || (c == 32)) && ((c_prev != 10) && (c_prev != 32))) {
                            amount_of_words = amount_of_words + 1;
                        }
                        c_prev = c;
                        c = fgetc(file);
                    }
                    if ((c != 10) && (c != 32)) {
                        amount_of_words = amount_of_words + 1;
                    }
                    if (line) { printf("����� � �����: %d\n", amount_of_lines); }
                    if (word) { printf("���� � �����: %ld\n", amount_of_words); }

                }
                fclose(file);
            } else {
                printf("\a�� �� ����� ���������� ���������� ��� ����� %s", filename);
                return 0;
            }


        } else {
            printf("\a������ ���������� ����� �����������!");
            return 0;
        }
    }
    return 0;
}
