NAME: Oscar Franklin 
DATE: 4/24/2024
PROJECT NAME: C Program with Bash Script Modification

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <time.h>

#define MAX_SNAPSHOTS 10

// Structure to store system snapshot
struct SystemSnapshot {
    char datetime[50];
    char hostname[1024];
    char releaseInfo[256];
    char kernelVersion[256];
    int cpuCount;
    long totalMemoryKB;
};

// Global variables
struct SystemSnapshot history[MAX_SNAPSHOTS];
int snapshotCount = 0;

// Function prototypes
void displayDateTime();
void displayHostName();
void displayReleaseInfo();
void displayKernelVersion();
void displayCPUCount();
void displayTotalMemory();
void addSnapshot();
void displayHistory();

// Function to display the current date and time
void displayDateTime() {
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    printf("Current Date and Time: %s", asctime(localTime));
}

// Function to display the system's host name
void displayHostName() {
    char hostName[1024];
    gethostname(hostName, sizeof(hostName));
    printf("Host Name: %s\n", hostName);
}

// Function to display the system's release information
void displayReleaseInfo() {
    struct utsname sysInfo;
    uname(&sysInfo);
    printf("Release Information: %s %s\n", sysInfo.sysname, sysInfo.release);
}

// Function to display the system's kernel version
void displayKernelVersion() {
    struct utsname sysInfo;
    uname(&sysInfo);
    printf("Kernel Version: %s\n", sysInfo.version);
}

// Function to display the number of CPUs or processor cores
void displayCPUCount() {
    printf("Number of CPUs: %d\n", get_nprocs());
}

// Function to display the total system memory (RAM)
void displayTotalMemory() {
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    printf("Total System Memory: %ld KB\n", memInfo.totalram / 1024);
}

// Function to add a system snapshot to the array
void addSnapshot() {
    time_t currentTime;
    struct tm *localTime;
    struct SystemSnapshot snapshot;

    time(&currentTime);
    localTime = localtime(&currentTime);

    // Store snapshot data
    strftime(snapshot.datetime, sizeof(snapshot.datetime), "%Y-%m-%d %H:%M:%S", localTime);
    gethostname(snapshot.hostname, sizeof(snapshot.hostname));
    struct utsname sysInfo;
    uname(&sysInfo);
    sprintf(snapshot.releaseInfo, "%s %s", sysInfo.sysname, sysInfo.release);
    sprintf(snapshot.kernelVersion, "%s", sysInfo.version);
    snapshot.cpuCount = get_nprocs();
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    snapshot.totalMemoryKB = memInfo.totalram / 1024;

    // Add snapshot to history
    if (snapshotCount < MAX_SNAPSHOTS) {
        history[snapshotCount++] = snapshot;
        printf("System snapshot added to history.\n");
    } else {
        printf("History is full. Cannot add more snapshots.\n");
    }
}

// Function to display the historical system snapshots
void displayHistory() {
    printf("Historical System Snapshots:\n");
    for (int i = 0; i < snapshotCount; i++) {
        printf("Snapshot %d:\n", i + 1);
        printf("  Date and Time: %s\n", history[i].datetime);
        printf("  Host Name: %s\n", history[i].hostname);
        printf("  Release Information: %s\n", history[i].releaseInfo);
        printf("  Kernel Version: %s\n", history[i].kernelVersion);
        printf("  Number of CPUs: %d\n", history[i].cpuCount);
        printf("  Total System Memory: %ld KB\n", history[i].totalMemoryKB);
    }
}

// Function to execute system resource monitor bash script
void executeResourceMonitor() {
    system("./resource_monitor.sh");
}

int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Display Date and Time\n");
        printf("2. Display Host Name\n");
        printf("3. Display Release Information\n");
        printf("4. Display Kernel Version\n");
        printf("5. Display CPU/Core Count\n");
        printf("6. Display Total System Memory\n");
        printf("7. Add System Snapshot to History\n");
        printf("8. Display Historical System Snapshots\n");
        printf("9. Execute System Resource Monitor (Bash Script)\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayDateTime();
                break;
            case 2:
                displayHostName();
                break;
            case 3:
                displayReleaseInfo();
                break;
            case 4:
                displayKernelVersion();
                break;
            case 5:
                displayCPUCount();
                break;
            case 6:
                displayTotalMemory();
                break;
            case 7:
                addSnapshot();
                break;
            case 8:
                displayHistory();
                break;
            case 9:
                executeResourceMonitor();
                break;
            case 10:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 10);

    return 0;
}
// Function to modify the refresh rate of the Bash script
void modifyRefreshRate() {
    int refreshRate;

    printf("Enter the refresh rate for the resource monitor (in seconds): ");
    scanf("%d", &refreshRate);

    FILE *bashScript = fopen("resource_monitor.sh", "r+");
    if (bashScript == NULL) {
        printf("Error: Unable to open the Bash script.\n");
        return;
    }

    // Find and replace the refresh rate in the Bash script
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), bashScript) != NULL) {
        if (strstr(buffer, "top -bn")) {
            fseek(bashScript, -strlen(buffer), SEEK_CUR);
            fprintf(bashScript, "top -bn%d", refreshRate);
            break;
        }
    }

    fclose(bashScript);
    printf("Refresh rate modified successfully.\n");
}
