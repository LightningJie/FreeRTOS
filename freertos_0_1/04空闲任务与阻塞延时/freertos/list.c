#include "list.h"

/* 链表初始化*/
void vListInitialiseItem(ListItem_t * const pxItem)
{
	pxItem->pvContainer=NULL;/* 不指向任何一个链表*/
}

//链表根节点初始化
void vListInitialise(List_t* const pxList)
{
	pxList->pxIndex=(ListItem_t *) &pxList->xListEnd;
	
	pxList->xListEnd.xItemValue=portMAX_DELAY;
	pxList->xListEnd.pxNext=(ListItem_t *) &pxList->xListEnd;
	pxList->xListEnd.pxPrevious=(ListItem_t *) &pxList->xListEnd;
	
	pxList->uxNumberOfItems=(UBaseType_t)0U;//无符号整型
	
}
//尾插法插入链表
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t * const pxIndex=pxList->pxIndex;
	
	pxNewListItem->pxNext=pxIndex;
	pxNewListItem->pxPrevious=pxIndex->pxPrevious;
	pxIndex->pxPrevious->pxNext=pxNewListItem;
	pxIndex->pxPrevious=pxNewListItem;
	
	pxNewListItem->pvContainer=(void *)pxList;
	
	(pxList->uxNumberOfItems)++;
}

/* 将节点按照升序排列插入到链表 */
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t *pxIterator;
	
	/* 获取节点的排序辅助值 */
	const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;

	/* 寻找节点要插入的位置 */
	if( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd );
		     pxIterator->pxNext->xItemValue <= xValueOfInsertion; 
			 pxIterator = pxIterator->pxNext )
		{
			/* 没有事情可做，不断迭代只为了找到节点要插入的位置 */			
		}
	}

	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;

	/* 记住该节点所在的链表 */
	pxNewListItem->pvContainer = ( void * ) pxList;

	/* 链表节点计数器++ */
	( pxList->uxNumberOfItems )++;
}


/* 将节点从链表中删除 */
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
	/* 获取节点所在的链表 */
	List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;

	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

	/* Make sure the index is left pointing to a valid item. */
	if( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}

	/* 初始化该节点所在的链表为空，表示节点还没有插入任何链表 */
	pxItemToRemove->pvContainer = NULL;
	
	/* 链表节点计数器-- */
	( pxList->uxNumberOfItems )--;

	/* 返回链表中剩余节点的个数 */
	return pxList->uxNumberOfItems;
}
