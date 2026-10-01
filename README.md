# Social Media Friend Recommendation System

A console-based Social Media Friend Recommendation System developed in C using
Data Structures and Algorithms.

The project represents users as vertices in a graph and friendships as edges.
It provides friend recommendations based on mutual friends and uses Breadth
First Search (BFS) to find the shortest connection path between users.

---

## 📌 Features

- Add new users
- Store user profile information
- Add friendships between users
- View user profiles
- View a user's friends
- Find mutual friends
- Recommend friends based on mutual connections
- Find the shortest path between two users using BFS
- Display the complete social network
- Display all registered users

---

## 🧠 Data Structures Used

### 1. Structure

A `struct` is used to store user information.

Each user contains:

- Name
- Interests
- Recent activity

### 2. Arrays

Arrays are used to store:

- User information
- User interests
- BFS queue
- Visited nodes
- Parent nodes
- Distance values

### 3. Graph

The social network is represented using an **Adjacency Matrix**.

If two users are friends:

```text
graph[u][v] = 1
graph[v][u] = 1