//
//  ProductSolution.h
//  HuaRongBlock
//
//  Created by liuwei on 14-12-5.
//
//

#ifndef __HuaRongBlock__ProductSolution__
#define __HuaRongBlock__ProductSolution__

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "SingleTon.h"

using namespace std;



//这样复制速度快
#define ggrid(x,y) (*((unsigned char*)cur_q->grid+4*(x)+(y)))
#define g_copy(g1,g2){/*复制棋盘 g2->g1*/\
unsigned int *t1,*t2;\
t1=(unsigned int*)(g1);\
t2=(unsigned int*)(g2);\
t1[0]=t2[0];\
t1[1]=t2[1];\
t1[2]=t2[2];\
t1[3]=t2[3];\
t1[4]=t2[4];\
}


//棋盘边界
typedef struct Bound {
	int top;
	int bottom;
	int left;
	int right;
}Bound;

typedef struct GridNode{
	unsigned char grid[5][4];	//棋盘
	GridNode *next_queue;	//队列中的下一个节点
	GridNode *parent;	//其父亲节点
	GridNode *next_hash;	//hash 表中的下一节点
}GridNode;

//哈希表结构
typedef struct hashlink{
	unsigned char len; //此桶中数据大小
	GridNode *next;
}hashlink;

//队列结构
typedef struct queuelink{
	GridNode *first;
	GridNode *iterater;
	GridNode *tail;
}queuelink;

#define MAX_CON 65536	//设最大为2^16
//哈希表



using namespace std;
class ProductSolutioin :  public SingleTon<ProductSolutioin>{
    friend class SingleTon<ProductSolutioin>;
public:
    string createSolution(string level);
    
protected:
    unsigned short GetHashValue(unsigned int *grid);
    
    void checkGridSetup(unsigned char* grid);
    
    void print(unsigned char* grid);
    
    char * InsertNode(unsigned *grid,GridNode *parent);
    
    int Detect(unsigned char* grid,int row,int col,int w,int h);
    
    bool IsResoluted(unsigned char* grid);
    
    bool test(GridNode *cur_q);
    
    bool GenNewGrid(unsigned char* old_grid,int row,int col,GridNode *cur_q);
    
    void copytoCharArray(unsigned char grid[][4], string destString);
    
    int Traverse(unsigned int *grid);
private:
    int stepCount = 0;
    
    hashlink hlink[MAX_CON]={0};
    //队头
    queuelink queue;
    
    unsigned char firstGrid[5][4];
    
    vector<string> answerStrings;
    
    Bound bound={0,4,0,3};
    
    stringstream stepsString;
};
#endif /* defined(__HuaRongBlock__ProductSolution__) */
