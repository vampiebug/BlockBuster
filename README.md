Team members: Caitlyn & Lily
Last modified: 22/07/2025

1. Which data structure performs faster on the inventory lookups and why?
   The binary tree performs faster for this because it does not have to look through every element of its structure; it can look through subtrees that avoid data (the left/right subtree from the root) it does not have to search through.
2. Report execution times for each data structure required on tests 1, 6, 7, 8, 9.
   Test 1: Singly linked list-6.074e-06 seconds, doubly linked list-2.17678 seconds (linked list test)/0.00257593 seconds (binary tree test), binary tree-2.496e-06 seconds
   Test 6: Singly linked list-2.2566e-05 seconds, doubly linked list-32.2448 seconds (linked list test)/0.0717918 seconds (binary tree test), binary tree-3.271e-06 seconds
   Test 7: Singly linked list-6.391e-06 seconds, doubly linked list-174.156 seconds (linked list test)/1.02296 seconds (binary tree test), binary tree-2.905e-06 seconds
   Test 8: Singly linked list-2.4692e-05 seconds, doubly linked list-1909.34 seconds (linked list)/48.5325 seconds (binary tree test), binary tree-2.024e-06 seconds
   Test 9: Singly linked list-, doubly linked list-, binary tree-2.194e-06 seconds
3. What might be a consequence of making the inventory sorted? If you made the inventory sorted, did you notice any differences?
    Making the inventory sorted will increase the time it takes to perform inventory lookups. Since the inventory elements need to look through the data structure to find the spot where it should go, additional time is required to complete this additonal action. This would add a worst-case scenario big O(n).
4. What Linux command(s) might one use to monitor the performance of a running process, especially to check if its performance is bound by either CPU or I/O?
    The Linux 'time' command is specifically used to determine how long a command takes to run and can be used in this case to test the performance of a running process. A tool that can give the real-time process statistics, including CPU and I/O time is 'htop' command, but looking at the CPU and I/O specifically also has their own tools. The command 'iotop' is a tool that monitors the disk I/O usage in real time by processes, and can be used to test the performance of a running process by viewing its activity in I/O. To view activity in CPU, the 'top' or 'vmstat' commands which will allow viewing of the CPU statistics or the virtual memory statistics, respectively.
