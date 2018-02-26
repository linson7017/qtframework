#ifndef QF_MESSAGEDEF_H__
#define QF_MESSAGEDEF_H__

#define QF_MESSAGE_UI 20000
//
//命令ID值定义，必须保证各命令ID不能重复，用户定义消息ID必须从QF_MESSAGE_UI开始
//
/*
int iValue = 0; 表格中某一单元格被双击事件
void *pValu
*/
const int QF_MESSAGE_TABLE_ITEM_DOUBLECLICKED  = QF_MESSAGE_UI + 1;

#endif