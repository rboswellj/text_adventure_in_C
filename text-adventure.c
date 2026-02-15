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
    char *outcome;
} character;

// Function prototypes
void startGame(void); // main game function, separate from main so it can be relaunched easily.
void characterCreation(character *c); // character creation function, takes a pointer to a character struct and fills it with user input
void intro(character *c); // Uses the details passed to the character struct to introduce the story
char* chooseDirection(character *c); // Takes the character struct, and then allows the character to choose a direction.
char* chooseApproach(character *c); // Takes the character struct, and then allows the character to choose an approach to the ogre based on the direction they chose.


// final battle function prototpes
// Class selection and previous choices will affect options available
char* battleOgreMage(character *c); // takes the character struct and determines battle outcome.
char* battleOgreWarrior(character *c); // takes the character struct and determines battle outcome.
char* battleOgreRogue(character *c); // takes the character struct and determines battle outcome.
char* battleOgreArcher(character *c); // takes the character struct and determines battle outcome.
// validation function prototype
int validateChoice(const char *choice, const char *option1, const char *option2);

// helpers
static void trim_newline(char *s); // removes trailing newline from fgets input
static char* dup_string(const char *s); // duplicates a string using dynamic memory allocation, returns pointer to new string
static void cleanup(character *c); // frees all dynamically allocated memory in the character struct and sets pointers to NULL

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

    // stores all of the character's information and choices, passed to all functions that need it.
    character hero;

    characterCreation(&hero); // creates the character and fills the struct with the character's information

    intro(&hero); // introduces the story using the character's information
    hero.direction = chooseDirection(&hero);  // allows the character to choose a direction and stores the choice in the struct
    hero.approach = chooseApproach(&hero);

    // determines the outcome of the battle based on the character's class and choices
    switch (hero.class[0]) {
        case 'W':
            hero.outcome = battleOgreWarrior(&hero);
            break;
        case 'M':
            hero.outcome = battleOgreMage(&hero);
            break;
        case 'R':
            hero.outcome = battleOgreRogue(&hero);
            break;
        case 'A':
            hero.outcome = battleOgreArcher(&hero);
            break;
    }


    // test print for the information in the struct.
    printf("\n%s the %s has chosen the %s path. They decided to %s\n", 
        hero.name, hero.class, hero.direction, hero.approach);

    printf("\n The outcome was %s!\n\n", hero.outcome);

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

void intro(character *c) {
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
    printf("\nYou have accepted a quest from the local %s's guild.\n", c->class);
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

char* battleOgreWarrior(character *c) {
    // battle logic for warrior class
    if (c->direction[0] == 'l') {
        // Left path, direct approach
        if (c->approach[0] == 'c') {
            printf("\nYou charge at the ogre, with your sword and shield raised.\n");
            printf("The ogre turns to face you.\n");
            printf("The ogre swings down on you with his club.\n");
            printf("You raise your shield just in time to block the attack, but the force of the blow knocks you back.\n");
            printf("You quickly recover and strike the ogre with your sword, dealing a powerful blow.\n");
            printf("After a fierce battle, you emerge victorious!\n");
            return "victory";
        // left path, sneak approach
        } else {
            printf("\nYou attempt to sneak up on the ogre and strike it from behind.\n");
            printf("However, you are wearing heavy armor and the clanging as you move alerts the ogre.\n");
            printf("The ogre turns around and sees you.\n");
            printf("The ogre is strong, and your attempt to sneak has left you vulnerable.\n");
            printf("The ogre leaps into action slamming down on you with its club.\n");
            printf("You attempt to block but are knocked prone on the ground.\n");
            printf("The last thing you see is the club swinging down on you.\n");
            printf("You are defeated.\n");
            return "defeat";
        }
    } else {
        // right path, direct approach
        if (c->approach[0] == 'c') {
            printf("\nYou charge at the ogre from the treeline, sword and shield in hand.\n");
            printf("The ogre is caught a bit off guard by your sudden attack, but readies himself.\n");
            printf("You get a clean hit on the ogre, but it is still standing.\n");
            printf("The ogre retaliates with a powerful strike, but your shield absorbs the blow.\n");
            printf("You retaliate with a clean strike to belly and defeat the ogre!\n");
            return "victory";
        // right path, sneak approach
        } else {
            printf("\nYou attempt to sneak up on the ogre and strike it from behind.\n");
            printf("However, you are wearing heavy armor and the clanging and rustling in the trees alerts the ogre.\n");
            printf("The ogre leaps into action slamming down on you with its club.\n");
            printf("You attempt to block but are knocked back against a tree.\n");
            printf("The wind is knocked out of you and you collapse on the ground in a daze.\n");
            printf("The last thing you see is the ogre leaping on to you with his club swinging down.\n");
            printf("You are defeated.\n");
            return "defeat";
        }
    }
        
}

char* battleOgreMage(character *c) {
    // battle logic for warrior class
    if (c->direction[0] == 'l') {
        // Left path, direct approach
        if (c->approach[0] == 'c') {
            printf("\nYou charge at the ogre, with your staff raised.\n");
            printf("The ogre turns to face you.\n");
            printf("You attempt to cast a fireball, but your incantation is cut short.\n");
            printf("The ogre hurls a rock, that hits you and interupts your casting");
            printf("The ogre leaps into the air towards you");
            printf("You quickly cast a shield spell.");
            printf("The club crashes down on your shield, absorbing some of the blow.");
            printf("The shield shatters as the ogre lands over you");
            printf("The last thing you see is the ogres club swinging towards you\n");
            return "defeat";
        // left path, sneak approach
        } else {
            printf("\nYou attempt to sneak up on the ogre and strike it from behind.\n");
            printf("You chant quitely under your breath.\n");
            printf("The ogre turns around just as you unleash an enormous fireball.\n");
            printf("The ogre is singed and burning but attempts to lunge at you.\n");
            printf("Fully prepared you launch a volley of magic missles as a follow up.\n");
            printf("The ogre falls to the ground, blasted to death.\n");
            return "victory";
        }
    } else {
        // right path, direct approach
        if (c->approach[0] == 'c') {
            printf("\nYou charge at the ogre from the treeline.\n");
            printf("The ogre is caught a bit off guard by your sudden approach, but readies himself.\n");
            printf("As you raise your staff and begin your incantation the ogre leaps.\n");
            printf("You launch the fireball at the incoming ogre, singing him, but he is still alive\n");
            printf("The ogre crashes down on you with his now burning club\n");
            printf("You feel the heat as the club approaches you, and then you feel nothing\n");
            return "defeat";
        // right path, sneak approach
        } else {
            printf("\nFrom the treeline you have plenty of time to prepare\n");
            printf("The ogre is unaware of your presence.\n");
            printf("As silently as you can manage you say your incantations.\n");
            printf("The ogre is startled as dark clouds form overhead.\n");
            printf("He looks up just in time to see a lightning bolt crash down upon him.\n");
            printf("The ogre collapses to the ground, singed and sparking.\n");
            return "victory";
        }
    }
        
}

char* battleOgreRogue(character *c) {
    // battle logic for warrior class
    if (c->direction[0] == 'l') {
        // Left path, direct approach
        if (c->approach[0] == 'c') {
            printf("\nYou charge at the ogre, with your daggers raised.\n");
            printf("The ogre turns to face you.\n");
            printf("As you rush forwards the ogre swings its huge club down on you.\n");
            printf("You are able to use your agility to barley roll out of the way.\n");
            printf("As you are attempting to stand you feel the club strike you in the side\n");
            printf("You are sent flying into the trees and strike hard against a large oak.\n");
            printf("Everything goes dark as you you struggle to breathe\n");
            return "defeat";
        // left path, sneak approach
        } else {
            printf("\nYou approach the Ogre quietly, daggers drawn.\n");
            printf("You watch the ground and are careful not to make a sound.\n");
            printf("Crouched behind the ogre you thrust your dagger between its ribs.\n");
            printf("Startled the ogre turns quickly, swinging its club.\n");
            printf("You nimbly duck out of the way, then thrust your dagger into the ogres heart.\n");
            printf("The ogre falls to the ground, dead.\n");
            return "victory";
        }
    } else {
        // right path, direct approach
        if (c->approach[0] == 'c') {
            printf("\nYou charge at the ogre from the treeline, daggers raised.\n");
            printf("The ogre is caught a bit off guard by your sudden approach, but readies himself.\n");
            printf("As you rush forward the ogre leaps, club raised.\n");
            printf("You manage to just barley roll out of the way as the ogre crashes to the ground\n");
            printf("You stumble to your feet, the ogre has his back to you.\n");
            printf("You rush forward with your daggers outstretched, prepared to strike\n");
            printf("The ogre quickly turns and its club strikes against your skull\n");
            printf("Everything goes dark\n");
            return "defeat";
        // right path, sneak approach
        } else {
            printf("\nFrom the treeline you have plenty of time to prepare and observe\n");
            printf("The ogre is unaware of your presence, feasting on a deer it has killed.\n");
            printf("Silently you approach, careful not to step on any sticks or twigs.\n");
            printf("The ogre is enjoying its meal as your dagger slides expertly between its ribs.\n");
            printf("You jump back as the ogre turns.\n");
            printf("The ogre struggles to raise its club, then collapses to the ground.\n");
            return "victory";
        }
    }      
}

char* battleOgreArcher(character *c) {
    // battle logic for warrior class
    if (c->direction[0] == 'l') {
        // Left path, direct approach
        if (c->approach[0] == 'c') {
            printf("\nYou rush towards the ogre with your bow drawn.\n");
            printf("The ogre turns to face you.\n");
            printf("You let loose your first arrow, and the ogre blocks with its arm.\n");
            printf("The arrow sinks into its left forearm as the ogre screams in pain.\n");
            printf("You notch a second arrow and begin to pull back to fire\n");
            printf("Before you can fire the carcass of the deer comes flying at you.\n");
            printf("You roll out of the way\n.");
            printf("Before you can stand the ogre leaps upon you.\n");
            printf("The club crashed down upon you\n");
            printf("Everything goes dark.\n");
            return "defeat";
        // left path, sneak approach
        } else {
            printf("\nYou approach the Ogre quietly, bow drawn.\n");
            printf("You watch the ground and are careful not to make a sound.\n");
            printf("You are able to line up the perfect shot.\n");
            printf("Your arrow pierces the ogre in the skull\n");
            printf("Startled the ogre turns quickly, swinging its club, wildly.\n");
            printf("You are far from the club's range and the ogre seems confused.\n");
            printf("As the Ogre flails wildly you line up your shot and release\n");
            printf("The arrow strikes between the ogre's eyes\n");
            printf("The ogre falls to the ground, dead.\n");
            return "victory";
        }
    } else {
        // right path, direct approach
        if (c->approach[0] == 'c') {
            printf("\nYou charge at the ogre from the treeline, bow raised, arrow knocked.\n");
            printf("The ogre is caught a bit off guard by your sudden approach, but readies himself.\n");
            printf("As you rush forward the ogre leaps, club raised.\n");
            printf("You manage to just barley roll out of the way as the ogre crashes to the ground\n");
            printf("You stumble to your feet, the ogre has his back to you.\n");
            printf("You pull your bow and, prepared to strike\n");
            printf("The ogre quickly turns and its club strikes against your skull\n");
            printf("Everything goes dark\n");
            return "defeat";
        // right path, sneak approach
        } else {
            printf("\nFrom the treeline you have plenty of time to prepare and observe\n");
            printf("The ogre is unaware of your presence, feasting on a deer it has killed.\n");
            printf("Silently you make your way to a better vantage point in the trees.\n");
            printf("The ogre is enjoying its meal as your first arrow strikes it in the neck.\n");
            printf("Startled and confused the ogre flails.\n");
            printf("The ogre hurls the deer in your general direction, but it does not reach your perch.\n");
            printf("Your second arrow strikes the ogre in the eye.\n");
            printf("After a bit more hopeless flailing the ogre collapses to the ground.\n");
            return "victory";
        }
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
    free(c->outcome);
    c->name = c->class = c->color = c->direction = c-> approach = c->outcome = NULL;
}
