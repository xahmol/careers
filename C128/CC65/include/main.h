#ifndef __MAIN_H_
#define __MAIN_H_

unsigned char dosCommand(const unsigned char lfn, const unsigned char drive, const unsigned char sec_addr, const char *cmd);
unsigned int cmd(const unsigned char device, const char *cmd);
void loadoverlay(char *name);
void wait(clock_t wait_cycles);
void cspaces(unsigned char number);
void printcentered(char* text, unsigned char xpos, unsigned char ypos, unsigned char width);
unsigned char getkey(char* allowedkeys, unsigned char joyallowed);
int input(unsigned char xpos, unsigned char ypos, char *str, unsigned char size);
unsigned char input_number(unsigned char xpos, unsigned char ypos, unsigned char minvalue, unsigned char maxvalue);
void presskeyprompt(unsigned char xpos, unsigned char ypos);
void windowsave(unsigned char ypos, unsigned char height);
void windowrestore();
void menumakeborder(unsigned char xpos, unsigned char ypos, unsigned char height, unsigned char width);
void menuplacebar();
unsigned char menupulldown(unsigned char xpos, unsigned char ypos, unsigned char menunumber);
unsigned char menumain();
unsigned char areyousure();
void fileerrormessage(unsigned char error);
void saveconfigfile();
void loadconfigfile();
void board_reposition(unsigned char row, unsigned char col);
void board_print(unsigned char row, unsigned char col, unsigned char screencode, unsigned char attribute);
void pawn_place(unsigned char playernumber);
unsigned char pawn_other(unsigned char playernumber);
void pawn_erase(unsigned char playernumber);
void board_reset();
void game_reset();
void inputofnames();
void dice_throw(unsigned char dicenumber);
unsigned char player_collegeexperience();
unsigned char card_selectopportunity();
char* cards_actiontext(unsigned char cardnumber);
unsigned char checkforbump_check(unsigned char car, unsigned char pos);

#endif // __MAIN_H_