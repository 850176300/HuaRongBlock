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
#include "CCMultiColumnTableView.h"

MultiColumnTableView* MultiColumnTableView::create(TableViewDataSource* dataSource, Size size)
{
	return MultiColumnTableView::create(dataSource, size, NULL);
}

MultiColumnTableView* MultiColumnTableView::create(TableViewDataSource* dataSource, Size size, Node *container)
{
	MultiColumnTableView *table = new MultiColumnTableView();
	table->initWithViewSize(size, container);
	table->autorelease();
	table->setDataSource(dataSource);
	table->_updateCellPositions();
	table->_updateContentSize();
  
	return table;
}

MultiColumnTableView::MultiColumnTableView() : m_colCount(1)
{
}

void MultiColumnTableView::setColCount(unsigned int cols)
{
	m_colCount = cols;
  
	if (this->getDirection() == Direction::BOTH)
	{
		this->_updateCellPositions();
	}
  
	this->_updateContentSize();
}

long MultiColumnTableView::__indexFromOffset(Point offset)
{
	int  index = 0;
	Size  cellSize;
	int  col, row;
	float    spaceWidth;
  
	cellSize = _dataSource->cellSizeForTable(this);
  
	switch (this->getDirection())
  {
    case Direction::HORIZONTAL:
    {
      spaceWidth = this->getContainer()->getContentSize().height / m_colCount;
      col        = (offset.y - (spaceWidth - cellSize.height)*0.5)/spaceWidth;
      row        = offset.x / cellSize.width;
    }
      break;
    default:
    {
      spaceWidth = this->getContainer()->getContentSize().width / m_colCount;
      col        = (offset.x - (spaceWidth - cellSize.width)*0.5)/spaceWidth;
      row        = offset.y / cellSize.height;
    }
      break;
	}
  
	index = col + row * m_colCount;
	return index;
}

Point MultiColumnTableView::__offsetFromIndex(ssize_t index)
{
	Point offset;
	Size  cellSize;
	float    spaceWidth;
	int  col, row;
  
	cellSize = _dataSource->cellSizeForTable(this);
  
	switch (this->getDirection())
	{
    case Direction::HORIZONTAL:
    {
      row        = index / m_colCount;
      col        = index % m_colCount;
      spaceWidth = this->getContainer()->getContentSize().height / m_colCount;
      offset     = Point(row * cellSize.height, col * spaceWidth + (spaceWidth - cellSize.width) * 0.5);
    }
      break;
      
    default:
    {
      row        = index / m_colCount;
      col        = index % m_colCount;
      spaceWidth = this->getContainer()->getContentSize().width / m_colCount;
      offset     = Point(col * spaceWidth + (spaceWidth - cellSize.width) * 0.5, row * cellSize.height);
    }
      break;
	}
  
	return offset;
  
}

void MultiColumnTableView::_updateCellPositions()
{
  int cellsCount = _dataSource->numberOfCellsInTableView(this) / m_colCount;
  _vCellsPositions.resize(cellsCount + 1, 0.0);
  
  if (cellsCount > 0)
  {
    float currentPos = 0;
    Size cellSize;
    for (int i=0; i < cellsCount; i++)
    {
      _vCellsPositions[i] = currentPos;
      cellSize = _dataSource->tableCellSizeForIndex(this, i);
      switch (this->getDirection())
      {
        case Direction::HORIZONTAL:
          currentPos += cellSize.width;
          break;
        default:
          currentPos += cellSize.height;
          break;
      }
    }
    _vCellsPositions[cellsCount] = currentPos;//1 extra value allows us to get right/bottom of the last cell
  }
  
}

void MultiColumnTableView::_updateContentSize()
{
	Size     size, cellSize, viewSize;
	unsigned int cellCount, rows;
  
	cellSize  = _dataSource->cellSizeForTable(this);
	cellCount = _dataSource->numberOfCellsInTableView(this);
	viewSize  = Size(getViewSize().width/getContainer()->getScaleX(), getViewSize().height/getContainer()->getScaleY());
  
	switch (this->getDirection())
	{
    case Direction::HORIZONTAL:
    {
      m_colCount = getViewSize().height / cellSize.height;
      rows     = ceilf(cellCount/((float)m_colCount));
      size     = Size(MAX(rows * cellSize.width, viewSize.width), m_colCount * cellSize.height);
    }
      break;
      
    default:
    {
      if (getDirection() == Direction::VERTICAL)
      {
        m_colCount = viewSize.width / cellSize.width;
      }
      rows     = ceilf(cellCount/((float)m_colCount));
      size     = Size(MAX(cellSize.width * m_colCount, viewSize.width), rows * cellSize.height);
    }
      break;
	}
  
	this->setContentSize(size);
  
	//FIXME? unsure if that code makes sense
	if (_oldDirection != _direction)
	{
		if (_direction == Direction::HORIZONTAL)
		{
			this->setContentOffset(Point(0,0));
		}
		else
		{
			//this->setContentOffset(Point(0,0));
			this->setContentOffset(Point(0,this->minContainerOffset().y));
		}
    
		_oldDirection = _direction;
	}
}

