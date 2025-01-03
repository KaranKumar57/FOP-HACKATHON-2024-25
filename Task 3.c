#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "playlist_records.txt"

struct Song {
    int songID;
    char title[100];
    char artist[100];
    float duration;
};

void loadPlaylist(struct Song **playlist, int *songCount);
void savePlaylist(struct Song *playlist, int songCount);
void addSong(struct Song **playlist, int *songCount);
void playSong(struct Song *playlist, int songCount);
void displayPlaylist(struct Song *playlist, int songCount);

int getValidInteger(const char *prompt);
float getValidFloat(const char *prompt);
void getValidString(const char *prompt, char *buffer, int size);

int main() {
    struct Song *playlist = NULL;
    int songCount = 0;
    int choice;

    loadPlaylist(&playlist, &songCount);

    do {
        printf("\n--- Music Playlist System ---\n");
        printf("1. Add Song\n");
        printf("2. Play Song\n");
        printf("3. Display Playlist\n");
        printf("4. Exit\n");

        choice = getValidInteger("Enter your choice: ");

        switch (choice) {
            case 1:
                addSong(&playlist, &songCount);
                break;
            case 2:
                playSong(playlist, songCount);
                break;
            case 3:
                displayPlaylist(playlist, songCount);
                break;
            case 4:
                savePlaylist(playlist, songCount);
                printf("Playlist saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    free(playlist);
    return 0;
}

void loadPlaylist(struct Song **playlist, int *songCount) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No existing playlist found. Starting with an empty playlist.\n");
        return;
    }

    struct Song temp;
    while (fscanf(file, "%d,%99[^,],%99[^,],%f\n", &temp.songID, temp.title, temp.artist, &temp.duration) == 4) {
        *playlist = realloc(*playlist, (*songCount + 1) * sizeof(struct Song));
        (*playlist)[*songCount] = temp;
        (*songCount)++;
    }
    fclose(file);
}

void savePlaylist(struct Song *playlist, int songCount) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error opening playlist file for writing.\n");
        return;
    }
    for (int i = 0; i < songCount; i++) {
        fprintf(file, "%d,%s,%s,%.2f\n", playlist[i].songID, playlist[i].title, playlist[i].artist, playlist[i].duration);
    }
    fclose(file);
}

void addSong(struct Song **playlist, int *songCount) {
    *playlist = realloc(*playlist, (*songCount + 1) * sizeof(struct Song));
    if (!*playlist) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    struct Song *newSong = &(*playlist)[*songCount];
    newSong->songID = *songCount + 1;

    getValidString("Enter Song Title: ", newSong->title, sizeof(newSong->title));
    getValidString("Enter Artist Name: ", newSong->artist, sizeof(newSong->artist));
    newSong->duration = getValidFloat("Enter Song Duration (in minutes): ");

    (*songCount)++;
    printf("Song added successfully with ID %d!\n", newSong->songID);
    savePlaylist(*playlist, *songCount);
    printf("Playlist saved to file.\n");
}

void playSong(struct Song *playlist, int songCount) {
    if (songCount == 0) {
        printf("Playlist is empty! Add songs to play.\n");
        return;
    }

    char input[100];
    printf("Enter Song ID, Title, or Artist to play: ");
    getchar(); // Consume leftover newline character
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    int songID = atoi(input);
    int found = 0;

    for (int i = 0; i < songCount; i++) {
        if (playlist[i].songID == songID || 
            strcasecmp(playlist[i].title, input) == 0 || 
            strcasecmp(playlist[i].artist, input) == 0) {
            printf("Playing Song: %s by %s [%.2f minutes]\n", playlist[i].title, playlist[i].artist, playlist[i].duration);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No song matching '%s' found in the playlist.\n", input);
    }
}

void displayPlaylist(struct Song *playlist, int songCount) {
    if (songCount == 0) {
        printf("Playlist is empty! Add songs to display.\n");
        return;
    }

    printf("\n--- Playlist ---\n");
    for (int i = 0; i < songCount; i++) {
        printf("%d. %s by %s [%.2f minutes]\n", playlist[i].songID, playlist[i].title, playlist[i].artist, playlist[i].duration);
    }
}

int getValidInteger(const char *prompt) {
    int value;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &value) == 1) break;
        printf("Invalid input! Please enter a valid integer.\n");
    }
    return value;
}

float getValidFloat(const char *prompt) {
    float value;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%f", &value) == 1 && value > 0) break;
        printf("Invalid input! Please enter a positive number.\n");
    }
    return value;
}

void getValidString(const char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        fgets(buffer, size, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) > 0) break;
        printf("Input cannot be empty. Please try again.\n");
    }
}