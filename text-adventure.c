/*
Robert Johnson
CSE-130-50-4262
2/15/2026
Story telling text adventure game. 

The player will be able to choose from a list of options to progress through the story.
It will also allow for text input for certain choices. 
The story will be about a hero who is on a quest to save the world from an evil villain.   
The story will have multiple endings depending on the choices the player makes.

The assignment is to utilize strings and memory pointer manipulation 
to create a dynamic and engaging story.
*/

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void startGame();
void characterCreation();
char* intro(char *name, char *class, char *color);
char* firstChoice(char *direction);
char* secondChoice();
char* thirdChoice();
void ending1();
void ending2();
void ending3();

// validation function prototypes
int validateChoice(char *choice, char *option1, char *option2);

// global arrays
//sores character info
char **characterInfo[3][50];
char **characterChoices[3][50];


int main() {
    startGame();
    return 0;
}

void startGame() {
    printf("Welcome to Simple Text Adventure!\n");
    characterCreation();
    intro(characterInfo[0], characterInfo[1], characterInfo[2]);
    firstChoice(characterChoices[0][0]);
}

void characterCreation() {
    char name[50];
    printf("Please enter your character's name: ");
    fgets(name, sizeof(name), stdin);
    printf("Welcome, %s! please select a character class: \n", name);
    printf("1. Warrior\n");
    printf("2. Mage\n");
    printf("3. Rogue\n");
    printf("4. Archer\n");
    int classChoice;
    scanf("%d", &classChoice);
    printf("You have chosen the %s class.\n", (classChoice == 1) ? "Warrior" : (classChoice == 2) ? "Mage" : (classChoice == 3) ? "Rogue" : "Archer");
    printf("Please enter your favorite color: ");
    char color[20];
    scanf("%s", color);
    printf("Your favorite color is %s.\n", color);
    **characterInfo[0] = name;
    **characterInfo[1] = (classChoice == 1) ? "Warrior" : (classChoice == 2) ? 
        "Mage" : (classChoice ==3) ? "Rogue" : "Archer";
    **characterInfo[2] = color;
}

int validateChoice(char *choice, char *option1, char *option2) {
    return (choice[0] == option1[0] || choice[0] == option2[0]);
}

char* intro(char *name, char *class, char *color) {
    char input[50];
    printf("You are a %s named %s. \n", class, name);
    switch (class[0]) {
        case 'W':
            printf("You are dressed in metal armor with a sword in one hand and a shield in the other.\n");
            printf("Your %s cape flutters in the wind.\n", color);
            break;
        case 'M':
            printf("You clutch a staff in your hand, brimming with magic power.\n");
            printf("Your %s robe billows around you.\n", color);
            break;
        case 'R':
            printf("You hold a gleaming dagger in each hand.\n");
            printf("Your %s cloak rests over your leather armor.\n", color);
            break;
        case 'A':
            printf("You hold a bow in your hands with an arrow knocked and ready.\n");
            printf("Your trusty %s quiver is strapped to your back.\n", color);
            break;
    }  
    printf("You have accepted a quest from the local adventurers guild.\n");
    printf("You venture into the nearby forest and defeat an ogre that has been terrorizing the village.\n");
    printf("You stand at a crossroads in the forest.\n");
    printf("To the left you see deep footprints that seem to belong to the ogre you seek./n");
    printf("To the right you see a path that leads to a dark cave.\n");
    printf("The left path will likely take you directly to the ogre.\n");
    printf("The right path has lower visibility, but it may provide an opportunity\n");
    printf("to sneak up behind the ogre and catch it off guard.\n");
    printf("Which path do you choose? (left or right): ");
    scanf("%s", input);
    while (!validateChoice(input, "left", "right")) {
        printf("Invalid choice. Please enter 'left' or 'right': ");
        scanf("%s", input);
    }
    if (input[0] == 'l') {
        printf("You take the left path and follow the footprints.\n");
        printf("This is no time for caution.\n");
    } else {
        printf("You take the right path and cautiously make your way through the forest.\n");
        printf("You hope to catch the ogre off guard.\n");
    }
    return input;
}

char* firstChoice(char *direction) {
    if (direction[0] == 'l') {
        printf("You follow the footprints and eventually come across the ogre.\n");
        printf("The ogre is large and intimidating, but you are determined to defeat it.\n");
        printf("It seems distracted by a deer it has killed and is feasting on it.\n");
        printf("Do you choose to rush the ogre head on or try to catch it off guard? (charge or sneak): ");
        char input[50];
        scanf("%s", input);
        while (!validateChoice(input, "charge", "sneak")) {
            printf("Invalid choice. Please enter 'fight' or 'sneak': ");
            scanf("%s", input);
        }
        if (input[0] == 'c') {
            printf("You charge at the ogre and with your weapon drawn.\n");
        } else {
            printf("You approach cautiously.\n");
        }
    } else {
        printf("You cautiously make your way through the forest.\n");
        printf("You eventually begin to hear a distant growl through the trees.\n");
        printf("You follow the sound and see the ogre with his back to you.\n");
        printf("The ogre is large and intimidating, but you are determined to defeat it.\n");
        printf("It seems distracted, it has killed a deer and is feasting on it.\n");
        printf("The ogre is not paying attention to you, so you have the element of surprise on your side.\n");
        return "sneak";
    }
}




