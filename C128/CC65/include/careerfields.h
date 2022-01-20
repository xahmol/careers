#ifndef __CAREERFIELDS_H_
#define __CAREERFIELDS_H_

void career_generic(unsigned char career, unsigned char position);
void career_waitforkey();
void career_gethappiness(unsigned char careernr, unsigned char position);
void career_getexperiencecard(unsigned char careernr, unsigned char position);
void career_getmoneytimesdie(unsigned char careernr, unsigned char position);
void career_gethappinessandfame(unsigned char careernr, unsigned char position);
void career_getmoney(unsigned char careernr, unsigned char position);
void career_loosehalfmoney();
void career_skipturn();
void career_getfame(unsigned char careernr, unsigned char position);
void career_getopportunitycard(unsigned char careernr, unsigned char position);
void career_getsalary(unsigned char careernr, unsigned char position);
void career_gotoparkbench();
void career_loosehalfsalary();
void career_gotohospital();
void career_getmoneyandfame(unsigned char careernr, unsigned char position);
void career_loosehalffame();
void career_getfamenohappiness(unsigned char careernr, unsigned char position);
void career_getsalarytimesdie(unsigned char careernr, unsigned char position);
void career_throwagain();
void career_loosemoneyorparkbench(unsigned char careernr, unsigned char position);

#endif // __CAREERFIELDS_H_