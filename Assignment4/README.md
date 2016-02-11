

# ASSIGNMENT 4 - C LANG
## KOBOLD

Simple client/server application, with multi threading, written in C.

This serves as a basic starting point to a M.U.D. (Multi User Dungeon)

Once the server is launched, users may connect from the client application.

They provide a name, which is sent to the server to create a new player in
a new thread. Each player has a thread on the server for receiving commands
and acting on them.

For this application, there is the Kobold Protocol.
The Kobold networking protocol is readable names that define short handed
strings for each command or response. They can be found in detail in kobold.h

Once connected, a user can examine the room they are in. This is done by
sending the GET_ROOM command to the server, and the server replies with the
current rooms description.

The only room is the starting room and players have no way of traversing the
the dungeon. While this is short featured as a M.U.D., the server and client
accomplish the task of sending/recieving information, and knowing when to stop,
while giving useful information to the user, making sure to end gracefully,
rather without reason.
