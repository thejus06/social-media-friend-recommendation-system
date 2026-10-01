#include <stdio.h>
#include <string.h>

#define MAX_USERS 50
#define MAX_INTERESTS 5
#define MAX_NAME 50
#define MAX_INTEREST 30
#define MAX_ACTIVITY 100

// ---------------- USER STRUCTURE ----------------

typedef struct {
  char name[MAX_NAME];
  char interests[MAX_INTERESTS][MAX_INTEREST];
  int interestCount;
  char recentActivity[MAX_ACTIVITY];
} User;

// ---------------- GLOBAL VARIABLES ----------------

User users[MAX_USERS];

// Adjacency matrix representing the graph
int graph[MAX_USERS][MAX_USERS];

int userCount = 0;

// ---------------- FUNCTION DECLARATIONS ----------------

void addUser();
void addFriendship();
void viewProfile();
void viewFriends();
void findMutualFriends();
void recommendFriends();
void shortestPath();
void displayNetwork();
void displayAllUsers();

// ======================================================
//                      MAIN FUNCTION
// ======================================================

int main() {

  int choice;

  do {

    printf("\n\n");
    printf("====================================================\n");
    printf("       SOCIAL MEDIA FRIEND RECOMMENDATION SYSTEM\n");
    printf("====================================================\n");

    printf("1.  Add User\n");
    printf("2.  Add Friendship\n");
    printf("3.  View User Profile\n");
    printf("4.  View Friends\n");
    printf("5.  Find Mutual Friends\n");
    printf("6.  Recommend Friends\n");
    printf("7.  Find Shortest Path (BFS)\n");
    printf("8.  Display Social Network\n");
    printf("9.  Display All Users\n");
    printf("10. Exit\n");

    printf("----------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {

    case 1:
      addUser();
      break;

    case 2:
      addFriendship();
      break;

    case 3:
      viewProfile();
      break;

    case 4:
      viewFriends();
      break;

    case 5:
      findMutualFriends();
      break;

    case 6:
      recommendFriends();
      break;

    case 7:
      shortestPath();
      break;

    case 8:
      displayNetwork();
      break;

    case 9:
      displayAllUsers();
      break;

    case 10:
      printf("\nThank you for using the system!\n");
      break;

    default:
      printf("\nInvalid choice! Please try again.\n");
    }

  } while (choice != 10);

  return 0;
}

// ======================================================
//                    ADD USER
// ======================================================

void addUser() {

  if (userCount >= MAX_USERS) {
    printf("\nMaximum user limit reached!\n");
    return;
  }

  printf("\n================ ADD USER ================\n");

  printf("Enter user name: ");
  scanf(" %[^\n]", users[userCount].name);

  printf("Enter number of interests (maximum %d): ", MAX_INTERESTS);

  scanf("%d", &users[userCount].interestCount);

  if (users[userCount].interestCount < 0) {
    users[userCount].interestCount = 0;
  }

  if (users[userCount].interestCount > MAX_INTERESTS) {
    users[userCount].interestCount = MAX_INTERESTS;
  }

  for (int i = 0; i < users[userCount].interestCount; i++) {

    printf("Enter interest %d: ", i + 1);

    scanf(" %[^\n]", users[userCount].interests[i]);
  }

  printf("Enter recent activity: ");

  scanf(" %[^\n]", users[userCount].recentActivity);

  printf("\nUser added successfully!\n");

  printf("User ID: %d\n", userCount);

  userCount++;
}

// ======================================================
//                  ADD FRIENDSHIP
// ======================================================

void addFriendship() {

  int u, v;

  if (userCount < 2) {

    printf("\nAt least two users are required!\n");

    return;
  }

  printf("\n=============== ADD FRIENDSHIP ===============\n");

  displayAllUsers();

  printf("\nEnter first user ID: ");
  scanf("%d", &u);

  printf("Enter second user ID: ");
  scanf("%d", &v);

  if (u < 0 || u >= userCount || v < 0 || v >= userCount) {

    printf("\nInvalid user ID!\n");

    return;
  }

  if (u == v) {

    printf("\nA user cannot be friends with themselves!\n");

    return;
  }

  if (graph[u][v] == 1) {

    printf("\nThese users are already friends!\n");

    return;
  }

  // Undirected graph
  graph[u][v] = 1;
  graph[v][u] = 1;

  printf("\nFriendship added successfully!\n");

  printf("%s <--> %s\n", users[u].name, users[v].name);
}

// ======================================================
//                  VIEW PROFILE
// ======================================================

void viewProfile() {

  int user;

  printf("\n=============== USER PROFILE ===============\n");

  displayAllUsers();

  printf("\nEnter user ID: ");
  scanf("%d", &user);

  if (user < 0 || user >= userCount) {

    printf("\nInvalid user ID!\n");

    return;
  }

  printf("\n---------------------------------------------\n");

  printf("User ID          : %d\n", user);

  printf("Name             : %s\n", users[user].name);

  printf("Interests        :\n");

  if (users[user].interestCount == 0) {

    printf("  No interests added.\n");

  } else {

    for (int i = 0; i < users[user].interestCount; i++) {

      printf("  - %s\n", users[user].interests[i]);
    }
  }

  printf("Recent Activity  : %s\n", users[user].recentActivity);

  printf("---------------------------------------------\n");
}

// ======================================================
//                    VIEW FRIENDS
// ======================================================

void viewFriends() {

  int user;
  int found = 0;

  printf("\n=============== VIEW FRIENDS ===============\n");

  displayAllUsers();

  printf("\nEnter user ID: ");
  scanf("%d", &user);

  if (user < 0 || user >= userCount) {

    printf("\nInvalid user ID!\n");

    return;
  }

  printf("\nFriends of %s:\n", users[user].name);

  printf("---------------------------------------------\n");

  for (int i = 0; i < userCount; i++) {

    if (graph[user][i] == 1) {

      printf("ID: %d   Name: %s\n", i, users[i].name);

      found = 1;
    }
  }

  if (!found) {

    printf("No friends found.\n");
  }
}

// ======================================================
//                 FIND MUTUAL FRIENDS
// ======================================================

void findMutualFriends() {

  int u, v;
  int found = 0;

  printf("\n============= MUTUAL FRIENDS =============\n");

  displayAllUsers();

  printf("\nEnter first user ID: ");
  scanf("%d", &u);

  printf("Enter second user ID: ");
  scanf("%d", &v);

  if (u < 0 || u >= userCount || v < 0 || v >= userCount) {

    printf("\nInvalid user ID!\n");

    return;
  }

  if (u == v) {

    printf("\nPlease select two different users.\n");

    return;
  }

  printf("\nMutual friends of %s and %s:\n", users[u].name, users[v].name);

  printf("---------------------------------------------\n");

  // A mutual friend must be connected to BOTH users
  for (int i = 0; i < userCount; i++) {

    if (graph[u][i] == 1 && graph[v][i] == 1) {

      printf("- %s (ID: %d)\n", users[i].name, i);

      found = 1;
    }
  }

  if (!found) {

    printf("No mutual friends found.\n");
  }
}

// ======================================================
//                 RECOMMEND FRIENDS
// ======================================================

void recommendFriends() {

  int user;

  int mutualCount[MAX_USERS] = {0};

  int found = 0;

  printf("\n============ FRIEND RECOMMENDATIONS ============\n");

  displayAllUsers();

  printf("\nEnter user ID: ");
  scanf("%d", &user);

  if (user < 0 || user >= userCount) {

    printf("\nInvalid user ID!\n");

    return;
  }

  /*
     For every person who is NOT already a friend,
     count how many mutual friends they have.

     Example:

            Bob
           /   \
        Alice  Charlie

     Bob is a mutual friend of Alice and Charlie.
  */

  for (int i = 0; i < userCount; i++) {

    // Do not recommend the user themselves
    if (i == user)
      continue;

    // Do not recommend existing friends
    if (graph[user][i] == 1)
      continue;

    // Count mutual friends
    for (int j = 0; j < userCount; j++) {

      if (graph[user][j] == 1 && graph[i][j] == 1) {

        mutualCount[i]++;
      }
    }
  }

  printf("\nFriend recommendations for %s:\n", users[user].name);

  printf("---------------------------------------------\n");

  /*
     Display users having at least one
     mutual friend.
  */

  for (int i = 0; i < userCount; i++) {

    if (i == user)
      continue;

    if (graph[user][i] == 1)
      continue;

    if (mutualCount[i] > 0) {

      printf("%d. %s\n", i, users[i].name);

      printf("   Mutual friends: %d\n", mutualCount[i]);

      found = 1;
    }
  }

  if (!found) {

    printf("No friend recommendations available.\n");
  }
}

// ======================================================
//               SHORTEST PATH USING BFS
// ======================================================

void shortestPath() {

  int start, destination;

  int queue[MAX_USERS];

  int front = 0;
  int rear = 0;

  int visited[MAX_USERS] = {0};

  int parent[MAX_USERS];

  int distance[MAX_USERS];

  printf("\n============= SHORTEST PATH (BFS) =============\n");

  displayAllUsers();

  printf("\nEnter starting user ID: ");
  scanf("%d", &start);

  printf("Enter destination user ID: ");
  scanf("%d", &destination);

  if (start < 0 || start >= userCount || destination < 0 ||
      destination >= userCount) {

    printf("\nInvalid user ID!\n");

    return;
  }

  if (start == destination) {

    printf("\nBoth users are the same.\n");

    return;
  }

  // Initialize arrays
  for (int i = 0; i < userCount; i++) {

    visited[i] = 0;

    parent[i] = -1;

    distance[i] = -1;
  }

  // Start BFS
  queue[rear++] = start;

  visited[start] = 1;

  distance[start] = 0;

  while (front < rear) {

    int current = queue[front++];

    // Check every possible neighbour
    for (int i = 0; i < userCount; i++) {

      if (graph[current][i] == 1 && visited[i] == 0) {

        visited[i] = 1;

        parent[i] = current;

        distance[i] = distance[current] + 1;

        queue[rear++] = i;
      }
    }
  }

  // Destination cannot be reached
  if (visited[destination] == 0) {

    printf("\nNo path exists between %s and %s.\n", users[start].name,
           users[destination].name);

    return;
  }

  // Reconstruct path
  int path[MAX_USERS];

  int pathLength = 0;

  int current = destination;

  while (current != -1) {

    path[pathLength++] = current;

    current = parent[current];
  }

  printf("\nShortest path:\n");

  for (int i = pathLength - 1; i >= 0; i--) {

    printf("%s", users[path[i]].name);

    if (i != 0)
      printf(" -> ");
  }

  printf("\n");

  printf("Number of connections: %d\n", distance[destination]);
}

// ======================================================
//                DISPLAY SOCIAL NETWORK
// ======================================================

void displayNetwork() {

  printf("\n============== SOCIAL NETWORK ==============\n");

  if (userCount == 0) {

    printf("No users available.\n");

    return;
  }

  for (int i = 0; i < userCount; i++) {

    printf("\n%s (ID: %d)", users[i].name, i);

    printf("\n   Friends: ");

    int found = 0;

    for (int j = 0; j < userCount; j++) {

      if (graph[i][j] == 1) {

        printf("%s", users[j].name);

        found = 1;

        // Formatting
        printf(", ");
      }
    }

    if (!found) {

      printf("No friends");
    }

    printf("\n");
  }
}

// ======================================================
//                DISPLAY ALL USERS
// ======================================================

void displayAllUsers() {

  printf("\nAvailable Users:\n");

  printf("---------------------------------------------\n");

  if (userCount == 0) {

    printf("No users available.\n");

    return;
  }

  for (int i = 0; i < userCount; i++) {

    printf("ID: %-3d Name: %s\n", i, users[i].name);
  }

  printf("---------------------------------------------\n");
}