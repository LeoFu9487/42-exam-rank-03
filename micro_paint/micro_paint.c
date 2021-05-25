#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#define F(a,b,c) for(int a = b ; a < c ; ++a)
#define ARG {error("argument"); return 1;}
#define OP {error("Operation file corrupted"); return 1;}

int ft_strlen(char *str)
{
    return *str ? 1 + ft_strlen(str + 1) : 0;
}

void ft_putstr(char *str)
{
    write(1, str, ft_strlen(str));
}

void error(char *str)
{
    ft_putstr("Error: ");
    ft_putstr(str);
    ft_putstr("\n");
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

FILE *operation_file;

char background[300][300];

int width, height;
char background_char;

void print_result()
{
    for (int i = 0 ; i < height ; ++i)
    {
        for (int j = 0 ; j < width ; ++j) ft_putchar(background[i][j]);
        ft_putchar('\n');
    }
}

char r_or_R, r_char;
float x, y, w, h;

void empty_rectangle()
{
    F(i,0,height) F(j,0,width) if ((float)j >= x && (float)j <= x + w && (float)i >= y && (float)i <= y + h) if ((float)j - x < 1.0 || x + w - (float)j < 1.0 || (float)i - y < 1.0 || y + h - (float)i < 1.0) background[i][j] = r_char;
}

void filled_rectangle()
{
    F(i,0,height) F(j,0,width) if ((float)j >= x && (float)j <= x + w && (float)i >= y && (float)i <= y + h) background[i][j] = r_char;
}

int main(int ac, char **av)
{
    if (ac != 2) ARG
    if (!(operation_file = fopen(av[1], "r"))) OP
    if (fscanf(operation_file, "%d %d %c\n", &width, &height, &background_char) != 3) OP
    if (width <= 0 || width > 300 || height <= 0 || height > 300) OP
    F(i, 0, height) F(j, 0, width) background[i][j] = background_char;
    while (1)
    {
        switch(fscanf(operation_file, "%c %f %f %f %f %c\n", &r_or_R, &x, &y, &w, &h, &r_char))
        {
            case 6:
                if (w <= 0.0 || h <= 0.0) OP
                else if (r_or_R == 'r') empty_rectangle();
                else if (r_or_R == 'R') filled_rectangle();
                else OP
                break ;
            case -1:
                print_result();
                return 0;
                break ;
            default:
                OP
        }
    }
    return 1;
}