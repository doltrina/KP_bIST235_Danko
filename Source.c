#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

int input(double ptr_array[100][2], int); // ���� ������ 
double output(double ptr_array[100][2], int); // ����� ������
int del(double ptr_array[100][2], int); // �������� ����
int write(double ptr_array[100][2], int, char*); // ������ � ����
int image(double, double); // ����� �����������
int read(char*); // ������ �� �����
double corr(); // �������� ������������ �����

int main() {
	setlocale(LC_CTYPE, "RUS");
	int choice; // ���������� ��� ������ ������; 
	int cor; // �������� �� ������������ ����� ������ ������
	int save = 0; // �������� �� ������������� ��������� ��������� � ����
	int check; // �������� �� �������� ������ ������ � ����
	double quan; // ����������� ���-�� ������
	char ans; // ���������� ��� ������ �� ������� "����������?"
	char fname[20] = "data.txt"; // ����������, �������� �������� ����� ��� ������ � ������
	double okna[100][2];
	int index = 0;
	

	printf("********************************\n");
	printf("*                              *\n");
	printf("*   ����������� ������������   *\n");
	printf("*                              *\n");
	printf("********************************\n");

	while (1) {
		
		printf("***����***\n1. ���� ������ ����� ����\n2. ����� ������ ���� ���\n3. ������� ����\n4. ������ ������ � ����\n5. ����� ����������� ��������� ����\n6. ������ �� �����\n7. �����\n\n������� ����� ������: ");
		cor = scanf("%d", &choice);
		system("cls");
		if (cor == 1) {
			switch (choice) {
			case 1:
				save = 1;
				while (1) {
					index = input(okna, index);
					printf("��� ���? �� - y, ��� - n\n");
					scanf("%c", &ans);
					system("cls");
					if (ans == 'n')  break;
				}
				break;
			case 2:
				if (index) {
					double quan_glass;
					quan_glass = output(okna, index);
					printf("\n��� ����� %.4lf ��^2 ������\n", quan_glass);
					printf("\n������� Enter ��� ������ � ����\n");
					getchar();
					getchar();
					system("cls");
				}
				else printf("������ �����������\n\n");
				break;
			case 3:
				save = 1;
				if (index) {
					while (index) {
						output(okna, index);
						index = del(okna, index);
						if (!index) {
							printf("��� ���� �������\n"); 
							printf("������� Enter ��� ������ � ����.");
							getchar();
							break;
						}
						printf("��� ���? �� - y, ��� - n\n");
						scanf("%c", &ans);
						getchar();
						if (ans == 'n')  break;
						system("cls");
					}
					system("cls");
				}
				else printf("������ �����������\n\n"); 
				break;
			case 4:
				if (index) {
					check = write(okna, index, fname);
					if (check) {
						printf("������ ������� �������� � ����.\n\n");
						save = 0;
					}
					else {
						printf("������ �� ���� �������� � ����.\n\n");
					}
				}
				else printf("������ �����������\n\n"); 
				break;
			case 5:
				if (index) {
					if (okna[index-1][0] > 25 || okna[index-1][1] > 50) printf("������� ������� �������\n\n");
					else {
						image(okna[index - 1][0], okna[index - 1][1]);
						printf("������� Enter ��� ������ � ����.");
						getchar();
						getchar();
						system("cls");
						break;
					}
				}
				else printf("������ �����������\n\n");
				getchar();
				break;

			case 6:
				read(fname);
				break;

			case 7:
				if (save && index) {
					printf("��������� ��������� � ����? �� - y, ��� - n\n");
					scanf("%c", &ans);
					
					if (ans = getchar() == 'n')  return 0;
					check = write(okna, index, fname);
					if (check) printf("������ ������� �������� � ����.\n\n");
					else printf("������ �� ���� �������� � ����.\n\n");
				}
				return 0; // ����� �� ���������

			default:
				printf("������ ������ ���.\n\n");
				getchar();
				break;
			}
		}
		else {
			system("cls");
			printf("������� ������������ ������.\n\n");
			getchar();


		}

	}

}


int input(double ptr_array[100][2], int index) {
	printf("������� ����� � ������ ������� ���� � ����������\n�������� - 2 ����� ����� �������\n\n");
	printf("�����: ");
	ptr_array[index][0] = corr();
	printf("������: ");
	ptr_array[index][1] = corr();
	
	return ++index;
}

double output(double ptr_array[100][2], int index) {
	double quan_glass = 0;
	printf("*****������*****\n\n����� | ������\n");
	for (int i = 0; i < index; i++) {
		printf("%5.2lf   %.2lf\n", ptr_array[i][0], ptr_array[i][1]);
		quan_glass += ptr_array[i][0] * ptr_array[i][1];
	}
	
	return quan_glass;
}

int del(double ptr_array[100][2], int index) {
	double width, height;
	int ind_del = -1;
	printf("\n������� ����� � ������ ������� ����, ������� ��������� �������, � ���������� \n�������� - 2 ����� ����� �������\n");
	printf("\n�����: ");
	height = corr();
	printf("������: ");
	width = corr();
	
	for (int i = 0; i < index; i++) {
		if ((height == ptr_array[i][0]) && (width == ptr_array[i][1])) {
			ind_del = i;
			break;
		}
	}
	if (ind_del == -1) {
		
		printf("���� � ���������� ��������� �� �������\n");
		return index;
	}
	for (int i = ind_del; i < index-1; i++) {
		ptr_array[i][0] = ptr_array[i + 1][0];
		ptr_array[i][1] = ptr_array[i + 1][1];
	}

	printf("���� �������\n");
	return --index;
}

int write(double ptr_array[100][2], int index, char* fname) {
	FILE* in = fopen(fname, "wt");
	if (!in) {
		printf("������ �������� ����� ��� ������");
		return 0;
	}
	for (int i = 0; i < index; i++) {
		fprintf(in ,"\n%.2lf %.2lf", ptr_array[i][0], ptr_array[i][1]);
	}
	fclose(in);
	return 1;
}

int read(char* fname) {
	double quan_glass = 0;
	double width, height;
	FILE* out = fopen(fname, "rt");
	if (out == NULL) {
		printf("������ �������� ����� ��� ������\n\n");
		return 0;
	}

	printf("*****������*****\n\n����� | ������\n");
	while (1) {
		fscanf(out, "%lf", &height);
		fscanf(out, "%lf", &width);
		printf("%.2lf %7.2lf\n", height, width);
		quan_glass += width * height;
		if (feof(out)) break;
	}
	fclose(out);
	printf("\n��� ����� %.4lf ��^2 ������\n\n������� Enter ��� ������ � ����\n", quan_glass);
	getchar();
	getchar();
	system("cls");
	return 1;
}

int image(double width, double height) {
	int w = ceil(width);
	int h = ceil(height);
	printf("������� ����:\n\n");
	for (int i = 0; i < h; i++) printf("*");
	printf("\n");
	for (int i = 0; i < w -2; i++) {
		for (int j = 0; j < h; j++) {
			if ((j == 0) || (j == h -1)) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	for (int i = 0; i < h; i++) printf("*");
	printf("\n\n");

	return 1;
}

double corr() {
	double value;
	int check;
	while (1) {
		int check = scanf("%lf", &value);
		getchar();
		if ((check != 1) || (value <= 0)) printf("������� ������������ ��������,\n������� ������ ��� ���: ");
		else break;
	}
	return value;
}