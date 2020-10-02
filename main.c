/* Nikhil Nayak wrote a solution for this problem.  In my solution the program uses pointers to get the information from the user.  Then, it uses a 'switch' statement to determine which calculation it needs to to in order to solve the head conductdion problem.
 Nikhil, or nikhilnayak98, posted solutions to the problems from "Problem Solving and Program Design in C" by Jerri R. Hanly and Elliott B. Koffman on GitHub in his 'CSE2041' repository. */
/*
 * Refactoring by Ryan Roderick
 * Refactor 2, with FUNCTIONS for EACH CALCULATION
 * Question 6, page 368, Hanly & Koffman:
 * Develop a collection of functions to solve simple
 * conduction problems using various forms of the
 * formula:
 *
 *          kA (T2 - T1)
 *     H = ---------------
 *              X
 *
 * where H is the rate of heat transfer in watts, k is
 * the coefficient of thermal conductivity for the
 * particular substance, A is the cross-sectional area
 * in m^2 (square meters), T2 and T1 are kelvin
 * tempertures on the two sides of the conductor, and
 * X is the thickness of the conductor in meters.
 *
 * Define a function for each variable in the formula.
 * For example, function calc_h would compute the rate
 * of heat transfer, calc_k would figure the
 * conductivity of thermal conductivity, calc_a would
 * find the cross-sectional area and so on.
 *
 * Develop a driver function that interacts with the
 * user in the following way [see program result].
 *
 * (Hint: Input of the question mark when looking for
 * a number will cause 'scanf' to return a value of 0.
 * Be sure to check for this and then scan the
 * question mark into a character variable before
 * proceeding with the remaining prompts.)
 */

#include <stdio.h>

double calc_h(double heat_transfer, double k, double area, double del_t, double m)
{
    heat_transfer = (k * area * del_t) / m;
    
    return(heat_transfer);
}

double calc_k(double heat_transfer, double k, double area, double del_t, double m)
{
    k = (heat_transfer * m) / (area * del_t);
    
    return(k);
}

double calc_a(double heat_transfer, double k, double area, double del_t, double m)
{
    area = (heat_transfer * m) / (k * del_t);
    
    return(area);
}

double calc_temp2(double heat_transfer, double k, double area, double temp1, double temp2, double m)
{
    temp2 = ((heat_transfer * m) / (k * area)) + temp1;
    
    return(temp2);
}

double calc_temp1(double heat_transfer, double k, double area, double temp1, double temp2, double m)
{
    temp1 = temp2 - ((heat_transfer * m) / (k * area));
    
    return(temp1);
}

double calc_m(double heat_transfer, double k, double area, double del_t, double m)
{
    m = (k * area * del_t) / heat_transfer;
    
    return(m);
}

char get_info(double*, double*, double*, double*, double*, double*);
void header(void);
double find_variable(char, double, double, double, double, double, double);
void display_solution(double, double, double, double, double, double);

void main()
{
    double variable, heat_transfer, conductivity, cross_area, temp2, temp1, thickness;
    char calc;
    
    calc = get_info(&heat_transfer, &conductivity, &cross_area, &temp2, &temp1, &thickness);
    
    header();
    
    variable = find_variable(calc, heat_transfer, conductivity, cross_area, temp2, temp1, thickness);
    
}
/*
 * Here, I'm getting the input information and
 * establishing which variable will be the variable for
 * the calculation.
 */
char get_info(double *heat_transfer, double *conductivity, double *area, double *temp2, double *temp1, double *thickness)
{
    int flag;
    char ch, calc = 0;
    
    printf("\nRespond to the prompts with the data known. For the unknown quantity, enter a question mark (?).");
    
    printf("\nRate of heat transfer (watts) >> ");
    flag = scanf("%lf", heat_transfer);
    if (flag == 0) {
        scanf(" %c", &ch);
        calc = 'h';
    }
    printf("\nCoefficient of thermal conductivity (W/m-K) >> ");
    flag = scanf("%lf", conductivity);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = 'k';
    }
    printf("\nCross-sectional area of conductor (m^2) >> ");
    flag = scanf("%lf", area);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = 'a';
    }
    printf("\nTemperature on one side (K) >> ");
    flag = scanf("%lf", temp2);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = '2';
    }
    printf("\nTemperature on other side (K) >> ");
    flag = scanf("%lf", temp1);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = '1';
    }
    printf("\nThickness of conductor (m) >> ");
    flag = scanf("%lf", thickness);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = 'x';
    }
    return(calc);
}

void header(void)
{
    printf("\n\n%5ckA (temp2 - temp1)", ' ');
    printf("\nH = ----------------");
    printf("\n%10cX", ' ');
}
/*
 * Here, I'm connecting the variable with its calculation
 * and calling a display of the results to complete the
 * problem.
 */
double find_variable(char calc, double heat_transfer, double k, double area, double temp2, double temp1, double m)
{
    double variable = 0.0;
    
    switch (calc)
    {
        case 'h':
            variable = calc_h(heat_transfer, k, area, (temp2 - temp1), m);
            printf("\n\nThe rate of heat transfer is %.1f W\n", variable);
            display_solution(variable, k, area, temp2, temp1, m);
            break;
            
        case 'k':
            variable = calc_k(heat_transfer, k, area, (temp2 - temp1), m);
            printf("\n\nThe coefficient of thermal conductivity is %.3f\n", variable);
            display_solution(heat_transfer, variable, area, temp2, temp1, m);
            break;
            
        case 'a':
            variable = calc_a(heat_transfer, k, area, (temp2 - temp1), m);
            printf("\n\nThe cross-sectional area of the conductor is %.3f\n", variable);
            display_solution(heat_transfer, k, variable, temp2, temp1, m);
            break;
            
        case '2':
            variable = calc_temp2(heat_transfer, k, area, temp1, temp2, m);
            printf("\n\nThe temperature on one side is %.0f\n", variable);
            display_solution(heat_transfer, k, area, variable, temp1, m);
            break;
            
        case '1':
            variable = calc_temp1(heat_transfer, k, area, temp1, temp2, m);
            printf("\n\nThe temperature on the other side is %.0f\n", variable);
            display_solution(heat_transfer, k, area, temp2, variable, m);
            break;
            
        case 'x':
            variable = calc_m(heat_transfer, k, area, (temp2 - temp1), m);
            printf("\n\nThe thickness of the conductor is %.3f\n", variable);
            display_solution(heat_transfer, k, area, temp2, temp1, variable);
            break;
    }
    return(variable);
}

void display_solution(double heat_transfer, double conductivity, double cross_area, double temp2, double temp1, double thickness)
{
    printf("\nH = %.1f W.", heat_transfer);
    printf("\nk = %.3f W/m-K.", conductivity);
    printf("\nA = %.3f m^2.", cross_area);
    printf("\ntemp2 = %.0f K.", temp2);
    printf("\ntemp1 = %.0f K.", temp1);
    printf("\nm = %.3f m.\n\n", thickness);
}

/*
 * What I learned: I can use the flag in an 'if'
 * statement to assign a value to a controlling
 * variable for a switch statement.
 *
 * Doing so allowed me to cut out many variables
 * and 'if/else' statements. And, I put each
 * calculation in a 'switch' statement because
 * they are all a version of the same equation.
 *
 */
