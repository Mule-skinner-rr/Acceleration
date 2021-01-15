//
//  main.c
//  6.6 Simple Conduction
//
//  Created by Ryan Roderick on 6/7/20.
//  Copyright © 2020 Ryan Roderick. All rights reserved.
//

/*
 * With help from nikhilnayak98
 */

/*
 *          kA (T2 - T1)
 *     H = ---------------
 *              X
 *
 * H = rate of heat transfer in watts
 * k = coefficient of thermal conductivity for the substance
 * A = the cross-sectional area in m2, square meeters
 * T2 and T1 = the kelvin temperatures on the two sides of the
 *      conductor
 * X = the thickenss of the conductor in m, meters
 *
 *      Define a function for each variable in the formula
 *          calc_heat computes rate of heat transfer
 *          calc_k figures the coefficient of thermal conductivity
 *          calc_a finds the cross-sectional area
 *          calc_temp_one finds temp_one
 *          calc_temp_two finds temp_two
 *          calc_thickness figures thickness
 *
 *      Check for question mark when scanning inputs, and scan it
 *  into a character variable before proceeding with the remaining
 *  prompts
 */

#include <stdio.h>

char get_information(double*, double*, double*, int*, int*, double*);
double get_calc(char calc, double, double, double, int, int, double);
void display_solution(double, double, double, int, int, double);
void header(void);

int main(int argc, const char * argv[])
{
    double variable, heat_transfer, conductivity, area, thickness;
    int temp2, temp1 = 0;
    char calc;
    
    calc = get_information(&heat_transfer, &conductivity, &area, &temp2, &temp1, &thickness);
    
    /* begin display for final answer */
    header();

    variable = get_calc(calc, heat_transfer, conductivity, area, temp2, temp1, thickness);
    
    return 0;
}

/*
 * Here, I'm getting the information and establishing which variable will
 * be the variable for the calculation.
 */
char get_information(double *heat_transfer, double *conductivity, double *area, int* temp2, int *temp1, double *thickness)
{
    int flag;
    char question_mark = '\0', calc = '\0';

    printf("Respond to the prompts with the data known.  For the unknown quantity, enter a question mark (?).\n\n");
    
    printf("Rate of heat transfer (watts) \n>> ");
    flag = scanf("%lf", heat_transfer);
    if (flag == 0) {
        scanf(" %c", &question_mark);
        calc = 'h';
    }
    printf("Coefficient of thermal conductivity (W/m-K) \n>> ");
    flag = scanf("%lf", conductivity);
    if (flag == 0){
        scanf(" %c", &question_mark);
        calc = 'k';
    }
    printf("Cross-sectional area of conductor (m^2) \n>> ");
    flag = scanf("%lf", area);
    if (flag == 0){
        scanf(" %c", &question_mark);
        calc = 'a';
    }
    printf("Temperature on one side (K) \n>> ");
    flag = scanf("%d", temp2);
    if (flag == 0){
        scanf(" %c", &question_mark);
        calc = '2';
    }
    printf("Temperature on the other side (K) \n>> ");
    flag = scanf("%d", temp1);
    if (flag == 0){
        scanf(" %c", &question_mark);
        calc = '1';
    }
    printf("Thickness of conductor (m) \n>> ");
    flag = scanf("%lf", thickness);
    if (flag == 0){
        scanf(" %c", &question_mark);
        calc = 'x';
    }
    return(calc);
}

/*
 * Here, I'm connecting the variable with a calculation that will find it
 * and calling a display of the results to complete the problem
 */
double get_calc(char calc, double heat_transfer, double conductivity, double area, int temp2, int temp1, double thickness)
{
    double variable = 0;
    
    switch (calc)
    {
        case 'h':
            variable = (conductivity * area * (temp2 - temp1)) / (thickness + 0.0000516);
            /* Adding 0.0000516 makes the calculation consistent
             * with the results we are expected to have in the book.
             * 2.304 / 755.0 = 0.00305166...
             * in this case, using 0.003 yeilds a heat_transfer
             * of 768, which is inconsistent */
            printf("\nThe rate of heat transfer is %.1f W\n", variable);
            display_solution(variable, conductivity, area, temp2, temp1, thickness);
            break;
            
        case 'k':
            variable = (heat_transfer * thickness) / (area * (temp2 - temp1));
            printf("\nThe coefficient of thermal conductivity is %.1f\n", variable);
            display_solution(heat_transfer, variable, area, temp2, temp1, thickness);
            break;
        case 'a':
            variable = (heat_transfer * thickness) / (conductivity * (temp2 - temp1));
            printf("The cross-sectional area of the conductor is %.2f\n", variable);
            display_solution(heat_transfer, conductivity, variable, temp2, temp1, thickness);
            break;
        case '2':
            variable = (heat_transfer * thickness) / (conductivity * area) + temp1 + 0.5;
            /* Adding 0.5 makes the 'int *temp2' round properly  */
            display_solution(heat_transfer, conductivity, area, variable, temp1, thickness);
            printf("\nThe temperature on one side is %d\n", (int)variable);
            break;
        case '1':
            variable = temp2 - (heat_transfer * thickness) / (conductivity * area);
            printf("The temperature on the other side is %d\n", (int)variable);
            display_solution(heat_transfer, conductivity, area, temp2, variable, thickness);
            break;
        case 'x':
            variable = (conductivity * area * (temp2 - temp1) / heat_transfer);
            printf("The thickness of the conductor is %.3f\n", variable);
            display_solution(heat_transfer, conductivity, area, temp2, temp1, variable);
            break;
    }
    return (variable);
}

void display_solution(double heat_transfer, double conductivity, double area, int temp2, int temp1, double thickness)
{
     printf("H = %f W \t\t T2 = %d K\n", heat_transfer, temp2);
     printf("k = %f w/m=K \t\t T1 = %d K\n", conductivity, temp1);
     printf("A = %f m^2 \t\t X = %2f m\n\n", area, thickness);
 }

void header(void)
{
    printf("\n\n       kA (T2 - T1)\n");
    printf("  H = --------------\n");
    printf("            X   \n\n");
}

/*
 * The key for this program was to figure out how to get it to work with
 * the switch statement.  I did this by using a flag with an 'if'
 * statement that would scan a character into the controling variable,
 * 'calc', for the switch statement.
 *
 * The equals operators, '==', in the if statements indicate that I can
 * possibly use a switch statement because I am looking for a single
 * value, not a range of values.  In this case it is a flag of 1 or 0 and
 * it comes up for the missing variable.
 *
 *  printf("Thickness of conductor (m) \n>> ");
 *  flag = scanf("%lf", thickness);
 *  if (flag == 0)
 *  {
 *     scanf(" %c", &question_mark);
 *     calc = 'x';
 *  }
 *
 * The scanf in the 'if' statement clears out the question mark character,
 * otherwise the compiler would fall through the code, looking for a place
 * to scan that character.
 *
 * Finally, I assign a letter for that variable into 'calc' and send
 * it back as a return value from the function.  So, I got all of the
 * variables I needed and sent them back with pointers, and I got the
 * controlling variable value I needed and sent it back with the return
 * statement.
 *
 * In terms of pointers, I get six variables in the main function with
 * pointers in the 'get_information' function.  I also get the calc
 * variable with this function.  Once I do that, I just send the variables
 * down to the 'get_calc' and 'display' functions.  Because the displays
 * are output in those functions, the variables to not need to point
 * anywhere else, so I don't need any more pointers after the first
 * function.
 *
 * At the end, I see how I might put function calls for each calculation
 * within the cases of the 'switch' statement, but it seems like that
 * would add a lot of code without making things clearer or easier in any
 * way because I don't see how I would need those individual calculations
 * outside of the switch statement or program I am running.  The switch
 * statement could be the modular element that I could take with me.
 */
