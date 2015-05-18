//
//  ProductSolution.cpp
//  HuaRongBlock
//
//  Created by liuwei on 14-12-5.
//
//

#include "ProductSolution.h"
#include "SuperGlobal.h"
unsigned short ProductSolutioin::GetHashValue(unsigned int *grid)
{
    unsigned int mask1 = 524287; //19个1
    unsigned int mask2 = 8191; //13个1
    unsigned short len = 65535;
    
    unsigned int result =0;
    result += ((grid[0] & (mask1<<13))>>13)|((grid[0] & mask2)<<19);
    result ^= grid[1];
    result += ((grid[2] & (mask1<<13))>>13)|((grid[2] & mask2)<<19);
    result ^= grid[3];
    result ^= ((grid[4] & (mask1<<13))>>13)|((grid[4] & mask2)<<19);
    result += grid[5];
    
    return result%len;
}

void ProductSolutioin::checkGridSetup(unsigned char* grid){
    int endx=-10;
    int endy=-10;
    int startx = -1;
    int starty = -1;
    int cx = -1;
    int cy = -1;
    char s = '\0';
    int firstAppear = -1;
    for (vector<string>::iterator m = answerStrings.begin() + answerStrings.size() - 1; m >= answerStrings.begin(); --m) {
        printf("===%s=====\n", (*m).c_str());
        int differentCount=0;
        stringstream ss;
        ss<<*m<<"\0";
        string gridString = ss.str();
        //        printf("the string stream is %s", ss.str().c_str());
        stringstream s1,s2;
        for (int i = 0; i < DataHeight; ++i) {
            for (int j = 0; j < DataWidth; ++j) {
                if (firstGrid[i][j] != gridString.at(i*DataWidth+j)) {
                    s1<<firstGrid[i][j];
                    s2<<gridString.at(i*DataWidth+j);
                    
                    if (firstAppear == -1) {
                        firstAppear = i*DataWidth+j;
                        startx = j;
                        starty = i;
                    }
                    if (gridString.at(i*DataWidth+j) != '0' && gridString.at(i*DataWidth+j) != 'B') {
                        endx = j ;
                        endy = i ;
                    }
                    if (firstGrid[i][j] != '0' && firstGrid[i][j] != 'B') {
                        startx = j;
                        starty = i;
                    }
                    if (gridString.at(i*DataWidth+j) == 'C') {
                        cx = j;
                        cy = i;
                    }
                    differentCount++;
                }
            }
        }
        
        
        string myS1 = s1.str();
        string myS2 = s2.str();
        int l1, l2;
        for (l1 = 0; l1 < myS1.length(); ++l1) {
            if (myS1.at(l1) != '0' && myS1.at(l1) != 'B') {
                s = myS1.at(l1);
                break;
            }
        }
        for (l2 = 0; l2 < myS2.length(); ++l2) {
            if (myS2.at(l2) != '0' && myS2.at(l2) != 'B') {
                break;
            }
        }
       
        if (s == 'S') {
            
            stepCount++;
//            printf("第%d:移动小兵\n", stepCount);
            stepsString<<startx+starty*4<<"->{"<<endx - startx<<","<<starty - endy<<"};";
        }else if (s == 'V' || s == 'H'){
            
            stepsString<<startx+starty*4<<"->{"<<endx - startx<<","<<starty - endy<<"};";
            stepCount++;
//            printf("第%d:移动五虎将\n",stepCount);
        }else if (s == 'C'){
            
            stepsString<<startx+starty*4<<"->{"<<endx - startx<<","<<starty - endy<<"};";
            stepCount++;
//            printf("第%d:移动曹操\n", stepCount);
        }else {
            
        }
//        printf("第%d步：%c\n", stepCount, s);
        g_copy(firstGrid,(*m).c_str());
    }
    if (cx == -1 && cy == -1) {
        for (int i = 0; i < DataHeight; ++i) {
            for (int j = 0; j < DataWidth; ++j) {
                if (firstGrid[i][j] == 'C') {
                    cx = j;
                    cy = i;
                }
            }
        }
    }
    stepCount++;
//    printf("第%d:移动曹操, %d, %d\n", stepCount,cx, cy);
    stepsString<<cx+cy*4<<"->{"<<1 - cx<<","<<cy-3<<"};";
    string thestring = stepsString.str();
    thestring.erase(thestring.size() - 1);
}

void ProductSolutioin::print(unsigned char* grid)
{
    int i;
    stringstream myStream;
    
    for(i=0;i<=DataHeight*2;i++)
    {
        for(int j=0;j<=DataWidth*4;j++)
        {
            
            if(i%2!=0) { //偶数行画 | 和 字母
                if(j%4==2)
                {
                    if(*(grid+DataWidth*(i/2)+(j/4))!='0')
                    {
                        myStream<<*(grid+DataWidth*(i/2)+(j/4));
                    }
                    else
                    {
                        myStream<<"0";
                    }
                }
            }
        }
    }
    answerStrings.push_back(myStream.str().c_str());
}

char * ProductSolutioin::InsertNode(unsigned *grid,GridNode *parent)
{			//检测是否有相同的棋盘格局
	unsigned short index= GetHashValue(grid);
	GridNode *p = hlink[index].next;
	GridNode *q = NULL;
    
	if(hlink[index].len == 0)
	{
		GridNode *g = new GridNode;
		//复制棋盘
		g_copy(g->grid,grid);
		g->next_queue = NULL;
		g->next_hash = NULL;
		g->parent = parent;
		queue.tail->next_queue = g;
		queue.tail=g;
		
		hlink[index].next = g;
		
		//此hash链数据值++
		hlink[index].len ++ ;
        //        printf("insert the tag\n");
		return (char*)g; //返回此节点的指针
	}
    
	if(hlink[index].len > 0)
	{
		while(p!=NULL)
		{
			//如果相同,则返回NULL,表示不用再插入相同的棋盘格局了
			if(grid[0] == *((unsigned int*)(p->grid[0]))&&\
               grid[1] == *((unsigned int*)(p->grid[1]))&&\
               grid[2] == *((unsigned int*)(p->grid[2]))&&\
               grid[3] == *((unsigned int*)(p->grid[3]))&&\
               grid[4] == *((unsigned int*)(p->grid[4])))
			{
				//fprintf(f,"Same Node\n");
				return NULL;
			}
			q = p;
			p = p->next_hash;
		}
		GridNode *g = new GridNode;
		//复制棋盘
		g_copy(g->grid,grid);
		g->next_queue = NULL;
		g->next_hash = NULL;
		g->parent = parent;
		queue.tail->next_queue = g;
		queue.tail=g;
		
		q->next_hash = g;
		
		//此hash链数据值++
		hlink[index].len ++ ;
        //        printf("insert the tag\n");
		return (char*)g; //返回此节点的指针
	}
	
	return NULL; //返回此节点的指针
}

int ProductSolutioin::Detect(unsigned char* grid,int row,int col,int w,int h)
{
	int result= 0;
	//检测上边,如果上边还有一层
	if(row-1>=0)
	{
        int j;
		for(j=0;j<w;j++)
		{
			if(*(grid+(row-1)*DataWidth+(col+j))!='B')
			{
				break;
			}
		}
		if(j==w)
			result += 1<<0;
	}
	
	//左边
	if(col-1>=0)
	{
        int j;
		for(j=0;j<h;j++)
		{
			if(*(grid+(row+j)*DataWidth+(col-1))!='B')
			{
				break;
			}
		}
		if(j==h)
			result += 1<<1;
	}
	
	//下边
	if(row+h<DataHeight)
	{
        int j;
		for(j=0;j<w;j++)
		{
			if(*(grid+(row+h)*DataWidth+(col+j))!='B')
			{
				break;
			}
		}
		if(j==w)
			result += 1<<2;
	}
	
	//右边
	if(col+w<DataWidth)
	{
        int j;
		for(j=0;j<h;j++)
		{
			if(*(grid+(row+j)*DataWidth+(col+w))!='B')
			{
				break;
			}
		}
		if(j==h)
			result += 1<<3;
	}
    //    printf("result is: %d\n",result);
	return result;	//
}

bool ProductSolutioin::test(GridNode *cur_q)
{
	for(int i=0;i<DataHeight;i++)
	{
        int j;
		for(j=0;j<DataWidth;j++)
		{
			switch(ggrid(i,j)) {
                case 'C':
                    if(ggrid(i+1,j)!='0' || \
                       ggrid(i,j+1)!='0' ||\
                       ggrid(i+1,j+1)!='0')
                        goto error;
                    break;
                case 'V':
                    if(ggrid(i+1,j)!='0')
                        goto error;
                    break;
                case 'H':
                    if(ggrid(i,j+1)!='0')
                        goto error;
                    break;
                default:
                    break;
			}
		}
	}
	return false;
error:
	
	return false;
}

bool ProductSolutioin::IsResoluted(unsigned char* grid)
{
//    printf("====%s====\n", grid);
	if(*(grid+3*DataWidth+1)=='C')
    {
		return true;
    }
	return false;
}

bool ProductSolutioin::GenNewGrid(unsigned char* old_grid,int row,int col,GridNode *cur_q)
{
    //    printf("perform count:%d\n", count++);
	int w,h;
	switch(*(old_grid+DataWidth*row+col)) {
        case 'C':	//曹操
            w=2;
            h=2;
            break;
        case 'V':	//竖着的五虎将
            w=1;
            h=2;
            break;
        case 'H':	//横着的五虎将,关羽
            w=2;
            h=1;
            break;
        case 'S':	//卒
            w=1;
            h=1;
            break;
        case 'B':	//空格,nothing to do
            break;;
        default:
            printf("error 士兵 %c \n",*(old_grid+DataWidth*row+col));
            return false;
	}
    
	//探知方向
	int direct = Detect(old_grid,row,col,w,h);
	//printf("Direct : ++++ %0x  \n",direct);
	
	unsigned char new_grid[5][4];
    
	//如果探知可以移动,则移动,并将新的格局加入到队列
	if(direct!=0)
	{
		int i,j;
		//向上
		if((direct & 0x01) == 0x01)
		{
			//将旧的格局copy到新的格局,在新的格局中修改数据
			g_copy(new_grid,old_grid);
			for(i=0;i<h+1;i++)
			{
				for(j=0;j<w;j++)
				{
					if(i==h)
					{
						new_grid[row-1+i][col+j] = 'B';
						continue;
					}
					new_grid[row-1+i][col+j]=new_grid[row+i][col+j];
				}
			}
			//printf("上**********************\n");
			//print((unsigned char*)new_grid);
            
			InsertNode((unsigned *)new_grid,cur_q);
			test(cur_q);
			if(IsResoluted((unsigned char*)new_grid))
			{
				printf("@@@@@@@@@ Resolution is Gernated! @@@@@@@@@@@@\n");
				return true;
			}
			
		}
		//向左
		if((direct & 0x02) == 0x02)
		{
			//将旧的格局copy到新的格局,在新的格局中修改数据
			g_copy(new_grid,old_grid);
			for(i=0;i<w+1;i++)
			{
				for(j=0;j<h;j++)
				{
					if(i==w)
					{
						new_grid[row+j][col-1+i] = 'B';
						continue;
					}
					new_grid[row+j][col-1+i]=new_grid[row+j][col+i];
				}
			}
			//printf("左**********************\n");
			//print((unsigned char*)new_grid);
            
			InsertNode((unsigned *)new_grid,cur_q);
			test(cur_q);
			if(IsResoluted((unsigned char*)new_grid))
			{
				printf("@@@@@@@@@ Resolution is Gernated! @@@@@@@@@@@@\n");
				return true;
			}
		}
		//向下
		if((direct & 0x04) == 0x04)
		{
			//将旧的格局copy到新的格局,在新的格局中修改数据
			g_copy(new_grid,old_grid);
			for(i=h;i>=0;i--)
			{
				for(j=0;j<w;j++)
				{
					if(i==0)
					{
						new_grid[row+i][col+j] = 'B';
						continue;
					}
					new_grid[row+i][col+j]=new_grid[row-1+i][col+j];
				}
			}
			//printf("下**********************\n");
			//print((unsigned char*)new_grid);
            
			InsertNode((unsigned *)new_grid,cur_q);
			test(cur_q);
			if(IsResoluted((unsigned char*)new_grid))
			{
				printf("@@@@@@@@@ Resolution is Gernated! @@@@@@@@@@@@\n");
				return true;
			}
		}
		//向右
		if((direct & 0x08) == 0x08)
		{
			//将旧的格局copy到新的格局,在新的格局中修改数据
			g_copy(new_grid,old_grid);
			for(i=w;i>=0;i--)
			{
				for(j=0;j<h;j++)
				{
					if(i==0)
					{
						new_grid[row+j][col+i] = 'B';
						continue;
					}
					new_grid[row+j][col+i]=new_grid[row+j][col+i-1];
				}
			}
			//printf("右**********************\n");
			//print((unsigned char*)new_grid);
            
			InsertNode((unsigned *)new_grid,cur_q);
			test(cur_q);
			if(IsResoluted((unsigned char*)new_grid))
			{
				printf("@@@@@@@@@ Resolution is Gernated! @@@@@@@@@@@@\n");
				return true;
			}
		}
		
	}
    
	return false;
}


//棋盘格局生成器,即走步器
int ProductSolutioin::Traverse(unsigned int *grid)
{
	//初始化队列
	GridNode head;
	queue.first = &head;
	queue.tail = &head;
    
	//加入初始棋盘格局
	if((queue.first = (GridNode*)InsertNode(grid,NULL))==NULL)
	{
		printf("Init error!\n");
		return 0;
	}
	queue.iterater = queue.first;
	
	//如果队列不空,则继续广度搜索
	while(queue.iterater!=NULL)
	{
        //        printf("===================start count %d\n", count);
		//对于棋盘中的每一个元素进行探测,看是否可以移动
		unsigned char *c_grid = (unsigned char*)(queue.iterater->grid);	//获取队列头的棋盘格局
		//print((unsigned char*)c_grid);
		for(int i=0;i<DataHeight;i++)
		{
			for(int j=0;j<DataWidth;j++)
			{
				//已经处理的或空格的情况
				if(*(c_grid+DataWidth*i+j)=='0' || *(c_grid+DataWidth*i+j)=='B')
					continue;
				
				//表明此网格上有一个man
				//printf("-----  %c  -----\n",*(c_grid+DataWidth*i+j));
				if(GenNewGrid((unsigned char*)c_grid,i,j,queue.iterater)==true)
				{
					//找到结果了..^_^
					//打印结果
					GridNode *p=queue.iterater;
					int n=0;
					
					while(p!=NULL)
					{
                        
						print((unsigned char*)p->grid);
                        //                        printf("add setup\n");
						p = p->parent;
						n++;
					}
                    checkGridSetup(firstGrid[0]);
					
					int sum=0;
					for(int i=0;i<MAX_CON;i++)
					{
						sum += hlink[i].len;
					}
					printf("搜索节点数目：%d \n",sum);
					return 1;
					
				}
			}
		}
		queue.iterater = queue.iterater->next_queue;
	}
    
	if (queue.iterater == NULL)
	{
		printf("*** No resultion! ***\n");
		return 0;
	}
    return 0;
}


void ProductSolutioin::copytoCharArray(unsigned char grid[][4], string destString){
    for (int i = 0; i < 5; ++i) {
        for (int j =0; j < 4; ++j) {
            grid[i][j] = destString.at(i*4+j);
        }
    }
}

string ProductSolutioin::createSolution(string level) {


    unsigned char init_grid[5][4]={
        'V','C','0','S',\
        '0','0','0','S',\
        'V','H','0','V',\
        '0','V','B','0',\
        'S','0','B','S'
    };

    stepCount = 0;
    stepsString.str( std::string() );
    stepsString.clear();
    answerStrings.clear();
    //            string step = line.substr(index + 22, line.size() - 1);
    copytoCharArray(init_grid, level);
    g_copy(firstGrid, init_grid);
    memset((char*)hlink,0,sizeof(hashlink)*MAX_CON);
    memset((char*)&queue,0,sizeof(queuelink));
    
    int result = Traverse((unsigned int*)init_grid);
    if (result == 1) {
        printf("the count ================= %d", (int)answerStrings.size());
    }else {
        return "no solution";
    }
    string thestring = stepsString.str();
    thestring.erase(thestring.size() - 1);

	return thestring;
}




