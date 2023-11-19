#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "BBSTree.h"

/**
 * @brief �ϲ�����ƽ���������
 * @param T1 - ��һ��ƽ�������ָ���ָ�롣
 * @param T2 - �ڶ���ƽ�������ָ���ָ�롣
 * @return ����ִ�гɹ�����OK�����򷵻�ERROR��
*/
Status Merge(BBSTree* T1, BBSTree* T2) {

}

/**
 * @brief ��ƽ�����������Ϊ����ƽ���������
 * @param T - ƽ�������ָ�롣
 * @param x - ���ڷ��ѵĹؼ��֡�
 * @param T_less - �洢С�ڵ��� x ��ƽ�������ָ���ָ�롣
 * @param T_greater - �洢���� x ��ƽ�������ָ���ָ�롣
 * @return
*/
Status Split(BBSTree T, RcdType x, BBSTree* T_less, BBSTree* T_greater) {

}

void Display() {

}

short JudgeChoice(int n) {
	short choice;
	while ((scanf("%hd", &choice) != 1) || choice < 1 || choice > n) {
		while (getchar() != '\n');//������뻺����
		printf("������Ϸ�������~~\n");
		printf("�����������(1~%d): ", n);
	}
	return choice;
}

int JudgeInput() {
	int ele;
	while (scanf("%d", &ele) != 1 || ele <= 0)
	{
		while (getchar() != '\n');
		printf("\n������������.\n");
	}
	return ele;
}

void DisplayMenu() {
	printf("\n");
	printf("***********************************************************************************\n");
	printf("   1.����ƽ�������                       2.����\n");
	printf("***********************************************************************************\n");
	printf("   3.����                                 4.ɾ��\n");
	printf("***********************************************************************************\n");
	printf("   5.���������ֱ�����ʽ��                 6.��ʾ\n");
	printf("***********************************************************************************\n");
	//printf("   7.�ϲ�                                 8.����\n");
	//printf("***********************************************************************************\n");
	printf("   9.���ٲ��˳�\n");
	printf(" ----------------------------------------------------------------------------------\n");
	printf("��ѡ������Ҫ�Ĳ���(1~9)��\n");
}

void TraverseMenu() {
	printf("\n");
	printf("***********************************************************************************\n");
	printf("   1.�������                             2.�������\n");
	printf("***********************************************************************************\n");
	printf("   3.�������                             4.��α���\n");
	printf("***********************************************************************************\n");
	printf("   5.exit\n");
	printf(" ----------------------------------------------------------------------------------\n");
	printf("��ѡ������Ҫ�Ĳ���(1~5)��\n");
}

int main(){
	while (1) {
		DisplayMenu();
		short choice = JudgeChoice(9);
		if (choice == 9) {
			printf("��ӭ���ٴ�ʹ��, �ټ�!\n");
			break;
		}
		switch (choice) {
		case 1:
			printf("��������Ҫ������ƽ���������Ԫ�صĸ�����");
			int n = JudgeInput();
			CreatAVLTree();
			printf("��ϲ����ƽ��������ѳɹ�������\n");
			Display();
			break;
		case 2:
		{
			printf("������������Ҫ��ѯ������(ֻ����������)��");
			int value = JudgeInput();
			if (Search()) {
				printf("��ƽ���������������Ҫ��ѯ������\n");
			}
			else {
				printf("�Բ��𣬸�ƽ���������û������Ҫ��ѯ������\n");
			}
			break;
		}
		case 3:
		{
			printf("����������Ҫ���������(ֻ����������)��");
			int value = JudgeInput();
			if (Insert()) {
				printf("��ϲ�������ѳɹ���������ݣ�\n");
				Display();
			}
			else {
				printf("�Բ��������������ʧ�ܣ������ǳ�����һЩ����\n");
			}
			break;
		}
		case 4:
		{
			printf("������������Ҫɾ��������(ֻ����������)��");
			int value = JudgeInput();
			if (Delete()) {
				printf("��ϲ�������ѳɹ�ɾ�������ݣ�\n");
				Display();
			}
			else {
				printf("�Բ�����ɾ��������ʧ�ܣ������ǳ�����һЩ����\n");
			}
			break;
		}
		case 5:
			Traverse_main();
			break;
		case 6:
			Display();
			break;
		//case 7:
		//case 8:
		case 9:
			Destroy();
			return;
		}
	}
}