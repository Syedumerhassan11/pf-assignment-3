#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeInventory(char*** speciesSupplies, int numSpecies);
void addSupplies(char*** speciesSupplies, int numSpecies, int* numSuppliesPerSpecies);
void updateSupply(char*** speciesSupplies, int speciesIndex, int supplyIndex);
void removeSpecies(char*** speciesSupplies, int* numSpecies, int* numSuppliesPerSpecies, int speciesIndex);
void displayInventory(char*** speciesSupplies, int numSpecies, int* numSuppliesPerSpecies);

int main() {
    int numSpecies;

    printf("Enter the number of species: ");
    scanf("%d", &numSpecies);

    char*** speciesSupplies = (char***)malloc(numSpecies * sizeof(char**));
    int* numSuppliesPerSpecies = (int*)calloc(numSpecies, sizeof(int));

    initializeInventory(speciesSupplies, numSpecies);

    int choice;
    do {
        printf("\n--- Pets in Heart Inventory Menu ---\n");
        printf("1. Add Supplies\n");
        printf("2. Update Supply\n");
        printf("3. Remove Species\n");
        printf("4. Display Inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addSupplies(speciesSupplies, numSpecies, numSuppliesPerSpecies);
                break;
            case 2: {
                int speciesIndex, supplyIndex;
                printf("Enter species index (0 to %d): ", numSpecies - 1);
                scanf("%d", &speciesIndex);
                printf("Enter supply index (0 to %d): ", numSuppliesPerSpecies[speciesIndex] - 1);
                scanf("%d", &supplyIndex);
                updateSupply(speciesSupplies, speciesIndex, supplyIndex);
                break;
            }
            case 3: {
                int speciesIndex;
                printf("Enter species index to remove (0 to %d): ", numSpecies - 1);
                scanf("%d", &speciesIndex);
                removeSpecies(speciesSupplies, &numSpecies, numSuppliesPerSpecies, speciesIndex);
                break;
            }
            case 4:
                displayInventory(speciesSupplies, numSpecies, numSuppliesPerSpecies);
                break;
            case 5:
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);
    int i=0;
	int j=0;
    for (; i < numSpecies; i++) {
        for (; j < numSuppliesPerSpecies[i]; j++) {
            free(speciesSupplies[i][j]);
        }
        free(speciesSupplies[i]);
    }
    free(speciesSupplies);
    free(numSuppliesPerSpecies);

    return 0;
}

void initializeInventory(char*** speciesSupplies, int numSpecies) {
	int i=0;
    for (; i < numSpecies; i++) {
        speciesSupplies[i] = NULL;
    }
}

void addSupplies(char*** speciesSupplies, int numSpecies, int* numSuppliesPerSpecies) {
    int speciesIndex;
    printf("Enter species index (0 to %d): ", numSpecies - 1);
    scanf("%d", &speciesIndex);

    if (speciesIndex < 0 || speciesIndex >= numSpecies) {
        printf("Invalid species index!\n");
        return;
    }

    int numSupplies;
    printf("Enter the number of supplies to add: ");
    scanf("%d", &numSupplies);

    speciesSupplies[speciesIndex] = (char**)realloc(speciesSupplies[speciesIndex], (numSuppliesPerSpecies[speciesIndex] + numSupplies) * sizeof(char*));
	int i=0;
    for (; i < numSupplies; i++) {
        char buffer[100];
        printf("Enter supply %d: ", i + 1);
        scanf("%s", buffer);
        speciesSupplies[speciesIndex][numSuppliesPerSpecies[speciesIndex] + i] = strdup(buffer);
    }

    numSuppliesPerSpecies[speciesIndex] += numSupplies;
}

void updateSupply(char*** speciesSupplies, int speciesIndex, int supplyIndex) {
    char buffer[100];
    printf("Enter new name for the supply: ");
    scanf("%s", buffer);

    free(speciesSupplies[speciesIndex][supplyIndex]);
    speciesSupplies[speciesIndex][supplyIndex] = strdup(buffer);
}

void removeSpecies(char*** speciesSupplies, int* numSpecies, int* numSuppliesPerSpecies, int speciesIndex) {
	int i=0;
    for (; i < numSuppliesPerSpecies[speciesIndex]; i++) {
        free(speciesSupplies[speciesIndex][i]);
    }
    free(speciesSupplies[speciesIndex]);
    

    for (; i < *numSpecies - 1; i++) {
        speciesSupplies[i] = speciesSupplies[i + 1];
        numSuppliesPerSpecies[i] = numSuppliesPerSpecies[i + 1];
    }

    (*numSpecies)--;
    speciesSupplies = (char***)realloc(speciesSupplies, (*numSpecies) * sizeof(char**));
    numSuppliesPerSpecies = (int*)realloc(numSuppliesPerSpecies, (*numSpecies) * sizeof(int));
}

void displayInventory(char*** speciesSupplies, int numSpecies, int* numSuppliesPerSpecies) {
    printf("\n--- Inventory ---\n");
    int i=0;
    int j=0;
    for (;i < numSpecies; i++) {
    	int i=0;
        printf("Species %d:\n", i);
        for (; j < numSuppliesPerSpecies[i]; j++) {
            printf("  %s\n", speciesSupplies[i][j]);
        }
    }
}
