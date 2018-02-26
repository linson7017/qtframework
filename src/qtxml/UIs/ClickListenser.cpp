#include <UIs/ClickListenser.h>
#include <QtCore/QVariant>
#include "Uicreator/ui_node.h"

Q_DECLARE_METATYPE(ui_node*);

ClickListenser::ClickListenser(void):Listener()
{
}


ClickListenser::~ClickListenser(void)
{
}

void ClickListenser::trigger()
{
	Listener::trigger(); //先调用父类的函数
	onClick(_sender);
}
