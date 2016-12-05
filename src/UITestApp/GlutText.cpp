#include "GlutText.h"
#include <QtOpenGL/QtOpenGL>
#include <gl/glut.h>

GlutText::GlutText(void)
{
}


GlutText::~GlutText(void)
{
}

void GlutText::showText(int iText, double posX, double posY,FontSize f,float r,float g,float b,float a)
{
	char text[100];
	sprintf(text,"%d",iText);
	showText(text,posX,posY,f,r,g,b,a);
}
void GlutText::showText(float fText, int precision, double posX, double posY,FontSize f,float r,float g,float b,float a)
{
	char text[100];
	char pc[10];
	itoa(precision,pc,10);
	std::string precisionStr="%.";
	precisionStr.append(pc);
	precisionStr.append("f");
	sprintf(text,precisionStr.c_str(),fText);
	showText(text,posX,posY,f,r,g,b,a);
}

void GlutText::showText(char* text, double posX, double posY,FontSize f,float r,float g,float b,float a)
{
	glColor4f(r,g,b,a);
	glRasterPos2f(posX,posY);
	for (int i=0;i<=strlen(text);++i)
	{
		char c = text[i];
		switch (f)
		{
		case FontSize_10:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
			break;
		case FontSize_12:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
			break;
		case FontSize_18:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
			break;
		default:
			break;
		}
		
	}
}