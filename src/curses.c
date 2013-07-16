/*
 *  curses.c
 *  LIME, The versatile 3D line modeling environment 
 *
 *  Created by Christian Brinch on 29/10/08.
 *  Copyright 2006-2012, Christian Brinch, 
 *  <brinch@nbi.dk>
 *  Niels Bohr institutet
 *  University of Copenhagen
 *	All rights reserved.
 *
 */

#include <curses.h>
#include <time.h>

void
greetings(){
	initscr();
	printw("*** LIME, The versatile line modeling engine, Ver.1.2\n*** Copyright 2006--2012, Christian Brinch <brinch@nbi.dk>\n");
	refresh();	
}

void
screenInfo(){
  move(4,4);  printw("Building grid      :");
  move(4,51); printw("|");
  move(5,4);  printw("Smoothing grid     :");
  move(5,51); printw("|");
  move(7,4);  printw("Statistics         :");
  move(9,4);  printw("Iterations         :"); 
  move(10,4); printw("Propagating photons:");
  move(10,51);printw("|");
  move(13,4); printw("Ray-tracing model  :");
  move(13,51);printw("|");
  move(4,60); printw("|      Molecular data");
  move(5,60); printw("|");
  move(6,60); printw("|");  
  move(7,60); printw("|");
  move(8,60); printw("|");
  move(9,60); printw("|");
  move(10,60); printw("|");
  move(11,60); printw("|");
  move(12,60); printw("|");
  move(13,60); printw("|");
  move(14,60); printw("|");
  refresh();	
}

void
done(int line){
	move(line,52); printw(" [ok]");
    refresh();
}

void
progressbar(double percent, int line){
  int i;
  for(i=0;i<(int)(percent*25.);i++){
    move(line,25+i);
    printw("#");
  }
  refresh();
}

void 
progressbar2(int prog, double percent, double minsnr, double fstquart, double median, double thrdquart){
  move(7,38); printw("                    ");            
  move(8,38); printw("                    ");
  move(7,25); printw("Min/Median(SNR)  %.2e %.2e", minsnr, median);
  move(8,25); printw("1st/3rd Quartile %.2e %.2e", fstquart, thrdquart);
  
  move(9,25+prog); printw("#");
  if(percent<100) {
    move(10,25);	 printw("                         ");
  }
  refresh();	
}

void 
goodnight(int initime, char filename[80]){
	int runtime=time(0)-initime;
	move(14,4); printw("Output written to %s", filename);
	move(22,0); printw("*** Program ended succesfully               ");
	move(22,58); printw("runtime: %3dh %2dm %2ds", runtime/3600, runtime/60%60, runtime%60);
	move(23,0); printw("*** [Press any key to quit]");
    refresh();
	getch();
	endwin();
}

void
quotemass(double mass){
  move(21,6); printw("Total mass contained in model: %3.2e solar masses", mass);
  refresh();
}



void 
warning(char message[80]){
	move(22,0); printw("*** %s\n",message);
	refresh();
}

void 
bail_out(char message[80]){
	move(22,0); printw("*** %s",message);
	move(23,0); printw("*** [Press any key to quit]");
    refresh();
	getch();
	endwin();
}

void
collpartmesg(char molecule[90], int partners, int specnumber){
  move(6,63); printw("%.25s", molecule);
  move(7,63); printw("%d collision partner(s):", partners);

  refresh();
}

void
collpartmesg2(char name[10], int partner){
  move(8,63); printw("%s ",name);
  refresh();
}

void
collpartmesg3(number, flag){
  move(10,63); printw("Model provides:");
  move(11,63); printw("%d density profile(s)", number);
  if(flag==1) {
    move(13,63); printw("*** Warning! ***");  
    move(14,63); printw("Too few density profiles");  
  }
  refresh();
}
