#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#pragma warning(disable:4996) //���� �Լ� ��� ���� ��� 

/* -------------------------------------- ������ ---------------------------------------------- */

//�ι� ���� ������
typedef enum _job { BAEKSU, ADMIN, PRIEST, DOCTOR, BANKER, MERCH } jobType; //���� �⺻����=NONE
typedef enum _estate { COMMONS, NOBILITY } estate; //�ź�
typedef enum _scholarship { BABO, THEOLOGY, LAW, MEDICINE } scholarship; //�й� �⺻����=NONE


/* -------------------------------------- ����ü ---------------------------------------------- */

typedef struct _city //���� ����
{
	char name[10]; //���� �̸�
	int popularity; //�α��� 
	int building[5]; //������ �ǹ�.  1. ���б� 2. ���� 3. ���� 4. �̼���

	int workman[99]; //�� ���(�ε����� ����)
} city;

typedef struct _person //�ι� ����
{
	char name[20]; //�̸�
	int age; //����
	int gender; //����. 1�� ���� 2�� ���� �������� ���� ���� ����
	jobType job; //��������
	estate status;//�ź�����
	scholarship scholar; //�й�����
	int scholarExp; //�й� ���õ� => ó���� ������� 6���� 12 ���� �������� �ϳ��� �ְ� ���ϸ��� 0���� 
	//�����ؼ� 1�� �ø��� �ɵ�
	//������ ����    ���� �ּ� 6�� �ִ� 12�� => �̷��� ������
	int maxExp;//6~12���̷���
	int city; //���� ��ġ�� ����
	int work; //���� �ϴ� Ȱ��. 0���� ��� ��� 1. �������� 2. ������ 3. �й��ױ�(���б��� ���� ����)
	int AP; // Active Point
} person; //�ι� ���� �Ϸ��� �迭 ���ڿ� �ǹ̺ο�

typedef struct _artist //������ ����
{
	char name[50]; //�̸�
	int startYear;
	int endYear;
	char paintNameA[100];
	int paintYearA;

	char paintNameB[100];
	int paintYearB;

	int city;

	//�������� ������ ����, ���� �׸��� ���� ����, ��ǰ 2�� ���� ����
} artist; //�ι� ���� �Ϸ��� �迭 ���ڿ� �ǹ̺ο�

typedef struct _artwork //����ǰ ����
{
	char name[100]; //�̸�
	char painterName[50];

	int year;//����ǰ ���� �ñ�

} artwork;

/*--------------------------------------�Լ�----------------------------------------------*///�̻��� �뷡��� ���� ���ϳ� �뷡�� �� ����

void date(person* person, int maxPeople) // ���� �������� �ϴ� ���� ���̰� ó���ϴ� �Լ�
{
	int deathDice = 0;
	int deathRate = 0;

	for (int index = 0; index <= maxPeople; index++) //�ִ� �������ŭ �������z ������ ��ĵ
	{
		if (*person[index].name != '\0') // �׾ �� ����� �ƴ� ���
		{
			person[index].age++;

			if (person[index].age >= 40) //40������ ���� ����.1�� ���� 4.5% �׷��� 40�쿡�� 60�� �Ǹ� 100%��
			{
				deathDice = rand() % 1000;
				deathRate = person[index].age * 45 - 800;

				if (deathRate < 100)
				{
					deathRate = 100;
				}

				if (deathDice > deathRate)//���̺� Ȯ���� �ֻ����� ������
				{
					//���߿� ���� �ٿ� ��� �޽��� ����� ��.
					*person[index].name = '\0';//�ι� ���(������ �ʱ�ȭ) (�����Բ� ���庼��? �޸�޸�.)
				}
			}
		}
	}

	return;
}
//���ؼ� ���� ���� ���� ����

// ù��° ���� ���� ������ ���ϱ� + 
void firstPerson(char* firstname)
{
	printf("����(������)�� �Է����ּ��� : ");
	scanf("%s", firstname);

	return;
}

void scholarSelect(scholarship* scholar, jobType* job) //�й� ���ϱ�
{
	int select;
	while (true)
	{
		printf("1.����, 2.����, 3.����\n");
		printf("�й��� �������ּ��� : ");//BAEKSU, ADMIN, PRIEST, DOCTOR, BANKER, MERCH
		scanf("%d", &select);

		switch (select) //BABO = 0, THEOLOGY = 1, LAW = 2, MEDICINE = 3
		{
		case 1:
		{
			*scholar = THEOLOGY;
			*job = PRIEST;
			return;
		}

		case 2:
		{
			*scholar = LAW;
			*job = ADMIN;
			return;
		}
		case 3:
		{
			*scholar = MEDICINE;
			*job = DOCTOR;
			return;
		}
		default:
		{
			*scholar = BABO;
			*job = BAEKSU;
			return;
		}
		}
	}
}

// �̸� ���Ҷ����� ���Ե� �Լ�
void naming(person* name, int index)
{
	printf("�̸��� �Է����ּ��� : ");
	scanf("%s", name[index].name);

	return;
}

// E_�������� �� �ǹ� �Ǽ�
void build(city* city, int cityindex, int* money, int* honor)//�ƾ� ����
{
	while (true)
	{
		int select = 0;
		int buildSelect;
		printf("���� �ǹ� ������ ���÷��� 1���� �������ּ���.\n�ٷ� �ǹ��� ���� �Ŷ�� �ٸ� ��ȣ�� �������ּ��� : ");
		scanf("%d", &select);

		if (select == 1)
		{
			printf("���� �̸� : %s\n", city[cityindex].name);
			printf("�����ϴ� �ǹ� ��� : ");

			if (city[cityindex].building[1] == 1) printf("���б�, ");
			if (city[cityindex].building[2] == 1) printf("����, ");
			if (city[cityindex].building[3] == 1) printf("����, ");
			if (city[cityindex].building[4] == 1) printf("�̼���, ");
			printf("\b\b");
			printf("\n");
		}


		while (1)
		{
			char select = 0;
			printf("1.���б� 2.���� 3.���� 4.�̼��� 5.���\n");//�������� �� �������� �׳� �� �����ää�����������������������������������������
			printf("���� �ǹ��� �������ּ��� (����): ");
			scanf("%d", &buildSelect);
			if (buildSelect != 5)
			{
				if (city[cityindex].building[buildSelect] == 0)
				{
					switch (buildSelect)
					{
					case 1:
						printf("���б��� �������� 10000G�� �ʿ��մϴ�. �����ðڽ��ϱ�? (Y/N)");

						scanf(" %c", &select);
						if (select == 'Y')
						{
							if (*money > 10000)
							{
								city[cityindex].building[buildSelect] = 1;
								*honor += 1;
								printf("�Ϸ�Ǿ����ϴ�.\n");
								return;
							}
							else
							{
								printf("���� �����մϴ�.\n");
								continue;
							}
						}
						else
						{
							continue;
						}
					case 2:
						printf("������ �������� 15000G�� �ʿ��մϴ�. �����ðڽ��ϱ�? (Y/N)");
						scanf(" %c", select);
						if (select == 'Y')
						{
							if (*money > 15000)
							{
								city[cityindex].building[buildSelect] = 1;
								*honor += 1;
								printf("�Ϸ�Ǿ����ϴ�.\n");
								return;
							}
							else
							{
								printf("���� �����մϴ�.\n");
								continue;
							}
						}
						else
						{
							continue;
						}
					case 3:
						printf("������ �������� 20000G�� �ʿ��մϴ�. �����ðڽ��ϱ�? (Y/N)");
						scanf(" %c", select);
						if (select == 'Y')
						{
							if (*money > 20000)
							{
								city[cityindex].building[buildSelect] = 1;
								*honor += 2;
								printf("�Ϸ�Ǿ����ϴ�.\n");
								return;
							}
							else
							{
								printf("���� �����մϴ�.\n");
								continue;
							}
						}
						else
						{
							continue;
						}
					case 4:
						printf("�̼����� �������� 15000G�� �ʿ��մϴ�. �����ðڽ��ϱ�? (Y/N)");
						scanf(" %c", select);
						if (select == 'Y')
						{
							if (*money > 15000)
							{
								city[cityindex].building[buildSelect] = 1;
								*honor += 2;
								printf("�Ϸ�Ǿ����ϴ�.\n");
								return;
							}
							else
							{
								printf("���� �����մϴ�.\n");
								continue;
							}
						}
						else
						{
							continue;
						}
					}

				}
				else
				{
					printf("�̹� ������ �ǹ��Դϴ�.\n");
				}
			}
			else
			{
				printf("���� �Ǽ��� ����մϴ�.\n");
				return;
			}
		}
	}
	return;
}

//���� ������
void movePeople(int* cityMove)
{
	printf("�̵��� ���ϴ� ���ø� �����ϼ���: ");
	scanf("%d", cityMove);
	printf("�ش� �ι��� %d�� ���÷� �̵��߽��ϴ�.\n", *cityMove);
	return;
}

//�ǹ� ����ֱ�
/*void movePeople(int* placeMove)
{
	while (1)
	{
		printf("�̵��� ���ϴ� ���ø� �����ϼ���: ");
		scanf("%d",placeMove);
		if (1 <= *placeMove <= 6)
		{
			printf("�ش� �ι��� %d�� �ǹ��� �̵��߽��ϴ�.", *placeMove);
		}
	}
}*/

//�ι�����.
void searching(int searchCity, person* newFace)
{
	person newPerson;
	int random;
	char select;
	char nameList[300][30] = { "Alessandro", "Aurora", "Marco", "Sofia", "Lorenzo",
	"Valentina", "Matteo", "Giorgia", "Andrea", "Chiara", "Francesco",
	"Beatrice", "Davide", "Martina", "Giuseppe", "Alice", "Leonardo",
	"Aurora", "Filippo", "Laura", "Mattia", "Sara", "Simone", "Giulia",
	"Gabriele", "Valeria", "Luca", "Giulia", "Mattia", "Elena", "Giacomo",
	"Aurora", "Alessandro", "Martina", "Riccardo", "Caterina", "Giovanni",
	"Maria", "Alessandro", "Elena", "Pietro", "Chiara", "Francesco", "Sofia",
	"Luca", "Laura", "Matteo", "Valentina", "Marco", "Aurora", "Giuseppe", "Alice",
	"Andrea", "Sofia", "Leonardo", "Martina", "Lorenzo", "Beatrice", "Davide", "Giulia",
	"Alessandro", "Emma", "Gabriele", "Valeria", "Simone", "Francesca", "Filippo", "Laura",
	"Matteo", "Sara", "Giovanni", "Sofia", "Marco", "Martina", "Alessia", "Francesco",
	"Aurora", "Leonardo", "Chiara", "Andrea", "Valentina", "Matteo", "Emma", "Lorenzo",
	"Beatrice", "Davide", "Giorgia", "Alessandro", "Sara", "Simone", "Giulia", "Gabriele",
	"Martina", "Matteo", "Valentina", "Francesco", "Aurora", "Luca", "Chiara", "Andrea",
	"Sofia", "Giovanni", "Francesca", "Lorenzo", "Beatrice", "Davide", "Valentina", "Matteo",
	"Emma", "Alessandro", "Sara", "Simone", "Giulia", "Gabriele", "Martina", "Francesco",
	"Aurora", "Luca", "Chiara", "Andrea", "Sofia", "Giovanni", "Francesca", "Lorenzo",
	"Beatrice", "Davide", "Valentina", "Matteo", "Emma", "Alessandro", "Sara", "Simone",
	"Giulia", "Gabriele", "Martina", "Francesco", "Aurora", "Luca", "Chiara", "Andrea",
	"Sofia", "Giovanni", "Francesca", "Lorenzo", "Beatrice", "Davide", "Valentina", "Matteo",
	"Emma", "Alessandro", "Sara", "Simone", "Giulia", "Gabriele", "Martina", "Francesco",
	"Aurora", "Luca", "Chiara", "Andrea", "Sofia", "Giovanni", "Francesca", "Lorenzo",
	"Beatrice", "Davide", "Valentina", "Matteo", "Emma", "Alessandro", "Sara", "Simone",
	"Giulia", "Gabriele", "Martina", "Francesco", "Aurora", "Luca", "Chiara", "Andrea",
	"Sofia", "Giovanni", "Francesca", "Lorenzo", "Beatrice", "Davide", "Valentina",
	"Matteo", "Emma", "Alessandro", "Sara", "Simone", "Giulia", "Gabriele", "Martina",
	"Francesco", "Aurora", "Luca", "Chiara", "Andrea", "Sofia", "Giovanni", "Francesca",
	"Lorenzo", "Beatrice", "Davide", "Valentina", "Matteo", "Emma", "Alessandro", "Sara",
	"Simone", "Giulia", "Gabriele", "Martina", "Francesco", "Aurora", "Luca", "Chiara",
	"Andrea", "Sofia", "Giovanni", "Francesca", "Lorenzo", "Beatrice", "Davide",
	"Valentina", "Matteo", "Emma", "Alessandro", "Sara", "Simone", "Giulia", "Gabriele",
	"Martina", "Francesco", "Aurora", "Luca", "Chiara", "Andrea", "Sofia", "Giovanni",
	"Francesca", "Lorenzo", "Beatrice", "Davide", "Valentina", "Matteo", "Emma",
	"Alessandro", "Sara", "Simone", "Giulia", "Gabriele", "Martina", "Francesco",
	"Aurora", "Luca", "Chiara", "Andrea" };

	printf("%d�� ���ÿ��� ���ο� �ι��� ã�ҽ��ϴ�!\n", searchCity);

	srand((unsigned int)time(NULL));
	random = rand() % 5;
	strcpy(newPerson.name, nameList[random]);
	printf("�̸�: %s\n", newPerson.name);

	srand((unsigned int)time(NULL));
	newPerson.age = rand() % 9 + 20;
	printf("����: %d\n", newPerson.age);

	srand((unsigned int)time(NULL));
	newPerson.gender = rand() % 2 + 1;
	printf("����: %c\n", newPerson.gender == 1 ? 'M' : 'F');

	srand((unsigned int)time(NULL));
	random = rand() % 6;
	printf("����: ");
	switch (random)
	{
	case 0://18���̸� �Ǵ� ������ �� 
		newPerson.job = BAEKSU;

		printf("����\n");
		break;

	case 1://�й� ����. ����
		newPerson.job = ADMIN;

		printf("������\n");
		break;

	case 2://�й� ����. ����
		newPerson.job = PRIEST;

		printf("������\n");
		break;

	case 3://�й� ����. ����
		newPerson.job = DOCTOR;

		printf("�ǻ�\n");
		break;

	case 4:
		newPerson.job = BANKER;

		printf("���డ\n");
		break;

	case 5:
		newPerson.job = MERCH;

		printf("����\n");
		break;

	default:
		printf("������ ����\n");
	}


	srand((unsigned int)time(NULL));
	random = rand() % 100;
	printf("�ź�: ");
	if (random < 3)
	{
		newPerson.status = COMMONS;

		printf("���\n");
	}
	else
	{
		newPerson.status = NOBILITY;

		printf("����\n");
	}

	srand((unsigned int)time(NULL));
	random = rand() % 4;
	printf("�й�: ");
	switch (random)
	{
	case 0:
		newPerson.scholar = BABO;
		printf("����� ����\n");
		break;
	case 1:
		newPerson.scholar = THEOLOGY;
		printf("����\n");
		break;
	case 2:
		newPerson.scholar = LAW;
		printf("����\n");
		break;
	case 3:
		newPerson.scholar = MEDICINE;
		printf("����\n");
		break;
	default:
		printf("���� ������ ��������\n\n");
	}

	srand((unsigned int)time(NULL));
	newPerson.scholarExp = 0;
	if (newPerson.scholar != BABO)
	{
		srand((unsigned int)time(NULL));
		newPerson.maxExp = rand() % 6 + 6;
	}
	else newPerson.maxExp = 0;

	newPerson.city = searchCity;
	newPerson.work = 0;
	newPerson.AP = 1;

	*newFace = newPerson;
	printf("������ �ι� ������ �߰��Ǿ����ϴ�.\n\n");
	return;
}

//���� �ι� ��� ���
void showPersonList(person* person, int maxPerson, char firstName[10], int searchCheck)
{
	for (int index = 0; index < maxPerson; index++)
	{
		if (person[index].name != '\0')
		{
			if (searchCheck == 0)
				printf("%d. %s %s\n", index + 1, firstName, person[index].name); // 0�� �ƴϰ� 1���� ��ȣ �Űܼ� �ι� ����ϰ� ���߿� �Է� ������ -1 �ϱ�
			else
				printf("%d. %s\n", index + 1, person[index].name);

			printf("����: %d\n", person[index].age);
			printf("����: %c\n", person[index].gender == 1 ? 'M' : 'F');
			printf("AP: %d\n", person[index].AP);


			printf("����: ");
			switch (person[index].job)
			{
			case BAEKSU://18���̸� �Ǵ� ������ �� 
				printf("����\n");
				break;
			case ADMIN://�й� ����. ����
				printf("������\n");
				break;
			case PRIEST://�й� ����. ����
				printf("������\n");
				break;
			case DOCTOR://�й� ����. ����
				printf("�ǻ�\n");
				break;
			case BANKER:
				printf("���డ\n");
				break;
			case MERCH://�ٷ� �� �� �ִ� ����
				printf("����\n");
				break;
			default:
				printf("������ ����\n");
			}


			printf("�ź�: ");
			switch (person[index].status)
			{
			case COMMONS:
				printf("���\n");
				break;
			case NOBILITY:
				printf("����\n");
				break;
			default:
				printf("�Ե� ���� ������!!\n");
			}


			printf("�й�: ");
			switch (person[index].scholar)
			{
			case BABO:
				printf("����� ����\n");
				break;
			case THEOLOGY:
				printf("����\n");
				break;
			case LAW:
				printf("����\n");
				break;
			case MEDICINE:
				printf("����\n");
				break;
			default:
				printf("���� ������ ��������\n");
			}

			if (person[index].city != 0 && searchCheck == 0)
			{
				printf("���� %d�� ���ÿ� ��ġ�� �ֽ��ϴ�.\n", person[index].city);
			}
			else
			{
				printf("���� ���ÿ� �߷ɵ��� ���� �ι��Դϴ�.\n");
			}

			if (searchCheck == 0)
			{
				switch (person[index].work)//���� �ϴ� Ȱ��. 0. ��� ��� 1. �������� 2. ������ 3. �й��ױ�(���б��� ���� ����)
				{
				case 1:
					printf("���ø� �����ϰ� �ֽ��ϴ�.\n");
					break;
				case 2:
					printf("���� ���� ���Դϴ�.\n");
					break;
				case 3:
					printf("���б����� �����ϴ� ���Դϴ�.\n");
					break;
				case 0:
					printf("����� ��ٸ��� ���Դϴ�.\n");
					break;
				default:
					break;
				}
			}

			if (person[index].scholar != BABO && searchCheck == 0)
			{
				if (person[index].scholarExp != person[index].maxExp)
					printf("�й��� �� ������ �ʿ䰡 �ֽ��ϴ�.\n");
			}
		}
		printf("\n");
	}
	return;
}


void printMap(int year, int money, int honor)
{
	printf("%d�� | ��__%d | ��__%d |\n", year, money, honor);
	printf("==================================================================================================== \n");
	printf("                    /                               _______ /        \n");
	printf("1.����(��)         /                ---------------                  \n");
	printf("------------------                /  2.�����(��)\033[33m_______\n\033[0m");
	printf("              ------------------    \033[33m/                 _ \033[0m4.����     \n\033[0m");
	printf("            /                      \033[33m/              ___/             \n\033[0m");
	printf("-----------                3.�ĸ�\033[33m__________    __/    \033[32m^^^^^^^^^^^^^^ \n\033[0m");
	printf("                           \033[33m��             \033[0m5.���׹�    \033[32m^^^^^^^^^^^^^ \n\033[0m");
	printf("                             \033[33m��             _|_   \033[32m^^^^^^^^^   \033[33m________ \n\033[0m");
	printf("                            6.����         \033[33m|   ��     \033[32m^^^^^  \033[33m/   \033[0m_____\033[33m��\033[0m__ \n\033[0m");
	printf("                              \033[32m^^^^^^^^^^^ \033[33m/     |         __/ \033[0m__/    9.����ġ��(��) \n\033[0m");
	printf("                      \033[32m^^^^^^^^^^ \033[33m________/      �� ____ /  \033[0m__/                 �� \n\033[0m");
	printf("             \033[32m^^^^^^^^^^^^   \033[33m___/               \033[0m10.�ж��  /                      �� \n\033[0m");
	printf("              \033[32m^^^^^^^^^   \033[33m/                      /       \033[0m/                         �� \n\033[0m");
	printf("\033[32m^^                \033[0m7.�����(��)\033[33m__________________|        \033[0m��                          | \n\033[0m");
	printf("\033[32m^^^^^^            \033[0m/           ��                \033[33m��\033[0m11.�Ƿ�ü��                         �� \n\033[0m");
	printf("   \033[32m^^^^^^^^    \033[0m/                ��           \033[33m_____/     |    \033[0m|                          |   \n\033[0m");
	printf("             -                    ��   12.�ǻ�          \033[33m|    \033[0m|                          |   \n");
	printf("           /                        ��       \033[33m|           ----\033[0m13.���ڳ�(��)              | \n");
	printf("   8.�ٸ����γ�(��)                   ��     \033[33m|              /  \033[0m��                        �� \n");
	printf("    /                                   ��   14.�θ�\033[33m______ /    \033[0m ��                        | \n");
	printf("----                                      �� ___     \033[33m��            \033[0m��                     / \n");
	printf("                                                 ��    \033[33m��            \033[0m��                  / \n");
	printf("                                                   ��    \033[33m��            \033[0m��                ��  \n");
	printf("                                                      15.������(��)       ��               �� \n");
	printf("                                                     /          / ��       |                 �� \n");
	printf("                                                    /__________/    ��_____|                   �� \n");
	printf("==================================================================================================== \n");
	return;
}

int revenue(jobType job, estate nobility)//NOBILITY
{
	int random;
	srand((unsigned int)time(NULL));

	switch (job) //BAEKSU, ADMIN, PRIEST, DOCTOR, BANKER, MERCH
	{
	case BAEKSU:
		random = rand() % 10 / 10 * 10 + 50;
		if (nobility == 1)
		{
			random * 2;
		}
		printf("���ɷ� %dG�� �������ϴ�.\n", random);
		return random;
	case DOCTOR:
		random = rand() % 1200 / 10 * 10 + 150;
		if (nobility == 1)
		{
			random * 2;
		}
		printf("����� ġ���ϰ� ����� �޾Ƽ� %dG�� �������ϴ�.\n", random);
		return random;
	case ADMIN:
		random = rand() % 1300 / 10 * 10 + 200;
		if (nobility == 1)
		{
			random * 2;
		}
		printf("������ �޾Ƽ� %dG�� �������ϴ�.\n", random);
		return random;
	case PRIEST:
		random = rand() % 1500 / 10 * 10 + 250;
		if (nobility == 1)
		{
			random * 2;
		}
		printf("������ �޾Ƽ� %dG�� �������ϴ�.\n", random);
		return random;
	case BANKER:
		random = rand() % 2000 / 10 * 10 + 300;
		if (nobility == 1)
		{
			random * 2;
		}
		printf("�������� %dG�� �������ϴ�.\n", random);
		return random;
	case MERCH:
		random = rand() % 2500 / 10 * 10 + 350;
		if (nobility == 1)
		{
			random * 2;
		}
		printf("�������� %dG�� �������ϴ�.\n", random);
		return random;
	}
	return 0;
}

/*void inputJob(person* person)
{
	int temp = 0;
	int tempJob = 0;
	temp = person->scholar;
	srand((unsigned int)time(NULL));
	do
	{
		tempJob = rand() % 8;
	} while (tempJob == 0);
	person->job = tempJob;
	return;
}*/

int main()
{
	int year = 1390;
	int honor = 0;
	char firstName[10] = { '\0', };

	city cityList[15] = { '\0', };
	strcpy(cityList[0].name, "����");
	strcpy(cityList[1].name, "�����");
	strcpy(cityList[2].name, "�ĸ�");
	strcpy(cityList[3].name, "����");
	strcpy(cityList[4].name, "���׹�");
	strcpy(cityList[5].name, "����");
	strcpy(cityList[6].name, "�����");
	strcpy(cityList[7].name, "�ٸ����γ�");
	strcpy(cityList[8].name, "����ġ��");
	strcpy(cityList[9].name, "�ж��");
	strcpy(cityList[10].name, "�Ƿ�ü");
	strcpy(cityList[11].name, "�ǻ�");
	strcpy(cityList[12].name, "���ڳ�");
	strcpy(cityList[13].name, "�θ�");
	strcpy(cityList[14].name, "������");

	artist artistList[31] = {
		{"����ġ��", 1401, 1428, "�� ������ü", 1428, "������", 1425, 11},
		{"���� ��Ƽÿ��", 1445, 1510, "��", 1482, "��ʽ��� ź��", 1486, 11},
		{"���������� �� ��ġ", 1452, 1519, "�𳪸���", 1506, "������ ����", 1498, 11},
		{"���̶����� �ο�����Ƽ", 1475, 1564, "õ�� â��", 1482, "�ٺ��", 1504, 11},
		{"��������", 1478, 1510, "��ǳ", 1508, "���ڴ� ��ʽ�", 1510, 9},
		{"Ƽġ�Ƴ� ��ÿ����", 1490, 1576, "�츣��� ��ʽ�", 1538, "�ǿ�Ÿ", 1576, 9},
		{"���Ŀ���", 1483, 1520, "���׳� �д�", 1510, "�׸��ҵ��� ����", 1520, 13},
		{"�ѽ� Ȧ����", 1497, 1543, "����", 1533, "� 8���� �ʻ�ȭ", 1537, 4},
		{"�˺극��Ʈ �ڷ�", 1471, 1528, "���� ��Ʈ�� ���� ��ȭ��", 1500, "�⵵�ϴ� ��", 1508, 4},
		{"�����δϹ��� ����", 1450, 1516, "�������� ����� ����", 1510, "�ϰ� ���� ���˿� �� ���� ����", 1500, 2},
		{"���͸� ����� �� �ƿ��", 1527, 1569, "�״����� �Ӵ�", 1559, "���� ȥ��", 1568, 2},
		{"�� �׷���", 1541, 1614, "�������� ������ ����", 1588, "�緹�� ǳ��", 1599, 8},
		{"���̶����� �޸��� �� ī�����", 1571, 1610, "Ȧ���丣�׽��� ���� ���� ����", 1599, "�񸮾��� �Ӹ��� ��� �ִ� ����", 1610, 8},
		{"���׸� �Ŀ� �纥��", 1577, 1640, "���ڰ��� ����", 1611, "�ϸ��� �Ǿ� ���", 1616, 5},
		{"�����Ʈ �ϸ��ռ� �� ����", 1606, 1669, "�������� ȣ���� ��ǳ�� �׸�����", 1633, "�߰�", 1642, 6},
		{"�Ƹ��׹̽þ� ��ƿ����Ű", 1596, 1652, "���곪�� �� ���", 1593, 1642, "����Ʈ�� �ϳ�", 1613,  3},
		{"�𿡰� �����ɽ�", 1599, 1660, "�극�� ���� �׺�", 1635, "�ó��", 1656, 8},
		{"���Ƽ��Ʈ�ø޿� ������", 1699, 1779, "���� ������", 1728, "��ħ �⵵", 1735, 3},
		{"������ ����", 1684, 1721, "Ű�׶� �������� ����", 1717, "�ĸ����� ����", 1718, 3},
		{"���������� �з�", 1814, 1875, "�̻� �ݴ� ����", 1857, "����", 1859, 3},
		{"�� ����", 1839, 1906, "���� ������ ���� �ҳ�", 1889, "����� ������", 1900, 6},
		{"�� ��", 1848, 1903, "Ÿ��Ƽ�� ���ε�", 1891, "�츮�� ��𿡼� �Դ°�? �츮�� �����ΰ�? �츮�� ���� ���°�?", 1898, 6},
		{"��Ʈ �� ����", 1853, 1890, "���� ������ ��", 1889, "�عٶ��", 1889, 2},
		{"���ξƸ� ����", 1832, 1883, "Ǯ�� ���� ���� �Ļ�", 1863, "�Ǹ� �δ� �ҳ�", 1866, 3},
		{"Ŭ�ε� ���", 1840, 1926, "�λ�, �ص���", 1872, "����", 1920, 3},
		{"�Ӹ� ��Ƽ��", 1869, 1954, "�縶�Ͼ� ǳ�� ���콺�� ���� ����", 1940, "��ī�罺", 1944, 6},
		{"�ٽǸ� ĭ��Ű", 1866, 1944, "���� ��", 1913, "�� ���� ��", 1923, 6},
		{"����ٸ��� ��ũ", 1863, 1944, "����", 1893, "�Ҿ�", 1896, 5},
		{"�ĺ�� ��ī��", 1881, 1973, "�ƺ� ó���", 1907, "�Ը���ī", 1937, 8},
		{"������ �ڼ�", 1887, 1968, "����� �������� ����", 1912, "��", 1917, 6},
		{"��ٵ��� �޸�", 1904, 1989, "����� ����", 1931, "�׷��� �� ������ Ż����ȭ", 1947, 8}
	};
	artist recruitedArtistList[31] = { '\0', };
	int maxArtist = 0;

	artwork artworkList[70] = { '\0', };
	int maxArtwork = 0;

	int money = 100; //�� <3

	person personList[1000] = { '\0', }; //'\0' ��� ���� X �ǹ� , �迭 0�� ù��° ���
	int maxPerson = 1;
	person searchList[1000] = { '\0', }; //�����ؼ� �߰��� ��� ���.
	int maxSearchPerson = 0;
	int personindex = 0; // ��� ���Ҷ� personindex ����ϱ� (�Լ� ���Կ�,�迭 ���� ����ȭ)
	int order = 0; // ��� ���� ���ϱ�.
	char answer = 0;

	//���ΰ� ����
	while (1) // ó������ �̸��� ������ ���ϱ�
	{
		firstPerson(&firstName);
		naming(&personList, personindex); // ù��° ��� �̸� ���ϱ�

		printf("����� �̸��� %s %s (��)�� �½��ϱ�? (Y/N)", firstName, personList[personindex]);

		scanf(" %c", &answer); // Y�� ���� N�̸� �ݺ�

		if (answer == 'Y')
		{
			break;
		}
		else;
	}
	city num = { '\0', };
	int cityindex = 0; // ���� ��ġ ���Ѿߵ� (�Լ� ���Կ�,�迭 ���� ����ȭ)
	//build(&num,cityindex);
	scholarSelect(&personList[0].scholar, &personList[0].job); // ù�ι� �й����� scholarSelect(&person[personindex].scholar)
	printf("\n");
	personList[0].age = 20;
	personList[0].gender = 1;
	personList[0].scholarExp = 0;
	personList[0].maxExp = 0;
	personList[0].AP = 1;
	personList[0].work = 0;
	int tempCity = 0;


	//�����ӽ���
	while (true) // << ���� ���ѷ���
	{
		printMap(year, money, honor);
		if (year > 1390)
		{
			int temp = 0;
			for (int index = 0; index < 15; index++)
			{
				if (cityList[index].building[2] == 1)
				{
					temp += 200;
				}
			}
			printf("���� ���� ������ %dG�Դϴ�.\n", temp);
			money += temp;
		}

		showPersonList(personList, maxPerson, firstName, 0);
		for (int index = 0; index < maxPerson; index++)
		{

			switch (personList[index].work)
			{
			case 0:
				break;
			case 1:
				searching(personList[index].city, &searchList[maxPerson]);
				maxSearchPerson += 1;
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}

		int moneyAnswer;

		//������ ���� �ܰ�
		for (int index = 0; index < 31; index++)
		{
			if (artistList[index].startYear == year)
			{
				printf("%s�� %d�� ���ÿ� �����߽��ϴ�!\n�Ŀ����� �ָ� �츮 ������ ������ �� �������� �𸨴ϴ�.\n�Ŀ��� �ݾ��� �Է��ϼ���(������ ������ �ʴ´ٸ� 0) : ", artistList[index].name, artistList[index].city);
				scanf("%d", &moneyAnswer);
				while (1)
				{
					if (0 <= moneyAnswer <= money)
					{
						if (moneyAnswer != 0)
						{
							/*
							typedef struct _artist //������ ����
							{
								char name[20]; //�̸�
								int startYear;
								int endYear;
								char paintNameA[60];
								int paintYearA;

								char paintNameB[60];
								int paintYearB;


								int city;

								�������� ������ ����, ���� �׸��� ���� ����, ��ǰ 2�� ���� ����
							} artist; //�ι� ���� �Ϸ��� �迭 ���ڿ� �ǹ̺ο�
							*/
							strcpy(recruitedArtistList[maxArtist].name, artistList[index].name);
							recruitedArtistList[maxArtist].startYear = artistList[index].startYear;
							recruitedArtistList[maxArtist].endYear = artistList[index].endYear;
							strcpy(recruitedArtistList[maxArtist].paintNameA, artistList[index].paintNameA);
							recruitedArtistList[maxArtist].paintYearA = artistList[index].paintYearA;
							strcpy(recruitedArtistList[maxArtist].paintNameB, artistList[index].paintNameB);
							recruitedArtistList[maxArtist].paintYearB = artistList[index].paintYearB;
							recruitedArtistList[maxArtist].city = artistList[index].city;

							maxArtist++;
							money -= moneyAnswer;

							printf("������ ���Կ� �����߽��ϴ�!\n\n");
							break;
						}
						else
						{
							printf("������ ������ �����߽��ϴ�.\n\n");
							break;
						}
					}
					else
					{
						printf("����� �� ���� �Է����ּ���.\n\n");
					}
				}
			}
		}

		for (int index = 0; index <= maxArtist; index++)
		{
			if (recruitedArtistList[index].paintYearA == year)
			{
				printf("�������� ���ο� �׸��� �׷Ƚ��ϴ�.\n���� �����߽��ϴ�!\n\n");
				printf("����: %s\n", recruitedArtistList[index].paintNameA);
				printf("�۰���: %s\n", recruitedArtistList[maxArtist].name);
				printf("���� �⵵: %d\n\n", recruitedArtistList[maxArtist].paintYearA);

				strcpy(artworkList[maxArtwork].name, recruitedArtistList[index].paintNameA);
				strcpy(artworkList[maxArtwork].painterName, recruitedArtistList[index].name);
				artworkList[maxArtwork].year = recruitedArtistList[maxArtist].paintYearA;

				honor += 4;
				maxArtwork++;
			}
		}

		for (int index = 0; index <= maxArtist; index++)
		{
			if (recruitedArtistList[index].paintYearB == year)
			{
				printf("�������� ���ο� �׸��� �׷Ƚ��ϴ�.\n���� �����߽��ϴ�!\n\n");
				printf("����: %s\n", recruitedArtistList[index].paintNameB);
				printf("�۰���: %s\n", recruitedArtistList[maxArtist].name);
				printf("���� �⵵: %d\n\n", recruitedArtistList[maxArtist].paintYearB);

				strcpy(artworkList[maxArtwork].name, recruitedArtistList[index].paintNameB);
				strcpy(artworkList[maxArtwork].painterName, recruitedArtistList[index].name);
				artworkList[maxArtwork].year = recruitedArtistList[maxArtist].paintYearB;

				honor += 4;
				maxArtwork++;
			}
		}

		for (int index = 0; index < maxPerson; index++)
		{
			switch (personList[index].work)
			{
			case 0:
				break;
			case 1:
				searching(personList[index].city, &searchList[maxPerson]);
				maxSearchPerson += 1;
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}

		int recruitCheck = 0;

		int loop = 1;
		for (int index = 0; index < maxPerson; index++) //AP �ʱ�ȭ
		{
			personList[index].AP = 1;
			personList[index].work = 0;
			if (personList[index].age >= 40)
			{
				if (personList[index].age == 40)
				{
					strcat(personList[index].name, "(���)");
				}
				personList[index].AP = 0;
			}
		}

		//2�ܰ�. �÷��̾��� �ൿ ����
		while (true) //1�� ������ �Ϸ絿�� �Ͼ�� �� ����
		{
			printf("���� %d�� �Դϴ�.\n", year);//���� �⵵ ����
			fflush(stdin);

			while (true)
			{
				int menuselect = 0;
				int searchselect = 0;

				printf("1.�ι� �ൿ ��Ű��\n2.�ι���� ����\n3.������ �ι���� ����\n4.�ǹ�����\n5.������ �ι� �����ϱ�\n6.������ �ִ� ����ǰ ��� ����\n7.�� �ѱ��: ");
				scanf("%d", &menuselect);
				fflush(stdin);
				if (menuselect == 1)
				{
					printf("�ൿ�� ���� �ι��� �������ּ���(���ڸ�)\n(�ൿ�� ���� �ι��� ���ٸ� 0) : "); // �ǹ� ���°� ���� �־�ߵɱ�
					scanf("%d", &personindex);
					fflush(stdin);
					if (personindex == 0)
					{
						break;
					}
					else;
					if (personindex > maxPerson)
					{
						printf("�������� �ʴ� �ι��Դϴ�.");
						continue;
					}
					else
					{
						if (personList[personindex - 1].AP != 1)
						{
							printf("�̹� �ൿ�� �� �ι��Դϴ�.\n");
							continue;
						}
					}
					printf("%s", personList[personindex - 1].name);
					printf("���ϴ� �ൿ�� �Է����ּ���.\n1.�����̵�\n2.���� �ι� ����\n3.������\n4.��������\n5.�������Ŀ�\n"); //���� �ϴ� Ȱ��. 0. ��� ��� 1. �������� 2. ������ 3. �й��ױ�(���б��� ���� ����)
					scanf("%d", &order);
					fflush(stdin);
					switch (order) //��� �Լ��� ����ٰ� �ֱ�
					{
					case 1:
						movePeople(&personList[personindex - 1].city); //�Լ��� printf �̹� ����
						break;
					case 2:
						if (personList[personindex - 1].city != 0)
						{
							printf("%d�� �ι��� ���ÿ� �ִ� �ι��� �����ϱ� �����߽��ϴ�.\n", personindex); // ���� �Լ� �ȳ���
							personList[personindex - 1].work = 1;
							personList[personindex - 1].AP = 0;
						}
						else
						{
							printf("�ش� �ι��� ���ÿ� ���� �ʽ��ϴ�.\n");
						}

						break;
					case 3:
						if (personList[personindex - 1].city != 0)
						{
							printf("%d�� �ι��� �����̸� �����߽��ϴ�.\n", personindex);
							money += revenue(personList[personindex - 1].job, personList[personindex - 1].status);
							//���� ��ġ�� �ǹ�. 0���� ��� ��� 2. ���б� 3. ���� 4. ���� 5. �̼���
							personList[personindex - 1].work = 2;
							personList[personindex - 1].AP = 0;
						}
						else
						{
							printf("�ش� �ι��� ���ÿ� ���� �ʽ��ϴ�.\n");
						}

						break;
					case 4:
						tempCity = personList[personindex - 1].city;
						if (cityList[tempCity].building[1] == 1)
						{
							if (money >= 250)
							{
								printf("���� ��ϱ��� 250G�Դϴ�. %d�� �ι��� ���п� ���н�Ű�ڽ��ϱ�? (Y/N) : ", personindex);
								scanf("%c", &answer);
								if (answer == "Y")
								{
									printf("%d�� �ι��� ���п� �����߽��ϴ�.\n", personindex);
									money -= 250;
									personList[personindex - 1].work = 3;
									personList[personindex - 1].AP = 0;
								}

							}
							else
							{
								printf("���� ��ϱ��� �����մϴ�.\n");
							}
						}
						else
						{
							printf("�� ���ÿ� ������ �������� �ʽ��ϴ�.\n");
						}
					case 5:

						break;
						// 1�������̵� 2���������� 3�����ù�ġ(������) 4����������(��ȥ������) 5���������Ŀ����� 6���й�
					case 6:
						continue;
					default:
						break;
					}

				}
				else if (menuselect == 2) // �ι����
				{
					showPersonList(personList, maxPerson, firstName, 0);
					continue;
				}
				else if (menuselect == 3) // ������ �ι� ���
				{
					showPersonList(searchList, maxPerson, firstName, 1);
					continue;
				}
				else if (menuselect == 4) // ���ðǼ�
				{
					build(&cityList, cityindex, &money, &honor);
					continue;
				}
				else if (menuselect == 5)//�ι� �����ϱ�. (���� �Ϸ�) ������ ������ ������ �� �ǵ���.
				{
					while (1)
					{
						if (recruitCheck == 0)
						{
							printf("������ ���ϴ� �ι��� �����ϼ���.\n");
							scanf("%d", searchselect);

							if (searchselect < maxSearchPerson)
							{
								if (strchr(searchList[searchselect - 1].name, "(���� �Ϸ�)") == NULL)
								{
									personList[maxPerson] = searchList[searchselect - 1]; // ������ ���� �ؾߵǳ�?
									printf("%s��(��) �츮 ������ ���ԵǾ����ϴ�.\n", searchList[searchselect - 1].name);
									strcat(searchList[searchselect - 1].name, "(���� �Ϸ�)");
									recruitCheck == 1;
								}
								else
								{
									printf("�̹� ������ �ι��Դϴ�.\n");
								}
							}
							else
							{
								printf("�������� �ʴ� �ι��Դϴ�.\n");
							}

						}
						else
							printf("�̹� �Ͽ� �̹� ������ �߽��ϴ�.\n");
						break;
					}
					continue;
				}
				else if (menuselect == 6)//�ϳѱ��
				{
					for (int index = 0; index <= maxArtwork; index++)
					{
						if (recruitedArtistList[index].paintYearB == year)
						{
							printf("����: %s\n", artworkList[index].name);
							printf("�۰���: %s\n", artworkList[maxArtist].painterName);
							printf("���� �⵵: %d\n\n", artworkList[maxArtist].year);
						}
					}
					continue;
				}
				else if (menuselect == 6)//�ϳѱ��
				{
					loop = 0;
					break;
				}

			}
			if (loop == 0)//break �Ǹ� ���� ����
			{
				break;
			}
		}
		if (honor >= 100) //break �Ǹ� ���� ����
		{
			break;
		}
		date(&personList, maxPerson);//��¥ �߰�     ������
		printf("�����ط� �Ѿ�ϴ�.\n\n");
		year++;
	}

	return 0;
}

/*
typedef struct _artist //������ ����
{
	char name[20]; //�̸�
	int startYear;
	int endYear;
	char paintNameA[60];
	int paintYearA;

	char paintNameB[60];
	int paintYearB;


	int city;

	�������� ������ ����, ���� �׸��� ���� ����, ��ǰ 2�� ���� ����
} artist; //�ι� ���� �Ϸ��� �迭 ���ڿ� �ǹ̺ο�
*/

// ������ �ι� �̸� �ȳ���(�̰� �ɰ�)

// ������ �� �ø���(������ �Ŀ�)
// ���� ��� ������ �Ŀ��ϰ� �����ϰ�
// �������� �ش� �⵵�� �ش� ���ÿ� ������? => ���ھƼ� ���԰���
// �ι� ���� ��->�ι� �߿� �׻��� �ϳ� ��� �÷��̾ ���� �Ἥ ���� ���� Ȯ���� (���� �����)
// ���������� ��ǰ ���鵵�� �ؾ��� => �������� �����ϸ� ��ǰ �ش� ������ ����ǰ�� ����
// ��Ȳ�� ���� 100���� �����ҷ�, ��������90, ��������80, ������70, �ƶ���60, �ж�����50, ��������40