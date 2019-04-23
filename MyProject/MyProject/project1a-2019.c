// preprocessor directive to support printing to the display

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 4

// the main program
void delay(unsigned long unfixedValue)
{
    volatile unsigned long a = 0;
    volatile unsigned int b = 0;
    for (a = unfixedValue; a > 0; a--)
    {
        for (b = 0; b < 100000; b++);
    }
    return;
}

void f1Data(unsigned long delay1)
{
    volatile int a = 0;
    const volatile int b = 0;
    for(long timer = 0; timer < delay1; timer++)
    {
        a = b + 1;
    }
}

void f2Clear(unsigned long delay2)
{
    volatile int a = 0;
    const volatile int b = 0;
    printf("     \r");
    for(long timer = 0; timer < delay2; timer++)
    {
        a = b + 1;
    }
}

void display(char letters[], int size)
{
  int i;
  for(i = 0; i < size; i++)
  {
    printf("%c", letters[i]);  // print a character
    fflush(stdout);  // add output to console
  }
}

void undisplay(int size)
{
  int i;
  for(i = 0; i < size; i++)
  {
    printf(" ");  // print a space character
    fflush(stdout);  // add output to console
  }
}

/*void app4()
{
    char letters[SIZE] = "ABCD";
    while(1)
    {
        display(letters, SIZE);
        printf("%c", 0x0d);
        delay(1000);
        undisplay(SIZE);
        printf("%c", 0x0d);
        delay(1000);
    }
}*/
/*int main()
{
    char letters[SIZE] = "ABCD";
    char temp[SIZE] = "    ";
    while(1)
    {
        for(int i = 0; i < SIZE; i++)
        {
            if(i == 0)
            {
               temp[0] = letters[0];
               temp[1] = ' ';
               temp[2] = letters[2];
               temp[3] = ' ';
            } else if(i == 2)
            {
               temp[0] = ' ';
               temp[1] = letters[1];
               temp[2] = ' ';
               temp[3] = letters[3];
            } else
            {
               temp[0] = ' ';
               temp[1] = ' ';
               temp[2] = ' ';
               temp[3] = ' ';
            }

            display(temp, SIZE);
            printf("%c", 0x0d);
            delay(5000);
        }
    }
    return 0;
}*/

int main()
{
    char letters[SIZE] = "  CD";
    while(1)
    {
        display(letters, SIZE);
        printf("%c", 0x0d);
        /*delay(5000);
        undisplay(SIZE/2);
        printf("%c", 0x0d);*/
        delay(5000);
    }
    return 0;
}

/*void app1()
{
    char temp[SIZE] = "ABCD";
    for(int j = 0; j < SIZE; j++)
    {
        for(int i = 0; i < SIZE; i++)
        {
            printf("%c", temp[i]);  // print a character
            fflush(stdout);  // add output to console
        }
        delay(1000);
    }
}*/

void f1Data(unsigned long *delay1, char[] passedString)
{
      for (volatile int i = 9; i >=0; i--)
      {
          myData[0] = i + '0';        //  convert the int i to ascii
          myData[1] = '\0';           //  terminate the string
          printf("%s ", passedString;
          fflush(stdout);
          delay(delay1);            //  delay so we can read the display
      }
      printf("%c", 0x0d);           //  print a carridge return
      fflush(stdout);
}

void f2Clear(unsigned long *delay2, char[] passedString)
{
      for (volatile int i = 0; i < 10; i++)
      {
          printf("%s ", passedString);
          fflush(stdout);
          delay(delay2);
      }

      printf("%c", 0x0d);           //  print a carridge return
      fflush(stdout);
}
