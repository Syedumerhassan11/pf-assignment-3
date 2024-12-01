#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ContentMetadata {
    char* title;
    float rating;
    int runtime;
    char* encodingFormat;
};

struct DevicePreferences {
    int resolution;
    float bandwidthUsage;
    int playbackHistory;
};

struct UserProfile {
    double* engagementScores;
    struct DevicePreferences** devicePreferences;
};

void initializeEngagementMatrix(double*** matrix, int numUsers, int numCategories) {
    *matrix = (double**)malloc(numUsers * sizeof(double*));
    for (int i = 0; i < numUsers; i++) {
        (*matrix)[i] = (double*)malloc(numCategories * sizeof(double));
    }
}

void initializeDeviceMatrix(struct DevicePreferences**** matrix, int numUsers, int numDevices) {
    *matrix = (struct DevicePreferences***)malloc(numUsers * sizeof(struct DevicePreferences**));
    for (int i = 0; i < numUsers; i++) {
        (*matrix)[i] = (struct DevicePreferences**)malloc(numDevices * sizeof(struct DevicePreferences*));
        for (int j = 0; j < numDevices; j++) {
            (*matrix)[i][j] = (struct DevicePreferences*)malloc(sizeof(struct DevicePreferences));
        }
    }
}

void initializeContentMetadataMatrix(struct ContentMetadata**** matrix, int numCategories, int numContent) {
    *matrix = (struct ContentMetadata***)malloc(numCategories * sizeof(struct ContentMetadata**));
    for (int i = 0; i < numCategories; i++) {
        (*matrix)[i] = (struct ContentMetadata**)malloc(numContent * sizeof(struct ContentMetadata*));
        for (int j = 0; j < numContent; j++) {
            (*matrix)[i][j] = (struct ContentMetadata*)malloc(sizeof(struct ContentMetadata));
        }
    }
}

void freeMemory(double** engagementMatrix, struct DevicePreferences*** deviceMatrix, struct ContentMetadata*** contentMetadataMatrix, int numUsers, int numCategories, int numDevices, int numContent) {
    for (int i = 0; i < numUsers; i++) {
        free(engagementMatrix[i]);
    }
    free(engagementMatrix);

    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numDevices; j++) {
            free(deviceMatrix[i][j]);
        }
        free(deviceMatrix[i]);
    }
    free(deviceMatrix);

    for (int i = 0; i < numCategories; i++) {
        for (int j = 0; j < numContent; j++) {
            free(contentMetadataMatrix[i][j]->title); // Free the title string
            free(contentMetadataMatrix[i][j]);
        }
        free(contentMetadataMatrix[i]);
    }
    free(contentMetadataMatrix);
}

void updateEngagementScore(double** engagementMatrix, int userIndex, int categoryIndex, double score) {
    engagementMatrix[userIndex][categoryIndex] = score;
}

void updateDevicePreferences(struct DevicePreferences*** deviceMatrix, int userIndex, int deviceIndex, int resolution, float bandwidthUsage, int playbackHistory) {
    deviceMatrix[userIndex][deviceIndex]->resolution = resolution;
    deviceMatrix[userIndex][deviceIndex]->bandwidthUsage = bandwidthUsage;
    deviceMatrix[userIndex][deviceIndex]->playbackHistory = playbackHistory;
}

void getContentMetadata(struct ContentMetadata*** contentMetadataMatrix, int categoryIndex, int contentIndex) {
    struct ContentMetadata* metadata = contentMetadataMatrix[categoryIndex][contentIndex];
    printf("Title: %s\n", metadata->title);
    printf("Rating: %.1f\n", metadata->rating);
    printf("Runtime: %d minutes\n", metadata->runtime);
    printf("Encoding Format: %s\n", metadata->encodingFormat);
}

int main() {
    int numUsers, numCategories, numDevices, numContent;

    printf("Enter number of users: ");
    scanf("%d", &numUsers);
    while (getchar() != '\n');  // Clear buffer

    printf("Enter number of categories: ");
    scanf("%d", &numCategories);
    while (getchar() != '\n');  // Clear buffer

    printf("Enter number of devices per user: ");
    scanf("%d", &numDevices);
    while (getchar() != '\n');  // Clear buffer

    printf("Enter number of content per category: ");
    scanf("%d", &numContent);
    while (getchar() != '\n');  // Clear buffer

    double** engagementMatrix;
    struct DevicePreferences*** deviceMatrix;
    struct ContentMetadata*** contentMetadataMatrix;

    initializeEngagementMatrix(&engagementMatrix, numUsers, numCategories);
    initializeDeviceMatrix(&deviceMatrix, numUsers, numDevices);
    initializeContentMetadataMatrix(&contentMetadataMatrix, numCategories, numContent);

    updateEngagementScore(engagementMatrix, 0, 1, 9.5);
    updateDevicePreferences(deviceMatrix, 0, 1, 1080, 5.5, 120);

    contentMetadataMatrix[1][2]->title = (char*)malloc(50 * sizeof(char));
    strcpy(contentMetadataMatrix[1][2]->title, "Example Movie");
    contentMetadataMatrix[1][2]->rating = 4.5;
    contentMetadataMatrix[1][2]->runtime = 120;
    contentMetadataMatrix[1][2]->encodingFormat = "HD";

    getContentMetadata(contentMetadataMatrix, 1, 2);

    freeMemory(engagementMatrix, deviceMatrix, contentMetadataMatrix, numUsers, numCategories, numDevices, numContent);

    return 0;
}

