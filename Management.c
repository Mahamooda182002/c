#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <mpg123.h>
#include <ao/ao.h>

#define MAX_SONGS 100
#define MAX_PLAYLISTS 10
#define MAX_SONG_LENGTH 100

// Structure to represent a song
struct Song {
    char title[MAX_SONG_LENGTH];
    char filename[MAX_SONG_LENGTH];
};

// Structure to represent a playlist
struct Playlist {
    char name[MAX_SONG_LENGTH];
    int numSongs;
    struct Song songs[MAX_SONGS];
};

// Function to load all songs from the current directory
int loadSongs(struct Song songs[]) {
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to read directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name) > 4 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".mp3") == 0) {
            strcpy(songs[count].filename, entry->d_name);
            strncpy(songs[count].title, entry->d_name, strlen(entry->d_name) - 4);
            songs[count].title[strlen(entry->d_name) - 4] = '\0';
            count++;
        }
    }

    closedir(dir);
    return count;
}

// Function to play a song
void playSong(const char *filename) {
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;
    int driver;
    ao_device *dev;

    ao_initialize();
    driver = ao_default_driver_id();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));

    mpg123_open(mh, filename);
    dev = ao_open_live(driver, &mpg123_fmt(mh)->rate, MPG123_MONO, MPG123_ENC_SIGNED_16, 0);

    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
        ao_play(dev, buffer, done);
    }

    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}

int main() {
    struct Song songs[MAX_SONGS];
    int numSongs = loadSongs(songs);

    printf("Welcome to the Music Player with Playlist Management!\n");

    // Create playlists
    struct Playlist playlists[MAX_PLAYLISTS];
    int numPlaylists = 0;

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Play a Song\n");
        printf("2. Create a Playlist\n");
        printf("3. View Playlists\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (numSongs == 0) {
                    printf("No songs found in the current directory.\n");
                } else {
                    printf("Available Songs:\n");
                    for (int i = 0; i < numSongs; i++) {
                        printf("%d. %s\n", i + 1, songs[i].title);
                    }

                    int songChoice;
                    printf("Enter the number of the song you want to play: ");
                    scanf("%d", &songChoice);

                    if (songChoice >= 1 && songChoice <= numSongs) {
                        playSong(songs[songChoice - 1].filename);
                    } else {
                        printf("Invalid song choice.\n");
                    }
                }
                break;

            case 2:
                if (numPlaylists < MAX_PLAYLISTS) {
                    printf("Enter the name of the new playlist: ");
                    scanf("%s", playlists[numPlaylists].name);
                    playlists[numPlaylists].numSongs = 0;

                    printf("Select songs to add to the playlist (Enter song number, 0 to finish):\n");
                    for (int i = 0; i < numSongs; i++) {
                        printf("%d. %s\n", i + 1, songs[i].title);
                    }

                    int songChoice;
                    while (1) {
                        scanf("%d", &songChoice);
                        if (songChoice >= 1 && songChoice <= numSongs) {
                            playlists[numPlaylists].songs[playlists[numPlaylists].numSongs++] = songs[songChoice - 1];
                        } else if (songChoice == 0)

