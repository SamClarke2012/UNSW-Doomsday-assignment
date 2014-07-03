/*
 *  doomsday.c
 *  A program to test a function dayOfWeek which determines which
 *  day of the week a particular date falls on.
 *  (only for dates after the start of the Gregorian calendar).
 *
 *  Program stub created by Richard Buckland on 27/03/12
 *  This program by Sam Clarke
 *  Freely licensed under Creative Commons CC-BY-3.0
 *
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE   1
#define FALSE  0
 
#define THURSDAY 0
#define FRIDAY   1
#define SATURDAY 2
#define SUNDAY   3
#define MONDAY   4
#define TUESDAY  5
#define WEDNESDAY 6

#define DAYS_IN_JAN       31
#define DAYS_IN_FEB       28
#define DAYS_IN_MARCH     31
#define DAYS_IN_FEB_LEAP  29

#define YEAR_END        12
#define DAYS_PER_WEEK   7
#define MAPPED_DAYS     6
#define DOOMSDAY_START  4

#define FIRST_DOOMSDAY_OF_APR  4 
 
#define OFFSET_NEAREST_DOOMSDAY_TO_MAY   5  // Simplified offsets
#define OFFSET_NEAREST_DOOMSDAY_TO_JUL   3
#define OFFSET_NEAREST_DOOMSDAY_TO_SEP   2
#define OFFSET_NEAREST_DOOMSDAY_TO_NOV   0



int dayOfWeek (int doomsday, int leapYear, int month, int day);
int findNearestDoomsday (int leapYear, int month, int day); // find the nearest DD
int getWeekdayOffset (int dist);                            // find the weekday offset
int wrapDays (int total);                                   // wrap days around



int main (int argc, char *argv[]) {
   assert (dayOfWeek (THURSDAY,  FALSE,  4,  4) == THURSDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  6,  6) == FRIDAY);
   assert (dayOfWeek (MONDAY,    FALSE,  8,  8) == MONDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE, 10, 10) == WEDNESDAY);
   assert (dayOfWeek (FRIDAY,    FALSE, 12, 12) == FRIDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  9,  5) == THURSDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  5,  9) == FRIDAY);
   assert (dayOfWeek (SUNDAY,    FALSE,  7, 11) == SUNDAY);
   assert (dayOfWeek (TUESDAY,   FALSE, 11,  7) == TUESDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE,  3,  7) == WEDNESDAY);
 
   assert (dayOfWeek (THURSDAY,  FALSE,  4,  5) == FRIDAY);
   assert (dayOfWeek (SATURDAY,  FALSE,  6,  5) == FRIDAY);
   assert (dayOfWeek (MONDAY,    FALSE,  8,  9) == TUESDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE, 10,  9) == TUESDAY);
   assert (dayOfWeek (FRIDAY,    FALSE, 12, 20) == SATURDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  9,  9) == MONDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  5,  5) == MONDAY);
   assert (dayOfWeek (SUNDAY,    FALSE,  7,  7) == WEDNESDAY);
   assert (dayOfWeek (TUESDAY,   FALSE, 11, 11) == SATURDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  3, 30) == SATURDAY);
 
   assert (dayOfWeek (TUESDAY,   FALSE,  2,  28) == TUESDAY);
   assert (dayOfWeek (TUESDAY,   FALSE,  2,  27) == MONDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  1,  3)  == THURSDAY);
 
   printf ("all tests passed - You are awesome!\n");

   return EXIT_SUCCESS;
}


 
int dayOfWeek (int doomsday, int leapYear, int month, int day) {  
   int dayOfWeek = 0;
   int distance = 0; 
   signed int offset = 0;
   
   distance = findNearestDoomsday (leapYear, month, day);
   
   offset = getWeekdayOffset (distance);
   
   dayOfWeek = doomsday + offset;
   
   dayOfWeek = wrapDays (dayOfWeek);

   return (dayOfWeek); 
}



int getWeekdayOffset (int dist) {  
   int count = 0;

   if (dist <= -DAYS_PER_WEEK) {
      count = dist % DAYS_PER_WEEK;
   } else if (dist >= DAYS_PER_WEEK) {
      count = dist % DAYS_PER_WEEK;
   } else {
      count = dist;
   }
   
   return (count);
}



int findNearestDoomsday (int leapYear, int month, int day) {
   int nearestDoomsday;

   if (month >= DOOMSDAY_START && month % 2 == 0) { // if month is 4,6,8,10,12    
      nearestDoomsday = month;                      // the doomsday is the month
      nearestDoomsday = day - nearestDoomsday;   
   }

   if (month >= DOOMSDAY_START && month % 2 != 0) {  // if month is 5,7,9,11
   
      if (month == 5) { // count to the last doomsday of april
         nearestDoomsday = day + OFFSET_NEAREST_DOOMSDAY_TO_MAY;
      }

      if (month == 7) { // count to the last doomsday of june
         nearestDoomsday = day + OFFSET_NEAREST_DOOMSDAY_TO_JUL;
      }

      if (month == 9) { // count to the last doomsday of august
         nearestDoomsday = day + OFFSET_NEAREST_DOOMSDAY_TO_SEP;  
      }

      if (month == 11) { // count to the last doomsday of october
         nearestDoomsday = day + OFFSET_NEAREST_DOOMSDAY_TO_NOV;  
      }
   }

   if (month == 1) {            // if the month is 1    

      if (leapYear == TRUE ) {  // count to the 4th of april
         nearestDoomsday = day - DAYS_IN_JAN  - DAYS_IN_FEB_LEAP - 
                           DAYS_IN_MARCH - FIRST_DOOMSDAY_OF_APR;
      } else {
         nearestDoomsday = day - DAYS_IN_JAN  - DAYS_IN_FEB - 
                           DAYS_IN_MARCH - FIRST_DOOMSDAY_OF_APR;
      }
   }

   if (month == 2) {            // if the month is 2    

      if (leapYear == TRUE ) {  // count to the 4th of april
         nearestDoomsday = day - DAYS_IN_FEB_LEAP - DAYS_IN_MARCH - 
                           FIRST_DOOMSDAY_OF_APR;
      } else {
         nearestDoomsday = day - DAYS_IN_FEB - DAYS_IN_MARCH - 
                           FIRST_DOOMSDAY_OF_APR;
      }
   }

   if (month == 3) {            // if the month is 3  
      nearestDoomsday = day - DAYS_IN_MARCH - FIRST_DOOMSDAY_OF_APR; 
   }                           // count to the 4th of april
   
   return (nearestDoomsday);
}



int wrapDays (int total) {
   int weekday = total;

   if (total > MAPPED_DAYS) {  // wrap around @ 6 & 0
      weekday = weekday - DAYS_PER_WEEK;
   } 

   if (weekday < 0) {
      weekday = DAYS_PER_WEEK + weekday;
   }
   
   return (weekday);
}