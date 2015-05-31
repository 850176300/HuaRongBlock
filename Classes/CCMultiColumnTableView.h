/****************************************************************************
Copyright (c) 2012 @hermanjakobi
Copyright (c) 2010 Sangwoo Im


Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCMULTITABLEVIEWCELL_H__
#define __CCMULTITABLEVIEWCELL_H__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
  //MODIFIED FOR cocos2d-x3.0beta2
	/**
	* It adds multiple column support to TableView.
	* Use ScrollViewDirectionBoth to set custom column count, colCount.
	* If a specific direction is set, table automatically find a proper value,
	* computing from viewSize and cellSize.
	*/

class MultiColumnTableView : public TableView
{
public:
	MultiColumnTableView();

	/**
	* An intialized table view object
	*
	* @param dataSource data source
	* @param size view size
	* @return table view
	*/
	static MultiColumnTableView* create(TableViewDataSource* dataSource, Size size);
	/**
	* An initialized table view object
	*
	* @param dataSource data source;
	* @param size view size
	* @param container parent object for cells
	* @return table view
	*/
	static MultiColumnTableView* create(TableViewDataSource* dataSource, Size size, Node *container);

	/**
	* the maximum number of columns.
	*/
	unsigned int m_colCount;

	void setColCount(unsigned int cols);

//--------------------------------------------------------------------
//	Overridden Methods from TableView
//--------------------------------------------------------------------
protected:
	virtual   long    __indexFromOffset(Point offset);
	virtual   Point   __offsetFromIndex(ssize_t index);
	virtual   void    _updateCellPositions();
  
public:
	virtual   void      _updateContentSize();
//--------------------------------------------------------------------


};

#endif /* __CCMULTITABLEVIEWCELL_H__ */
