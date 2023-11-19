#ifndef BBSTREE_H
#define BBSTREE_H

/* 定义状态值 */
#define TRUE   1
#define FALSE  0
#define OK     1
#define ERROR  0
#define IBFEASIBLE  -1
#define OVERFLOW    -2 

/* 定义平衡因子值 */
#define LH +1//左⾼ 
#define EH 0//等⾼ 
#define RH -1//右⾼

typedef int Status;
typedef int KeyType;// 元素类型为整数类型

typedef struct {
    KeyType key;// 关键字项
} RecordType, RcdType;

typedef struct {
    RcdType data;                            // 结点存储的数据信息
    int bf;                                  // 结点平衡因子
    struct BBSTNode* lchild, * rchild;       // 左、右子树指针
}BBSTNode, *BBSTree;

/**
 * @brief 创建一个空的平衡二叉树。
 * @param T - 指向平衡二叉树指针的指针。
 * @return 函数执行成功返回OK，否则返回ERROR。
*/
Status CreateEmpty(BBSTree* T);

/**
 * @brief 销毁平衡二叉树。
 * @param T - 指向平衡二叉树指针的指针。
*/
void Destroy(BBSTree* T);

/**
 * @brief 判断平衡二叉树是否为空。
 * @param T - 平衡二叉树指针。
 * @return 空返回TRUE，否则返回FALSE。
*/
Status IsEmpty(BBSTree T);

/**
 * @brief 右旋操作。
 * @param p - 指向需要进行右旋的结点指针的指针。
*/
void R_Rotate(BBSTree* p);

/**
 * @brief 左旋操作。
 * @param p - 指向需要进行左旋的结点指针的指针。
*/
void L_Rotate(BBSTree* p);

/**
 * @brief 左平衡操作，用于调整平衡二叉树的结构，确保左右子树高度差不超过1。
 * @param T - 平衡二叉树指针的指针。
*/
void LeftBalance(BBSTree* T);

/**
 * @brief 右平衡操作，用于调整平衡二叉树的结构，确保左右子树高度差不超过1。
 * @param T - 平衡二叉树指针的指针。
*/
void RightBalance(BBSTree* T);

/**
 * @brief 向平衡二叉树中插入结点。
 * @param T - 平衡二叉树指针的指针。
 * @param e - 待插入的数据。
 * @param taller - 标识树是否长高的指针。
 * @return 函数执行成功返回OK，否则返回ERROR。
*/
Status Insert(BBSTree* T, RcdType e, Status* taller);

/**
 * @brief 删除平衡二叉树中的结点。
 * @param T - 平衡二叉树指针的指针。
 * @param e - 待删除的数据。
 * @param shorter - 标识树是否变矮的指针。
 * @return 函数执行成功返回OK，否则返回ERROR。
*/
Status Delete(BBSTree* T, RcdType e, Status* shorter);

/**
 * @brief 在平衡二叉树中搜索指定的数据。
 * @param T - 平衡二叉树指针。
 * @param e - 待搜索的数据。
 * @return 数据存在返回OK，否则返回ERROR。
*/
Status Search(BBSTree T, RcdType e);

/**
 * @brief 获取平衡二叉树中的最小数据。
 * @param T - 平衡二叉树指针。
 * @param e - 用于存储最小数据的指针。
*/
void GetMin(BBSTree T, RcdType* e);

/**
 * @brief - 用于存储最大数据的指针
 * @param T - 平衡二叉树指针。
 * @param e - 用于存储最大数据的指针。
*/
void GetMax(BBSTree T, RcdType* e);

/**
 * @brief 中序遍历平衡二叉树。
 * @param T - 平衡二叉树指针。
*/
void InOrderTraversal(BBSTree T);

/**
 * @brief 先序遍历平衡二叉树。
 * @param T - 平衡二叉树指针。
*/
void PreOrderTraversal(BBSTree T);

/**
 * @brief 后序遍历平衡二叉树。
 * @param T - 平衡二叉树指针。
*/
void PostOrderTraversal(BBSTree T);

#endif //BBSTREE_H