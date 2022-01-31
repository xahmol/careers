#ifndef __CAREER1_H_
#define __CAREER1_H_

void career_generic(unsigned char career, unsigned char position);
void career_waitforkey();
void career_gethappiness(unsigned char careernr, unsigned char position);
void career_getexperiencecard(unsigned char careernr, unsigned char position);
void career_getmoneytimesdie(unsigned char careernr, unsigned char position);
void career_gethappinessandfame(unsigned char careernr, unsigned char position);
void career_gotoparkbench();
void career_gotohospital();
void career_loosemoneyorparkbench(unsigned char careernr, unsigned char position);
void career_getfamebuthospital(unsigned char careernr, unsigned char position);
void career_endofcareer();

#endif // __CAREER2_H_