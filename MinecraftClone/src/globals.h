/*
 * gloabls.h
 *
 *  Created on: Mar 5, 2016
 *      Author: root
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int width;
int height;
int swidth;
int sheight;
int mouseX;
int mouseY;
int mouseButton;
int csf;
int def_width;
int def_height;
int def_wrap;
#define PI 3.141592653589793

#ifdef __MINGW32__
#define INSTALLDIR "C:/oglt/"
#else
#define INSTALLDIR "/dsk/ogla/"
#endif

#endif /* GLOBALS_H_ */
