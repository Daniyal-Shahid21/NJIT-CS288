#include <stdio.h>

int main() {
    int number;
    printf("Welcome to the Number Analysis Program!\n");

    for (int i = 0; i < 5; i++) {
        printf("Please enter number %d: ", i + 1);
        scanf("%d", &number);
        
        if (number > 0) {
            printf("You entered: %d - Positive number\n", number);
        } else if (number < 0) {
            printf("You entered: %d - Negative number\n", number);
        } else {
            printf("You entered: %d - It's zero!\n", number);
        }
    }

    char name[50];
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Hello, %s! Let's proceed with the analysis.\n", name);

    float grade;
    printf("Enter your grade: ");
    scanf("%f", &grade);
    printf("Your grade is: %.2f\n", grade);
    
    int age;
    printf("How old are you? ");
    scanf("%d", &age);
    printf("You are %d years old.\n", age);

    printf("Let's do some calculations!\n");
    
    for (int i = 0; i < 3; i++) {
        int x, y;
        printf("Enter two numbers (x and y) for calculation %d: ", i + 1);
        scanf("%d %d", &x, &y);
        printf("Sum of %d and %d is: %d\n", x, y, x + y);
        printf("Difference of %d and %d is: %d\n", x, y, x - y);
        printf("Product of %d and %d is: %d\n", x, y, x * y);
        printf("Division of %d by %d is: %.2f\n", x, y, (float)x / y);
    }

    printf("Thanks for using the Number Analysis Program!\n");
    printf("Goodbye!\n");
    
    return 0;
}
