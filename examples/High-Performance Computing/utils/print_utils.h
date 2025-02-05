/**
 * @file    : print_utils.h
 * @brief   : Header file for printing utility in C/C++
 * @author  : David Blickenstorfer
 * 
 * @date 28/01/2025
 * @copyright Developed by David Blickenstorfer
 */

#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <stdio.h>
#include <errno.h> 

// Define standard ANSI color codes 
#define ANSI_RESET      "\033[0m"  //< Default text
#define ANSI_BLACK      "\033[30m" //< Black text
#define ANSI_RED        "\033[31m" //< Red text 
#define ANSI_GREEN      "\033[32m" //< Green text 
#define ANSI_YELLOW     "\033[33m" //< Yellow text 
#define ANSI_BLUE       "\033[34m" //< Blue text 
#define ANSI_MAGENTA    "\033[35m" //< Magenta text 
#define ANSI_CYAN       "\033[36m" //< Cyan text 
#define ANSI_WHITE      "\033[37m" //< White text 

// Define bold ANSI color codes
#define ANSI_BOLD         "\033[1;0m"   //< Default text 
#define ANSI_BOLD_BLACK   "\033[1;30m"  //< Black text
#define ANSI_BOLD_RED     "\033[1;31m"  //< Red text 
#define ANSI_BOLD_GREEN   "\033[1;32m"  //< Green text 
#define ANSI_BOLD_YELLOW  "\033[1;33m"  //< Yellow text 
#define ANSI_BOLD_BLUE    "\033[1;34m"  //< Blue text 
#define ANSI_BOLD_MAGENTA "\033[1;35m"  //< Magenta text
#define ANSI_BOLD_CYAN    "\033[1;36m"  //< Cyan text 
#define ANSI_BOLD_WHITE   "\033[1;37m"  //< White text

// Define underlined ANSI color codes
#define ANSI_UNDERLINED         "\033[4;0m"     //< Default text
#define ANSI_UNDERLINED_BLACK   "\033[4;30m"    //< Black text
#define ANSI_UNDERLINED_RED     "\033[4;31m"    //< Red text 
#define ANSI_UNDERLINED_GREEN   "\033[4;32m"    //< Green text 
#define ANSI_UNDERLINED_YELLOW  "\033[4;33m"    //< Yellow text 
#define ANSI_UNDERLINED_BLUE    "\033[4;34m"    //< Blue text 
#define ANSI_UNDERLINED_MAGENTA "\033[4;35m"    //< Magenta text
#define ANSI_UNDERLINED_CYAN    "\033[4;36m"    //< Cyan text 
#define ANSI_UNDERLINED_WHITE   "\033[4;37m"    //< White text 

// Define flash ANSI color codes
#define ANSI_FLASH          "\033[5;0m"     //< Default text
#define ANSI_FLASH_BLACK    "\033[5;30m"    //< Black text
#define ANSI_FLASH_RED      "\033[5;31m"    //< Red text 
#define ANSI_FLASH_GREEN    "\033[5;32m"    //< Green text 
#define ANSI_FLASH_YELLOW   "\033[5;33m"    //< Yellow text 
#define ANSI_FLASH_BLUE     "\033[5;34m"    //< Blue text 
#define ANSI_FLASH_MAGENTA  "\033[5;35m"    //< Magenta text
#define ANSI_FLASH_CYAN     "\033[5;36m"    //< Cyan text  
#define ANSI_FLASH_WHITE    "\033[5;37m"    //< White text 

/**
 * @name: print
 * @author: David Blickenstorfer
 * @brief: print given text with given color and type
 * @param color: char, determine the color of the text
 * 'd' : default
 * 'r' : red
 * 'g' : green
 * 'y' : yellow
 * 'b' : blue
 * 'm' : magenta
 * 'c' : cyan
 * 'k' : black
 * 'w' : white
 * @param type: char, determine the type of the text
 * 'd' : default
 * 'b' : bold
 * 'u' : underlined
 * 'f' : flashy
 * @param text: char*, the printing text
 */
void print(const char color, const char type, const char* text)
{
    char* print_setting;
    if(type == 'd'){
        switch(color)
        {
        case 'd':
            print_setting = ANSI_RESET;
            break;
        case 'r':
            print_setting = ANSI_RED;
            break;
        case 'g':
            print_setting = ANSI_GREEN;
            break;
        case 'y':
            print_setting = ANSI_YELLOW;
            break;
        case 'b':
            print_setting = ANSI_BLUE;
            break;
        case 'm':
            print_setting = ANSI_MAGENTA;
            break;
        case 'c':
            print_setting = ANSI_CYAN;
            break;
        case 'k':
            print_setting = ANSI_BLACK;
            break;
        case 'w':
            print_setting = ANSI_WHITE;
            break;
        default:
            perror("print : Invalid argument!");
            return;
        }
    } 
    else if(type == 'b'){
        switch(color)
        {
        case 'd':
            print_setting = ANSI_BOLD;
            break;
        case 'r':
            print_setting = ANSI_BOLD_RED;
            break;
        case 'g':
            print_setting = ANSI_BOLD_GREEN;
            break;
        case 'y':
            print_setting = ANSI_BOLD_YELLOW;
            break;
        case 'b':
            print_setting = ANSI_BOLD_BLUE;
            break;
        case 'm':
            print_setting = ANSI_BOLD_MAGENTA;
            break;
        case 'c':
            print_setting = ANSI_BOLD_CYAN;
            break;
        case 'k':
            print_setting = ANSI_BOLD_BLACK;
            break;
        case 'w':
            print_setting = ANSI_BOLD_WHITE;
            break;
        default:
            perror("print : Invalid argument!");
            return;
        }
    }else if(type == 'u'){
        switch(color)
        {
        case 'd':
            print_setting = ANSI_UNDERLINED;
            break;
        case 'r':
            print_setting = ANSI_UNDERLINED_RED;
            break;
        case 'g':
            print_setting = ANSI_UNDERLINED_GREEN;
            break;
        case 'y':
            print_setting = ANSI_UNDERLINED_YELLOW;
            break;
        case 'b':
            print_setting = ANSI_UNDERLINED_BLUE;
            break;
        case 'm':
            print_setting = ANSI_UNDERLINED_MAGENTA;
            break;
        case 'c':
            print_setting = ANSI_UNDERLINED_CYAN;
            break;
        case 'k':
            print_setting = ANSI_UNDERLINED_BLACK;
            break;
        case 'w':
            print_setting = ANSI_UNDERLINED_WHITE;
            break;
        default:
            perror("print : Invalid argument!");
            return;
        }
    }else if(type == 'f'){
        switch(color)
        {
        case 'd':
            print_setting = ANSI_FLASH;
            break;
        case 'r':
            print_setting = ANSI_FLASH_RED;
            break;
        case 'g':
            print_setting = ANSI_FLASH_GREEN;
            break;
        case 'y':
            print_setting = ANSI_FLASH_YELLOW;
            break;
        case 'b':
            print_setting = ANSI_FLASH_BLUE;
            break;
        case 'm':
            print_setting = ANSI_FLASH_MAGENTA;
            break;
        case 'c':
            print_setting = ANSI_FLASH_CYAN;
            break;
        case 'k':
            print_setting = ANSI_FLASH_BLACK;
            break;
        case 'w':
            print_setting = ANSI_FLASH_WHITE;
            break;
        default:
            perror("print : Invalid argument!");
            return;
        }
    }else{
        perror("print : Invalid argument!");
        return;
    }
    printf("%s%s%s", print_setting, text, ANSI_RESET);
}

/**
 * @name: print
 * @author: David Blickenstorfer
 * @brief: print given text with given color and type and go to
 * next line in terminal
 * @param color: char, determine the color of the text
 * 'r' : red
 * 'g' : green
 * 'y' : yellow
 * 'b' : blue
 * 'm' : magenta
 * 'c' : cyan
 * 'k' : black
 * 'w' : white
 * @param type: char, determine the type of the text
 * 'd' : default
 * 'b' : bold
 * 'u' : underlined
 * 'f' : flashy
 * @param text: char*, the printing text
 */
void println(const char color, const char type, const char* text)
{
    print(color, type, text);
    printf("\n");
}




#endif // PRINT_UTILS_H