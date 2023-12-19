#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

int input(double ptr_array[100][2], int); // ввод данных 
double output(double ptr_array[100][2], int); // вывод данных
int del(double ptr_array[100][2], int); // удаление рамы
int write(double ptr_array[100][2], int, char*); // запись в файл
int image(double, double); // вывод изображения
int read(char*); // чтение из файла
double corr(); // проверка корректности ввода

int main() {
	setlocale(LC_CTYPE, "RUS");
	int choice; // переменная для выбора пункта; 
	int cor; // проверка на корректность ввода номера пункта
	int save = 0; // проверка на необходимость сохранить изменения в файл
	int check; // проверка на успешную запись данных в файл
	double quan; // необходимое кол-во стекла
	char ans; // переменная для ответа на вопроса "Продолжить?"
	char fname[20] = "data.txt"; // переменная, хранящая название файла для записи и чтения
	double okna[100][2];
	int index = 0;
	

	printf("********************************\n");
	printf("*                              *\n");
	printf("*   Калькулятор остекленения   *\n");
	printf("*                              *\n");
	printf("********************************\n");

	while (1) {
		
		printf("***МЕНЮ***\n1. Ввод данных одной рамы\n2. Вывод данных всех рам\n3. Удалить раму\n4. Запись данных в файл\n5. Вывод изображения последней рамы\n6. Чтение из файла\n7. Выход\n\nВведите номер пункта: ");
		cor = scanf("%d", &choice);
		system("cls");
		if (cor == 1) {
			switch (choice) {
			case 1:
				save = 1;
				while (1) {
					index = input(okna, index);
					printf("Еще раз? Да - y, Нет - n\n");
					scanf("%c", &ans);
					system("cls");
					if (ans == 'n')  break;
				}
				break;
			case 2:
				if (index) {
					double quan_glass;
					quan_glass = output(okna, index);
					printf("\nВам нужно %.4lf дм^2 стекла\n", quan_glass);
					printf("\nНажмите Enter для выхода в меню\n");
					getchar();
					getchar();
					system("cls");
				}
				else printf("Данные отсутствуют\n\n");
				break;
			case 3:
				save = 1;
				if (index) {
					while (index) {
						output(okna, index);
						index = del(okna, index);
						if (!index) {
							printf("Все рамы удалены\n"); 
							printf("Нажмите Enter для выхода в меню.");
							getchar();
							break;
						}
						printf("Еще раз? Да - y, Нет - n\n");
						scanf("%c", &ans);
						getchar();
						if (ans == 'n')  break;
						system("cls");
					}
					system("cls");
				}
				else printf("Данные отсутствуют\n\n"); 
				break;
			case 4:
				if (index) {
					check = write(okna, index, fname);
					if (check) {
						printf("Данные успешно записаны в файл.\n\n");
						save = 0;
					}
					else {
						printf("Данные не были записаны в файл.\n\n");
					}
				}
				else printf("Данные отсутствуют\n\n"); 
				break;
			case 5:
				if (index) {
					if (okna[index-1][0] > 25 || okna[index-1][1] > 50) printf("Размеры слишком большие\n\n");
					else {
						image(okna[index - 1][0], okna[index - 1][1]);
						printf("Нажмите Enter для выхода в меню.");
						getchar();
						getchar();
						system("cls");
						break;
					}
				}
				else printf("Данные отсутствуют\n\n");
				getchar();
				break;

			case 6:
				read(fname);
				break;

			case 7:
				if (save && index) {
					printf("Сохранить изменения в файл? Да - y, Нет - n\n");
					scanf("%c", &ans);
					
					if (ans = getchar() == 'n')  return 0;
					check = write(okna, index, fname);
					if (check) printf("Данные успешно записаны в файл.\n\n");
					else printf("Данные не были записаны в файл.\n\n");
				}
				return 0; // выход из программы

			default:
				printf("Такого пункта нет.\n\n");
				getchar();
				break;
			}
		}
		else {
			system("cls");
			printf("Введены некорректные данные.\n\n");
			getchar();


		}

	}

}


int input(double ptr_array[100][2], int index) {
	printf("Введите длину и ширину оконной рамы в дециметрах\nТочность - 2 знака после запятой\n\n");
	printf("Длина: ");
	ptr_array[index][0] = corr();
	printf("Ширина: ");
	ptr_array[index][1] = corr();
	
	return ++index;
}

double output(double ptr_array[100][2], int index) {
	double quan_glass = 0;
	printf("*****Данные*****\n\nДлина | Ширина\n");
	for (int i = 0; i < index; i++) {
		printf("%5.2lf   %.2lf\n", ptr_array[i][0], ptr_array[i][1]);
		quan_glass += ptr_array[i][0] * ptr_array[i][1];
	}
	
	return quan_glass;
}

int del(double ptr_array[100][2], int index) {
	double width, height;
	int ind_del = -1;
	printf("\nВведите длину и ширину оконной рамы, которую требуется удалить, в дециметрах \nТочность - 2 знака после запятой\n");
	printf("\nДлина: ");
	height = corr();
	printf("Ширина: ");
	width = corr();
	
	for (int i = 0; i < index; i++) {
		if ((height == ptr_array[i][0]) && (width == ptr_array[i][1])) {
			ind_del = i;
			break;
		}
	}
	if (ind_del == -1) {
		
		printf("Рама с указанными размерами не найдена\n");
		return index;
	}
	for (int i = ind_del; i < index-1; i++) {
		ptr_array[i][0] = ptr_array[i + 1][0];
		ptr_array[i][1] = ptr_array[i + 1][1];
	}

	printf("Рама удалена\n");
	return --index;
}

int write(double ptr_array[100][2], int index, char* fname) {
	FILE* in = fopen(fname, "wt");
	if (!in) {
		printf("Ошибка открытия файла для записи");
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
		printf("Ошибка открытия файла для чтения\n\n");
		return 0;
	}

	printf("*****Данные*****\n\nДлина | Ширина\n");
	while (1) {
		fscanf(out, "%lf", &height);
		fscanf(out, "%lf", &width);
		printf("%.2lf %7.2lf\n", height, width);
		quan_glass += width * height;
		if (feof(out)) break;
	}
	fclose(out);
	printf("\nВам нужно %.4lf дм^2 стекла\n\nНажмите Enter для выхода в меню\n", quan_glass);
	getchar();
	getchar();
	system("cls");
	return 1;
}

int image(double width, double height) {
	int w = ceil(width);
	int h = ceil(height);
	printf("Оконная рама:\n\n");
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
		if ((check != 1) || (value <= 0)) printf("Введено некорректное значение,\nВведите данные еще раз: ");
		else break;
	}
	return value;
}