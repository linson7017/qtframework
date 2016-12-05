#pragma once
class GlutText
{
public:
	enum FontSize
	{
		FontSize_10,
		FontSize_12,
		FontSize_18
	};
	GlutText(void);
	~GlutText(void);
	static void showText(char* text, double posX, double posY, FontSize f=FontSize_12,float r=1.0,float g=1.0,float b=1.0,float a=1.0);
	static void showText(int iText, double posX, double posY, FontSize f=FontSize_12,float r=1.0,float g=1.0,float b=1.0,float a=1.0);
	static void showText(float fText, int precision, double posX, double posY, FontSize f=FontSize_12,float r=1.0,float g=1.0,float b=1.0,float a=1.0);

};

