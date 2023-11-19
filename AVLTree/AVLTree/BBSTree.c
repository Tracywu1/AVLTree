#include <stdio.h>
#include <stdlib.h>
#include "BBSTree.h"

Status CreateEmpty(BBSTree* T) {
	*T = NULL; // 将指针指向空
	return OK;
}

void Destroy(BBSTree* T) {
	if (*T != NULL) {
		Destroy(&((*T)->lchild)); // 递归销毁左子树
		Destroy(&((*T)->rchild)); // 递归销毁右子树
		free(*T); // 释放当前节点
		*T = NULL; // 置空指针
	}
}

Status IsEmpty(BBSTree T) {
	return T == NULL ? TRUE : FALSE; // 如果树为空返回TRUE，否则返回FALSE
}

void R_Rotate(BBSTree* p) {
	BBSTree lc = (*p)->lchild;//lc指向p结点的左孩子
	(*p)->lchild = lc->rchild;//lc结点的右子树置为p结点的左子树
	lc->rchild = *p;//置p结点（原根结点）为lc结点的右孩子
	*p = lc;//p指向新的根结点
}

void L_Rotate(BBSTree* p) {
	BBSTree rc = (*p)->rchild;//rc指向p结点的右孩子
	(*p)->rchild = rc->lchild;//rc结点的左子树置为p结点的右子树
	rc->lchild = p;//置p结点（原根结点）为rc结点的左孩子
	p = rc;//p指向新的根结点
}

void LeftBalance(BBSTree* T) {
	BBSTree lc, rd;
	lc = (*T)->lchild;//lc指向T的左孩子
	switch (lc->bf) {//检查T的左子树的平衡因子，并作相应处理
	case LH: //LL型，右旋
		(*T)->bf = lc->bf = EH; R_Rotate(T); break;
	case RH: //新结点插⼊在T的左孩子的右子树上属LR型，双旋
		rd = lc->rchild;
		switch (rd->bf) {// 修改T及其左孩子的平衡因子
		case LH: (*T)->bf = RH; lc->bf = EH; break;
		case EH: (*T)->bf = lc->bf = EH; break;
		case RH: (*T)->bf = EH; lc->bf = LH; break;
		}
		rd->bf = EH;
		L_Rotate((*T)->lchild);//对T的左子树作左旋调整
		R_Rotate(T);//对T作右旋调整
		break;
	}
}

void RightBalance(BBSTree* T) {
	BBSTree rc, ld;
	rc = (*T)->rchild; // rc指向T的右孩子
	switch (rc->bf) { // 检查T的右子树的平衡因子，并作相应处理
	case RH: // RR型，左旋
		(*T)->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH: // 新结点插入在T的右孩子的左子树上属RL型，双旋
		ld = rc->lchild;
		switch (ld->bf) { // 修改T及其右孩子的平衡因子
		case RH: (*T)->bf = LH; rc->bf = EH; break;
		case EH: (*T)->bf = rc->bf = EH; break;
		case LH: (*T)->bf = EH; rc->bf = RH; break;
		}
		ld->bf = EH;
		R_Rotate(&((*T)->rchild)); // 对T的右子树作右旋调整
		L_Rotate(T); // 对T作左旋调整
		break;
	}
}


Status Insert(BBSTree* T, RcdType e, Status* taller) {
	if (NULL == T) {
		*T = (BBSTree)malloc(sizeof(BBSTNode)); (*T)->data = e;
		(*T)->bf = EH; (*T)->lchild = NULL; (*T)->rchild = NULL; taller = TRUE;
	}
	else if (e.key == (*T)->data.key) {
		taller = FALSE; return FALSE;
	}
	else if (e.key < (*T)->data.key) {
		if (FALSE == InsertAVL((*T)->lchild, e, taller))return FALSE;
		if (TRUE == taller) {
			switch((*T)->bf) {
			case LH: LeftBalance(T); taller = FALSE; break;
			case EH: (*T)->bf = LH; taller = TRUE; break;
			case RH: (*T)->bf = EH; taller = FALSE; break;
			}
		}
	}
	else {
		if (FALSE == InsertAVL((*T)->rchild, e, taller))return FALSE;
		if (TRUE == taller) {
			switch ((*T)->bf) {
			case LH: (*T)->bf = EH; taller = FALSE; break;
			case EH: (*T)->bf = RH; taller = TRUE; break;
			case RH: RightBalance(T); taller = FALSE; break;
			}
		}
	}
	return TRUE;
}

Status Delete(BBSTree* T, RcdType e, Status* shorter) {
    if (*T == NULL) {
        *shorter = FALSE;
        return FALSE;
    }
    else {

		/*当T为根结点时*/
        if (e.key == (*T)->data.key) {
            BBSTree p;
            if ((*T)->lchild == NULL && (*T)->rchild == NULL) { // 叶子结点
                free(*T);
                *T = NULL;
                *shorter = TRUE;
            }
            else if ((*T)->lchild == NULL) { // 只有右子树
                p = *T;
                *T = (*T)->rchild;
                free(p);
                *shorter = TRUE;
            }
            else if ((*T)->rchild == NULL) { // 只有左子树
                p = *T;
                *T = (*T)->lchild;
                free(p);
                *shorter = TRUE;
            }
            else { // 左右子树均存在
				RcdType minData;
				GetMin((*T)->rchild, &minData); // 使用 GetMin 函数获取右子树的最小值结点的数据
				                                // 取右子树的最小值不需要调整平衡，取左子树的最大值则需要
				(*T)->data = minData; // 将右子树最小值节点的值赋给当前结点
				Delete(&((*T)->rchild), minData, shorter); // 删除右子树最小值结点
                if (*shorter) {
                    switch ((*T)->bf) {
                    case LH: (*T)->bf = EH; *shorter = TRUE; break;
                    case EH: (*T)->bf = RH; *shorter = FALSE; break;
                    case RH: RightBalance(T); *shorter = TRUE; break;
                    }
                }
            }
            return TRUE;
        }

        else if (e.key < (*T)->data.key) {
            if (FALSE == Delete(&((*T)->lchild), e, shorter)) return FALSE;
            if (*shorter) {
                switch ((*T)->bf) {
                case LH: LeftBalance(T); *shorter = TRUE; break;
                case EH: (*T)->bf = LH; *shorter = FALSE; break;
                case RH: (*T)->bf = EH; *shorter = TRUE; break;
                }
            }
        }
        else {
            if (FALSE == Delete(&((*T)->rchild), e, shorter)) return FALSE;
            if (*shorter) {
                switch ((*T)->bf) {
                case LH: (*T)->bf = EH; *shorter = TRUE; break;
                case EH: (*T)->bf = RH; *shorter = FALSE; break;
                case RH: RightBalance(T); *shorter = TRUE; break;
                }
            }
        }
    }
    return TRUE;
}


Status Search(BBSTree T, RcdType e) {
	if (T == NULL) {
		return FALSE; // 树为空，返回FALSE
	}
	else if (e.key == T->data.key) {
		return TRUE; // 找到节点，返回TRUE
	}
	else if (e.key < T->data.key) {
		return Search(T->lchild, e); // 递归在左子树中搜索
	}
	else {
		return Search(T->rchild, e); // 递归在右子树中搜索
	}
}

void GetMin(BBSTree T, RcdType* e) {
	if (T == NULL) {
		return; // 树为空，直接返回
	}
	else if (T->lchild == NULL) {
		*e = T->data; // 最左边的节点即为最小值节点
	}
	else {
		GetMin(T->lchild, e); // 递归在左子树中查找最小值
	}
}

void GetMax(BBSTree T, RcdType* e) {
	if (T == NULL) {
		return; // 树为空，直接返回
	}
	else if (T->rchild == NULL) {
		*e = T->data; // 最右边的节点即为最大值节点
	}
	else {
		GetMax(T->rchild, e); // 递归在右子树中查找最大值
	}
}

void InOrderTraversal(BBSTree T) {
	if (T != NULL) {
		InOrderTraversal(T->lchild); // 先递归遍历左子树
		// 处理当前节点
		printf("%d ", T->data.key); 
		InOrderTraversal(T->rchild); // 再递归遍历右子树
	}
}

void PreOrderTraversal(BBSTree T) {
	if (T != NULL) {
		// 处理当前节点
		printf("%d ", T->data.key); 
		PreOrderTraversal(T->lchild); // 先递归遍历左子树
		PreOrderTraversal(T->rchild); // 再递归遍历右子树
	}
}

void PostOrderTraversal(BBSTree T) {
	if (T != NULL) {
		PostOrderTraversal(T->lchild); // 先递归遍历左子树
		PostOrderTraversal(T->rchild); // 再递归遍历右子树
		// 处理当前节点
		printf("%d ", T->data.key);
	}
}