#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "BBSTree.h"

/**
 * @brief 合并两个平衡二叉树。
 * @param T1 - 第一个平衡二叉树指针的指针。
 * @param T2 - 第二个平衡二叉树指针的指针。
 * @return 函数执行成功返回OK，否则返回ERROR。
*/
Status Merge(BBSTree* T1, BBSTree* T2) {

}

/**
 * @brief 将平衡二叉树分裂为两个平衡二叉树。
 * @param T - 平衡二叉树指针。
 * @param x - 用于分裂的关键字。
 * @param T_less - 存储小于等于 x 的平衡二叉树指针的指针。
 * @param T_greater - 存储大于 x 的平衡二叉树指针的指针。
 * @return
*/
Status Split(BBSTree T, RcdType x, BBSTree* T_less, BBSTree* T_greater) {

}

void Display() {

}

short JudgeChoice(int n) {
	short choice;
	while ((scanf("%hd", &choice) != 1) || choice < 1 || choice > n) {
		while (getchar() != '\n');//清空输入缓冲区
		printf("请输入合法操作码~~\n");
		printf("请输入操作码(1~%d): ", n);
	}
	return choice;
}

int JudgeInput() {
	int ele;
	while (scanf("%d", &ele) != 1 || ele <= 0)
	{
		while (getchar() != '\n');
		printf("\n请输入正整数.\n");
	}
	return ele;
}

void DisplayMenu() {
	printf("\n");
	printf("***********************************************************************************\n");
	printf("   1.创建平衡二叉树                       2.查找\n");
	printf("***********************************************************************************\n");
	printf("   3.插入                                 4.删除\n");
	printf("***********************************************************************************\n");
	printf("   5.遍历（四种遍历方式）                 6.显示\n");
	printf("***********************************************************************************\n");
	//printf("   7.合并                                 8.分裂\n");
	//printf("***********************************************************************************\n");
	printf("   9.销毁并退出\n");
	printf(" ----------------------------------------------------------------------------------\n");
	printf("请选择您需要的操作(1~9)：\n");
}

void TraverseMenu() {
	printf("\n");
	printf("***********************************************************************************\n");
	printf("   1.先序遍历                             2.中序遍历\n");
	printf("***********************************************************************************\n");
	printf("   3.后序遍历                             4.层次遍历\n");
	printf("***********************************************************************************\n");
	printf("   5.exit\n");
	printf(" ----------------------------------------------------------------------------------\n");
	printf("请选择您需要的操作(1~5)：\n");
}

int main(){
	while (1) {
		DisplayMenu();
		short choice = JudgeChoice(9);
		if (choice == 9) {
			printf("欢迎您再次使用, 再见!\n");
			break;
		}
		switch (choice) {
		case 1:
			printf("请输入您要创建的平衡二叉树的元素的个数：");
			int n = JudgeInput();
			CreatAVLTree();
			printf("恭喜您！平衡二叉树已成功创建！\n");
			Display();
			break;
		case 2:
		{
			printf("请您输入您想要查询的数据(只能输入整数)：");
			int value = JudgeInput();
			if (Search()) {
				printf("该平衡二叉树上有你想要查询的数据\n");
			}
			else {
				printf("对不起，该平衡二叉树上没有您想要查询的数据\n");
			}
			break;
		}
		case 3:
		{
			printf("请输入您想要插入的数据(只能输入整数)：");
			int value = JudgeInput();
			if (Insert()) {
				printf("恭喜您，您已成功插入该数据！\n");
				Display();
			}
			else {
				printf("对不起，您插入该数据失败，可能是出现了一些问题\n");
			}
			break;
		}
		case 4:
		{
			printf("请您输入您想要删除的数据(只能输入整数)：");
			int value = JudgeInput();
			if (Delete()) {
				printf("恭喜您，您已成功删除该数据！\n");
				Display();
			}
			else {
				printf("对不起，您删除该数据失败，可能是出现了一些问题\n");
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