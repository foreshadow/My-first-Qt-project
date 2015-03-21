#ifndef UNIVERSAL
#define UNIVERSAL

#include <QtCore>

extern void delay(int s);
extern void splash(QString path, int delaySecond, int x, int y);

#define CARD_WIDTH 75
#define CARD_HEIGHT 100
#define CARD_OVERLAP 5
#define CARD_OVERLAP_DX CARD_WIDTH / 4
#define CARD_POP_DY CARD_HEIGHT / 3
#define CARD_WIDTH_IN_PIC 75
#define CARD_HEIGHT_IN_PIC 100

#define FOR_TO(l, r) for (int i=l; i<=r; i++)
#define FOR_DOWNTO(r, l) for (int i=r; i>=l; i--)
#define FOR_TO_2(l, r) for (int j=l; j<=r; j++)
#define FOR_DOWNTO_2(r, l) for (int j=r; j>=l; j--)
#define FOR_TO_3(l, r) for (int k=l; k<=r; k++)
#define FOR_DOWNTO_3(r, l) for (int k=r; k>=l; k--)
//  Be careful of potential error:
//      redeclaration of `i'

#define GAMETEST
#define ONLINE

#endif // UNIVERSAL
