/*
Robert Johnson
CSE-130-50-4262
2/15/2026
Story telling text adventure game.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Character struct, used to store all of the character's information and choices.
typedef struct {
    char *name;
    char *class;
    char *color;
    char *direction;
    char *approach;
    char *thirdChoice;
} character;

// Function prototypes
void startGame(void); // main game function, separate from main so it can be relaunched easily.
void characterCreation(character *c); // character creation function, takes a pointer to a character struct and fills it with user input
char* intro(character *c); // Uses the details passed to the character struct to introduce the story
char* chooseDirection(character *c); // Takes the character struct, and then allows the character to choose a direction.
char* chooseApproach(character *c); // Takes the character struct, and then allows the character to choose an approach to the ogre based on the direction they chose.

// validation function prototypes
int validateChoice(const char *choice, const char *option1, const char *option2);

// helpers
static void trim_newline(char *s);
static char* dup_string(const char *s);
static void cleanup(character *c);

int main(void) {
    startGame();
    return 0;
}

void startGame(void) {
    printf("\n\n");
    printf("===============================================================================\n");
    printf("Welcome to Simple Text Adventure!\n\n");
    printf("In this game, you will create a character and make choices that affect the outcome of your adventure.\n");
    printf("Let's get started!\n");
    printf("===============================================================================\n\n");

    // Stores: 0=name, 1=class, 2=color
    character hero;

    characterCreation(&hero);

    intro(&hero);
    hero.direction = chooseDirection(&hero);
    printf("\n%s the %s has chosen the %s path.\n", hero.name, hero.class, hero.direction);
    hero.approach = chooseApproach(&hero);
    printf("\n%s the %s has chosen the %s path. They decided to %s\n", hero.name, hero.class, hero.direction, hero.approach);

}

void characterCreation(character *myCharacter) {
    char nameBuf[10];
    char colorBuf[20];

    printf("Please enter your character's name: ");
    if (!fgets(nameBuf, sizeof(nameBuf), stdin)) {
        printf("Input error.\n");
        exit(1);
    }
    trim_newline(nameBuf);

    printf("\nWelcome, %s! Please select a character class:\n", nameBuf);
    printf("1. Warrior\n");
    printf("2. Mage\n");
    printf("3. Rogue\n");
    printf("4. Archer\n");

    int classChoice = 0;
    while (1) {
        printf("Enter 1-4: ");
        if (scanf("%d", &classChoice) == 1 && classChoice >= 1 && classChoice <= 4) {
            break;
        }
        printf("Invalid input.\n");
        while (getchar() != '\n') { } // clear input buffer
    }
    while (getchar() != '\n') { } // consume leftover newline after scanf

    const char *className =
        (classChoice == 1) ? "Warrior" :
        (classChoice == 2) ? "Mage" :
        (classChoice == 3) ? "Rogue" : "Archer";

    printf("You have chosen the %s class.\n", className);

    printf("\nPlease enter your favorite color: ");
    if (!fgets(colorBuf, sizeof(colorBuf), stdin)) {
        printf("Input error.\n");
        exit(1);
    }
    trim_newline(colorBuf);

    printf("Your favorite color is %s.\n\n", colorBuf);

    // Allocate and store safely (pointer + memory manipulation requirement)
    myCharacter->name = dup_string(nameBuf);
    myCharacter->class = dup_string(className);
    myCharacter->color = dup_string(colorBuf);
}

int validateChoice(const char *choice, const char *option1, const char *option2) {
    if (!choice || !choice[0]) return 0;

    // compare only first character, case-insensitive (simple)
    char c = (char)tolower((unsigned char)choice[0]);
    char o1 = (char)tolower((unsigned char)option1[0]);
    char o2 = (char)tolower((unsigned char)option2[0]);

    return (c == o1 || c == o2);
}

char* intro(character *c) {
    printf("\n");
    printf("===============================================================================\n");
    printf("You are a %s named %s.\n", c->class, c->name);

    switch (c->class[0]) {
        case 'W':
            printf("You are dressed in metal armor with a sword in one hand and a shield in the other.\n");
            printf("Your %s cape flutters in the wind.\n", c->color);
            break;
        case 'M':
            printf("You clutch a staff in your hand, brimming with magic power.\n");
            printf("Your %s robe billows around you.\n", c->color);
            break;
        case 'R':
            printf("You hold a gleaming dagger in each hand.\n");
            printf("Your %s cloak rests over your leather armor.\n", c->color);
            break;
        case 'A':
            printf("You hold a bow in your hands with an arrow knocked and ready.\n");
            printf("Your trusty %s quiver is strapped to your back.\n", c->color);
            break;
        default:
            break;
    }
}

char* chooseDirection(character *c) {
    char input[50];
    printf("\nYou have accepted a quest from the local adventurers guild.\n");
    printf("You venture into the nearby forest to defeat the ogre terrorizing the town.\n\n");
    printf("You stand at a crossroads in the forest.\n");
    printf("To the left you see a clear path with deep footprints that seem to belong to the ogre you seek.\n");
    printf("To the right you see a path that is more obscured by trees and would likely provide cover.\n");
    printf("Which path do you choose? (left or right): ");

    while (1) {
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Input error.\n");
            exit(1);
        }
        trim_newline(input);

        if (validateChoice(input, "left", "right")) break;
        printf("Invalid choice. Please enter 'left' or 'right': ");
    }

    if (tolower((unsigned char)input[0]) == 'l') {
        printf("\nYou take the left path and follow the footprints.\n");
        printf("This is no time for caution.\n");
        return "left";   
    } else {
        printf("\nYou take the right path and cautiously make your way through the forest.\n");
        printf("You hope to catch the ogre off guard.\n");
        return "right";  
    }
}

char* chooseApproach(character *c) {
    char input[50];

    if (tolower(c->direction[0]) == 'l') {
        printf("\nYou follow the footprints and eventually come across the ogre.\n");
        printf("It seems distracted by a deer it has killed and is feasting on it.\n");
        printf("Do you rush in head on or try to catch it off guard? (charge or sneak): ");

    } else {
        printf("\nYou cautiously make your way through the forest.\n");
        printf("You hear a distant growl through the trees.\n");
        printf("You find the ogre with his back to you, distracted by his meal.\n");
        printf("You have the element of surprise.\n");
        printf("Do you rush in head on or try to catch it off guard? (charge or sneak): ");
    }

    while (1) {
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Input error.\n");
            exit(1);
        }
        trim_newline(input);

        if (validateChoice(input, "charge", "sneak")) {
            break;
        }
        printf("Invalid choice. Please enter 'charge' or 'sneak': ");
    }

    if (tolower((unsigned char)input[0]) == 'c') {
        printf("\nYou charge at the ogre with your weapon drawn!\n");
        return "charge";
    } else {
        printf("\nYou approach cautiously, using the trees as cover.\n");
        return "sneak";
    }
    
}

// helpers

static void trim_newline(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

static char* dup_string(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char *p = (char*)malloc(n);
    if (!p) {
        printf("Out of memory.\n");
        exit(1);
    }
    memcpy(p, s, n);
    return p;
}

static void cleanup(character *c) {
    free(c->name);
    free(c->class);
    free(c->color);
    free(c->direction);
    free(c->approach);
    free(c->thirdChoice);
    c->name = c->class = c->color = c->direction = c-> approach = c->thirdChoice = NULL;
}
