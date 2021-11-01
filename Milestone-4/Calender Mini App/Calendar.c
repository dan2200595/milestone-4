#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"


// flush function is used to 
// remove new line character at the end of line
void flush() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// function for add a new note
// prompt date and note from user
// write it into a file
void add_reminder() {
    // define variables
    struct Reminder reminder;
    FILE* fp;
    // open file in read mode
    fp = fopen("reminder.bin", "r");
    // check whether file is null
    if (fp == NULL) {
        // open file in writing mode
        fp = fopen("reminder.bin", "w");
    }
    // close the file
    fclose(fp);
    // remove new line character
    flush();
    // prompt user for username
    printf("Enter your name:");
    fgets(reminder.name, 50, stdin);
    // prompt date month and year from user
    printf("Date and Month(ex: dd mm): ");
    scanf_s("%d %d", &reminder.day, &reminder.month);
    // remove new line character
    flush();
    // prompt reminder from user
    printf("Reminder description (max: 512 chars): ");
    fgets(reminder.description, 512, stdin);
    // open file in append mode
    fp = fopen("reminder.bin", "a+");
    // if file cannot open exit from program
    if (fp == NULL) {
        printf("reminder.bin file is unable to open\n");
        exit(1);
    }
    // write note into the file
    fwrite(&reminder, sizeof(struct Reminder), 1, fp);
    // display success message and close file
    printf("Reminder sucessfully added to the calendar\n");
    fclose(fp);
}


// function for display all remianders
// read note.bin file
// display standered output to user
void display_Reminders(char* name) {
    // define variables
    FILE* fp;
    struct Reminder reminder;
    
    
    // open file as read mode
    fp = fopen("reminder.bin", "r");
    // if file cannot open exit from program
    if (fp == NULL) {
        printf("reminder.bin file is unable to open\n");
        exit(1);
    }
    int i = 0;
    int exist = 0;
    // read all remainders in note.bin file
    while (fread(&reminder, sizeof(struct Reminder), 1, fp)) {
        if (!strcmp(reminder.name, name)){
            printf("Date: %d/%d/2021\n", reminder.day, reminder.month);
            printf("Reminder: %s\n\n", reminder.description);
            reminders = (struct Reminder*)malloc((i + 1) * sizeof(struct Reminder));
            reminders[i] = reminder;
            i++;
            exist = 1;
        }
    }
    if (!exist) {
        printf("There is no reminders under the name %s", name);
    }
    // close file
    fclose(fp);
}

// function to display main menu 
// display options available
// get the option from user
int menu_option(void) {
    int option;
    // display the options available
    printf("\n---------Welcome to Calendar program main menu----------\n");
    printf("\t1. Display calendar\n");
    printf("\t2. Add a reminder\n");
    printf("\t3. Display all reminders\n");
    printf("\t4. Exit\n");
    // prompt option from user
    printf("Enter your option: ");
    scanf_s("%d", &option);
    printf("\n");
    return option;
}


// function for determine daycode
// get year as parameter
// find daycode for given year
int find_Day_Code(int year) {
    // define variables
    int daycode;
    int d1, d2, d3;
    // calculation for find daycode
    d1 = (year - 1.) / 4.0;
    d2 = (year - 1.) / 100.;
    d3 = (year - 1.) / 400.;
    // calculate the daycode
    daycode = (year + d1 - d2 + d3) % 7;
    return daycode;
}


// function for find leap year
// if given year is leap year
// return True else False
void is_Leap_Year(int year) {
    // check whether year is leap
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
        days_in_month[2] = 29;
    }
    else {
        days_in_month[2] = 28;
    }
}


// function for print calendar of a given year
// get year and daycode as the parameters
// display the calendar
void print_calendar(int year, int daycode) {

    // run until begin to end of the months of the year
    for (int m = 1; m < 13; m++) {
        // print month name and days
        printf("\n\n\n------------%s-------------", months[m]);
        printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n");
        // set the position of the 1st date in a month
        for (int day = 1; day <= 1 + daycode * 5; day++) {
            printf(" ");
        }
        // Print all the dates for a month
        for (int day = 0; day < days_in_month[m]; day++) {
            printf("%2d", day + 1);
            // Is day before Sat? Else start next line Sun.
            if (((day + 1) + daycode) % 7 > 0)
                printf("   ");
            else
                printf("\n ");
        }
        // Set the position to display for next month
        daycode = (daycode + days_in_month[m]) % 7;
    }
}

// function for print calendar of whole year
void display_calendar() {
    int year;
    printf("Please enter a year (ex: 2020): ");
    scanf_s("%d", &year);
    // find daycode for given year
    int daycode = find_Day_Code(year);
    // check whether if it is a leap year
    is_Leap_Year(year);
    // display callender
    print_calendar(year, daycode);
    printf("\n");
}

// function for print calendar of
// specific monthof given year
void print_month(int year, int month) {
    // find daycode for given year
    int daycode = find_Day_Code(year);
    // check whether if it is a leap year
    is_Leap_Year(year);
    // run until begin to end of the months of the year
    for (int m = 1; m < month; m++) {
        // Set the position to display for next month
        daycode = (daycode + days_in_month[m]) % 7;
    }
    // print month name and days
    printf("\n------------%d %s-------------",year, months[month]);
    printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    // set the position of the 1st date in a month
    for (int day = 1; day <= 1 + daycode * 5; day++) {
        printf(" ");
    }
    // Print all the dates for a month
    for (int day = 0; day < days_in_month[month]; day++) {
        printf("%2d", day + 1);
        // Is day before Sat? Else start next line Sun.
        if (((day + 1) + daycode) % 7 > 0)
            printf("   ");
        else
            printf("\n ");
    }
}

// function to find day of the week
void dayOfWeek(int month, int day, int year) {
    char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    //algorithm for find day of the week
    int a = (14 - month) / 12;
    double y = year - a;
    double   m = month + 12 * a - 2;
    int d = (int)(day + y + (int)(y / 4) - (int)(y / 100) + (int)(y / 400) + (int)((31 * m) / 12)) % 7;
    printf("\n%s %d,%d is a %s.\n",months[month],day,year,days[d]);
}


// main driver function
int main(void) {
    // define varibles
    int year,month,day,option,op;
    // run until user exit from the program
    while (1) {
        // get the user option
        option = menu_option();
        // if option is 1 display calendar
        if (option == 1) {
            // prompt user for selecting the desired option
            printf("\t1. Display all months of a year\n");
            printf("\t2. Display specific month of a year\n");
            printf("\t3. Display the day of the week any date falls on.\n");
            printf("Select option: ");
            scanf_s("%d", &op);
            // print calendar of whole given year
            if (op == 1) {
                display_calendar();
            }// print the calendar of
             // given year specific month
            else if (op == 2) {
                printf("Please enter a year and month (ex: yyyy mm ): ");
                scanf_s("%d %d",&year, &month);
                print_month(year, month);
            }// print the day of the week
             // for given date
            else if (op == 3) {
                printf("Please enter a year, month and day (ex: yyyy mm dd): ");
                scanf_s("%d %d %d", &year, &month, &day);
                dayOfWeek(month, day, year);
            }// if option invalid print error message
            else {
                printf("Invalid option. Try again!\n");
                exit(-1);
            }
        }// add a reminder
        else if (option == 2) {
            add_reminder();         
        }// display all reminders
        else if (option == 3) {  
            char* username[50];
            flush();
            printf("Enter the username: ");
            fgets(username, 50, stdin);
            display_Reminders(username);
        }// exit from the program
        else if (option == 4) {
            printf("Thank you for using calendar program.\n");
            break;
        }// print error message and exit
        else {
            printf("Please, enter the valid input!");
            exit(-1);
        }
    }
}