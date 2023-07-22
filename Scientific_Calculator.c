#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define maxm 200

int top = -1;
char stack[maxm];
char infix[maxm];
char postfix[maxm];

int isEmpty();
int isFull();
char peek();
char pop();
int space(char c);
void push(char oper);
int precedence(char ch);
void infix_to_postfix(char infix[]);
double postfix_eval(char postfix[]);

int isEmpty() {
    return top == -1;
}

int isFull() {
    return top == maxm - 1;
}

char peek() {
    return stack[top];
}

char pop() {
    if (isEmpty())
        return -1;
    char ch = stack[top];
    top--;
    return ch;
}

void push(char oper) {
    if (isFull())
        printf("Stack Full");
    else {
        top++;
        stack[top] = oper;
    }
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

void infix_to_postfix(char infix[]) {
    int i, j = 0;
    char symbol, next;
    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];
        if(!space(symbol)){
            switch (symbol) {
            case '(':
                push(symbol);
                break;
            case ')':
                while ((next = pop()) != '(')
                    postfix[j++] = next;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while (!isEmpty() && precedence(peek()) >= precedence(symbol))
                    postfix[j++] = pop();
                push(symbol);
                break;
            default:
                postfix[j++] = symbol;
            }
        }
    }
    while (!isEmpty())
        postfix[j++] = pop();
    postfix[j] = '\0';
}

double postfix_eval(char postfix[]) {
    int i;
    for (i = 0; i < strlen(postfix); i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9')
            push(postfix[i] - '0');
        else {
            int a = pop();
            int b = pop();
            switch (postfix[i]) {
                case '+':
                    push(b + a);
                    break;
                case '-':
                    push(b - a);
                    break;
                case '*':
                    push(b * a);
                    break;
                case '/':
                    push(b / a);
                    break;
                case '^':
                    push(pow(b, a));
                    break;
            }
            }
        }
        return pop();
    }

double prefix_eval(char prefix[]) {
int len;
int res, i;
len = strlen(prefix);
for (i = len - 1; i >= 0; i--) {
    if (isdigit(prefix[i])) {
        push(prefix[i] - '0');
    } else {
        int opp1 = pop();
        int opp2 = pop();
        switch (prefix[i]) {
            case '+':
                push(opp1 + opp2);
                break;
            case '-':
                push(opp1 - opp2);
                break;
            case '*':
                push(opp1 * opp2);
                break;
            case '/':
                push(opp1 / opp2);
                break;
            case '^':
                res = pow(opp1, opp2);
                push(res);
                break;
            }
        }
    }
    return pop();
}

int space(char c)
{
    if(c == ' ' || c == '\t' || c == '\n')
        return 1;
    else
        return 0;
}

void removeSpaces(char* str) {
    int count = 0;
    
    for (int i = 0; str[i]; i++) {
        if (!isspace(str[i])) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

// void ClearBuffer() {
//     int c;
//     while ((c = getchar()) != '\n' && c != EOF) {
//         continue;
//     }
// }

// void removeNewline(char* str) {
//     int len = strlen(str);
//     if (str[len - 1] == '\n') {
//         str[len - 1] = '\0';
//     }
// }

typedef struct {
    double real;
    double imaginary;
} Complex;

Complex addComplex(Complex num1, Complex num2) {
    Complex result;
    result.real = num1.real + num2.real;
    result.imaginary = num1.imaginary + num2.imaginary;
    return result;
}

Complex subtractComplex(Complex num1, Complex num2) {
    Complex result;
    result.real = num1.real - num2.real;
    result.imaginary = num1.imaginary - num2.imaginary;
    return result;
}

Complex multiplyComplex(Complex num1, Complex num2) {
    Complex result;
    result.real = (num1.real * num2.real) - (num1.imaginary * num2.imaginary);
    result.imaginary = (num1.real * num2.imaginary) + (num1.imaginary * num2.real);
    return result;
}

Complex divideComplex(Complex num1, Complex num2) {
    Complex result;
    double denominator = (num2.real * num2.real) + (num2.imaginary * num2.imaginary);
    result.real = ((num1.real * num2.real) + (num1.imaginary * num2.imaginary)) / denominator;
    result.imaginary = ((num1.imaginary * num2.real) - (num1.real * num2.imaginary)) / denominator;
    return result;
}

typedef struct {
    double magnitude;
    double angle;
} Polar;

Polar convertToPolar(Complex complex) {
    Polar polar;
    polar.magnitude = sqrt(complex.real * complex.real + complex.imaginary * complex.imaginary);
    polar.angle = atan2(complex.imaginary, complex.real);
    return polar;
}

unsigned long long factorial(int n) {
    if (n == 0) {
        return 1;
    } else if (n > 0 && n <= 65){
        return n * factorial(n - 1);
    }
    else {
        printf("Sorry, the factorial of %d cannot be calculated!\n", n);
        exit(1);
    }
}

void matrixAddition(int m, int n) {
    int mat1[m][n], mat2[m][n], result[m][n];

    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element (%d,%d): ", i, j);
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element (%d,%d): ", i, j);
            scanf("%d", &mat2[i][j]);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    printf("Result of matrix addition:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }
}

void matrixSubtraction(int m, int n) {
    int mat1[m][n], mat2[m][n], result[m][n];

    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element (%d,%d): ", i, j);
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element (%d,%d): ", i, j);
            scanf("%d", &mat2[i][j]);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }

    printf("Result of matrix subtraction:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }
}

void matrixMultiplication() {
    int m1, n1, m2, n2;

    printf("Enter the dimensions of the first matrix (m1 n1): ");
    scanf("%d %d", &m1, &n1);
    printf("Enter the dimensions of the second matrix (m2 n2): ");
    scanf("%d %d", &m2, &n2);

    if (n1 != m2) {
        printf("Invalid dimensions for matrix multiplication!\n");
        return;
    }

    int mat1[m1][n1], mat2[m2][n2], result[m1][n2];

    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n1; j++) {
            printf("Enter element (%d,%d): ", i, j);
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < m2; i++) {
        for (int j = 0; j < n2; j++) {
            printf("Enter element (%d,%d): ", i, j);
            scanf("%d", &mat2[i][j]);
        }
    }

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    printf("Result of matrix multiplication:\n");
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }
}

void matrixTranspose(int m, int n) {
    int mat[m][n], transposed[n][m];

    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element (%d,%d): ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            transposed[i][j] = mat[j][i];
        }
    }

    printf("Transposed matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d\t", transposed[i][j]);
        }
        printf("\n");
    }
}

void matrixConjugate(int m, int n) {
    int mat[m][n], conjugate[m][n];

    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element (%d,%d): ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            conjugate[i][j] = -mat[i][j];
        }
    }

    printf("Conjugate matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", conjugate[i][j]);
        }
        printf("\n");
    }
}

long long decimalToBinary(int decimal) {
    long long binary = 0;
    int remainder, i = 1;

    while (decimal != 0) {
        remainder = decimal % 2;
        decimal /= 2;
        binary += remainder * i;
        i *= 10;
    }
    return binary;
}

int binaryToDecimal(long long binary) {
    int decimal = 0, i = 0, remainder;

    while (binary != 0) {
        remainder = binary % 10;
        binary /= 10;
        decimal += remainder * pow(2, i);
        ++i;
    }
    return decimal;
}

void decimalToHexadecimal(int decimal) {
    char hexadecimal[100];
    int i = 0, remainder;

    while (decimal != 0) {
        remainder = decimal % 16;

        if (remainder < 10)
            hexadecimal[i++] = remainder + 48;
        else
            hexadecimal[i++] = remainder + 55;

        decimal /= 16;
    }
    printf("Hexadecimal: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%c", hexadecimal[j]);

    printf("\n");
}

int hexadecimalToDecimal(char hexadecimal[]) {
    int decimal = 0, digit, i = 0;

    while (hexadecimal[i]) {
        if (hexadecimal[i] >= '0' && hexadecimal[i] <= '9')
            digit = hexadecimal[i] - '0';
        else if (hexadecimal[i] >= 'A' && hexadecimal[i] <= 'F')
            digit = hexadecimal[i] - 'A' + 10;
        else if (hexadecimal[i] >= 'a' && hexadecimal[i] <= 'f')
            digit = hexadecimal[i] - 'a' + 10;
        else {
            printf("Error: Invalid input for hexadecimal conversion!\n");
            exit(1);
        }
        decimal = decimal * 16 + digit;
        i++;
    }
    return decimal;
}

int decimalToOctal(int decimal) {
    int octal = 0, i = 1;

    while (decimal != 0) {
        octal += (decimal % 8) * i;
        decimal /= 8;
        i *= 10;
    }
    return octal;
}

int octalToDecimal(int octal) {
    int decimal = 0, i = 0;

    while (octal != 0) {
        decimal += (octal % 10) * pow(8, i);
        ++i;
        octal /= 10;
    }
    return decimal;
}

void UnitConversion();
void ScientificCalc();

double poundsToKilograms(double pounds) {
    return pounds * 0.453592;
}

double kilogramsToPounds(double kilograms) {
    return kilograms / 0.453592;
}

double inchesToCentimeters(double inches) {
    return inches * 2.54;
}

double centimetersToInches(double centimeters) {
    return centimeters / 2.54;
}

double squareFeetToSquareMeters(double squareFeet) {
    return squareFeet * 0.092903;
}

double squareMetersToSquareFeet(double squareMeters) {
    return squareMeters / 0.092903;
}

double gallonsToLiters(double gallons) {
    return gallons * 3.78541;
}

double litersToGallons(double liters) {
    return liters / 3.78541;
}

double minutesToSeconds(double minutes) {
    return minutes * 60;
}

double secondsToMinutes(double seconds) {
    return seconds / 60;
}

double kilometersPerHourToMetersPerSecond(double kmPerHour) {
    return kmPerHour * 0.277778;
}

double metersPerSecondToKilometersPerHour(double mPerSecond) {
    return mPerSecond / 0.277778;
}

double pascalToAtmosphere(double pascal) {
    return pascal / 101325;
}

double atmosphereToPascal(double atmosphere) {
    return atmosphere * 101325;
}

double joulesToCalories(double joules) {
    return joules / 4.184;
}

double caloriesToJoules(double calories) {
    return calories * 4.184;
}

double wattsToHorsepower(double watts) {
    return watts / 745.7;
}

double horsepowerToWatts(double horsepower) {
    return horsepower * 745.7;
}

double newtonsToPoundForce(double newtons) {
    return newtons * 0.224809;
}

double poundForceToNewtons(double poundForce) {
    return poundForce / 0.224809;
}

double degreesToRadians(double degrees) {
    return degrees * 0.0174533;
}

double radiansToDegrees(double radians) {
    return radians / 0.0174533;
}

void Continue() {
    char option;
    printf("\nDo you want to continue? (y/n): ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard characters
    }
    scanf(" %c", &option);
    
    if (option == 'y' || option == 'Y') {
        ScientificCalc();
    }
    else if (option == 'n' || option == 'N') {
        printf("\nThank you for using the calculator.\n");
        exit(0);
    }
    else {
        printf("Invalid option. Please try again.\n");
        Continue();
    }
}

void ScientificCalc(){
    double num1, num2;
    Complex complex1, complex2, result;
    int choice,number,m,n;

    start: // Checkpoint for starting the program
    printf("\n******** SCIENTIFIC CALCULATOR ********\n");
    printf("\n");
    printf("========================================\n");
    printf("\n");
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
    printf("5. Power (^)\n");
    printf("6. Square Root (sqrt)\n");
    printf("7. Exponential (e^x)\n");
    printf("8. Natural Logarithm (ln)\n");
    printf("9. Logarithm (log10)\n");
    printf("10. Sine (sin)\n");
    printf("11. Cosine (cos)\n");
    printf("12. Tangent (tan)\n");
    printf("13. Arcsine (sin^-1)\n");
    printf("14. Arccosine (cos^-1)\n");
    printf("15. Arctangent (tan^-1)\n");
    printf("16. Hyperbolic sine (sinh)\n");
    printf("17. Hyperbolic cosine (cosh)\n");
    printf("18. Hyperbolic tangent (tanh)\n");
    printf("19. 10 raised to x (10^x)\n");
    printf("20. 2 raised to x (2^x)\n");
    printf("21. Evaluate Infix Expression\n");
    printf("22. Evaluate Prefix Expression\n");
    printf("23. Evaluate Postfix Expression\n");
    printf("24. Complex Addition\n");
    printf("25. Complex Subtraction\n");
    printf("26. Complex Multiplication\n");
    printf("27. Complex Division\n");
    printf("28. Convert from comlpex (a+bi) to polar (r,theta)\n");
    printf("29. Factorial (n!)\n");
    printf("30. Matrix Addition\n");
    printf("31. Matrix Subtraction\n");
    printf("32. Matrix Multiplication\n");
    printf("33. Matrix Transpose\n");
    printf("34. Matrix Conjugate\n");
    printf("35. Decimal to Binary\n");
    printf("36. Binary to Decimal\n");
    printf("37. Decimal to Hexadecimal\n");
    printf("38. Hexadecimal to Decimal\n");
    printf("39. Decimal to Octal\n");
    printf("40. Octal to Decimal\n");
    printf("41. Unit Conversions\n");
    printf("42. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter two numbers: ");
            scanf("%lf %lf", &num1, &num2);
            printf("Sum = %.2lf\n", num1 + num2);
            Continue();
            break;

        case 2:
            printf("Enter two numbers: ");
            scanf("%lf %lf", &num1, &num2);
            printf("Difference = %.2lf\n", num1 - num2);
            Continue();
            break;

        case 3:
            printf("Enter two numbers: ");
            scanf("%lf %lf", &num1, &num2);
            printf("Product = %.2lf\n", num1 * num2);
            Continue();
            break;

        case 4:
            printf("Enter two numbers: ");
            scanf("%lf %lf", &num1, &num2);
            printf("Quotient = %.2lf\n", num1 / num2);
            Continue();
            break;

        case 5:
            printf("Enter the base number: ");
            scanf("%lf", &num1);
            printf("Enter the exponent: ");
            scanf("%lf", &num2);
            printf("Result = %.2lf\n", pow(num1, num2));
            Continue();
            break;

        case 6:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("Square Root = %.2lf\n", sqrt(num1));
            Continue();
            break;

        case 7:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("Exponential = %.2lf\n", exp(num1));
            Continue();
            break;

        case 8:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("Natural Logarithm = %.2lf\n", log(num1));
            Continue();
            break;

        case 9:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("Logarithm (base 10) = %.2lf\n", log10(num1));
            Continue();
            break;

        case 10:
            printf("Enter an angle in radians: ");
            scanf("%lf", &num1);
            printf("Sine = %.2lf\n", sin(num1));
            Continue();
            break;

        case 11:
            printf("Enter an angle in radians: ");
            scanf("%lf", &num1);
            printf("Cosine = %.2lf\n", cos(num1));
            Continue();
            break;

        case 12:
            printf("Enter an angle in radians: ");
            scanf("%lf", &num1);
            printf("Tangent = %.2lf\n", tan(num1));
            Continue();
            break;

        case 13:
            printf("Enter a value between -1 and 1: ");
            scanf("%lf", &num1);
            printf("Arcsine = %.2lf\n", asin(num1));
            Continue();
            break;

        case 14:
            printf("Enter a value between -1 and 1: ");
            scanf("%lf", &num1);
            printf("Arccosine = %.2lf\n", acos(num1));
            Continue();
            break;

        case 15:
            printf("Enter a value: ");
            scanf("%lf", &num1);
            printf("Arctangent = %.2lf\n", atan(num1));
            Continue();
            break;

        case 16:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("sinh(%.2lf) = %.2lf\n", num1, sinh(num1));
            Continue();
            break;

        case 17:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("cosh(%.2lf) = %.2lf\n", num1, cosh(num1));
            Continue();
            break;

        case 18:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("tanh(%.2lf) = %.2lf\n", num1, tanh(num1));
            Continue();
            break;

        case 19:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("10 raised to %.2lf = %.2lf\n", num1, pow(10, num1));
            Continue();
            break;

        case 20:
            printf("Enter a number: ");
            scanf("%lf", &num1);
            printf("2 raised to %.2lf = %.2lf\n", num1, pow(2, num1));
            Continue();
            break;

        case 21: 
            printf("Enter the infix expression: ");
            char infixExpression[maxm];
            scanf_s("%s", infixExpression, maxm);
            removeSpaces(infixExpression);
            infix_to_postfix(infixExpression);
            double x = postfix_eval(postfix);
            printf("Result = %.2lf\n",x);
            Continue();
            break;

        case 22: 
            printf("Enter the prefix expression: ");
            char prefixExpression[maxm];
            scanf_s("%s", prefixExpression, maxm);
            removeSpaces(prefixExpression);
            double y = prefix_eval(prefixExpression);
            printf("Result = %.2lf\n", y);
            Continue();
            break;

        case 23: 
            printf("Enter the postfix expression: ");
            char postfixExpression[maxm];
            scanf_s("%s", postfixExpression, maxm);
            removeSpaces(postfixExpression);
            double z = postfix_eval(postfixExpression);
            printf("Result = %.2lf\n",z);
            Continue();
            break;

        case 24:
            printf("Enter the real and imaginary parts of the first complex number: ");
            scanf("%lf %lf", &complex1.real, &complex1.imaginary);
            printf("Enter the real and imaginary parts of the second complex number: ");
            scanf("%lf %lf", &complex2.real, &complex2.imaginary);
            result = addComplex(complex1, complex2);
            printf("Sum = %.2lf + %.2lfi\n", result.real, result.imaginary);
            Continue();
            break;

        case 25:
            printf("Enter the real and imaginary parts of the first complex number: ");
            scanf("%lf %lf", &complex1.real, &complex1.imaginary);
            printf("Enter the real and imaginary parts of the second complex number: ");
            scanf("%lf %lf", &complex2.real, &complex2.imaginary);
            result = subtractComplex(complex1, complex2);
            printf("Difference = %.2lf + %.2lfi\n", result.real, result.imaginary);
            Continue();
            break;

        case 26:
            printf("Enter the real and imaginary parts of the first complex number: ");
            scanf("%lf %lf", &complex1.real, &complex1.imaginary);
            printf("Enter the real and imaginary parts of the second complex number: ");
            scanf("%lf %lf", &complex2.real, &complex2.imaginary);
            result = multiplyComplex(complex1, complex2);
            printf("Product = %.2lf + %.2lfi\n", result.real, result.imaginary);
            Continue();
            break;

        case 27:
            printf("Enter the real and imaginary parts of the first complex number: ");
            scanf("%lf %lf", &complex1.real, &complex1.imaginary);
            printf("Enter the real and imaginary parts of the second complex number: ");
            scanf("%lf %lf", &complex2.real, &complex2.imaginary);
            result = divideComplex(complex1, complex2);
            printf("Quotient = %.2lf + %.2lfi\n", result.real, result.imaginary);
            Continue();
            break;

        case 28:
            printf("Enter the real and imaginary parts of the complex number: ");
            scanf("%lf %lf", &complex1.real, &complex1.imaginary);
            Polar polar = convertToPolar(complex1);
            printf("Polar Form: %.2f * e^(i * %.2f radians)\n", polar.magnitude, polar.angle);
            Continue();
            break;

        case 29:
            printf("Enter a number between 0 and 65: ");
            scanf("%d", &number);
            if (number < 0) {
                printf("Factorial is not defined for negative numbers.\n");
            } 
            else {
                unsigned long long fact = factorial(number);
                printf("Factorial of %d = %llu\n", number, fact);
            }
            Continue();
            break;

        case 30:
            printf("Enter the dimensions of the matrices (m, n): ");
            scanf("%d %d", &m, &n);
            matrixAddition(m, n);
            Continue();
            break;

        case 31:
            printf("Enter the dimensions of the matrices (m, n): ");
            scanf("%d %d", &m, &n);
            matrixSubtraction(m, n);
            Continue();
            break;

        case 32:
            matrixMultiplication();
            Continue();
            break;

        case 33:
            printf("Enter the dimensions of the matrix (m, n): ");
            scanf("%d %d", &m, &n);
            matrixTranspose(m, n);
            Continue();
            break;

        case 34:
            printf("Enter the dimensions of the matrix (m, n): ");
            scanf("%d %d", &m, &n);
            matrixConjugate(m, n);
            Continue();
            break;

        case 35:
            printf("Enter a decimal number: ");
            scanf("%d", &num1);
            printf("Binary = %lld\n\n", decimalToBinary((int)num1));
            Continue();
            break;

        case 36:
            printf("Enter a binary number: ");
            scanf("%lld", &num1);
            printf("Decimal = %d\n\n", binaryToDecimal((long long)num1));
            Continue();
            break;

        case 37:
            printf("Enter a decimal number: ");
            scanf("%d", &num1);
            decimalToHexadecimal((int)num1);
            printf("\n");
            Continue();
            break;

        case 38: 
            char hex[100];
            printf("Enter a hexadecimal number: ");
            scanf("%s", hex);
            printf("Decimal = %d\n\n", hexadecimalToDecimal(hex));
            Continue();
            break;

        case 39:
            printf("Enter a decimal number: ");
            scanf("%d", &num1);
            printf("Octal = %d\n\n", decimalToOctal((int)num1));
            Continue();
            break;

        case 40:
            printf("Enter an octal number: ");
            scanf("%d", &num1);
            printf("Decimal = %d\n\n", octalToDecimal((int)num1));
            Continue();
            break;

        case 41:
            UnitConversion();
            break;

        case 42:
            printf("Thank you for using the program!\n");
            break;

        default:
            printf("Invalid choice! Please choose a valid option.\n");
            printf("\n");
            goto start;
            break;
    }
}

void UnitConversion(){
    int choice1;
    double input, result;
    char choice2;
    printf("\n");
    printf("********** Scientific Calculator - Unit Conversions **********\n");
    printf("==============================================================\n");
    printf("\n");
    printf("1. Celsius to Fahrenheit\n");
    printf("2. Fahrenheit to Celsius\n");
    printf("3. Celsius to Kelvin\n");
    printf("4. Kelvin to Celsius\n");
    printf("5. Miles to Kilometers\n");
    printf("6. Kilometers to Miles\n");
    printf("7. Pounds to Kilograms\n");
    printf("8. Kilograms to Pounds\n");
    printf("9. Inches to Centimeters\n");
    printf("10. Centimeters to Inches\n");
    printf("11. Square Feet to Square Meters\n");
    printf("12. Square Meters to Square Feet\n");
    printf("13. Gallons to Liters\n");
    printf("14. Liters to Gallons\n");
    printf("15. Minutes to Seconds\n");
    printf("16. Seconds to Minutes\n");
    printf("17. Kilometers per Hour to Meters per Second\n");
    printf("18. Meters per Second to Kilometers per Hour\n");
    printf("19. Pascal to Atmosphere\n");
    printf("20. Atmosphere to Pascal\n");
    printf("21. Joules to Calories\n");
    printf("22. Calories to Joules\n");
    printf("23. Watts to Horsepower\n");
    printf("24. Horsepower to Watts\n");
    printf("25. Newtons to Pound Force\n");
    printf("26. Pound Force to Newtons\n");
    printf("27. Degrees to Radians\n");
    printf("28. Radians to Degrees\n");

    printf("Enter your choice: ");
    scanf("%d", &choice1);

    switch (choice1) {
        case 1:
            // Celsius to Fahrenheit
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = (input * 9 / 5) + 32;
            printf("%.2lf Celsius = %.2lf Fahrenheit\n", input, result);
            break;
        case 2:
            // Fahrenheit to Celsius
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = (input - 32) * 5 / 9;
            printf("%.2lf Fahrenheit = %.2lf Celsius\n", input, result);
            break;
        case 3:
            // Celsius to Kelvin
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = input + 273.15;
            printf("%.2lf Celsius = %.2lf Kelvin\n", input, result);
            break;
        case 4:
            // Kelvin to Celsius
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = input - 273.15;
            printf("%.2lf Kelvin = %.2lf Celsius\n", input, result);
            break;
        case 5:
            // Miles to Kilometers
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = input * 1.60934;
            printf("%.2lf Miles = %.2lf Kilometers\n", input, result);
            break;
        case 6:
            // Kilometers to Miles
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = input / 1.60934;
            printf("%.2lf Kilometers = %.2lf Miles\n", input, result);
            break;
        case 7:
            // Pounds to Kilograms
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = poundsToKilograms(input);
            printf("%.2lf Pounds = %.2lf Kilograms\n", input, result);
            break;
        case 8:
            // Kilograms to Pounds
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = kilogramsToPounds(input);
            printf("%.2lf Kilograms = %.2lf Pounds\n", input, result);
            break;
        case 9:
            // Inches to Centimeters
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = inchesToCentimeters(input);
            printf("%.2lf Inches = %.2lf Centimeters\n", input, result);
            break;
        case 10:
            // Centimeters to Inches
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = centimetersToInches(input);
            printf("%.2lf Centimeters = %.2lf Inches\n", input, result);
            break;
        case 11:
            // Square Feet to Square Meters
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = squareFeetToSquareMeters(input);
            printf("%.2lf Square Feet = %.2lf Square Meters\n", input, result);
            break;
        case 12:
            // Square Meters to Square Feet
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = squareMetersToSquareFeet(input);
            printf("%.2lf Square Meters = %.2lf Square Feet\n", input, result);
            break;
        case 13:
            // Gallons to Liters
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = gallonsToLiters(input);
            printf("%.2lf Gallons = %.2lf Liters\n", input, result);
            break;
        case 14:
            // Liters to Gallons
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = litersToGallons(input);
            printf("%.2lf Liters = %.2lf Gallons\n", input, result);
            break;
        case 15:
            // Minutes to Seconds
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = minutesToSeconds(input);
            printf("%.2lf Minutes = %.2lf Seconds\n", input, result);
            break;
        case 16:
            // Seconds to Minutes
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = secondsToMinutes(input);
            printf("%.2lf Seconds = %.2lf Minutes\n", input, result);
            break;
        case 17:
            // Kilometers per Hour to Meters per Second
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = kilometersPerHourToMetersPerSecond(input);
            printf("%.2lf Kilometers per Hour = %.2lf Meters per Second\n", input, result);
            break;
        case 18:
            // Meters per Second to Kilometers per Hour
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = metersPerSecondToKilometersPerHour(input);
            printf("%.2lf Meters per Second = %.2lf Kilometers per Hour\n", input, result);
            break;
        case 19:
            // Pascal to Atmosphere
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = pascalToAtmosphere(input);
            printf("%.2lf Pascal = %.2lf Atmosphere\n", input, result);
            break;
        case 20:
            // Atmosphere to Pascal
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = atmosphereToPascal(input);
            printf("%.2lf Atmosphere = %.2lf Pascal\n", input, result);
            break;
        case 21:
            // Joules to Calories
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = joulesToCalories(input);
            printf("%.2lf Joules = %.2lf Calories\n", input, result);
            break;
        case 22:
            // Calories to Joules
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = caloriesToJoules(input);
            printf("%.2lf Calories = %.2lf Joules\n", input, result);
            break;
        case 23:
            // Watts to Horsepower
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = wattsToHorsepower(input);
            printf("%.2lf Watts = %.2lf Horsepower\n", input, result);
            break;
        case 24:
            // Horsepower to Watts
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = horsepowerToWatts(input);
            printf("%.2lf Horsepower = %.2lf Watts\n", input, result);
            break;
        case 25:
            // Newtons to Pound Force
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = newtonsToPoundForce(input);
            printf("%.2lf Newtons = %.2lf Pound Force\n", input, result);
            break;
        case 26:
            // Pound Force to Newtons
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = poundForceToNewtons(input);
            printf("%.2lf Pound Force = %.2lf Newtons\n", input, result);
            break;
        case 27:
            // Degrees to Radians
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = degreesToRadians(input);
            printf("%.2lf Degrees = %.2lf Radians\n", input, result);
            break;
        case 28:
            // Radians to Degrees
            printf("Enter the input value: ");
            scanf("%lf", &input);
            result = radiansToDegrees(input);
            printf("%.2lf Radians = %.2lf Degrees\n", input, result);
            break;

        default:
            printf("Invalid choice!\n");
            printf("Do you want to continue? (y/n): ");
            scanf(" %c",&choice2);
            if(choice2=='y'||choice2=='Y'){
                UnitConversion();
            }
            else{
                ScientificCalc();
            }
            break;
        }
    }

int main() {
    ScientificCalc();
    return 0;
}