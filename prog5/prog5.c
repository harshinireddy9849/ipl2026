#include <stdio.h>
#include <stdlib.h>

union decision {
    unsigned char flags;
    struct {
        // Changed to unsigned char to match the 1-byte alignment of 'flags'
        unsigned char your_choice:1;          
        unsigned char your_mothers_choice:1;
        unsigned char your_fathers_choice:1;
        unsigned char socially_acceptable:1;
        unsigned char financially_viable:1;
        unsigned char do_you_aptitude:1;
        unsigned char do_you_likeit:1;
        unsigned char decision:1;            
    } field;
};

// Function Prototypes
union decision input();
void make_decision(union decision *d);
void print_decision(union decision d);
void print_conclusion_based_on_flags(union decision d);

int main() {
    union decision my_life;

    // 1. Gather choices and parameters
    my_life = input();

    // 2. Compute inner alignment and find the final outcome
    make_decision(&my_life);

    // 3. Print the contextual human narrative
    print_decision(my_life);

    // 4. Extract meaning directly from the byte signature
    print_conclusion_based_on_flags(my_life);

    return 0;
}

union decision input() {
    union decision d;
    int temp;
    
    // Clear out memory before assigning bits
    d.flags = 0;

    printf("=== LIFE DECISION INPUT ENGINE ===\n");
    printf("Answer with 1 (Yes) or 0 (No):\n\n");

    printf("Does your Mother approve? ");
    scanf("%d", &temp); d.field.your_mothers_choice = temp & 1;

    printf("Does your Father approve? ");
    scanf("%d", &temp); d.field.your_fathers_choice = temp & 1;

    printf("Is this choice socially acceptable? ");
    scanf("%d", &temp); d.field.socially_acceptable = temp & 1;

    printf("Is it financially viable/sustainable? ");
    scanf("%d", &temp); d.field.financially_viable = temp & 1;

    printf("Do you actually have the baseline aptitude for it? ");
    scanf("%d", &temp); d.field.do_you_aptitude = temp & 1;

    printf("Do you genuinely like doing it? ");
    scanf("%d", &temp); d.field.do_you_likeit = temp & 1;

    return d;
}

void make_decision(union decision *d) {
    /* 
       The Choice Expression Formula:
       Your choice is born when your aptitude overlaps with what you like.
    */
    d->field.your_choice = d->field.do_you_aptitude && d->field.do_you_likeit;

    /* 
       The Executive Ultimate Decision Formula:
       To execute, it must be something you want AND financially sustainable, OR
       it has complete unified backing from both parents to override constraints.
    */
    if ((d->field.your_choice && d->field.financially_viable) || 
        (d->field.your_mothers_choice && d->field.your_fathers_choice)) {
        d->field.decision = 1;
    } else {
        d->field.decision = 0;
    }
}

void print_decision(union decision d) {
    printf("\n============================================\n");
    printf("         THE DECISION NARRATIVE             \n");
    printf("============================================\n");

    // Evaluate Personal Alignment
    if (d.field.your_choice) {
        printf("You are personally aligned. You enjoy this pursuit and excel at it.\n");
    } else if (d.field.do_you_likeit && !d.field.do_you_aptitude) {
        printf("This is a passionate hobby. You love it, but you lack the natural skills right now.\n");
    } else if (!d.field.do_you_likeit && d.field.do_you_aptitude) {
        printf("This is a golden cage. You are highly skilled at it, but it bores you completely.\n");
    } else {
        printf("You have absolutely zero personal stake or capability here.\n");
    }

    // Evaluate External Dynamic
    if (d.field.your_mothers_choice && d.field.your_fathers_choice) {
        printf("Family backing is rock solid. Both your parents stand firmly behind you.\n");
    } else if (d.field.your_mothers_choice || d.field.your_fathers_choice) {
        printf("There is tension at home. Your parents are completely divided on this path.\n");
    } else {
        printf("You are completely on your own; your family does not agree with this direction.\n");
    }

    // Environmental Checks
    printf("Environment: This path is %s and %s.\n",
           d.field.financially_viable ? "economically sound" : "highly risky financially",
           d.field.socially_acceptable ? "socially embraced" : "counter-cultural / rebellious");

    // The Final Verdict
    printf("\n>>> VERDICT: ");
    if (d.field.decision) {
        printf("GREEN LIGHT. You are moving forward with this path.\n");
    } else {
        printf("RED LIGHT. This choice has been abandoned or vetoed.\n");
    }
}

void print_conclusion_based_on_flags(union decision d) {
    printf("\n============================================\n");
    printf("         BYTE SIGNATURE INTERPRETATION       \n");
    printf("============================================\n");
    
    printf("Raw Integer Profile (Flags Value): %d\n", d.flags);
    printf("Analysis: ");

    // Utilizing the raw byte map pattern to judge the type of existence
    if (d.flags == 0xFF) {
        printf("The Golden Child. You have achieved total absolute harmony across every matrix of life.\n");
    } else if (d.flags == 0x00) {
        printf("The Blank Canvas. Total existential stasis.\n");
    } else if (d.field.decision == 0 && (d.flags > 20)) {
        printf("The Compromised Martyr. Almost every circumstantial green light is on, yet you blocked it.\n");
    } else if (d.field.decision == 1 && !d.field.socially_acceptable && !d.field.financially_viable) {
        printf("The Renegade Idealist. Proceeding with zero funds and societal friction. Fasten your seatbelt.\n");
    } else if (d.field.your_choice && !d.field.decision) {
        printf("The Stifled Soul. You want it and have the skills, but external reality choked out the choice.\n");
    } else if (d.field.decision && !d.field.your_choice) {
        printf("The Passenger. You are carrying out a decision that you do not want or excel at.\n");
    } else {
        printf("Standard Pragmatist. Navigating normal, nuanced compromises of adult life.\n");
    }
    printf("============================================\n");
}