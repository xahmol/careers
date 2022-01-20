#ifndef __DEFINES_H_
#define __DEFINES_H_

/* Machine code area addresses mapping */
#define MACOSTART           0x1300      // Start of machine code area
#define MACOSIZE            0x0800      // Length of machine code area

/* Bank 1 memory addresses mapping */
#define LOADSAVEBUFFER      0x2000      // 4 Kilobytes load and save buffer
#define SIDBASEADDRESS      0x3000      // 8 Kilobytes for SID data
#define WINDOWBASEADDRESS   0x5000      // Base address for windows system data
#define SCREENMAPADDRESS    0x7000      // Base for screen map

/* Global variables */

// Menu system variables

struct WindowStruct
{
    unsigned int address;
    unsigned char ypos;
    unsigned char height;
};
extern struct WindowStruct Window[9];

extern unsigned int windowaddress;
extern unsigned char windownumber;

//Menu data
extern unsigned char menubaroptions;
extern unsigned char pulldownmenunumber;
extern char menubartitles[5][12];
extern unsigned char menubarcoords[5];
extern unsigned char pulldownmenuoptions[11];
extern char pulldownmenutitles[11][5][17];

// Global variables
extern unsigned char bootdevice;
extern char DOSstatus[40];
extern char buffer[81];
extern char version[22];
extern unsigned char overlay_active;

extern char updownenter[4];
extern char leftright[3];
extern char alldirections[6];

extern unsigned char musicnumber;
extern unsigned char joyinterface;
extern unsigned char autosavetoggle;

// Game variables

// Board, cards and careers data
struct RingStruct
{
    unsigned char xcoord;
    unsigned char ycoord;
    unsigned char color;
    unsigned char outcome;
};
extern struct RingStruct ring[32];

struct CareerStruct
{
    unsigned char length;
    unsigned char returnfield;
    char name[20];
    unsigned char startfield;
};
extern struct CareerStruct career[8];

struct CareerfieldStruct
{
    unsigned char xcoord;
    unsigned char ycoord;
    unsigned char color;
    char text[27];
    unsigned char outcome;
    unsigned char amount1;
    unsigned char amount2;
};
extern struct CareerfieldStruct careerfield[8][14];

struct OpportunitycardStruct
{
    unsigned char conditionfree;
    unsigned char careernumber;
    unsigned char available;                         // ka(x)
};
extern struct OpportunitycardStruct opportunitycard[15];

//Pawn, field and dice graphics string data
extern char dicegraphics[6][3][4];

extern char pawngraphics[3][3];

// Player and game data
struct PlayerdataStruct
{
    char name[20];           // sp$(x,0)
    char experience[11];     // sp$(x,1)
    unsigned char career;    // sp(x,0)
    unsigned char position;  // sp(x,1)
    unsigned long salary;    // sp(x,2)
    unsigned long money;     // sp(x,3)
    unsigned char happiness; // sp(x,4)
    unsigned char fame;      // sp(x,5)
    unsigned char winmoney;
    unsigned char winhappiness;
    unsigned char winfame;
    unsigned char computer;  // sp(x,6)
    unsigned char skipturn;  // sp(x,7)
    unsigned char cards[19]; // ks(x,y)
};
extern struct PlayerdataStruct player[4];

extern unsigned char whichcard[20];         //wc(x)
extern unsigned char cardreset[15];
extern unsigned char fieldinformation;  //ai
extern unsigned char gameendflag;           // es
extern unsigned char anotherturn;           // ne
extern unsigned char playerturn;            // bs
extern unsigned char waitkeyflag;
extern unsigned char dice_double;           // dd
extern unsigned char dice_total;            // dg

extern unsigned char choice;
extern unsigned char xoffset;
extern unsigned char yoffset;

/* Game board dimensions */
#define BOARD_WIDTH         108
#define BOARD_HEIGHT        54
#define BOARD_ATTRPADDING   48

/* References to redefined chars */
/* Frame border graphics */
#define C_RIGHTLINE  0x67
#define C_LEFTLINE   0x74
#define C_UPLINE     0x63
#define C_LOWLINE    0x64
#define C_UPRIGHT    0x6D
#define C_UPLEFT     0x6E
#define C_LOWRIGHT   0x69
#define C_LOWLEFT    0x6B

/* Board graphics */
#define C_BLOCKUNDER 0x64
#define C_HEART      0x66
#define C_STAR       0x2A
#define C_DOLLAR     0x24

/* References to steering chars */
#define C_LEFT      157
#define C_RIGHT     29
#define C_DOWN      17
#define C_UP        145
#define C_ENTER     13
#define C_SPACE     32
#define C_DELETE    20
#define C_INSERT    148
#define C_INVSPACE  160
#define C_ESC       27

/* Defines for versioning */
/* Version number */
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
/* Build year */
#define BUILD_YEAR_CH0 (__DATE__[ 7])
#define BUILD_YEAR_CH1 (__DATE__[ 8])
#define BUILD_YEAR_CH2 (__DATE__[ 9])
#define BUILD_YEAR_CH3 (__DATE__[10])
/* Build month */
#define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')
#define BUILD_MONTH_CH0 \
    ((BUILD_MONTH_IS_OCT || BUILD_MONTH_IS_NOV || BUILD_MONTH_IS_DEC) ? '1' : '0')
#define BUILD_MONTH_CH1 \
    ( \
        (BUILD_MONTH_IS_JAN) ? '1' : \
        (BUILD_MONTH_IS_FEB) ? '2' : \
        (BUILD_MONTH_IS_MAR) ? '3' : \
        (BUILD_MONTH_IS_APR) ? '4' : \
        (BUILD_MONTH_IS_MAY) ? '5' : \
        (BUILD_MONTH_IS_JUN) ? '6' : \
        (BUILD_MONTH_IS_JUL) ? '7' : \
        (BUILD_MONTH_IS_AUG) ? '8' : \
        (BUILD_MONTH_IS_SEP) ? '9' : \
        (BUILD_MONTH_IS_OCT) ? '0' : \
        (BUILD_MONTH_IS_NOV) ? '1' : \
        (BUILD_MONTH_IS_DEC) ? '2' : \
        /* error default */    '?' \
    )
/* Build day */
#define BUILD_DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
#define BUILD_DAY_CH1 (__DATE__[ 5])
/* Build hour */
#define BUILD_HOUR_CH0 (__TIME__[0])
#define BUILD_HOUR_CH1 (__TIME__[1])
/* Build minute */
#define BUILD_MIN_CH0 (__TIME__[3])
#define BUILD_MIN_CH1 (__TIME__[4])

#endif // __DEFINES_H_